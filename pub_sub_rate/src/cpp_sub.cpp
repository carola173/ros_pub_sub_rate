/*
Objective : To collect the subscriber frequency rate and publish to a topic in order to collect the performance of the
            subscriber's topic data is coming from python publisher and the c++ publisher
*/

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h" // Publishing the subscriber frequency rate



double previous_time = 0; //Initialize previous time for the first incoming message
double time_now, elapsed_time, rate_freq;
ros::Publisher rate_pub;
std_msgs::Float64 msg_;// A double message type is decalred to publish the rate
/*
Function name: subCallBack
Description: This function keep the track of the frequency rate at which the data is subscribed from the publisher
             and publishs the frequency rate to the topic Cpp_Sub_FreqRate
             ros::spin() ensures that the callback function subCallBack is called until the node is shutdown.

*/
void subCallback(const std_msgs::String::ConstPtr& msg)
{
    time_now = ros::Time::now().toSec(); //Get current time of the system time
	elapsed_time = time_now - previous_time; //Obtain elapsed time between the callbacks, between the consecutive incoming messages
	previous_time=time_now;// Used to calculate the time difference between the current and previous message. 
	rate_freq=1/elapsed_time;// Calculates the frequency rate using elapsed time
    ROS_INFO("I heard: [%s]", msg->data.c_str());  // Print the published message
    ROS_INFO("REAL RATE %f",rate_freq); // Print the frequency rate
    msg_.data=rate_freq; // Assigning the frequency rate to the message
    rate_pub.publish(msg_);//Publish the frequency rate to be read by the rqt_plot
}
   


int main(int argc, char **argv)
{
    ros::init(argc, argv, "cppSubscriber"); // Node name registeration to the ROS-MASTER
    /*
     Automated management of ROS Node Life Cycle either when the nodehandler is is created it will call ros::start(),
     and when the last ros::NodeHandle is destroyed, it will call ros::shutdown()
    */
    ros::NodeHandle n; 
    rate_pub = n.advertise<std_msgs::Float64>("/CppSubFreqRate", 1000); // Publisher which will publish the subscriber frequency rate
    /*
     Subcriber will get data from topic /cppSub and call the function subCallBack
    */
    ros::Subscriber sub = n.subscribe("msg", 1000, subCallback); 
    /*
        In order to call the callbacks used ros::spin, callback runs untill the node is shutdown or Ctrl+c is pressed
    */
    ros::spin();
    return 0;
}
