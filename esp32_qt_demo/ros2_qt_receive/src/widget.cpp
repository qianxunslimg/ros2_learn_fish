#include "widget.h"
#include "ui_widget.h"

#include "QFuture"

Widget::Widget(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Widget)
{
    _node_cnt = 0;
    ui->setupUi(this);
    connect(ui->btn_publish_laser, &QPushButton::clicked, this, &Widget::on_BtnPublishLaser_clicked);

    rclcpp::init(0, {});
    _node_sub = std::make_shared<MinimalSubscriber>("ros2_qt_receive");
    _node_pub = std::make_shared<MinimalPublisher>("ros2_qt_publish");
}

Widget::~Widget()
{
    delete ui;
    rclcpp::shutdown();
}

void Widget::on_BtnPublishLaser_clicked()
{
}