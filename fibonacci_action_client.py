import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from custom_action_interfaces.action import Fibonacci


class FibonacciActionClient(Node):

    def __init__(self):
        super().__init__('fibonacci_action_client')

        # create an action client using the custom action definition from the previous tutorial on Creating an action
        # create an ActionClient by passing it three arguments:
        # 1. A ROS 2 node to add the action client to: self
        # 2. The type of the action: Fibonacci
        # 3. The action name: 'fibonacci'
        self._action_client = ActionClient(self, Fibonacci, 'fibonacci')

    # define a method send_goal
    # This method waits for the action server to be available, then sends a goal to the server. It returns a future that we can later wait on.
    def send_goal(self, order):
        goal_msg = Fibonacci.Goal()
        goal_msg.order = order

        self._action_client.wait_for_server()

        # The ActionClient.send_goal_async() method returns a future to a goal handle
        # self._send_goal_future = self._action_client.send_goal_async(goal_msg)
        self._send_goal_future = self._action_client.send_goal_async(goal_msg, feedback_callback=self.feedback_callback)        

        # First we register a callback for when the future is complete
        self._send_goal_future.add_done_callback(self.goal_response_callback)               

        # return self._action_client.send_goal_async(goal_msg)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        # check to see if the goal was rejected and return early since we know there will be no result
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return

        self.get_logger().info('Goal accepted :)')

        # Now that we’ve got a goal handle, we can use it to request the result with the method get_result_async()
        # Similar to sending the goal, we will get a future that will complete when the result is ready. 
        # Let’s register a callback just like we did for the goal response
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    # In the callback, we log the result sequence and shutdown ROS 2 for a clean exit
    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info('Result: {0}'.format(result.sequence))
        rclpy.shutdown()        

    def feedback_callback(self, feedback_msg):
        # get the feedback portion of the message
        feedback = feedback_msg.feedback
        # print the partial_sequence field to the screen
        self.get_logger().info('Received feedback: {0}'.format(feedback.partial_sequence))


def main(args=None):
    # initialize ROS 2
    rclpy.init(args=args)

    # creates an instance of our FibonacciActionClient node
    action_client = FibonacciActionClient()

    # send a goal
    # future = action_client.send_goal(10)

    # wait until that goal has been completed
    # rclpy.spin_until_future_complete(action_client, future)

    action_client.send_goal(10)

    rclpy.spin(action_client)    


# call main() in the entry point of our Python program
if __name__ == '__main__':
    main()