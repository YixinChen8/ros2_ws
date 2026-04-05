#include "rclcpp/rclcpp.hpp"
// #include "example_interfaces/srv/add_two_ints.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"                                       // CHANGE

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  // if (argc != 3) {
  if (argc != 4) { // CHANGE    
      // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_three_ints_client X Y Z");      // CHANGE      
      return 1;
  }

  // // create the node "add_two_ints_client"
  // std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
  // // create the client "add_two_ints" for the node "add_two_ints_client"
  // rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client =
  //   node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_client");  // CHANGE
  rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client =                // CHANGE
    node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints");          // CHANGE    

  // the request is created. Its structure is defined by the .srv file mentioned earlierhe request is created. Its structure is defined by the .srv file
  // auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
  auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();       // CHANGE
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);
  request->c = atoll(argv[3]);                                                              // CHANGE


  // The while loop gives the client 1 second to search for service nodes in the network. If it can’t find any, it will continue waiting
  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      // If the client is canceled (e.g. by you entering Ctrl+C into the terminal), it will return an error log message stating it was interrupted
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
  } else {
    // RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_three_ints");    // CHANGE

  }

  rclcpp::shutdown();
  return 0;
}