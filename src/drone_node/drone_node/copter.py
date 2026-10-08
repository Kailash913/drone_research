import rclpy
from rclpy.node import Node
class Copter(Node):
    def __init__(self):
        super().__init__('copter')
        self.get_logger().info('Copter node started')
def main(args=None):
    rclpy.init(args=args)
    node = Copter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
if __name__ == '__main__':
    main()



