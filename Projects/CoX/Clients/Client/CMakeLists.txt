set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# for version and revision info. Derived from https://github.com/dolphin-emu/dolphin/blob/master/CMakeLists.txt#L132
find_package(Git)
if(GIT_FOUND)
  # defines SEGS_CLIENT_REVISION
  execute_process(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
      OUTPUT_VARIABLE SEGS_CLIENT_REVISION
      OUTPUT_STRIP_TRAILING_WHITESPACE)
  # defines SEGS_CLIENT_DESCRIPTION
  execute_process(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} describe --always --long --dirty
      OUTPUT_VARIABLE SEGS_CLIENT_DESCRIPTION
      OUTPUT_STRIP_TRAILING_WHITESPACE)

  # remove hash (and trailing "-0" if needed) from description
  string(REGEX REPLACE "(-0)?-[^-]+((-dirty)?)$" "\\2" SEGS_CLIENT_DESCRIPTION "${SEGS_CLIENT_DESCRIPTION}")

  # defines SEGS_CLIENT_BRANCH
  execute_process(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
      OUTPUT_VARIABLE SEGS_CLIENT_BRANCH
      OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

# version number
set(SEGS_CLIENT_VERSION_MAJOR "0")
set(SEGS_CLIENT_VERSION_MINOR "1")
set(SEGS_CLIENT_VERSION_PATCH "0")

# If SEGS Client is not built from a Git repository, default the version info to
# reasonable values.
if(NOT SEGS_CLIENT_REVISION)
    set(SEGS_CLIENT_DESCRIPTION "${SEGS_CLIENT_VERSION_MAJOR}.${SEGS_CLIENT_VERSION_MINOR}.${SEGS_CLIENT_VERSION_PATCH}")
    set(SEGS_CLIENT_REVISION "${SEGS_CLIENT_DESCRIPTION} (no further info)")
    set(SEGS_CLIENT_BRANCH "develop")
endif()

add_definitions(
    "-DSEGS_CLIENT_VERSION=\"${SEGS_CLIENT_VERSION_MAJOR}.${SEGS_CLIENT_VERSION_MINOR}.${SEGS_CLIENT_VERSION_PATCH}\""
    "-DSEGS_CLIENT_BRANCH=\"${SEGS_CLIENT_BRANCH}\""
    "-DSEGS_CLIENT_DESCRIPTION=\"${SEGS_CLIENT_DESCRIPTION}\""
    )

find_package(Qt5 COMPONENTS Core Quick QuickControls2 Multimedia REQUIRED)
find_package(Qt5QuickCompiler)

set(target_CPP
    main.cpp
    Login/Login.cpp
)
set(target_INCLUDE
    Login/Login.h
    Version/Version.h
)

set(target_RESOURCES
    qml.qrc
    Theme/Theme.qrc
    SettingsDialog/SettingsDialog.qrc
)

set(SOURCES
    ${target_CPP}
    ${target_INCLUDE}
    ${target_RESOURCES}
)

add_executable(SEGS_Client ${SOURCES})

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
    RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/client
)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/client/logs)
