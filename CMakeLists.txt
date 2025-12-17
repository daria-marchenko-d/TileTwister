cmake_minimum_required(VERSION 3.10)
project(TileTwister VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===========================================
# CORRECT ABSOLUTE PATHS (FIXED)
# ===========================================
set(SDL2_ROOT "C:/Program Files/msys64/home/daria/libs/SDL2-2.28.5")
set(SDL2_TTF_ROOT "C:/Program Files/msys64/home/daria/libs/SDL2_ttf-2.20.2")

set(SDL2_INCLUDE_DIR "${SDL2_ROOT}/x86_64-w64-mingw32/include")
set(SDL2_TTF_INCLUDE_DIR "${SDL2_TTF_ROOT}/x86_64-w64-mingw32/include")

set(SDL2_LIB_DIR "${SDL2_ROOT}/x86_64-w64-mingw32/lib")
set(SDL2_TTF_LIB_DIR "${SDL2_TTF_ROOT}/x86_64-w64-mingw32/lib")

# ===========================================
# INCLUDE DIRECTORIES
# ===========================================
include_directories("include")
include_directories("${SDL2_INCLUDE_DIR}")
include_directories("${SDL2_TTF_INCLUDE_DIR}")

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
    "${SDL2_LIB_DIR}/libSDL2main.a"
    "${SDL2_LIB_DIR}/libSDL2.dll.a"
    "${SDL2_TTF_LIB_DIR}/libSDL2_ttf.dll.a"
    mingw32
)