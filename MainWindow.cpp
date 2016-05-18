#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Cell.hpp"
#include <QGraphicsScene>
#include <QColor>
#include <QDebug>
#include <QMessageBox>

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


int MainWindow::check(){
    for (int j=0; j<9; j++){
        for (int i=0; i<9; i++){
            if (m_cells[j][i]->state()!=Cell::Statenothing){
                if (j<6){
                    if (m_cells[j][i]->state() == m_cells[j+1][i]->state() == m_cells[j+2][i]->state() == m_cells[j+3][i]->state() and m_cells[j][i]->state() == m_cells[j+4][i]->state() ){
                        if (m_cells[j][i]->state() == Cell::StateX) {
                            return 1;
                        } else {
                            return 2;
                        }
                    }

                    if (i<6){
                        if (m_cells[j][i]->state() == m_cells[j][i+1]->state() == m_cells[j][i+2]->state() == m_cells[j][i+3]->state() and m_cells[j][i]->state() == m_cells[j][i+4]->state()){
                            if (m_cells[j][i]->state() == Cell::StateX) {
                                return 1;
                            } else {
                                return 2;
                            }
                        }
                    }

                    if (j<6 and i<6){
                        if (m_cells[j][i]->state() == m_cells[j+1][i+1]->state() == m_cells[j+2][i+2]->state() == m_cells[j+3][i+3]->state() and m_cells[j][i]->state() == m_cells[j+4][i+4]->state()){
                            if (m_cells[j][i]->state() == Cell::StateX) {
                                return 1;
                            } else {
                                return 2;
                            }
                        }
                    }

                    if (j>4 and i<6){
                        if (m_cells[j][i]->state() == m_cells[j+1][i-1]->state() == m_cells[j+2][i-2]->state() == m_cells[j+3][i-3]->state() and m_cells[j][i]->state() == m_cells[j+4][i-4]->state()){
                            if (m_cells[j][i]->state() == Cell::StateX) {
                                return 1;
                            } else {
                                return 2;
                            }
                        }
                    }
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCellClicked(Cell *cell)
{
    static bool firstPlayerMove = false;

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

    if (check() != 0) {
        QMessageBox msgBox;
        if (check() == 1) {
            msgBox.setText("X wins!");
        }
        if (check() == 2) {
            msgBox.setText("0 wins!");
        }
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            for (int j=0; j<9; j++) {
                for(int i=0; i<9; i++) {
                    m_cells[j][i]->setState(Cell::Statenothing);
                }
            }
            m_scene->update();
            break;
        case QMessageBox::Close:
            exit(0);
            break;
        default:
            break;
        }
    }
}
