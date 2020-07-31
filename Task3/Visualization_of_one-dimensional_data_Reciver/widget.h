#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QtWidgets>

#include <QtGui>
#include <QtCore>

#include <QTimer>
#include <QTime>
#include <QPair>

#include "udpsocket.h"
#include "receivingdatathread.h"
#include "datacontainer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void updateUI();


private:
    Ui::Widget *ui;
    QTimer* renderTimer;

protected:

    void closeEvent(QCloseEvent *event) override;

    void mousePressEvent(QMouseEvent *eventPress) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void paintTimeLine();
    QPair<float, float> getTruePointPosition(milliseconds x, float y, milliseconds timeNow);

    UdpSocket* socket;
    ReceivingDataThread* thread;
    DataContainer* container;

    QPointF mouseClickPosition;
    bool isMove = false;

    float move_x = 0;
    float move_y = 0;

    float scaleUIFactor = 0.01;
    milliseconds lastYPoint;

};
#endif // WIDGET_H
