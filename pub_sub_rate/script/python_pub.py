#!/usr/bin/env python
import rospy
from std_msgs.msg import String 
from std_msgs.msg import Int32
from dynamic_reconfigure.server import Server as DynamicReconfigureServer #dynamic reconfiguration server
from pub_sub_rate.cfg import dynamicConfigConfig 


class PythonPub():
    def callback(self, config, level):
        self.pub_string=config["pub_string"] # Re-configurable parameter for accepting the string value
        self.loop_rate=config["loop_rate"] # Re-configurable parameter for  loop rate
        return config
    
    def __init__(self):
        self.loop_rate=10
        pub_msg = rospy.Publisher('/msg', String, queue_size=1000) # publisher for publishing the message
        pub_rate = rospy.Publisher('/PythonPublisherRate', Int32, queue_size=1000)# publisher for publishing the publisher rate
        rospy.init_node('pythonPublisher', anonymous=True) 
        self.server = DynamicReconfigureServer(dynamicConfigConfig, self.callback)
        while not rospy.is_shutdown():
            rate = rospy.Rate(self.loop_rate)
            pub_msg.publish(self.pub_string)
            pub_rate.publish(self.loop_rate)
            rate.sleep()


if __name__ == '__main__':
    try:
        pu=PythonPub()
    except rospy.ROSInterruptException:
        pass