cmake_minimum_required(VERSION 3.16)

project(QT_APP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Network)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appQT_APP
    main.cpp
)

qt_add_qml_module(appQT_APP
    URI QT_APP
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES timer.h timer.cpp
        SOURCES usb.h usb.cpp
        SOURCES
        SOURCES action.h action.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQT_APP PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQT_APP
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQT_APP
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Network
    PRIVATE ${LIBUSB_LIBRARIES}
)

target_include_directories(appQT_APP PRIVATE ${LIBUSB_INCLUDE_DIRS})

include(GNUInstallDirs)
install(TARGETS appQT_APP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
