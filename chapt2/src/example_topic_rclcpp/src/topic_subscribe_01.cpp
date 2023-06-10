//
// Created by qianxunslimg on 4/19/23.
//
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using Msg = std_msgs::msg::String;
class TopicSubscribe01 : public rclcpp::Node{
public:
    TopicSubscribe01(std::string name) : Node(name){
        RCLCPP_INFO(this->get_logger(), "Hello, i am %s", name.c_str());
        command_subscribe_ = this->create_subscription<std_msgs::msg::String>
                ("command", 10, std::bind(&TopicSubscribe01::command_callback, this, std::placeholders::_1));
    }
private:
    rclcpp::Subscription<Msg>::SharedPtr command_subscribe_;
    void command_callback(const Msg::SharedPtr msg){
        double speed = 0.0f;
        if(msg->data == "forward"){
            speed = 0.2f;
        }
        RCLCPP_INFO(this->get_logger(), "receive order %s, speed %f", msg->data.c_str(), speed);
    }
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicSubscribe01>("topic_subscribe_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}