import time

import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node

from custom_action_interfaces.action import Fibonacci


class FibonacciActionServer(Node):

    def __init__(self):
        super().__init__('fibonacci_action_server')

        # instantiate a new action server with four arguments:
        # 1. A ROS 2 node to add the action server to: self.
        # 2. The type of the action: Fibonacci (imported in line 5).
        # 3. The action name: 'fibonacci'.
        # 4. A callback function for executing accepted goals: self.execute_callback. This callback must return a result message for the action type.
        self._action_server = ActionServer(
            self,
            Fibonacci,
            'fibonacci',
            self.execute_callback)

    # define an execute_callback method that will be called to execute a goal once it is accepted.
    def execute_callback(self, goal_handle):
        self.get_logger().info('Executing goal...')
        
        # sequence = [0, 1]
        feedback_msg = Fibonacci.Feedback()
        feedback_msg.partial_sequence = [0, 1]

        for i in range(1, goal_handle.request.order):
            # sequence.append(sequence[i] + sequence[i-1])
            feedback_msg.partial_sequence.append(
                feedback_msg.partial_sequence[i] + feedback_msg.partial_sequence[i-1])
            self.get_logger().info('Feedback: {0}'.format(feedback_msg.partial_sequence))
            goal_handle.publish_feedback(feedback_msg)
            time.sleep(1)

        goal_handle.succeed()

        result = Fibonacci.Result()
        # result.sequence = sequence
        result.sequence = feedback_msg.partial_sequence
        return result


def main(args=None):
    rclpy.init(args=args)

    fibonacci_action_server = FibonacciActionServer()

    rclpy.spin(fibonacci_action_server)


if __name__ == '__main__':
    main()