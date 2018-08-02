#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "editorscene.hh"
#include <QDebug>
#include <QAction>

const unsigned int EDITOR_WIDTH{25};
const unsigned int EDITOR_HEIGHT{20};

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), editor_{EDITOR_WIDTH, EDITOR_HEIGHT}, activeTile_{nullptr} {

    ui->setupUi(this);

    ui->graphicsViewEditor->setScene(&editor_);
    //ui->graphicsViewEditor->setFixedSize(820, 660);
    ui->graphicsViewEditor->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    ui->graphicsViewTiles->setScene(&tileSelector_);
    //ui->graphicsViewTiles->setFixedSize(200, 660);
    ui->graphicsViewTiles->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    //setFixedSize(1060, 720);

    bool success{connect(&editor_, &EditorScene::tileClicked, this, &MainWindow::updateTile)};
    Q_ASSERT(success);
    success = connect(&tileSelector_, &TileSelectorScene::tileSelected, this, &MainWindow::setActiveTile);
    Q_ASSERT(success);

    tiles_.loadTileConfig("../cfg/tiles.yml");
    tileSelector_.setTileSet(tiles_.tileTypes());

    success = connect(ui->actionNew, &QAction::triggered, this, &MainWindow::fileNew);
    Q_ASSERT(success);
    success = connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    Q_ASSERT(success);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fileNew() {
    editor_.createNew(EDITOR_WIDTH, EDITOR_HEIGHT);
}

void MainWindow::updateTile(TileItem *tile) {
    if (activeTile_ != nullptr) {
        tile->setPixmap(activeTile_->pixmap());
        tile->setTileId(activeTile_->tileId());
        ui->statusBar->showMessage(tr("Placed tile in (%1, %2)").arg(tile->tileX()).arg(tile->tileY()));
    }
}

void MainWindow::setActiveTile(TileItem *tile) {
    if (activeTile_) {
        // Set previous tile inactive
        activeTile_->setHighlight(false);
    }

    ui->statusBar->showMessage(tr("Selected tile id: %1").arg(tile->tileId()));
    activeTile_ = tile;
    tile->setHighlight(true);
}
