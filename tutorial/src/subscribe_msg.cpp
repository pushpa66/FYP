#include "ros/ros.h"
#include <sstream>
#include "tutorial/dummy.h"

void dummyCallBack(const tutorial::dummy::ConstPtr& msg){
	
	//string firstName = msg->firstName;
	//string lastName = msg->lastName;
	int count = msg->count;
	std::cout << count << " " << msg->firstName << " " << msg->lastName << std::endl;
}

int main(int argc, char **argv)
{
	// Initiate new ROS node named "publisherMessage"
	ros::init(argc, argv, "subscriberMessage");
	ros::NodeHandle nh;
	
	ros::Subscriber exampleSubscriber = nh.subscribe("/publishMsg", 20, dummyCallBack);
	ros::spin();
	return 0;
}

