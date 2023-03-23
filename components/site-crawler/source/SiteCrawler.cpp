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
    QString stringXmlData = data.data();
    emit linkVisited(QString::fromStdString(m_currentUrl), stringXmlData);
    findLinksAndAddToQueue(stringXmlData);
    emit triggerTakeNext();
}

void SiteCrawler::networkReplyError(QNetworkReply::NetworkError error)
{
    auto* reply = static_cast<QNetworkReply*>(sender());
    reply->deleteLater();
    if (error == QNetworkReply::UnknownServerError)
    {
        emit triggerTakeNext();
    }
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

void SiteCrawler::findLinksAndAddToQueue(const QString& data)
{
    QRegularExpression regularExpression(m_regularExpressionString);
    auto regIterator = regularExpression.globalMatch(data);
    while(regIterator.hasNext())
    {
        QRegularExpressionMatch match = regIterator.next();
        if (match.hasMatch())
        {
            auto url = match.captured(1).toStdString();
            std::string endUrl;
            if (url.find("https://") == std::string::npos ) //it has relative path
            {
                auto index = m_currentUrl.find_last_of('/');
                endUrl = m_currentUrl.substr(0, index+1) + url;
            }
            else
            {
                endUrl = url;
            }
            auto find = std::find(m_visitedUrls.begin(), m_visitedUrls.end(), endUrl);
            if (find == m_visitedUrls.end())
            {
                m_queue.push(endUrl);
                m_visitedUrls.emplace_back(endUrl);
            }
        }
    }
}
