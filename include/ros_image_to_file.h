#ifndef ROS_IMAGE_TO_FILE_H
#define ROS_IMAGE_TO_FILE_H

#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


/**
 * @brief The ImageToFile class
 */
class ImageToFile {

public:
    /**
     * @brief ImageToFile
     * @param _priv_nh
     * @param _b_show_image
     */
    ImageToFile(ros::NodeHandle _priv_nh = ros::NodeHandle("~"), bool _b_show_image=false);

private:
    /**
     * @brief writeImage
     * @param _msg
     * @param _image
     * @return
     */
    bool dump(const sensor_msgs::ImageConstPtr& _msg, const cv::Mat& _image);
    /**
     * @brief image_cb
     * @param msg
     */
    void sub_cb(const sensor_msgs::ImageConstPtr& msg);

    std::string build_filename(const ros::Time &_stamp);
    inline std::string get_extension() const { return ".jpg"; }

protected:
    ros::NodeHandle nh_;

private:
    std::string prefix_;
    bool show_image_;

    std::string topic_name_;
    image_transport::Subscriber sub_;
};

#endif // ROS_IMAGE_TO_FILE_H
