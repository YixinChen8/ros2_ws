import rclpy
from rclpy.node import Node

# create the class "MinimalParam"
class MinimalParam(Node):
    # create the constructor with: 1) the node name "minimal_param_node"; 2) the parameter value as "my_parameter = world"
    def __init__(self):
        super().__init__('minimal_param_node')

        from rcl_interfaces.msg import ParameterDescriptor
        my_parameter_descriptor = ParameterDescriptor(description='This parameter is mine!')        

        # self.declare_parameter('my_parameter', 'world')
        self.declare_parameter('my_parameter', 'world', my_parameter_descriptor)

        # "timer" is initialized with a period of 1
        self.timer = self.create_timer(1, self.timer_callback)

    def timer_callback(self):
        # gets the parameter my_parameter from the node, and stores it in "my_param"
        my_param = self.get_parameter('my_parameter').get_parameter_value().string_value

        # the "get_logger" function ensures the event is logged
        self.get_logger().info('Hello %s!' % my_param)

        my_new_param = rclpy.parameter.Parameter(
            'my_parameter',
            rclpy.Parameter.Type.STRING,
            'world'
        )
        all_new_parameters = [my_new_param]
        # The "set_parameters" function then sets the parameter my_parameter back to the default string value "world"
        # In the case that the user changed the parameter externally, this ensures it is always reset back to the original
        self.set_parameters(all_new_parameters)

def main():
    # ROS 2 is initialized
    rclpy.init()
    # an instance of the MinimalParam class is constructed
    node = MinimalParam()
    # "rclpy.spin" starts processing data from the node
    rclpy.spin(node)

if __name__ == '__main__':
    main()