#pragma once

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "datatype.hpp"

using namespace std::chrono_literals;

class MyNode : public rclcpp::Node
{
public:
    MyNode(const std::string &node_name)
        : Node(node_name, rclcpp::NodeOptions().use_intra_process_comms(true))
    {
        string_publisher_ = this->create_publisher<std_msgs::msg::String>("topic_string", 10);
        int_publisher_ = this->create_publisher<std_msgs::msg::Int32>("topic_int", 10);
    }

    void publishStringMessageByLoop()
    {
        timer_ = this->create_wall_timer(
            500ms, std::bind(&MyNode::timer_callback, this));
    }

    void publishStringMessage(std::string str)
    {
        auto message = std_msgs::msg::String();
        message.data = str;
        RCLCPP_INFO(this->get_logger(), message.data.c_str());
        string_publisher_->publish(message);
    }

    void publishIntMessage(int num)
    {
        auto message = std_msgs::msg::Int32();
        message.data = num;
        RCLCPP_INFO(this->get_logger(), std::to_string(message.data));
        int_publisher_->publish(message);
    }

private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello, " + std::string(this->get_name()) + "! ";
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        string_publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr string_publisher_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr int_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};
