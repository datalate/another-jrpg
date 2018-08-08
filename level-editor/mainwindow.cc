#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "editorscene.hh"
#include <QDebug>
#include <QAction>
#include <QFileDialog>
#include <QString>
#include "yaml-cpp/yaml.h"

const unsigned int DEFAULT_EDITOR_WIDTH{25};
const unsigned int DEFAULT_EDITOR_HEIGHT{20};

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), editor_{DEFAULT_EDITOR_WIDTH, DEFAULT_EDITOR_HEIGHT}, activeTile_{nullptr} {

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
    success = connect(ui->graphicsViewTiles, &TileSelectorView::sizeChanged, &tileSelector_, &TileSelectorScene::rePositionItems);
    Q_ASSERT(success);

    tiles_.loadTileConfig("../cfg/tiles.yml");
    tileSelector_.setTileSet(tiles_.tileTypes());

    success = connect(ui->actionNew, &QAction::triggered, this, &MainWindow::fileNew);
    Q_ASSERT(success);
    success = connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    Q_ASSERT(success);
    success = connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    Q_ASSERT(success);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fileNew() {
    editor_.createNew(DEFAULT_EDITOR_WIDTH, DEFAULT_EDITOR_HEIGHT);
}

void MainWindow::open() {
    const QString filePath{QFileDialog::getOpenFileName(this, "Open", QString(), "*.yml")};
    QString errorMsg;
    bool ok{true};
    YAML::Node node;

    if (!YamlParser::loadFile(filePath.toStdString(), node)) {
        errorMsg = "Failed to open/parse file";
        ok = false;
    }
    else {
        std::string name;
        unsigned int width{0};
        unsigned int height{0};
        std::vector<unsigned int> tileData;

        YamlParser::parse<std::string>(node["name"], name);
        YamlParser::parse<unsigned int>(node["width"], width);
        YamlParser::parse<unsigned int>(node["height"], height);
        YamlParser::parse<std::vector<unsigned int>>(node["tiles"], tileData);

        if (name.empty() || width == 0 || height == 0 || tileData.empty()) {
            errorMsg = "Key attributes missing";
            ok = false;
        }
        else if (tileData.size() != width * height) {
            errorMsg = "Incorrect number of tiles";
            ok = false;
        }
        else {
            std::vector<TileItem*> tiles;
            unsigned int x{0};
            unsigned int y{0};
            for (const auto& tile : tileData) {
                tiles.push_back(new TileItem(x, y, tile, this));
                ++x;

                if (x == width) {
                    x -= width;
                    ++y;
                }
            }
        }

        if (!ok) {
            ui->statusBar->showMessage(tr("Failed to open level '%1': %2").arg(filePath).arg(errorMsg));
        }
        else {
            ui->statusBar->showMessage(tr("Opened file '%1'").arg(filePath));
        }
    }
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
