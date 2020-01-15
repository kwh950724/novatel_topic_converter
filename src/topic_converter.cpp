#include <iostream>

#include <ros/ros.h>
#include <novatel_msgs/INSPVAX.h>
#include <geographic_msgs/GeoPointStamped.h>

class NovatelConverter {
private:
	ros::NodeHandle nh_;
	ros::Subscriber novatel_sub_;
	ros::Publisher geo_pub_;
public:
	NovatelConverter(void) {
		initSetup();
		std::cout<<"NOVATEL CONVERTER NODE INITIALIZED."<<std::endl;
	}

	void initSetup(void) {
		novatel_sub_ = nh_.subscribe("/novatel_data/inspvax", 10, &NovatelConverter::novatelCallback, this);
		geo_pub_ = nh_.advertise<geographic_msgs::GeoPointStamped>("/gps/geopoint", 10);
	}
	
	void novatelCallback(const novatel_msgs::INSPVAX::ConstPtr &msg) {
		geographic_msgs::GeoPointStamped geo_msg;
	
		geo_msg.header.stamp = ros::Time::now();
		geo_msg.header.frame_id = "gps";
	
		geo_msg.position.latitude = msg->latitude;
		geo_msg.position.longitude = msg->longitude;
		geo_msg.position.altitude = msg->altitude;
		
		std::cout<<"LATITUDE: "<<geo_msg.position.latitude<<std::endl;
		std::cout<<"LONGITUDE: "<<geo_msg.position.longitude<<std::endl;
		std::cout<<"ALTITUDE: "<<geo_msg.position.altitude<<std::endl;
		std::cout<<"===================="<<std::endl;		

		geo_pub_.publish(geo_msg);
	} 
};

int main(int argc, char** argv) {
	ros::init(argc, argv, "novatel_topic_converter");
	
	NovatelConverter nc;

	ros::spin();

	return 0;
}
