#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace palomino
{

class VincentDriver : public rclcpp::Node
{
public:
  explicit VincentDriver(const rclcpp::NodeOptions & options)
  : Node("vincent_driver", options)
  {
    RCLCPP_INFO(this->get_logger(), "VincentDriver node started.");
  }
};

}  // namespace palomino

// 👇 REQUIRED for composable nodes
RCLCPP_COMPONENTS_REGISTER_NODE(palomino::VincentDriver)