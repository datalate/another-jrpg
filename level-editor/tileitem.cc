#include "tileitem.hh"
#include "common.hh"

TileItem::TileItem(unsigned int x, unsigned int y, int id, QObject* parent) :
    QObject{parent}, QGraphicsPixmapItem{},
    x_{x}, y_{y}, id_{id}, highlight_{false} {

    setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
    setAcceptedMouseButtons(Qt::LeftButton);
}

void TileItem::setHighlight(bool highlight) {
    highlight_ = highlight;
    update();
}

void TileItem::setTileId(int id) {
    id_ = id;
}

void TileItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);

    emit clicked(this);
}

void TileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);

    if (highlight_) {
        const QRectF& r{boundingRect()};
        painter->setPen(Qt::white);
        painter->drawRect(QRect(r.x(), r.y(), r.width()-painter->pen().width(), r.height()-painter->pen().width()));
    }
}
