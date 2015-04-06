#include "traktmovies.h"

#include "traktrequest.h"

TraktMovies::TraktMovies(QObject *parent) :
    QObject(parent)
{
}

TraktMoviesModel *TraktMovies::popular()
{
    TraktRequest *request = new TraktRequest(this);
    request->setPath("/movies/popular");
    request->addQueryItem("extended", "images");

    return new TraktMoviesModel(request, this);
}

TraktMoviesModel *TraktMovies::trending()
{
    TraktRequest *request = new TraktRequest(this);
    request->setPath("/movies/trending");
    request->addQueryItem("extended", "images");

    return new TraktMoviesModel(request, this);
}