// urls:
// - http://wiki.ros.org/image_transport/Tutorials/SubscribingToImages
// - -> a lire: http://wiki.ros.org/image_transport/Tutorials (pas réellement utilisé ici encore)
// - http://wiki.ros.org/image_transport/Tutorials/SubscribingToImages
//   - http://wiki.ros.org/cv_bridge/Tutorials/UsingCvBridgeToConvertBetweenROSImagesAndOpenCVImages

#include <ros/ros.h>
#include <string>

#include <sub_img_to_file_node.h>
#include <opencv2/highgui/highgui.hpp>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_listener");

    ros::NodeHandle priv_nh("~");

    bool b_show_image;
    if ( priv_nh.getParam("show_image", b_show_image) && b_show_image )
    {
        ROS_INFO_STREAM("Show image recorded");
        cv::namedWindow("view");
        cv::startWindowThread();
    }

    ImageToFile itof(priv_nh, b_show_image);

    ros::spin();

    cv::destroyWindow("view");
}
