#include "rclcpp/rclcpp.hpp"

class Node02 : public rclcpp::Node{

public:
    // 构造函数,有一个参数为节点名称
    Node02(std::string name) : Node(name){
        // 打印一句
        RCLCPP_INFO(this->get_logger(), 
        "Hello, i am %s.",name.c_str());
    }
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    /*产生一个node_03的节点*/
    auto node = std::make_shared<Node02>("node_02");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}