cmake_minimum_required(VERSION 3.16)

project(auto-penyata VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_definitions(_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
endif()

# --- Find Packages ---
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)

# --- Icon Setup ---
set(MACOSX_BUNDLE_ICON_FILE icon.icns)
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/icon.icns")
set(app_icon_windows "${CMAKE_CURRENT_SOURCE_DIR}/icon.ico")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# --- Source Files ---
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/header/mainwindow.h
    src/mainwindow.ui
    src/jsonmanager.cpp
    src/header/jsonmanager.h
    src/setting.cpp
    src/header/setting.h
    src/apur.cpp
    src/header/apur.h
    src/blockmanager.cpp
    src/header/blockmanager.h
    src/pagemanager.cpp
    src/header/pagemanager.h
    src/belanja.cpp
    src/header/belanja.h
    src/pdfgenerator.cpp
    src/header/pdfgenerator.h
    src/hasil.cpp
    src/header/hasil.h
    src/asetbukansemasa.cpp
    src/header/asetbukansemasa.h
    src/asetsemasa.cpp
    src/header/asetsemasa.h
    src/liabilitibukansemasa.cpp
    src/header/liabilitibukansemasa.h
    src/liabilitisemasa.cpp
    src/header/liabilitisemasa.h
    src/ekuitipemilik.cpp
    src/header/ekuitipemilik.h
    src/statusbar.cpp
    src/header/statusbar.h
)

# Append platform-specific icons to sources so they get compiled/bundled
if(WIN32)
    list(APPEND PROJECT_SOURCES ${app_icon_windows})
elseif(APPLE)
    list(APPEND PROJECT_SOURCES ${app_icon_macos})
endif()

# --- Target Definition ---
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(auto-penyata
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(auto-penyata SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(auto-penyata
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# --- Target Includes & Links ---
target_include_directories(auto-penyata PRIVATE src src/header)

set_target_properties(auto-penyata PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(auto-penyata PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
)

# --- Target Properties ---
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.auto-penyata)
endif()

set_target_properties(auto-penyata PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_NAME "Auto Penyata"
    OUTPUT_NAME "Auto Penyata"
    MACOSX_BUNDLE_ICON_FILE "icon.icns" 
)

# --- Installation ---
include(GNUInstallDirs)
install(TARGETS auto-penyata
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(auto-penyata)
endif()