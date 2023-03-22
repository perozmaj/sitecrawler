#pragma once

#include "QtNetwork/qnetworkaccessmanager.h"
#include <queue>
#include <QObject>
#include <QXmlStreamReader>
#include <QtNetwork/QNetworkReply>
class SiteCrawler : public QObject
{
    Q_OBJECT
public:
    SiteCrawler(const QString& url,
                 QObject* parent = nullptr);
signals:
    void triggerTakeNext();
    void linkVisited(const QString& link, const QString& data);
    void finished();
private slots:
    void networkReplyFinished();
    void networkReplyError(QNetworkReply::NetworkError error);
    void takeNext();
private:
    std::queue<std::string> m_queue;
    QXmlStreamReader m_streamReader;
    QNetworkAccessManager m_networkAccessManager;
    std::string m_currentUrl;
    std::vector<std::string> m_visitedUrls;
};
