#include "Cell.hpp"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "MainWindow.hpp"
Cell::Cell():QGraphicsObject()

{
    m_state=Statenothing;
}

QRectF Cell::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->drawRect(0,0,50,50);
   switch (m_state) {
   case StateX:
       painter->drawText(25,25, "X");
       break;
   case State0:
       painter->drawText(25,25, "0");
       break;
   case StateWinX:
       painter->setBrush(Qt::green);
       painter->drawRect(0,0,50,50);
       painter->drawText(25,25,"X");
       break;
   case StateWin0:
       painter->setBrush(Qt::green);
       painter->drawRect(0,0,50,50);
       painter->drawText(25,25, "0");
       break;
   default:
       break;
   }
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void Cell::setState(State stat)
{
    if (m_state == stat)
    {
        return;
    }
    m_state=stat;

    update();
}



void Cell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(this);
}

