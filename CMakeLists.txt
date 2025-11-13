cmake_minimum_required(VERSION 3.10)
project(SoloPlayer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(ALSA REQUIRED alsa)
pkg_check_modules(FFTW3 REQUIRED fftw3)
pkg_check_modules(SDL2 REQUIRED sdl2)

add_executable(main main.cpp)

# Include directories
target_include_directories(main PRIVATE
    ${ALSA_INCLUDE_DIRS}
    ${FFTW3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
)

# Compile flags (important for SDL2)
target_compile_options(main PRIVATE
    ${ALSA_CFLAGS_OTHER}
    ${FFTW3_CFLAGS_OTHER}
    ${SDL2_CFLAGS_OTHER}
)

# Link libraries
target_link_libraries(main PRIVATE
    ${ALSA_LIBRARIES}
    ${FFTW3_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_LDFLAGS}   # << Add this line to fix SDL2 linker errors
    m pthread
)

