cmake_minimum_required(VERSION 2.8.3)
project(pub_sub_rate)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  dynamic_reconfigure
)

## System dependencies are found with CMake's conventions
 find_package(Boost REQUIRED COMPONENTS system)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## Generate dynamic reconfigure parameters in the 'cfg' folder
generate_dynamic_reconfigure_options(
    cfg/dynamicConfig.cfg
 )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pub_sub_rate
   CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)



## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
 add_executable(cppPublisher src/cpp_pub.cpp)
 add_executable(cppSubscriber src/cpp_sub.cpp)


add_dependencies(cppPublisher  pub_sub_rate_gencfg)
add_dependencies(cppSubscriber pub_sub_rate_gencfg)

## Specify libraries to link a library or executable target against

target_link_libraries(cppPublisher
   ${catkin_LIBRARIES}
 )
target_link_libraries(cppSubscriber
   ${catkin_LIBRARIES}
 )
