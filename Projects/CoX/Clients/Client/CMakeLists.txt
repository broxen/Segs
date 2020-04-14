set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick QuickControls2 Multimedia REQUIRED)

set(SOURCES
    main.cpp
    qml.qrc
)
set(HEADERS version.h)

add_executable(SEGS_Client ${SOURCES} ${HEADERS})

target_link_libraries(SEGS_Client PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2 Qt5::Multimedia)

install(TARGETS SEGS_Client
    DESTINATION deploy
)
IF(WIN32)
    include(Windeployqt)
    windeployqt(SEGS_Client deploy)
ELSEIF(APPLE)
    include(Macdeployqt)
    macdeployqt(SEGS_Client deploy)
ENDIF()

# Retain directory structure in visual studio
get_target_property(TARGET_SOURCES SEGS_Client SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCES})
set_target_properties (SEGS_Client PROPERTIES
    FOLDER Projects/CoX/Clients
    RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/utilities
)
