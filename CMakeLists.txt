cmake_minimum_required(VERSION 2.8.3)
project(novatel_topic_converter)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geographic_msgs
  novatel_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(topic_converter src/topic_converter.cpp)
target_link_libraries(topic_converter ${catkin_LIBRARIES})
