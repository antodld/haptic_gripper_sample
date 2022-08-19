#pragma once

#include <mc_control/mc_controller.h>


#include "api.h"

struct Test_grasping_DLLAPI Test_grasping : public mc_control::MCController
{
    Test_grasping(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

    bool run() override;

    void reset(const mc_control::ControllerResetData & reset_data) override;
private:
    mc_rtc::Configuration config_;
};