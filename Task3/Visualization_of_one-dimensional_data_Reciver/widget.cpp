#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // needed for mouse events
    this->setMouseTracking(true);

    // just render timer)
    renderTimer = new QTimer();
    renderTimer->setInterval(5);
    connect(renderTimer, SIGNAL(timeout()), this, SLOT(updateUI()));
    renderTimer->start(100);

    thread = new ReceivingDataThread();
    thread->start();

    lastYPoint = duration_cast< std::chrono::milliseconds>(system_clock::now().time_since_epoch());
    container = DataContainer::GetInstance();
}

Widget::~Widget()
{
    delete ui;

    thread->setStopSignal(true);
    thread->wait();

    delete thread;
}

QPair<float, float> Widget::getTruePointPosition(milliseconds x, float y, milliseconds timeNow)
{
    float a1 = this->width() * 4 / 5;
    float b1 = this->height() / 2;

    // calculate point for render
    float a2 = (a1 - ((timeNow - x).count())) * 10;
    float b2 = b1 - (y * 75);

    a2 -= this->width() / 2;
    b2 -= this->height() / 2;

    // ability to scale graphic
    a2 *= scaleUIFactor;
    b2 *= scaleUIFactor;

    // ability to move graphic
    a2 += move_x;
    b2 += move_y;

    a2 += this->width() / 2;
    b2 += this->height() / 2;

    return {a2, b2};
}

void Widget::paintEvent(QPaintEvent *event)
{
    // indicator on the timeline for start render data by Y point
    milliseconds timeNow = duration_cast< std::chrono::milliseconds>(
        system_clock::now().time_since_epoch());

    QPainter painter(this);

    QPointF lineStart( 0            , this->height() / 2 + move_y);
    QPointF lineEnd(   this->width(), this->height() / 2 + move_y);

    painter.drawLine(lineStart, lineEnd);
    painter.drawText(lineStart, "TimeLine");

    int countOfMissing = 0;
    auto contaiterPointer = container->GetContaiterPointer();
    QPair<milliseconds, float> item;
    int offsetX = 0;
    // synchronization of threads
    container->mutex.lock();

    // getting and iteration over all datas
    auto it = contaiterPointer->end();

    while(it != contaiterPointer->begin())
    {
        it--;
        item = *it;

        milliseconds a = item.first;
        float b = item.second;

        QPair<float, float> point;

        // item.first == lastYPoint ? offsetX++ : offsetX += (lastYPoint - item.first).count();
        // lastYPoint = item.first;

        point = getTruePointPosition(a - std::chrono::milliseconds(offsetX), b, timeNow);

        // a, b = point;
        // Fuck!

        float x = point.first;
        float y = point.second;

        // if point is not on the widget
        if (x < 0 || y < 0 || x > this->width() || y > this->height())
        {
            // it++;
            countOfMissing++;

            continue;
        }

        QPointF pointF(x, y);
        painter.drawEllipse(pointF, 1, 1);

        // it++;
    }

    container->mutex.unlock();

    if (countOfMissing > contaiterPointer->size() / 3) scaleUIFactor /= 1.1;

}

void Widget::updateUI()
{
    // rerender UI by timer tick
    repaint();
}

void Widget::closeEvent(QCloseEvent *event)
{
    socket->disconnect();
}

void Widget::mousePressEvent(QMouseEvent *eventPress)
{
    isMove = true;
    mouseClickPosition = Widget::mapFromGlobal(this->cursor().pos());
}


void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (isMove == true)
    {
        QPointF clickReleasePosition = Widget::mapFromGlobal(this->cursor().pos());

        move_x += clickReleasePosition.x() - mouseClickPosition.x();
        move_y += clickReleasePosition.y() - mouseClickPosition.y();

        mouseClickPosition = clickReleasePosition;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    isMove = false;
}

void Widget::wheelEvent(QWheelEvent *event)
{
   int scaleFactor = event->delta();

   if (scaleFactor > 0) scaleUIFactor *= 1.1;
   else scaleUIFactor /= 1.1;

}


