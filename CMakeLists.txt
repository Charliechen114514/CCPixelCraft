cmake_minimum_required(VERSION 3.16)

project(CCImageEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Project settings
# Config the opencv path

# Get the deference path for the opencv, this should
# Point to the lib directory contains .cmake file of the opencv
if(CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(GLOBAL_OPENCV_DIR "D:\\OpencvLib\\Opencv490MSVC\\release\\x64\\vc17\\lib")
else()
    set(GLOBAL_OPENCV_DIR "D:\\OpencvLib\\Opencv490MSVC\\debug\\x64\\vc17\\lib")
endif()

# Set If the test case is required
set(REQ_TEST ON)

# Set if the develop examples are required
set(REQ_EXAMPLE OFF)

# Find neccessary packages for the projects
# Projects requires the opencv as the
# neccessary building library for usage

# Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Opencv
set(OpenCV_DIR ${GLOBAL_OPENCV_DIR}) # xxxx目录包含OpenCVConfig.cmake
find_package(OpenCV REQUIRED)	# 找到opencv库

# Followings are Ui include and sources files
# Which follows the Part of Displaying and
# interacting with user

# Broadcast the project infos
message(STATUS "Broadcasting the project infos")
message(STATUS "Root source directory: ${CMAKE_SOURCE_DIR}")


# For some reason, We need to set the searching path of
# ui components which inherited from the Qt Components
set(COMPONENT_SEARCHING_PATH
    Ui/Components/DisplayLabel
    Ui/Components/PreviewLabel
)

set(TARGET_SEARCHING_PATH
    Core/
    Ui/
    Core/ImageImporter
    Ui/MainWindow
    Core/Utils/
    Core/predef/
    Ui/Initializer
    Ui/ActionMonitor
    ${COMPONENT_SEARCHING_PATH}
)

set(CORE_SOURCE
    Core/ImageImporter/ImageImporter.cpp
    Core/ImageHolder/ImageHolder.cpp
    Core/Utils/convertor/image_convertor.cpp
    Core/StatusBarInfoManager/StatusBarInfoManager.cpp
)

set(CORE_INCLUDE
    Core/ImageImporter/ImageImporter.h
    Core/ImageHolder/ImageHolder.h
    Core/Utils/convertor/image_convertor.h
    Core/StatusBarInfoManager/StatusBarInfoManager.h
)

set(UiComponenet_SOURCE
    Ui/Components/DisplayLabel/DisplayLabel.cpp
    Ui/Components/PreviewLabel/PreviewLabel.cpp
)

set(UiComponenet_INCLUDE
    Ui/Components/DisplayLabel/DisplayLabel.h
    Ui/Components/PreviewLabel/PreviewLabel.h
)


set(UI_SOURCE
    Ui/MainWindow/CCImageMainWindow.cpp
    Ui/UiUtils.cpp
    Ui/MainWindow/UiMainWindowInitializer.cpp
    Ui/WindowHelper/windoweventhelper.cpp
    Ui/ActionMonitor/eventhandlefunctor.cpp
    Ui/ActionMonitor/KeyboardMonitor/keyboardmonitor.cpp
    Ui/ActionMonitor/MouseMonitor/mousemonitor.cpp
    Ui/ActionMonitor/eventhandlefunctor.cpp
    Ui/ImageInfoWidget/ImageInfoWidget.cpp
)

set( UI_INCLUDE
    Ui/UiUtils.h
    Ui/MainWindow/CCImageMainWindow.h
    Ui/MainWindow/UiMainWindowInitializer.h
    Ui/WindowHelper/windoweventhelper.h
    Ui/ActionMonitor/eventhandlefunctor.h
    Ui/ActionMonitor/KeyboardMonitor/keyboardmonitor.h
    Ui/ActionMonitor/MouseMonitor/mousemonitor.h
    Ui/ActionMonitor/eventhandlefunctor.h
    Ui/ImageInfoWidget/ImageInfoWidget.h
)

set( SOURCE
    ${UI_SOURCE}
    ${UiComponenet_SOURCE}
    ${CORE_SOURCE}
    Core/main.cpp
)

set(INCLUDES
    ${UI_INCLUDE}
    ${UiComponenet_INCLUDE}
    ${CORE_INCLUDE}
    Core/predef/predef.h
)

set(UI_FILE
    Ui/MainWindow/CCImageMainWindow.ui
    Ui/ImageInfoWidget/ImageInfoWidget.ui
)

set(QRC_FILE Sources/sources.qrc)

set(PROJECT_SOURCES
    ${SOURCE}
    ${INCLUDES}
    ${UI_FILE}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CCImageEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QRC_FILE}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CCImageEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CCImageEditor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CCImageEditor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CCImageEditor
    PUBLIC
        ${OpenCV_LIBRARIES}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(CCImageEditor
    PUBLIC
        ${TARGET_SEARCHING_PATH}
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CCImageEditor)
endif()
set_target_properties(CCImageEditor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CCImageEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CCImageEditor)
endif()

# We start test only when in releasing mode :)
if(REQ_TEST AND CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Release")
    add_subdirectory(Test)
endif()

# We shell build examples if we need to
if(REQ_EXAMPLE)
    add_subdirectory(develop_example/examples)
endif()




