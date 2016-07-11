#ifndef ROS_IMAGE_TO_FILE_CPP
#define ROS_IMAGE_TO_FILE_CPP

#include <ros_image_to_file.h>
#include <ros_tools/ros_macros.h>

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
    // On construit le nom du fichier image par rapport à ce timestamp
    std::stringstream ss_image_filename;
    ss_image_filename << prefix_ << \
                         _stamp << \
                         get_extension();
    return ss_image_filename.str();
}

bool ImageToFile::dump(const sensor_msgs::ImageConstPtr& _msg, const cv::Mat& _image)
{
    const std::string filename = build_filename(_msg->header.stamp);

    // On écrit l'image
    cv::imwrite( filename, _image );

    // Debug info
    ROS_INFO_STREAM("Write image file: " << filename);
}

void ImageToFile::sub_cb(const sensor_msgs::ImageConstPtr& msg)
{
    try {
        cv::Mat image = cv_bridge::toCvCopy(msg, "bgr8")->image;
        dump( msg, image );
        if( show_image_ ) {
            cv::imshow("view", image);
            cv::waitKey(30);
        }
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

#endif // ROS_IMAGE_TO_FILE_CPP
