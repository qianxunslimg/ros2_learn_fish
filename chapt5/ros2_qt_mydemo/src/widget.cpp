#include "widget.h"
#include "ui_widget.h"

#include "QFuture"

Widget::Widget(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Widget)
{
    _node_cnt = 0;
    ui->setupUi(this);
    connect(ui->btn_montor_control, &QPushButton::clicked, this, &Widget::on_BtnMontorControl_clicked);
    connect(ui->btn_publish_string, &QPushButton::clicked, this, &Widget::on_BtnPublishString_clicked);
    connect(ui->btn_laser_control, &QPushButton::clicked, this, &Widget::on_BtnLaserControl_clicked);

    rclcpp::init(0, {});
    _node = std::make_shared<MyNode>("send2esp32");

    laser_state = COMMAND_TYPE::LASER_STOP;
}

Widget::~Widget()
{
    delete ui;
    rclcpp::shutdown();
}

void Widget::test()
{
    rclcpp::init(0, {});
    rclcpp::spin(_node);
    rclcpp::shutdown();
}

int num = 0;

void Widget::on_BtnMontorControl_clicked()
{
    if (montor_state == COMMAND_TYPE::MONTOR_STOP)
    {
        _node->publishIntMessage(COMMAND_TYPE::MONTOR_START);
        ui->btn_montor_control->setText("stop montor");
        montor_state = COMMAND_TYPE::MONTOR_START;
    }
    else
    {
        _node->publishIntMessage(COMMAND_TYPE::MONTOR_STOP);
        ui->btn_montor_control->setText("start montor");
        montor_state = COMMAND_TYPE::MONTOR_STOP;
    }
}

void Widget::on_BtnPublishString_clicked()
{
    std::string str_edit = ui->m_edit_string->toPlainText().toStdString();
    _node->publishStringMessage(str_edit);
}
void Widget::on_BtnLaserControl_clicked()
{
    if (laser_state == COMMAND_TYPE::LASER_STOP)
    {
        _node->publishIntMessage(COMMAND_TYPE::LASER_START);
        ui->btn_laser_control->setText("stop laser");
        laser_state = COMMAND_TYPE::LASER_START;
    }
    else
    {
        _node->publishIntMessage(COMMAND_TYPE::LASER_STOP);
        ui->btn_laser_control->setText("start laser");
        laser_state = COMMAND_TYPE::LASER_STOP;
    }
}