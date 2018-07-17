#include <ros/ros.h>
#include <ros/network.h>
#include <geometry_msgs/Twist.h>

/**
 * This tutorial demonstrates how to send a velocity command to a p2os robot
 */
const double TWIST_LINEAR = 0.05; //.5 m/s forward
const double TWIST_ANGULAR = 0; //0 rad/s

int main(int argc, char **argv){
		ros::init (argc, argv, "command1");
    ros::NodeHandle n;
    
    ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 100);
    
    ros::Rate loop_rate(10);
    
    while (ros::ok()){
        geometry_msgs::Twist cmd_msg;
        cmd_msg.linear.x = TWIST_LINEAR;
        cmd_msg.angular.z = TWIST_ANGULAR;
        
        cmd_pub.publish(cmd_msg);
        
        ros::spinOnce();
        
        loop_rate.sleep();
    }
    
    
    return 0;
}
