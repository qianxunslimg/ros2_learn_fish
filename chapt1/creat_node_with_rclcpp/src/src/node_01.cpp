#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv){
    //init
    rclcpp::init(argc, argv);
    //creat a node
    auto node = std::make_shared<rclcpp::Node>("node_01");
    //print a introduce
    RCLCPP_INFO(node->get_logger(), "node_01 has started...");
    //run the node and list for quit signal
    rclcpp::spin(node);
    //stop
    rclcpp::shutdown();
    return 0;
}