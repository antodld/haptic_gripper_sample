#pragma once

#include <mc_control/mc_controller.h>
#include <std_msgs/Int64.h>
#include "ROSSubscriber.h"

#include "api.h"

struct Test_grasping_DLLAPI Test_grasping : public mc_control::MCController
{
    Test_grasping(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

    bool run() override;

    void reset(const mc_control::ControllerResetData & reset_data) override;
private:
    
    void rosSpinner();
    double controller_dt_;
    double openning_val_ = 1;
    std::string gripper_;
    mc_rtc::Configuration config_;
    std::shared_ptr<ros::NodeHandle> nh_;
    std::thread spinThread_;
    double maxTime_ = 0.5;
    double freq_ = 0.01;
    std::string hand_topic_ = "topic";
    std::string hand_pub_topic = "";
    ROSFloatSubscriber hand_sub_;
    ros::Publisher gripper_pub_;
};