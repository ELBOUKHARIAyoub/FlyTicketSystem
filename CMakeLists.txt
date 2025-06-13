cmake_minimum_required(VERSION 3.14)
project(FlyTicketSystem)

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0074 NEW)

set(SFML_ROOT "C:/SFML")  # Adjust to your correct SFML version path
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(FlyTicketSystem main.cpp
        User.h
        User.cpp
        UserManager.h
        UserManager.cpp
        InputBox.h
        InputBox.cpp
        AdminPanel.h
        AdminPanel.cpp
        Flight.h
        FlightManager.h
        FlightManager.cpp
        UserPanel.h
        UserPanel.cpp
        utils.h
        utils.cpp
)

target_link_libraries(FlyTicketSystem
        sfml-graphics
        sfml-window
        sfml-system
)
