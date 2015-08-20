#include <iostream>
#include <cstdio>
#include <cstdlib>  
#include <ros/ros.h>
#include <pcl/console/parse.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>    
#include <pcl/io/openni_grabber.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/people/ground_based_people_detection_app.h>
#include <pcl/common/time.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <people_detection/person_cluster.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

// PCL viewer //
pcl::visualization::PCLVisualizer viewer("PCL Viewer");

// Mutex: //
boost::mutex cloud_mutex;

bool new_cloud_available_flag;
PointCloudT::Ptr cloud(new PointCloudT);

enum { COLS = 640, ROWS = 480 };

void callback(const sensor_msgs::PointCloud2ConstPtr& msg){
   cloud_mutex.lock();
   sensor_msgs::PointCloud2 msg0 = *msg;
  //manually ordering cloud if cloud is unordered, assumes 480x640 kinect camera.
   msg0.height = 480;
   msg0.width = 640;
   msg0.row_step = 640 * msg0.point_step;
   PointCloudT cloud0;
   pcl::fromROSMsg(msg0, cloud0); //Converting from sensor_msgs::PointCloud2 to PointCloudT
   *cloud = cloud0;
   new_cloud_available_flag = true;
   cloud_mutex.unlock();
 }

struct callback_args{
  // structure used to pass arguments to the callback function
  PointCloudT::Ptr clicked_points_3d;
  pcl::visualization::PCLVisualizer::Ptr viewerPtr;
};
  
