#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    renderTimer = new QTimer();
    renderTimer->setInterval(0);
    connect(renderTimer, SIGNAL(timeout()), this, SLOT(updateUI()));
    renderTimer->start(100);

    socket = new UdpSocket();
}

Widget::~Widget()
{
    delete ui;
    delete socket;
}


void Widget::on_pushButton_clicked()
{
    this->socket->ChangeStopSignal();

    QString s1 = "Start sending data";
    QString s2 = "Stop sending data";

    if (ui->pushButton->text() == s1) ui->pushButton->setText(s2);
    else ui->pushButton->setText(s1);
}

void Widget::closeEvent(QCloseEvent *event)
{
    this->socket->disconnect();
}


void Widget::updateUI()
{
    // Send UI by timer tick
    socket->SendData();
}
