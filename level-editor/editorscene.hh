#ifndef EDITORSCENE_HH
#define EDITORSCENE_HH

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include "tileitem.hh"

class EditorScene : public QGraphicsScene {
    Q_OBJECT
public:
    EditorScene(unsigned int width, unsigned int height);

    void createNew(unsigned int width, unsigned int height);

    bool tileExists(unsigned int x, unsigned int y) const;
    TileItem* tileAt(unsigned int x, unsigned int y) const; // throws exception if not valid

signals:
    void tileClicked(TileItem*);

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
    void clear();

    std::vector<TileItem*> tiles_; // no ownership
    unsigned int width_;
    unsigned int height_;
};

#endif // GRIDSCENE_HH
