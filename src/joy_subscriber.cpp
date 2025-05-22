#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"

class JoySubscriber : public rclcpp::Node {
public:
    JoySubscriber() : Node("joy_subscriber") {
        subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10,
            [this](sensor_msgs::msg::Joy::UniquePtr msg) {
                RCLCPP_INFO(this->get_logger(), "Axes:");
                for (size_t i = 0; i < msg->axes.size(); ++i) {
                    RCLCPP_INFO(this->get_logger(), "  [%zu]: %f", i, msg->axes[i]);
                }

                RCLCPP_INFO(this->get_logger(), "Buttons:");
                for (size_t i = 0; i < msg->buttons.size(); ++i) {
                    RCLCPP_INFO(this->get_logger(), "  [%zu]: %d", i, msg->buttons[i]);
                }
            });
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JoySubscriber>());
    rclcpp::shutdown();
    return 0;
}