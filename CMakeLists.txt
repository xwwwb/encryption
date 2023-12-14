cmake_minimum_required(VERSION 3.5)

project(Encryption VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 设置OpenCV目录所在
# https://cmake.org/cmake/help/latest/module/FindOpenSSL.html
# set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@1.1/")
set(OPENSSL_ROOT_DIR "/opt/homebrew/Cellar/openssl@3/3.1.4")

# 搜索OpenCV目录
find_package(OpenSSL REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        md5.h md5.cpp md5.ui
        des.h des.cpp des.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Encryption
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Encryption APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Encryption SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Encryption
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Encryption PRIVATE Qt${QT_VERSION_MAJOR}::Widgets OpenSSL::SSL)

set_target_properties(Encryption PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Encryption
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Encryption)
endif()

