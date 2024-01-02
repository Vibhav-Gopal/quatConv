#include "quatConv.h"
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "quatConv/orientation.h"
#define SUBSCRIBER_TOPIC "/in_topic"
#define SUBSCRIBER_DATATYPE sensor_msgs::Imu
#define PUBLISHER_DATATYPE quatConv::orientation
#define PUBLISHER_TOPIC "/out_topic"
ros::Publisher publisher;
void cb(const SUBSCRIBER_DATATYPE data)
{
    Quarternion q;
    q.x = data.orientation.x;
    q.y = data.orientation.y;
    q.z = data.orientation.z;
    q.w = data.orientation.w;
    RotationVector angles;
    angles = toEuler(q);
    PUBLISHER_DATATYPE msg;
    msg.heading = angles.heading;
    msg.attitude = angles.attitude;
    msg.bank = angles.bank;
    publisher.publish(msg);

}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"quat2rpy");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe(SUBSCRIBER_TOPIC,1000,cb);
    publisher = nh.advertise<PUBLISHER_DATATYPE>(PUBLISHER_TOPIC,1000);
    ros::spin();
    return 0;
}