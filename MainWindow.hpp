#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QColor>
class QGraphicsScene;
class Cell;

namespace Ui {
class MainWindow;
}

class QGraphicsSimpleTextItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Cell *m_cells[9][9];
    int check();
    void color1(int i);


protected slots:
    void onCellClicked(Cell *cell);
//    void onFieldStateChanged();

private:
    QGraphicsScene *m_scene;
    Ui::MainWindow *ui;
    QColor *m_color;
//    QGraphicsSimpleTextItem *m_gameStateText;


};

#endif // MAINWINDOW_HPP
