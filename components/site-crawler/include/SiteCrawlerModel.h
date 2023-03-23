#pragma once

#include <QStandardItemModel>

class SiteCrawlerModel : public QStandardItemModel
{
    Q_OBJECT
    Q_PROPERTY(bool isCrawling READ getIsCrawling NOTIFY isCrawlingChanged)
public:
    enum Roles
    {
        LinkRole = Qt::UserRole + 1,
        DataRole
    };
    SiteCrawlerModel(QObject* parent = nullptr);
    [[nodiscard]] QHash<int,QByteArray> roleNames() const override;
    [[nodiscard]] bool getIsCrawling() const;

signals:
    void isCrawlingChanged();
public slots:
    void crawlClicked(const QString & url);
    void linkVisited(const QString& link, const QString& data);
    void crawlFinished();
private:
    bool m_isCrawling = false;
};
