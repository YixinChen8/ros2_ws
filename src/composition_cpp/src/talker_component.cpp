#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp_components/register_node_macro.hpp"

using namespace std::chrono_literals;

namespace composition_cpp
{

class Talker : public rclcpp::Node
{
public:
  explicit Talker(const rclcpp::NodeOptions & options)
  : Node("talker_component", options)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
    timer_ = this->create_wall_timer(
      1s, std::bind(&Talker::on_timer, this));
  }

private:
  void on_timer()
  {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello from composable node";
    publisher_->publish(msg);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace composition_cpp

RCLCPP_COMPONENTS_REGISTER_NODE(composition_cpp::Talker)