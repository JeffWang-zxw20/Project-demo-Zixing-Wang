cmake_minimum_required(VERSION 2.8.3)
project(mocap_optitrack)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g -fPIC")

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs geometry_msgs tf roslaunch message_generation)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp message_runtime
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_mocap_node 
  src/mocap_node.cpp  
  src/mocap_config.cpp
  src/mocap_datapackets.cpp
  src/socket.cpp
)

target_link_libraries(${PROJECT_NAME}_mocap_node ${catkin_LIBRARIES})

set_target_properties(${PROJECT_NAME}_mocap_node PROPERTIES
                      OUTPUT_NAME mocap_node PREFIX "")
install(TARGETS 
  ${PROJECT_NAME}_mocap_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

# Check the validity of the supplied launch files.
roslaunch_add_file_check(launch)

