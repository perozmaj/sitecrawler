#include "SiteCrawlerModel.h"
#include "SiteCrawler.h"
#include <iostream>
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
    std::cout << "Received url " << url.toStdString() << std::endl;
    auto* siteCrawler = new SiteCrawler(url);
    connect(siteCrawler, &SiteCrawler::linkVisited, this, &SiteCrawlerModel::siteVisited);
    connect(siteCrawler, &SiteCrawler::finished, this, &SiteCrawlerModel::crawlFinished);
    //handle deletion on finished
}

void SiteCrawlerModel::siteVisited(const QString& link, const QString& data)
{
    auto* pItem = new QStandardItem();
    pItem->setData(link, Roles::LinkRole);
    pItem->setData(data, Roles::DataRole);
    appendRow(pItem);
}

void SiteCrawlerModel::crawlFinished()
{

}
