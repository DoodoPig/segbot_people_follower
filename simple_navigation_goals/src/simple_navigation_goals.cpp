#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <people_detection/person_cluster.h>
#include <math.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
float goalx;
float goaly;
bool person_found_flag = false;

void callback(const people_detection::person_clusterConstPtr& msg){
 goalx = msg->depth - 0.5;
 goaly = -1*(msg->x);
 if ((int)msg->indicator == 0)
 	person_found_flag = true;
 else
	person_found_flag = false;
 }

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe<people_detection::person_cluster>("/people", 1, callback);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  while(ros::ok()){
	if(person_found_flag == true){
  		//we'll send a goal to the robot to move to the person meter forward
  		goal.target_pose.header.frame_id = "base_link";
  		goal.target_pose.header.stamp = ros::Time::now();

  		goal.target_pose.pose.position.x = goalx;
  		goal.target_pose.pose.position.y = goaly;
  		goal.target_pose.pose.orientation.z = sin(atan(goaly/goalx)/2);
  		goal.target_pose.pose.orientation.w = cos(atan(goaly/goalx)/2);
		//goal.target_pose.pose.position.x = 3.15;
		//goal.target_pose.pose.position.y = -2.8;
		//goal.target_pose.pose.orientation.z = sin(atan(-2.8/3.15)/2);
		//goal.target_pose.pose.orientation.w = cos(atan(-2.8/3.15)/2);
		//goal.target_pose.pose.orientation.w = 1.0;

 		ROS_INFO("Sender 0 Sending goal x = %f, y = %f", goalx, goaly);
		ac.sendGoal(goal);

		ac.waitForResult();

 		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    		  ROS_INFO("Hooray, the base moved to the person");
  		else
    		  ROS_INFO("The base failed to move to the person");
		
		person_found_flag = false;
	}
	
	ros::spinOnce();
  }

  return 0;
}
