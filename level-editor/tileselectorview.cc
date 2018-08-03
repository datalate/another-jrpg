#include "tileselectorview.hh"
#include <QDebug>

TileSelectorView::TileSelectorView(QWidget *parent) :
    QGraphicsView{parent} {


}

void TileSelectorView::resizeEvent(QResizeEvent *event) {
    emit sizeChanged(event->oldSize(), event->size());
    QGraphicsView::resizeEvent(event);
}
