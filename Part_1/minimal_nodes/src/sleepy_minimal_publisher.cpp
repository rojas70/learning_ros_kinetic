#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "minimal_publisher2"); // name of this node will be "minimal_publisher2"
    ros::NodeHandle n; // two lines to create a publisher object that can talk to ROS
    ros::Publisher my_publisher_object = n.advertise<std_msgs::Float64>("topic1", 1);
    //"topic1" is the name of the topic to which we will publish
    // the "1" argument says to use a buffer size of 1; could make larger, if expect network backups
    
    std_msgs::Float64 input_float; //create a variable of type "Float64", 
    // as defined in: /opt/ros/indigo/share/std_msgs
    // any message published on a ROS topic must have a pre-defined format, 
    // so subscribers know how to interpret the serialized data transmission
   
   ros::Rate naptime(1.0); 


    input_float.data = 0.0;
    
    while (ros::ok()) 
    {
        input_float.data = input_float.data + 0.001; 
        my_publisher_object.publish(input_float); 
	naptime.sleep(); 
    }
}

