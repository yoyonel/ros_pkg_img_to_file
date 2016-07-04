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
    void image_cb(const sensor_msgs::ImageConstPtr& msg);

protected:
    ros::NodeHandle nh_;

private:
    std::string prefix_;

    bool b_show_image_;

    std::string image_topic_;

    image_transport::Subscriber sub_;
};

#endif // ROS_IMAGE_TO_FILE_H
