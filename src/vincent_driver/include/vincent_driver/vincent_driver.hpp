#ifndef VINCENT_DRIVER__VINCENT_DRIVER_HPP_
#define VINCENT_DRIVER__VINCENT_DRIVER_HPP_

#include "rclcpp/rclcpp.hpp"

namespace palomino
{

class VincentDriver : public rclcpp::Node
{
public:
  explicit VincentDriver(const rclcpp::NodeOptions & options);
};

}  // namespace palomino

#endif