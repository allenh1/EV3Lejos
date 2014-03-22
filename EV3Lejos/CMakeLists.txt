##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.0)
project(EV3Lejos)

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS roscpp tf nav_msgs)#qt_build roscpp)
find_package(Qt5 COMPONENTS Core Gui Network Widgets)
include_directories(${catkin_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything. 
catkin_package()
add_definitions(-fPIC)

##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically 
# included via the dependency call in package.xml
#rosbuild_prepare_qt5(Core Gui Network) # Add the appropriate components to the component list here
set(QT_USE_QTNETWORK)
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
##############################################################################
# Sections
##############################################################################

#file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui) # As of now, we have no Ui.
#file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc) # Nor do we have QtResources.
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.h) # Include header files

#QT4_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
#QT4_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)
#qt5_use_modules(GLOB_RECURSE QT_SOURCES Widgets Network)
##############################################################################
# Binaries
##############################################################################

add_executable(EV3Lejos ${QT_SOURCES} ${QT_MOC_HPP})
target_link_libraries(EV3Lejos ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES} ${catkin_LIBRARIES})
install(TARGETS EV3Lejos RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

