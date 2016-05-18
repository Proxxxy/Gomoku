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
            m_cells[j][i]->setState(Cell::Statenothing);
            m_cells[j][i]->setPos(j*50,i*50);
            connect(m_cells[j][i], SIGNAL(clicked(Cell*)), this, SLOT(onCellClicked(Cell*)));

        }
    }
    m_scene->update();
}


int MainWindow::check(Cell* cell){

    int cx = cell->x()/50;
    int cy = cell->y()/50;
    int hcounter = 1;
    int vcounter = 1;
    int drcounter = 1;
    int dlcounter = 1;
    int step = 1;
    bool win = false;

    bool nBlock = false; // left
    bool pBlock = false; // right
    bool vvBlock = false; // up
    bool vnBlock = false; // down
    bool dvBlock = false; // right up
    bool dnBlock = false; // left down
    bool dvvBlock = false; // right down
    bool dvnBlock = false; // left up

    while (true) {
        if (win) { break; }

        if (cx == 8) {
            pBlock = true;
            dvBlock = true;
            dvvBlock = true;
        }
        if (cx == 0) {
            nBlock = true;
            dnBlock = true;
            dvnBlock = true;
        }
        if (cy == 8) {
            vnBlock = true;
            dvBlock = true;
            dvnBlock = true;
        }
        if (cy == 0) {
            vvBlock = true;
            dnBlock = true;
            dvvBlock = true;
        }

        if (nBlock && pBlock && vnBlock && vvBlock && dvBlock && dnBlock && dvvBlock && dvnBlock) { break; }

        if (!pBlock){
            if(m_cells[cx+step][cy]->state() == cell->state()) {
                hcounter++;
            } else { pBlock = true; }
        }

        if (!nBlock) {
            if(m_cells[cx-step][cy]->state() == cell->state()) {
                hcounter++;
            } else { nBlock = true; }
        }

        if (!vnBlock){
            if(m_cells[cx][cy+step]->state() == cell->state()) {
                vcounter++;
            } else { vnBlock = true; }
        }

        if (!vvBlock) {
            if(m_cells[cx][cy-step]->state() == cell->state()) {
                vcounter++;
            } else { vvBlock = true; }
        }

        if (!dvBlock){
            if(m_cells[cx+step][cy+step]->state() == cell->state()) {
                drcounter++;
            } else { dvBlock = true; }
        }

        if (!dnBlock) {
            if(m_cells[cx-step][cy-step]->state() == cell->state()) {
                drcounter++;
            } else { dnBlock = true; }
        }

        if (!dvvBlock){
            if(m_cells[cx+step][cy-step]->state() == cell->state()) {
                dlcounter++;
            } else { dvvBlock = true; }
        }

        if (!dvnBlock) {
            if(m_cells[cx-step][cy+step]->state() == cell->state()) {
                dlcounter++;
            } else { dvnBlock = true; }
        }

        step++;

        if (hcounter == 5 || vcounter == 5 || drcounter == 5 || dlcounter == 5) {
            win = true;
        }
    }

    if (win) {
        if (cell->state() == Cell::StateX){
            return 1;
        }
        else if (cell->state() == Cell::State0) {
            return 2;
        }
    }
    return 0;
}

void MainWindow::setLabel(QString string)
{
    ui->label->setText(string);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCellClicked(Cell *cell)
{
    static bool firstPlayerMove = false;

    if(cell->state() != Cell::Statenothing) {
        return;
    }

    if (firstPlayerMove) {
        cell->setState(Cell::State0);
        firstPlayerMove = false;
        setLabel("Ход X");
    } else {
        cell->setState(Cell::StateX);
        firstPlayerMove = true;
        setLabel("Ход 0");
    }
    int status = check(cell);
    if (status) {
        QMessageBox msgBox;
        if (status == 1) {
            msgBox.setText("X wins!");
        }
        if (status == 2) {
            msgBox.setText("0 wins!");
        }

        msgBox.setWindowTitle("Gomoku: winner!");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
        msgBox.setButtonText(QMessageBox::Ok, "New Game");
        msgBox.setButtonText(QMessageBox::Close, "Quit");
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
            for (int j=0; j<9; j++) {
                for(int i=0; i<9; i++) {
                    m_cells[j][i]->setState(Cell::Statenothing);
                    setLabel("Ход X");
                }
            }
            m_scene->update();
            firstPlayerMove = false;
            break;
        case QMessageBox::Close:
            exit(0);
            break;
        default:
            break;
        }
    }
}
