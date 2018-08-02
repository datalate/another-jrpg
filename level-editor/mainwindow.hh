#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "editorscene.hh"
#include "tileselectorscene.hh"
#include "../src/tilemanager.hh"
#include "tileitem.hh"

namespace Ui {
    class MainWindow;
}

extern const unsigned int EDITOR_WIDTH;
extern const unsigned int EDITOR_HEIGHT;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void fileNew();
    void updateTile(TileItem* tile);
    void setActiveTile(TileItem* tile);

private:
    Ui::MainWindow* ui;
    EditorScene editor_;
    TileSelectorScene tileSelector_;
    Level::TileManager tiles_;
    TileItem* activeTile_;
};

#endif // MAINWINDOW_HH
