#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtConcurrent/QtConcurrent>
#include "topic.h"

namespace Ui
{
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    ~Widget();

private:
    void test();

    std::shared_ptr<MyNode> _node;

    Ui::Widget *ui;
    int _node_cnt;
    COMMAND_TYPE laser_state;
    COMMAND_TYPE montor_state;

private slots:
    void on_BtnMontorControl_clicked();
    void on_BtnPublishString_clicked();
    void on_BtnLaserControl_clicked();
};

#endif // WIDGET_H
