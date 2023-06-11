#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MyParam : public rclcpp::Node
{
private:
    /* data */
    rclcpp::TimerBase::SharedPtr timer_;

public:
    MyParam() : rclcpp::Node("my_param_node")
    {
        this->declare_parameter("my_param", "world");
        timer_ = this->create_wall_timer(1000ms, [&]()
                                         {
                                             std::string my_param_string = this->get_parameter("my_param").as_string();
                                             RCLCPP_INFO(this->get_logger(), "Hello, the current param is %s", my_param_string.c_str());
                                             // std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_param", "world")};
                                             // this->set_parameters(all_new_parameters);  // change it back
                                         });
    }
};

int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyParam>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
