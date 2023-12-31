#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class ServiceClient01 : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    ServiceClient01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
        // 创建客户端
        client_ = this->create_client<example_interfaces::srv::AddTwoInts>("my_add_two_ints_service");
    }

    void send_request(int a, int b)
    {
        RCLCPP_INFO(this->get_logger(), "计算%d+%d", a, b);

        // 1.等待服务端上线
        while (!client_->wait_for_service(std::chrono::seconds(1)))
        {
            // 等待时检测rclcpp的状态
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "等待服务的过程中被打断...");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "等待服务端上线中");
        }

        // 2.构造请求的
        auto request =
            std::make_shared<example_interfaces::srv::AddTwoInts_Request>();
        request->a = a;
        request->b = b;

        // 3.发送异步请求，然后等待返回，返回时调用回调函数
        client_->async_send_request(
            request, std::bind(&ServiceClient01::result_callback_, this,
                               std::placeholders::_1));
        // // another style to get res at the same position
        // auto result_future = client->async_send_request(request);
        // if (rclcpp::spin_until_future_complete(node, result_future) !=
        //     rclcpp::FutureReturnCode::SUCCESS)
        // {
        //     RCLCPP_ERROR(node->get_logger(), "service call failed :(");
        //     return 1;
        // }
        // auto result = result_future.get();
    };

private:
    // 声明客户端
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;

    void result_callback_(
        rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture
            result_future)
    {
        auto response = result_future.get();
        RCLCPP_INFO(this->get_logger(), "计算结果：%ld", response->sum);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*创建对应节点的共享指针对象*/
    auto node = std::make_shared<ServiceClient01>("service_client_01");
    /* 运行节点，并检测退出信号*/
    // 增加这一行，node->send_request(5, 6);，计算5+6结果
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            node->send_request(i, j);
        }
    }
    //    node->send_request(5, 6);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}