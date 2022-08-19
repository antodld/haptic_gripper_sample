#include "Test_grasping.h"

Test_grasping::Test_grasping(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::MCController(rm, dt)
{
  config_.load(config);
  solver().addConstraintSet(contactConstraint);
  solver().addConstraintSet(kinematicsConstraint);
  solver().addTask(postureTask);
  solver().setContacts({{}});

  if (config.has("gripper"))
  {
    config("gripper",gripper_);
  }
  if (config.has("sub_topic"))
  {
    config("sub_topic",hand_topic_);
  }
  if (config.has("pub_topic"))
  {
    config("pub_topic",hand_pub_topic);
  }


  nh_ = mc_rtc::ROSBridge::get_node_handle();
  spinThread_ = std::thread(std::bind(&Test_grasping::rosSpinner, this));

  logger().addLogEntry("Gripper_openning_command", [this]() -> const double & {return openning_val_;});

  mc_rtc::log::info("Subscribing to {}",hand_topic_);


  hand_sub_.subscribe(*nh_, hand_topic_);
  hand_sub_.maxTime(maxTime_);
  gripper_pub_ = nh_->advertise<std_msgs::Int64>(hand_pub_topic, 1);
  controller_dt_ = dt;
  mc_rtc::log::success("Test_grasping init done ");
}

bool Test_grasping::run()
{
  
  auto & gripper = robot().gripper(gripper_);
  hand_sub_.tick(controller_dt_);
  
  if (hand_sub_.data().isValid()){
    
    openning_val_ = hand_sub_.data().value();

  }
  gripper.setTargetOpening(openning_val_);

  //Calcul

  //Calcul

  std_msgs::Int64 pub_msg;
  pub_msg.data = 0;
  gripper_pub_.publish(pub_msg);

  return mc_control::MCController::run();
}

void Test_grasping::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::MCController::reset(reset_data);
}
void Test_grasping::rosSpinner()
{
  mc_rtc::log::info("ROS spinner thread created");
  ros::Rate r(freq_);
  while(ros::ok())
  {
    ros::spinOnce();
    r.sleep();
  }
  mc_rtc::log::info("ROS spinner destroyed");
}

CONTROLLER_CONSTRUCTOR("Test_grasping", Test_grasping)
