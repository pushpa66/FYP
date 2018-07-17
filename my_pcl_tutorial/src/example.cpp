#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

ros::Publisher pub;

void cloud_cb (const sensor_msgs::PointCloud2 pCloud){
  // Create a container for the data.
  sensor_msgs::PointCloud2 output;

  // get width and height of 2D point cloud data
  int width = pCloud.width;
  int height = pCloud.height;

  // Convert from u (column / width), v (row/height) to position in array
  // where X,Y,Z data starts
  //int arrayPosition = v*pCloud.row_step + u*pCloud.point_step;
  int arrayPosition = 0;

  // compute position in array where x,y,z data start
  int arrayPosX = arrayPosition + pCloud.fields[0].offset; // X has an offset of 0
  int arrayPosY = arrayPosition + pCloud.fields[1].offset; // Y has an offset of 4
  int arrayPosZ = arrayPosition + pCloud.fields[2].offset; // Z has an offset of 8

  float X = 0.0;
  float Y = 0.0;
  float Z = 0.0;

  memcpy(&X, &pCloud.data[arrayPosX], sizeof(float));
  memcpy(&Y, &pCloud.data[arrayPosY], sizeof(float));
  memcpy(&Z, &pCloud.data[arrayPosZ], sizeof(float));
  
  std::cout << "X " << X <<std::endl;
  std::cout << "Y " << Y <<std::endl;
  std::cout << "Z " << Z <<std::endl;

  // Do data processing here...
  output = pCloud;

  // Publish the data.
  pub.publish (output);
}

int main (int argc, char** argv){
  // Initialize ROS
  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  // ros::Subscriber sub = nh.subscribe ("input", 1, cloud_cb);
  ros::Subscriber sub = nh.subscribe ("/camera/depth/points", 100, cloud_cb);
  

  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("my_output", 100);

  // Spin
  ros::spin ();
}
