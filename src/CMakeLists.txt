set(controller_SRC
  Test_grasping.cpp
)

set(controller_HDR
  Test_grasping.h
  ROSSubscriber.h
)



add_controller(${PROJECT_NAME} ${controller_SRC} ${controller_HDR})
target_link_libraries(${PROJECT_NAME} PUBLIC mc_rtc::mc_rtc_ros)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DTest_grasping_EXPORTS")

