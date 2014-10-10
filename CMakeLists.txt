# Subtitle Studio
# Joel Anttila 2014

# PREFIX PATH ON DEV MACHINE
# -DCMAKE_PREFIX_PATH=C:\\Qt\\Qt5.3.0\\5.3\\msvc2013\\lib\\cmake\\Qt5

cmake_minimum_required(VERSION 2.8.11)
set(PRJ subtitlestudio)
project(${PRJ})

# Automoc & Moc includes.
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Find qt5 widgets package.
#find_package(Qt5Core REQUIRED Qt5Widgets REQUIRED Qt5Gui REQUIRED Qt5Sql REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Sql REQUIRED)
find_package(LIBVLC REQUIRED)

if(LIBVLC_FOUND)
    message(LIBVLC_FOUND)
endif()


set(QT_USE_QTSQL TRUE)

include_directories(${LIBVLC_INCLUDE_DIR})
include_directories(${Qt_INCLUDE_DIR})
#include_directories(${Qt5Core_INCLUDES}) # ${Qt5Widgets_INCLUDES})

#add_definitions(${Qt5Widgets_DEFINITIONS})
#set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS}")

# Need to run moc on this.
#file(COPY ui/StudioWindow.ui DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add sources to the build.
add_subdirectory(src)

set(TLIB ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY} ${Qt_LIBRARIES})

add_executable(${PRJ} WIN32 ${SRC_LIST}) #${LIBVLC_LIBRARY})
target_link_libraries(${PRJ} ${TLIB})

qt5_use_modules(${PRJ} Widgets Sql)

qt5_wrap_ui(ui/ui_StudioWindow.h ui/StudioWindow.ui)

#target_link_libraries(${PRJ} Widgets)
