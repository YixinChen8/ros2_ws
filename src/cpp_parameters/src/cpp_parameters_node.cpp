#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam()
  : Node("minimal_param_node")
  {
    // Created a parameter descriptor "param_desc"
    auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
    param_desc.description = "This parameter is mine!";

    // creates a parameter with the name "my_parameter" and a default value "world"
    this->declare_parameter("my_parameter", "world", param_desc);

    // a lambda function called "timer_callback" is declared. 
    // It performs a by-reference capture of the current object "this", takes no input arguments and returns void
    auto timer_callback = [this](){
      // gets the parameter my_parameter from the node, and stores it in "my_param"
      std::string my_param = this->get_parameter("my_parameter").as_string();

      // the "RCLCPP_INFO" function ensures the event is logged
      RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());

      std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", "world")};
      // The "set_parameters" function sets the parameter "my_parameter" back to the default string value "world"
      this->set_parameters(all_new_parameters);
    };
    // "timer_" is initialized with a period of 1000ms, which causes the timer_ is initialized with a period of 1000ms, which causes the "timer_callback" function to be executed once a secondtimer_callback function to be executed once a second
    timer_ = this->create_wall_timer(1000ms, timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  // ROS 2 is initialized
  rclcpp::init(argc, argv);
  // The instance of the "MinimalParam" class is constructed
  // and rclcpp::spin starts processing data from the node
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}