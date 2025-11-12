cmake_minimum_required(VERSION 3.10)
project(SoloPlayer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ALSA REQUIRED alsa)
pkg_check_modules(FFTW3 REQUIRED fftw3)

add_executable(main main.cpp)

# Include directories
target_include_directories(main PRIVATE
    ${ALSA_INCLUDE_DIRS}
    ${FFTW3_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(main PRIVATE
    ${ALSA_LIBRARIES}
    ${FFTW3_LIBRARIES}
    m pthread
)
