#ifndef TILESELECTORVIEW_HH
#define TILESELECTORVIEW_HH

#include <QGraphicsView>
#include <QResizeEvent>

class TileSelectorView : public QGraphicsView {
    Q_OBJECT

public:
    TileSelectorView(QWidget* parent = nullptr);

signals:
    void sizeChanged(const QSize& oldSize, const QSize& size);

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // TILESELECTORVIEW_HH
