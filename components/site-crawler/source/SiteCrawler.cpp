#include "SiteCrawler.h"
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QRegularExpression>
#include <iostream>
SiteCrawler::SiteCrawler(const QString& url, QObject* parent):
    QObject(parent),
    m_networkAccessManager(this),
    m_currentUrl(url.toStdString())
{
    QNetworkRequest request;
    request.setUrl(QUrl((url)));
    auto* reply = m_networkAccessManager.get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(networkReplyFinished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkReplyError(QNetworkReply::NetworkError)));
    connect(this, &SiteCrawler::triggerTakeNext, this, &SiteCrawler::takeNext);
}

void SiteCrawler::networkReplyFinished()
{
    auto* reply = static_cast<QNetworkReply*>(sender());
    auto data = reply->readAll();
    QString stringData = data.data();
    emit linkVisited(QString::fromStdString(m_currentUrl), stringData);
    QRegularExpression re("<a\\s+(?:[^>]*?\\s+)?href=\"([^\"]*)\"");
    //QRegularExpression re("href=['\"](?<url>.*?)['\"]");
    auto i = re.globalMatch(stringData);
    while(i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            auto url = match.captured(1).toStdString();
            if (url.find("https://") == std::string::npos ) //it has relative path
            {
                auto index = m_currentUrl.find_last_of('/');
                url = m_currentUrl.substr(0, index+1) + url;
            }
            auto find = std::find(m_visitedUrls.begin(), m_visitedUrls.end(), url);
            if (find == m_visitedUrls.end())
            {
                m_queue.push(url);
                m_visitedUrls.emplace_back(url);
            }

        }
    }
    emit triggerTakeNext();
}

void SiteCrawler::networkReplyError(QNetworkReply::NetworkError error)
{
    auto* reply = static_cast<QNetworkReply*>(sender());
    reply->deleteLater();
    std::cout << "Error string"  << m_currentUrl << std::endl;
        emit triggerTakeNext();
}

void SiteCrawler::takeNext()
{
    if(m_queue.empty())
    {
        emit finished();
        return;
    }
    m_currentUrl = m_queue.front();
    m_queue.pop();

    QNetworkRequest request;
    request.setUrl(QUrl((QString::fromStdString(m_currentUrl))));
    auto* reply = m_networkAccessManager.get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(networkReplyFinished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkReplyError(QNetworkReply::NetworkError)));


}
