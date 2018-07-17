#include "ros/ros.h"
#include <sstream>
#include "tutorial/dummy.h"

int main(int argc, char **argv)
{
	// Initiate new ROS node named "publisherMessage"
	ros::init(argc, argv, "publisherMessage");
	ros::NodeHandle n;
	
	ros::Publisher examplePublisher = n.advertise<tutorial::dummy>("/publishMsg", 1000);
	ros::Rate loop_rate(1); // 1 message per second

	int counter = 0;

	while(ros::ok()){ // Keep spinning loop until user presses Ctrl+C

		tutorial::dummy msg;
		msg.firstName = "Pushpa";
		msg.lastName = "Kumara";
		msg.count = counter;
		
		//Print the content of the message in the terminal
		std::cout<< "Sending Msg # " << (int)msg.count << ": The message has first name : " << msg.firstName << " last name : " << msg.lastName << std::endl;
		
		//Publish the message
		examplePublisher.publish(msg);
		ros::spinOnce(); // Need to call this function ofte to allow ROS to process incoming messages
		loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
		counter++;
	}
	return 0;
}

