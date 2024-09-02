cmake_minimum_required(VERSION 3.29)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(DynamicVersion)
dynamic_version(PROJECT_PREFIX Hello_)

IF (DEFINED CMAKE_BUILD_TYPE)
    message(STATUS "Preset build type ${CMAKE_BUILD_TYPE}")
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug
Release.")
ELSE ()
    message(STATUS "No preset build type")
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build,
options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release.")
ENDIF ()

project(hello-qtwebengine LANGUAGES CXX VERSION ${PROJECT_VERSION})

set(COPYRIGHT "Copyright (c) 2024 Turscar.")
set(IDENTIFIER "ie.turscar.${PROJECT_NAME}")
set(COMPANY "Turscar")

message(STATUS "Building ${PROJECT_NAME} ${PROJECT_VERSION} for ${CMAKE_BUILD_TYPE}")
message("version: ${PROJECT_VERSION}")
message("version-full: ${PROJECT_VERSION_FULL}")
message("commit: ${GIT_COMMIT}")
message("short-hash: ${GIT_SHORT_HASH}")
message("describe: ${GIT_DESCRIBE}")
message("distance: ${GIT_DISTANCE}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if (EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any director
y with a CMakeLists.txt file). Please make a build subdirectory. Feel free to re
move CMakeCache.txt and CMakeFiles.")
endif ()

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        WebEngineWidgets
        REQUIRED)

add_executable(hello-qtwebengine main.cc)

target_link_libraries(hello-qtwebengine PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::WebEngineWidgets
)

set(CUR_TARGET hello-qtwebengine)

if (APPLE)

    set_target_properties(hello-qtwebengine PROPERTIES
            MACOSX_BUNDLE ON
            MACOSX_BUNDLE_GUI_IDENTIFIER ie.turscar.${CUR_TARGET}
            MACOSX_BUNDLE_BUNDLE_NAME ${CUR_TARGET}
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION_FULL}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
            MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION_FULL}
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/MacOSXBundleInfo.plist.in
            MACOSX_BUNDLE_ICON_FILE Icon.icns
    )
    target_sources(hello-qtwebengine PRIVATE Icon.icns)
    set_source_files_properties(Icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
elseif (WIN32)
    set(ICON_FILE "${PROJECT_SOURCE_DIR}/images/abacus.ico")
    configure_file("${PROJECT_SOURCE_DIR}/windows_metafile.rc.in"
            "windows_metafile.rc"
    )
    set_target_properties(hello-qtwebengine PROPERTIES
            WIN32_EXECUTABLE ON
    )
    target_sources(hello-qtwebengine PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/windows_metafile.rc")
else ()
endif ()
