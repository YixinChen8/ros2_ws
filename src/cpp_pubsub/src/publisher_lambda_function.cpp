// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>
// #include <string>

#include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/string.hpp"

// Use the message structure "Num.msg" created myself in the package "tutorial_interfaces"
#include "tutorial_interfaces/msg/num.hpp"                                            // CHANGE

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses a fancy C++11 lambda
 * function to shorten the callback syntax, at the expense of making the
 * code somewhat more difficult to understand at first glance. */

class MinimalPublisher : public rclcpp::Node
{
public:
  // The public constructor names the node minimal_publisher and initializes count_ to 0
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    /* the publisher is initialized with the String message type, the topic name topic, 
    and the required queue size to limit messages in the event of a backup */ 

    // publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>("topic", 10);  // CHANGE
    // publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>("YixinTopic", 10);  // CHANGE

    /*
    a lambda function called timer_callback is declared. 
    It performs a by-reference capture of the current object this, takes no input arguments and returns void.
    */
    // auto timer_callback =
    //   [this]() -> void {
           // creates a new message of type String
    //     auto message = std_msgs::msg::String();
    //     message.data = "Hello, world! " + std::to_string(this->count_++);
    //     RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    //     this->publisher_->publish(message);
    //   };

    auto timer_callback = [this](){
      auto message = tutorial_interfaces::msg::Num();                                   // CHANGE
      message.num = this->count_++;                                                     // CHANGE 
      RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.num << "'");    // CHANGE
      publisher_->publish(message);
    };
    // timer_ is initialized, which causes the timer_callback function to be executed twice a second      
    timer_ = this->create_wall_timer(500ms, timer_callback);
    // timer_ = this->create_wall_timer(5s, timer_callback);    
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;             // CHANGE  
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
