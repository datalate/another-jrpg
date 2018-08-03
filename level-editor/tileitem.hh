#ifndef TILEITEM_HH
#define TILEITEM_HH

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>

class TileItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    TileItem(unsigned int x, unsigned int y, int id, QObject* parent = nullptr);

    void setHighlight(bool highlight);
    void setTileId(int id);
    void setTilePosition(QPoint pos);

    unsigned int tileX() const { return x_; }
    unsigned int tileY() const { return y_; }
    int tileId() const { return id_; }

signals:
    void clicked(TileItem*);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    unsigned int x_;
    unsigned int y_;
    int id_;

    bool highlight_;
};

#endif // TILEITEM_HH
