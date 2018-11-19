#include<ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include<example_action_server/demoAction.h>

int g_count = 0;
bool g_count_failure = false;

class ExampleActionServer {
private:

  ros::NodeHandle nh_;  // we'll need a node handle; get one upon instantiation

  actionlib::SimpleActionServer<example_action_server::demoAction> as_;
  
  example_action_server::demoGoal goal_; 
  example_action_server::demoResult result_; 
  example_action_server::demoFeedback feedback_; 
  int countdown_val_;

public:
  ExampleActionServer(); //define the body of the constructor outside of class definition

  ~ExampleActionServer(void) {
  }
  // Action Interface
  void executeCB(const actionlib::SimpleActionServer<example_action_server::demoAction>::GoalConstPtr& goal);
};

ExampleActionServer::ExampleActionServer() : as_(nh_, "timer_action", boost::bind(&ExampleActionServer::executeCB, this, _1),false) 
{
  ROS_INFO("in constructor of exampleActionServer...");
  as_.start(); //start the server running
}

void ExampleActionServer::executeCB(const actionlib::SimpleActionServer<example_action_server::demoAction>::GoalConstPtr& goal) {

  ROS_INFO("in executeCB");
  ROS_INFO("goal input is: %d", goal->input);  

  ros::Rate timer(1.0); // 1Hz timer
  countdown_val_ = goal->input;
  
  while (countdown_val_>0) {
    ROS_INFO("countdown = %d",countdown_val_);
       
    // each iteration, check if cancellation has been ordered
    if (as_.isPreemptRequested()){	
      ROS_WARN("goal cancelled!");
      result_.output = countdown_val_;
      as_.setAborted(result_); // tell the client we have given up on this goal; send the result message as well
      return; // done with callback
    }

    // set how to handle feedback
    feedback_.fdbk = countdown_val_; 
    as_.publishFeedback(feedback_); 
    countdown_val_--; 
    timer.sleep(); 
  }

  result_.output = countdown_val_; //value should be zero, if completed countdown
  as_.setSucceeded(result_); // return the "result" message to client, along with "success" status
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "timer_action_server_node"); // name this node 
  ROS_INFO("instantiating the timer_action_server: ");

  ExampleActionServer as_object; // create an instance of the class "ExampleActionServer"
    
  ROS_INFO("going into spin");
  ros::spin();

  return 0;
}

