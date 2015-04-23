#include "traktseasonsmodel.h"

#include "traktshow.h"

TraktSeasonsModel::TraktSeasonsModel(TraktShow *show, QObject *parent) :
    TraktModel(buildRequest(show), parent),
    m_show(show)
{
}

TraktRequest *TraktSeasonsModel::buildRequest(TraktShow *show)
{
    TraktRequest *request = new TraktRequest();
    request->setPath(QString("/shows/%1/seasons").arg(show->ids()->trakt()));
    request->addQueryItem("extended", "images");

    return request;
}

QVariant TraktSeasonsModel::data(const QModelIndex &index, int role) const
{
    TraktSeason *season = at(index.row());

    if (!season) {
        return QVariant();
    }

    switch (role) {
    case RoleNumber:
        return season->number();
    case RoleIds:
    {
        QVariant var;
        var.setValue(season->ids());
        return var;
    }
    case RoleRating:
        return season->rating();
    case RoleVotes:
        return season->votes();
    case RoleEpisodeCount:
        return season->episodeCount();
    case RoleAiredEpisodes:
        return season->airedEpisodes();
    case RoleImages:
    {
        QVariant var;
        var.setValue(season->images());
        return var;
    }
    }

    return QVariant();
}

QHash<int, QByteArray> TraktSeasonsModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames.insert(RoleIds, "ids");
    roleNames.insert(RoleNumber, "number");
    roleNames.insert(RoleRating, "rating");
    roleNames.insert(RoleVotes, "votes");
    roleNames.insert(RoleEpisodeCount, "episodeCount");
    roleNames.insert(RoleAiredEpisodes, "airedEpisodes");
    roleNames.insert(RoleImages, "images");
    return roleNames;
}

TraktSeason *TraktSeasonsModel::convertItem(const QVariantMap &item)
{
    return new TraktSeason(item, m_show);
}

TraktSeason *TraktSeasonsModel::at(int i) const
{
    return TraktModel::at(i);
}