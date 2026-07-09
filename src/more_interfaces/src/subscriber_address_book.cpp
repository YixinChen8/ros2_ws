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

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookSubscriber : public rclcpp::Node
{
public:
  AddressBookSubscriber()
  : Node("address_book_subscriber")
  {
    // auto topic_callback =
    //   [this](std_msgs::msg::String::UniquePtr msg) -> void {
    //     RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    //   };
    // subscription_ =
    //   this->create_subscription<std_msgs::msg::String>("topic", 10, topic_callback);

    auto topic_callback = [this](const more_interfaces::msg::AddressBook & address_book){     // CHANGE
      RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << address_book.first_name << "'");    // 
      RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << address_book.last_name << "'");    // CHANGE      
      RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << address_book.phone_number << "'");    // CHANGE      
      RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << address_book.phone_type << "'");    // CHANGE  
    };
    subscription_ = this->create_subscription<more_interfaces::msg::AddressBook>(    // CHANGE
      "address_book", 10, topic_callback);      
    // subscription_ = this->create_subscription<tutorial_interfaces::msg::Num>(    // CHANGE
    //   "YixinTopic", 10, topic_callback);          
  }


  private:
    // rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::Subscription<more_interfaces::msg::AddressBook>::SharedPtr subscription_;  // CHANGE  
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AddressBookSubscriber>());
  rclcpp::shutdown();
  return 0;
}