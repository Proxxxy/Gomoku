#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QGraphicsScene>
#include <Qcolor>
#include "Cell.hpp"
#include <iostream>
#include <windows.h>
#include <QDebug>


const int cellSize = 32;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_scene = new QGraphicsScene();

    ui->setupUi(this);
    ui->graphicsView->setScene(m_scene);
    for (int j=0; j<9; j++) {
        for(int i=0; i<9; i++) {
            m_cells[j][i] = new Cell();
            m_scene->addItem(m_cells[j][i]);
            m_cells[j][i]->setPos(i*50,j*50);
            connect(m_cells[j][i], SIGNAL(clicked(Cell*)), this, SLOT(onCellClicked(Cell*)));
            m_cells[j][i]->setState(Cell::Statenothing);
        }
    }
    m_scene->update();

}

//int MainWindow::check()
//{
//    for (int i=1; i < 3; i++)
//        if ((m_cells[0]->state() == Cell::State(i) and m_cells[0]->state() == m_cells[1]->state() and m_cells[1]->state() == m_cells[2]->state()) ||
//            (m_cells[0]->state() == Cell::State(i) and m_cells[0]->state() == m_cells[4]->state() and m_cells[4]->state() == m_cells[8]->state()) ||
//            (m_cells[0]->state() == Cell::State(i) and m_cells[0]->state() == m_cells[3]->state() and m_cells[3]->state() == m_cells[6]->state()) ||
//            (m_cells[6]->state() == Cell::State(i) and m_cells[6]->state() == m_cells[7]->state() and m_cells[7]->state() == m_cells[8]->state()) ||
//            (m_cells[2]->state() == Cell::State(i) and m_cells[2]->state() == m_cells[5]->state() and m_cells[5]->state() == m_cells[8]->state()) ||
//            (m_cells[2]->state() == Cell::State(i) and m_cells[2]->state() == m_cells[4]->state() and m_cells[4]->state() == m_cells[6]->state()) ||
//            (m_cells[1]->state() == Cell::State(i) and m_cells[1]->state() == m_cells[4]->state() and m_cells[4]->state() == m_cells[6]->state()) ||
//            (m_cells[3]->state() == Cell::State(i) and m_cells[3]->state() == m_cells[4]->state() and m_cells[4]->state() == m_cells[5]->state()) )
//            return i;

//}

//void MainWindow::color1(int i)
//{
//    if (m_cells[0]->state() == m_cells[1]->state() and m_cells[1]->state() == m_cells[2]->state()){
//        m_cells[0]->setState(Cell::State(i));
//        m_cells[1]->setState(Cell::State(i));
//        m_cells[2]->setState(Cell::State(i));
//    }
//    if (m_cells[0]->state() == m_cells[4]->state() and m_cells[4]->state() == m_cells[8]->state()){
//        m_cells[0]->setState(Cell::State(i));
//        m_cells[4]->setState(Cell::State(i));
//        m_cells[8]->setState(Cell::State(i));
//    }
//    if (m_cells[0]->state() == m_cells[3]->state() and m_cells[3]->state() == m_cells[6]->state()){
//        m_cells[0]->setState(Cell::State(i));
//        m_cells[3]->setState(Cell::State(i));
//        m_cells[6]->setState(Cell::State(i));
//    }
//    if (m_cells[6]->state() == m_cells[7]->state() and m_cells[7]->state() == m_cells[8]->state()){
//        m_cells[6]->setState(Cell::State(i));
//        m_cells[7]->setState(Cell::State(i));
//        m_cells[8]->setState(Cell::State(i));
//    }
//    if (m_cells[2]->state() == m_cells[5]->state() and m_cells[5]->state() == m_cells[8]->state()){
//        m_cells[2]->setState(Cell::State(i));
//        m_cells[5]->setState(Cell::State(i));
//        m_cells[8]->setState(Cell::State(i));
//    }
//    if (m_cells[2]->state() == m_cells[4]->state() and m_cells[4]->state() == m_cells[6]->state()){
//        m_cells[2]->setState(Cell::State(i));
//        m_cells[4]->setState(Cell::State(i));
//        m_cells[6]->setState(Cell::State(i));
//    }
//    if (m_cells[1]->state() == m_cells[4]->state() and m_cells[4]->state() == m_cells[6]->state()){
//        m_cells[1]->setState(Cell::State(i));
//        m_cells[4]->setState(Cell::State(i));
//        m_cells[6]->setState(Cell::State(i));
//    }
//    if (m_cells[3]->state() == m_cells[4]->state() and m_cells[4]->state() == m_cells[5]->state()){
//        m_cells[3]->setState(Cell::State(i));
//        m_cells[4]->setState(Cell::State(i));
//        m_cells[5]->setState(Cell::State(i));
//    }
//}

int MainWindow::check(){
    for (int j=0; j<9; j++){
        for (int i=0; i<9; i++){
            if (m_cells[j][i]->state()!=Cell::Statenothing){
                if (m_cells[j][i]->state() == m_cells[j+1][i]->state() and m_cells[j+1][i]->state() == m_cells[j+2][i]->state() and m_cells[j+1][i]->state() == m_cells[j+3][i]->state()){
                    return 1;
                }
                if (m_cells[j][i]->state() == m_cells[j][i+1]->state() and m_cells[j][i+1]->state() == m_cells[j][i+2]->state() and m_cells[j][i+1]->state() == m_cells[j][i+3]->state()){
                    return 1;
                }
                if (m_cells[j][i]->state() == m_cells[j+1][i+1]->state() and m_cells[j+1][i+1]->state() == m_cells[j+2][i+2]->state() and m_cells[j+1][i+1]->state() == m_cells[j+3][i+3]->state()){
                    return 1;
                }
            }
        }
    }
}
//void MainWindow::onFieldStateChanged()
//{
//    if (check()==2 || check()==1) {
//            m_gameStateText->setText("Game over");
//            m_gameStateText->setPos((m_scene->width() - m_gameStateText->boundingRect().width()) / 2,
//                                   (m_scene->height() - m_gameStateText->boundingRect().height()) / 2);
//            m_gameStateText->setVisible(true);
//        } else {
//            m_gameStateText->setVisible(false);
//        }
//    }


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCellClicked(Cell *cell)
{
    static bool firstPlayerMove = false;
    static int moveCounter = 0;

    if(cell->state() != Cell::State(0)) {
        return;
     }


    if (firstPlayerMove) {
        cell->setState(Cell::State0);
        firstPlayerMove = false;
    } else {
        cell->setState(Cell::StateX);
        firstPlayerMove = true;
    }
    moveCounter++;

    if (check()==1){
       if (check()==1){
       exit(10000);
    }
       if (check()==2){
    }
}
}


