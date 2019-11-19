# ros_pub_sub_rate
Validating the publish and subscribe rate in ROS for C++ and Pyhon.

There are four launch files showing the possible combination
A. cpp_pub_py_sub.launch - Launching publisher in cpp and Subscriber in Python

B. cpp_pub_sub.launch - Launching subsriber and publisher in cpp

C. py_pub_cpp_sub.launch- Launch publisher in python and subscriber in cpp

D. py_pub_sub.launch - Launching publisher and subscriber in python

Since Pytho is slower than the C++ program as the python codes are interpeted everytime it is executed while the cpp code is once compiled then the cpp object code is linked to the ROS which runs.
The python code is interpreted i.e it is compiled in run time, while the program is being executed. That makes the code slower.

When the publishing rate increases then the subsciber rate needs to match it. For the following scenario it sometime doesnot matches for instance when the publisher is cpp and subscriber is python - As python code is complied everytime on runtime

When the loop rate paramter is kept at 10 ,there is discontunity in the subscriber rate sometimes when the python is the subsciber node that time the subscibtion is low as 9Hz which i didnt see it when CPP is the subscribption node  

Rospy contains functions similar to roscpp, with operations related to node, topic, service, param, and time.

The main difference between the rospy and roscpp is that one is used for python, enabling the interpreted capablity and another one is for the CPP node enabling ROS to use the complied object code respectively.

Also rospy has a completely different threading model. Every subscriber and timer in rospy spawns its own thread, and rospy.spin() is jut an infinite loop that lets those threads operate. For that reason, mutexes are very important in rospy when globals or class variables are used.

Along with this theh rospy doesn't have the concept of the roshandle,Operations such as creating a publisher and a subscriber are directly encapsulated into functions or classes in rospy. 

The naming of some rospy interfaces is inconsistent with roscpp. In some places, developers need to pay attention to avoid calling errors.
