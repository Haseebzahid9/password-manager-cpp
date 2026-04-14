# ============================================================
#  Haseeb Zahid Password Manager
#  Developed by Haseeb Zahid
#  Build file: CMakeLists.txt  (CMake)
# ============================================================

cmake_minimum_required(VERSION 3.16)
project(PasswordManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
# Fallback to Qt5 if Qt6 not found
if(NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
endif()

set(SOURCES
    main.cpp
    encryption.cpp
    password_manager.cpp
    file_handler.cpp
    login_dialog.cpp
    add_password_dialog.cpp
    main_window.cpp
)

set(HEADERS
    encryption.h
    password_manager.h
    file_handler.h
    login_dialog.h
    add_password_dialog.h
    main_window.h
)

add_executable(PasswordManager ${SOURCES} ${HEADERS})

if(Qt6_FOUND)
    target_link_libraries(PasswordManager Qt6::Core Qt6::Gui Qt6::Widgets)
else()
    target_link_libraries(PasswordManager Qt5::Core Qt5::Gui Qt5::Widgets)
endif()

if(WIN32)
    set_target_properties(PasswordManager PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
