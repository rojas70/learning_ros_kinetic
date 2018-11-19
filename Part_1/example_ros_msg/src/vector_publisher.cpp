#include <ros/ros.h>
#include <custom_msgs/VecOfDoubles.h> 

int main(int argc, char **argv) {
    ros::init(argc, argv, "vector_publisher"); 
    ros::NodeHandle n;
    
    ros::Publisher my_publisher_object = n.advertise<custom_msgs::VecOfDoubles>("vec_topic", 1);
    
    custom_msgs::VecOfDoubles vec_msg; 

    double counter=0; 
    ros::Rate naptime(1.0); 
   
    vec_msg.dbl_vec.resize(3);

    vec_msg.dbl_vec[0]=1.414;    
    vec_msg.dbl_vec[1]=2.71828;    
    vec_msg.dbl_vec[2]=3.1416;
    
    vec_msg.dbl_vec.push_back(counter);
    
    while(ros::ok())  {

      counter+=1.0;
      vec_msg.dbl_vec.push_back(counter);
      
      my_publisher_object.publish(vec_msg);
      naptime.sleep(); 
    }
}   

