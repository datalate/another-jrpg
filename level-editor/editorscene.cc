#include "editorscene.hh"
#include <QDebug>
#include "common.hh"

EditorScene::EditorScene(unsigned int width, unsigned int height) :
    QGraphicsScene{},
    width_{width}, height_{height} {

    setSceneRect(0, 0, width * TILE_WIDTH, height * TILE_HEIGHT);
    setBackgroundBrush(QBrush(QColor(Qt::darkGray)));

    for (unsigned int y{0}; y < height; ++y) {
        for (unsigned int x{0}; x < width; ++x) {
            TileItem* tile{new TileItem(x, y, -1)};
            addItem(tile); // transfer ownership
            tiles_.push_back(tile);
        }
    }
}

void EditorScene::createNew(unsigned int width, unsigned int height) {
    width_ = width;
    height_ = height;

    setSceneRect(0, 0, width * TILE_WIDTH, height * TILE_HEIGHT);
    clear();

    for (unsigned int y{0}; y < height; ++y) {
        for (unsigned int x{0}; x < width; ++x) {
            TileItem* tile{new TileItem(x, y, -1)};
            addItem(tile); // transfer ownership
            tiles_.push_back(tile);
        }
    }
}

void EditorScene::clear() {
    while (!items().empty()) {
        QGraphicsItem* item{items().back()};
        removeItem(item);
        delete item;
    }

    tiles_.clear();
}

bool EditorScene::tileExists(unsigned int x, unsigned int y) const {
    return x < width_ && y < height_;
}

TileItem* EditorScene::tileAt(unsigned int x, unsigned int y) const {
    return tiles_.at(y * width_ + x);
}

void EditorScene::drawBackground(QPainter* painter, const QRectF& rect) {
    painter->fillRect(rect, backgroundBrush());

    painter->setBrush(Qt::white);
    painter->drawRect(sceneRect());

    const qreal left{0};
    const qreal top{0};

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x <= sceneRect().right(); x += TILE_WIDTH) {
        lines.append(QLineF(x, sceneRect().top(), x, sceneRect().bottom()));
    }
    for (qreal y = top; y <= sceneRect().bottom(); y += TILE_HEIGHT) {
        lines.append(QLineF(sceneRect().left(), y, sceneRect().right(), y));
    }

    painter->setPen(backgroundBrush().color());
    painter->drawLines(lines.data(), lines.size());
}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    const int x{(int)(mouseEvent->scenePos().x() / 32)};
    const int y{(int)(mouseEvent->scenePos().y() / 32)};

    if (mouseEvent->button() == Qt::LeftButton && tileExists(x, y)) {
        TileItem* tile{tileAt(x, y)};

        if (tile != nullptr) {
            emit tileClicked(tile);
        }
    }
}
