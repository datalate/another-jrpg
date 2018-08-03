#include "tileselectorscene.hh"
#include <QDebug>
#include "common.hh"

using Level::TileInfo;

TileSelectorScene::TileSelectorScene() {
    setBackgroundBrush(QBrush(QColor(Qt::darkGray)));
}

void TileSelectorScene::setTileSet(const std::unordered_map<unsigned int, TileInfo>& tileSet) {
    unsigned int x{0};
    unsigned int y{0};

    for (auto const& tileInfo: tileSet) {
        auto const& info{tileInfo.second};

        TileItem* tile{new TileItem(x, y, info.id)};
        qDebug() << QString::fromStdString(info.texture) << x << y;

        // TODO: image/pixmap manager to reduce number of copies
        const QImage img{"../img/" + QString::fromStdString(info.texture) + ".png"};
        tile->setPixmap(QPixmap::fromImage(img));
        addItem(tile); // transfer ownership

        bool success{connect(tile, &TileItem::clicked, this, &TileSelectorScene::onTileClicked)};
        Q_ASSERT(success);

        tileSet_.push_back(tile);
        x += 1;
    }

    //setSceneRect(0, 0, 2 * 32, 2 * 32);
    emit tileSelected(tileSet_.front()); // Default tile
}

void TileSelectorScene::rePositionItems(const QSize& oldSize, const QSize& size) {
    Q_UNUSED(oldSize);

    const int width{size.width() / (int)TILE_WIDTH};

    int x{0};
    int y{0};
    for (auto const& tile: tileSet_) {
        tile->setTilePosition({x, y});

        ++x;
        if (x == width) {
            x -= width;
            ++y;
        }
    }

    setSceneRect(0, 0, width * TILE_WIDTH, y * TILE_HEIGHT);
}

void TileSelectorScene::onTileClicked(TileItem* tile) {
    emit tileSelected(tile);
}
