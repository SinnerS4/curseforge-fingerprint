cmake_minimum_required(VERSION 3.26)
project(curseforge_fingerprint)

set(CMAKE_CXX_STANDARD 17)
set(Boost_NO_WARN_NEW_VERSIONS 1)

# Find Boost
find_package(Boost REQUIRED COMPONENTS iostreams)

add_executable(
    curseforge_fingerprint
    main.cpp
    ogfingerprint.cpp
    fingerprint.cpp
)

target_link_libraries(curseforge_fingerprint Boost::iostreams)