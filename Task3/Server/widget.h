#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

#include "udpsocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    UdpSocket* socket;

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);

    void updateUI();

private:
    Ui::Widget *ui;

    QTimer* renderTimer;
};
#endif // WIDGET_H
