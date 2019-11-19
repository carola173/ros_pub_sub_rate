#include "ros/ros.h"
#include <sstream>
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include <dynamic_reconfigure/server.h>
#include <pub_sub_rate/dynamicConfigConfig.h>


class cppPub
{
    public:
        int lp_rate;
        std::string pub_string;
        ros::Publisher pub_rate ;
        ros::Publisher pub_msg;

        void callback(pub_sub_rate::dynamicConfigConfig &config, uint32_t level)
        {
            lp_rate=config.loop_rate;
            pub_string=config.pub_string;
        }
        cppPub(ros::NodeHandle n)
        {

            this->pub_rate = n.advertise<std_msgs::Int32>("/CppPublisherRate", 1000);
            this->pub_msg = n.advertise<std_msgs::String>("/msg", 1000);
            dynamic_reconfigure::Server<pub_sub_rate::dynamicConfigConfig> server;
            dynamic_reconfigure::Server<pub_sub_rate::dynamicConfigConfig>::CallbackType dyn;
            dyn = boost::bind(&cppPub::callback,this, _1, _2);
            server.setCallback(dyn);
            test_run();
        }

        void test_run()
        {
            while (ros::ok())
            {
                ros::Rate loop_rate(this->lp_rate);
                std_msgs::Int32 rate_;
                std_msgs::String msg_;
                msg_.data=this->pub_string;
                rate_.data=this->lp_rate;
                pub_rate.publish(rate_);
                pub_msg.publish(msg_);
                ros::spinOnce();
                loop_rate.sleep();   

            }
        }

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cppPublisher"); //node name
    ros::NodeHandle nh; // create a node handle; need to pass this to the class constructor
    cppPub cppPubRos(nh); 

    return 0;
}