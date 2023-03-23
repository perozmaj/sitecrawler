#include "SiteCrawlerModel.h"
#include "SiteCrawler.h"
SiteCrawlerModel::SiteCrawlerModel(QObject* parent) :
    QStandardItemModel(parent)
{

}

QHash<int, QByteArray> SiteCrawlerModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[Roles::LinkRole] = "link";
    roleNames[Roles::DataRole] = "data";
    return roleNames;
}

void SiteCrawlerModel::crawlClicked(const QString& url)
{
    m_isCrawling = true;
    emit isCrawlingChanged();
    auto* siteCrawler = new SiteCrawler(url, this);
    connect(siteCrawler, &SiteCrawler::linkVisited, this, &SiteCrawlerModel::linkVisited);
    connect(siteCrawler, &SiteCrawler::finished, this, &SiteCrawlerModel::crawlFinished);
    connect(siteCrawler, &SiteCrawler::finished, siteCrawler, &QObject::deleteLater);
}

void SiteCrawlerModel::linkVisited(const QString& link, const QString& data)
{
    auto* pItem = new QStandardItem();
    pItem->setData(link, Roles::LinkRole);
    pItem->setData(data, Roles::DataRole);
    appendRow(pItem);
}

void SiteCrawlerModel::crawlFinished()
{
    m_isCrawling = false;
    emit isCrawlingChanged();
}

bool SiteCrawlerModel::getIsCrawling() const
{
    return m_isCrawling;
}