void
pp_callback (const pcl::visualization::PointPickingEvent& event, void* args)
{
  struct callback_args* data = (struct callback_args *)args;
  if (event.getPointIndex () == -1)
    return;
  PointT current_point;
  event.getPoint(current_point.x, current_point.y, current_point.z);
  data->clicked_points_3d->points.push_back(current_point);
  // Draw clicked points in red:
  pcl::visualization::PointCloudColorHandlerCustom<PointT> red (data->clicked_points_3d, 255, 0, 0);
  data->viewerPtr->removePointCloud("clicked_points");
  data->viewerPtr->addPointCloud(data->clicked_points_3d, red, "clicked_points");
  data->viewerPtr->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, "clicked_points");
  std::cout << current_point.x << " " << current_point.y << " " << current_point.z << std::endl;
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "people_detection");
  ros::NodeHandle n;
  new_cloud_available_flag = false;
  ros::Subscriber sub = n.subscribe<sensor_msgs::PointCloud2>("/camera/depth_registered/points", 1, callback);
  ros::Publisher people_pub = n.advertise<people_detection::person_cluster>("people", 1);

    // Algorithm parameters:
  std::string svm_filename = "/home/doodoros/rosbuild_ws/sandbox/people_detection/data/trainedLinearSVMForPeopleDetectionWithHOG.yaml";
  float min_confidence = -1.5;
  float min_height = 1.3;
  float max_height = 2.3;
  float voxel_size = 0.06;
  Eigen::Matrix3f rgb_intrinsics_matrix;
  rgb_intrinsics_matrix << 525, 0.0, 319.5, 0.0, 525, 239.5, 0.0, 0.0, 1.0; // Kinect RGB camera intrinsics
	

  // Wait for the first frame:
  while(!new_cloud_available_flag) 
    {
    	boost::this_thread::sleep(boost::posix_time::milliseconds(1));
			ros::spinOnce();
    }

  new_cloud_available_flag = false;

  cloud_mutex.lock ();    // for not overwriting the point cloud
  
  // Display pointcloud:
  pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb(cloud);
  viewer.addPointCloud<PointT> (cloud, rgb, "input_cloud");
  viewer.setCameraPosition(0,0,-2,0,-1,0,0);
  
  // Add point picking callback to viewer:
  struct callback_args cb_args;
  PointCloudT::Ptr clicked_points_3d (new PointCloudT);
  cb_args.clicked_points_3d = clicked_points_3d;
  cb_args.viewerPtr = pcl::visualization::PCLVisualizer::Ptr(&viewer);
  viewer.registerPointPickingCallback (pp_callback, (void*)&cb_args);
  std::cout << "Shift+click on three floor points, then press 'Q'..." << std::endl;

  // Spin until 'Q' is pressed:
  viewer.spin();
    
  cloud_mutex.unlock ();
  
  // Ground plane estimation:
  Eigen::VectorXf ground_coeffs;
  ground_coeffs.resize(4);
  std::vector<int> clicked_points_indices;
  for (unsigned int i = 0; i < clicked_points_3d->points.size(); i++)
    {
      clicked_points_indices.push_back(i);
    }
  
	pcl::SampleConsensusModelPlane<PointT> model_plane(clicked_points_3d);
  model_plane.computeModelCoefficients(clicked_points_indices,ground_coeffs);
  std::cout << "Ground plane: " << ground_coeffs(0) << " " << ground_coeffs(1) << " " << ground_coeffs(2) << " " << ground_coeffs(3) << std::endl;

  // Initialize new viewer:
  pcl::visualization::PCLVisualizer viewer("PCL Viewer");
  viewer.setCameraPosition(0,0,-2,0,-1,0,0);
  
  // Create classifier for people detection:  
  pcl::people::PersonClassifier<pcl::RGB> person_classifier;
  person_classifier.loadSVMFromFile(svm_filename);   // load trained SVM
  
  // People detection app initialization: sort of redundant, constructor sets all of this already
  pcl::people::GroundBasedPeopleDetectionApp<PointT> people_detector;    // people detection object
  people_detector.setVoxelSize(voxel_size);                        // set the voxel size
  people_detector.setIntrinsics(rgb_intrinsics_matrix);            // set RGB camera intrinsic parameters
  people_detector.setClassifier(person_classifier);                // set person classifier
  people_detector.setHeightLimits(min_height, max_height);         // set person classifier    // people detection object
  
  // For timing:
  static unsigned count = 0;
  static double last = pcl::getTime ();
  
  // Main loop:

  unsigned int indicator = 0;
  unsigned int i = 0;
  float goaldepth;
  float goalx;
  float goaldepthold;
  float goalxold;

  while (!viewer.wasStopped() && ros::ok())
  {

	if (new_cloud_available_flag && cloud_mutex.try_lock ())    // if a new cloud is available
    {

      new_cloud_available_flag = false;
      people_detection::person_cluster msg;


      // Perform people detection on the new cloud:
      std::vector<pcl::people::PersonCluster<PointT> > clusters;

      people_detector.setInputCloud(cloud);
      people_detector.setGround(ground_coeffs);  
      people_detector.compute(clusters);        
      ground_coeffs = people_detector.getGround();                 // get updated floor coefficients
      
      // Draw cloud and people bounding boxes in the viewer:
      viewer.removeAllPointClouds();
      viewer.removeAllShapes();
      pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb(cloud);
      viewer.addPointCloud<PointT> (cloud, rgb, "input_cloud");
      unsigned int k = 0;
      for(std::vector<pcl::people::PersonCluster<PointT> >::iterator it = clusters.begin(); it != clusters.end(); ++it)
      {
        if(it->getPersonConfidence() > min_confidence)             // draw only people with confidence above a threshold
        {
          // draw theoretical person bounding box in the PCL viewer:
          it->drawTBoundingBox(viewer, k);
	  if (k == 0){
		if (i == 0)
		{
	    		ROS_INFO("The distance is: %f", it->getDistance());
	   		ROS_INFO("The center coordinates are: x = %f, y = %f, z = %f", (it->getCenter())[0], (it->getCenter())[1], (it->getCenter())[2]);	
            		goalx = (it->getCenter())[0];
            		//goaly = -1*(it->getCenter())[0];
	    		goaldepth = (it->getCenter())[2];
			goalxold = goalx;
			goaldepthold = goaldepth;
	    		//goalx = (it->getCenter())[2];
	    		//people_pub.publish(msg);
		}
		else
		{
	    		ROS_INFO("The distance is: %f", it->getDistance());
	   		ROS_INFO("The center coordinates are: x = %f, y = %f, z = %f", (it->getCenter())[0], (it->getCenter())[1], (it->getCenter())[2]);
			goalxold = goalx;
			goaldepthold = goaldepth;	
            		goalx = (it->getCenter())[0];
            		//goaly = -1*(it->getCenter())[0];
	    		goaldepth = (it->getCenter())[2];
	    		//goalx = (it->getCenter())[2];
	    		//people_pub.publish(msg);
		}
	  }
            k++;
        }
      }

      //std::cout << k << " people found" << std::endl;
      if (k == 1){
	if ((abs(goalx -goalxold) < 1) && (abs(goaldepth - goaldepthold) < 1))
	   i++;
        else
	   i = 0;
      }

      if (i >= 3){
	indicator = indicator == 0? 1:0;
	ROS_INFO("Publishing to %d", indicator);
	msg.x = goalx;
	msg.depth = goaldepth;
	msg.indicator = (uint8_t)indicator;
	people_pub.publish(msg);
	ROS_INFO("Message published");
	i = 0;
	}
	
      viewer.spinOnce();
      // Display average framerate:
      if (++count == 30)
      {
        double now = pcl::getTime ();
        std::cout << "Average framerate: " << double(count)/double(now - last) << " Hz" <<  std::endl;
        count = 0;
        last = now;
      }
      cloud_mutex.unlock ();
    }
    ros::spinOnce();
  }
  ros::spin();
  return 0;
}
