#ifndef TILESELECTORSCENE_HH
#define TILESELECTORSCENE_HH

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <unordered_map>
#include <vector>
#include "tileitem.hh"
#include "../src/types.hh"

class TileSelectorScene : public QGraphicsScene {
    Q_OBJECT

public:
    TileSelectorScene();

    void setTileSet(const std::unordered_map<unsigned int, Level::TileInfo>& tileSet);

public slots:
    void rePositionItems(const QSize& oldSize, const QSize& size);

signals:
    void tileSelected(TileItem*);

private slots:
    void onTileClicked(TileItem* tile);

private:
    std::vector<TileItem*> tileSet_; // no ownership
};

#endif // TILESELECTORSCENE_HH
