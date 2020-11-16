#include <ros/ros.h>
#include <example_ros_service/ExampleServiceMsg.h>

#include <iostream>
#include <string>

using namespace std;

bool callback(example_ros_service::ExampleServiceMsgRequest& request,
	      example_ros_service::ExampleServiceMsgResponse& response)
{
  ROS_INFO("callback activated");
  string in_name(request.name); 
  response.on_the_list=false;
    
  if (in_name.compare("Bob")==0)
    {
      ROS_INFO("asked about Bob");
      response.age = 32;
      response.good_guy=false;
      response.on_the_list=true;
      response.nickname="BobTheTerrible";
    } 

  if (in_name.compare("Ted")==0)
    {
      ROS_INFO("asked about Ted");
      response.age = 21;
      response.good_guy=true;
      response.on_the_list=true;
      response.nickname="Ted the Benevolent";
    }    
    
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "example_ros_service");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("lookup_by_name", callback);

  ROS_INFO("Service server is ready to look up names....");

  ros::spin();

  return 0;
}
