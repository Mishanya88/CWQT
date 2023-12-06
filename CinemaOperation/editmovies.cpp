#include "editmovies.h"

EditMovies::EditMovies(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant EditMovies::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex EditMovies::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex EditMovies::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int EditMovies::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int EditMovies::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant EditMovies::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
