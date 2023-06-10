#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtConcurrent/QtConcurrent>
#include "minimal_publisher.h"
#include "minimal_subscriber.h"

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

    std::shared_ptr<MinimalSubscriber> _node_sub;
    std::shared_ptr<MinimalPublisher> _node_pub;

    Ui::Widget *ui;
    int _node_cnt;
    COMMAND_TYPE laser_state;

private slots:
    void on_BtnPublishLaser_clicked();
};

#endif // WIDGET_H
