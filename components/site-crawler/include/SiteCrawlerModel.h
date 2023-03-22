#pragma once

#include <QStandardItemModel>

class SiteCrawlerModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum Roles
    {
        LinkRole = Qt::UserRole + 1,
        DataRole
    };
    SiteCrawlerModel(QObject* parent = nullptr);
    virtual QHash<int,QByteArray> roleNames() const override;

public slots:
    void crawlClicked(const QString & url);
    void siteVisited(const QString& link, const QString& data);
    void crawlFinished();
};
