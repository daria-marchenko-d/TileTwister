cmake_minimum_required(VERSION 3.10)
project(TileTwister VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===========================================
# SDL3 PATHS (UPDATED STRUCTURE)
# ===========================================
set(SDL3_ROOT "C:/Program Files/msys64/home/daria/libs/SDL3-devel-3.2.2-mingw/SDL3-3.2.2")
set(SDL3_TTF_ROOT "C:/Program Files/msys64/home/daria/libs/SDL3_ttf-devel-3.2.2-mingw/SDL3_ttf-3.2.2")

set(SDL3_INCLUDE_DIR "${SDL3_ROOT}/x86_64-w64-mingw32/include")
set(SDL3_TTF_INCLUDE_DIR "${SDL3_TTF_ROOT}/x86_64-w64-mingw32/include")

set(SDL3_LIB_DIR "${SDL3_ROOT}/x86_64-w64-mingw32/lib")
set(SDL3_TTF_LIB_DIR "${SDL3_TTF_ROOT}/x86_64-w64-mingw32/lib")

# ===========================================
# INCLUDE DIRECTORIES
# ===========================================
include_directories("include")
include_directories("${SDL3_INCLUDE_DIR}")
include_directories("${SDL3_TTF_INCLUDE_DIR}")

# ===========================================
# SOURCE FILES
# ===========================================
file(GLOB_RECURSE SOURCES "src/*.cpp")

# ===========================================
# CREATE EXECUTABLE
# ===========================================
add_executable(TileTwister ${SOURCES})

# ===========================================
# LINK LIBRARIES
# ===========================================
target_link_libraries(TileTwister
    "${SDL3_LIB_DIR}/libSDL3.dll.a"
    "${SDL3_TTF_LIB_DIR}/libSDL3_ttf.dll.a"
    mingw32
)