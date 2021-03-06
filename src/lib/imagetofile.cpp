#ifndef ROS_IMAGE_TO_FILE_CPP
#define ROS_IMAGE_TO_FILE_CPP


#include <ros_image_to_file.h>
#include <ros_tools/ros_macros.h>
#include <opencv2/highgui/highgui.hpp>

#include "config.h"
//#define __USE_OPENCV_BRIDGE__

static const std::string kOPENCV_WINDOW = "view";


ImageToFile::ImageToFile (ros::NodeHandle _priv_nh, bool _b_show_image)
{
    GET_ROS_PARAM(prefix, prefix_, "IMG_", _priv_nh, nh_);
    GET_ROS_PARAM(show_image, show_image_, true, _priv_nh, nh_);
    GET_ROS_PARAM(topic_name, topic_name_, "/camera/image", _priv_nh, nh_);

    image_transport::ImageTransport it(nh_);
    sub_ = it.subscribe(topic_name_, 1, &ImageToFile::sub_cb, this);
    ROS_INFO ("Listening for incoming data on topic %s",
              nh_.resolveName (topic_name_).c_str ());
}

std::string ImageToFile::build_filename(const ros::Time& _stamp)
{
    // On construit le nom du fichier image par rapport � ce timestamp
    std::stringstream ss_image_filename;
    ss_image_filename << prefix_ << \
                         _stamp << \
                         get_extension();
    return ss_image_filename.str();
}

bool ImageToFile::dump(const sensor_msgs::ImageConstPtr& _msg, const cv::Mat& _image)
{
    const std::string filename = build_filename(_msg->header.stamp);

#ifdef _USE_OPENCV_BRIDGE_
    // On �crit l'image
    cv::imwrite( filename, _image );
#endif

    // Debug info
    ROS_INFO_STREAM("Write image file: " << filename);
}

void ImageToFile::sub_cb(const sensor_msgs::ImageConstPtr& msg)
{    
    ROS_INFO_STREAM("Dans le callback de ImageToFile !");

#ifdef _USE_OPENCV_BRIDGE_
//    cv_bridge::CvImagePtr cv_ptr;
//    try
//    {
//        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
//    }
//    catch (cv_bridge::Exception& e)
//    {
//        ROS_ERROR("cv_bridge exception: %s", e.what());
//        return;
//    }
//    // Update GUI Window
//    cv::imshow(kOPENCV_WINDOW, cv_ptr->image);
//    cv::waitKey(3);


    try {
//        cv::Mat image = cv_bridge::toCvCopy(msg, "bgr8")->image;
//        const cv::Mat image = cv_bridge::toCvShare(msg, "bgr8")->image;

        const cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg, "bgr8");
        const cv::Mat image = cv_ptr->image;
        dump( msg, image );
        if( show_image_ ) {
            cv::imshow(kOPENCV_WINDOW, image);
            cv::waitKey(3);
        }
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
#endif
}

#endif // ROS_IMAGE_TO_FILE_CPP
