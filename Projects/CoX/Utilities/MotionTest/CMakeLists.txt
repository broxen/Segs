find_package(Qt5 5.8 COMPONENTS Core Gui Widgets OpenGL Network REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(MotionTest_SOURCES
    MainWindow.ui
    MainWindow.cpp
    MainWindow.h
    MotionTest.cpp
    MotionTest.h
    main.cpp
)

add_executable(MotionTest WIN32 ${MotionTest_SOURCES})
target_link_libraries(MotionTest PUBLIC Qt5::Core Qt5::Widgets Qt5::Network)
