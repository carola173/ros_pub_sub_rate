#!/usr/bin/env python
import rospy
from std_msgs.msg import String 
from std_msgs.msg import Float64 #Double message for real rate publication

#Global variables
previous_time=0 #Initialize previous time for the first incoming message
rate_pub = rospy.Publisher('/PythonSubFreqRate', Float64, queue_size=1000) #The publisher variable should be declared global, as the message will be sent inside the Subscriber callback

'''
Function name: subCallBack
Description: This function keep the track of the frequency rate at which the data is subscribed from the publisher
             and publishs the frequency rate to the topic Python_Sub_FreqRate
             rospy::spin() ensures that the callback function subCallBack is called until the node is shutdown.

'''
def subCallBack(data):
    global previous_time

    now=rospy.get_time() #Get current time of the system time
    elapsed_time=now-previous_time #Obtain elapsed time between the callbacks, between the consecutive incoming messages
    previous_time=now # Used to calculate the time difference between the current and previous message
    freq_rate=1/elapsed_time #Calculates the frequency rate using elapsed time
    rospy.loginfo("I heard: %s", data.data)  # Print the published message
    rospy.loginfo("REAL RATE %f",freq_rate ) # Print the frequency rate
    rate_pub.publish(freq_rate) #Publish the frequency rate to be read by the rqt_plot

def listener():
    
    rospy.init_node('pythonSubscriber', anonymous=True)  # Node name registeration to the ROS-MASTER

    rospy.Subscriber("/msg", String, subCallBack) #Subcriber will get data from topic /cppSub and call the function subCallBack
    '''
        In order to call the callbacks used rospy.spin, callback runs untill the node is shutdown or Ctrl+c is pressed
    '''
    rospy.spin()

if __name__ == '__main__':
    listener()