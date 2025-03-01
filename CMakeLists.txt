cmake_minimum_required(VERSION 3.29)
project(COMP345project)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "/path/to/your/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(COMP345project main.cpp
        Critter.cpp
        Critter.h
        CritterGroupGenerator.cpp
        CritterGroupGenerator.h
        Observable.cpp
        Observable.h
        Observer.h
        CritterObserver.cpp
        CritterObserver.h
        CritterGroup.cpp
        CritterGroup.h
        CritterGroupObserver.cpp
        CritterGroupObserver.h)

# Link SFML libraries
target_link_libraries(COMP345project sfml-graphics sfml-window sfml-system)
