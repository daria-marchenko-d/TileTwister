cmake_minimum_required(VERSION 3.20)
project(TileTwister VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===========================================
# SDL3 PATHS
# ===========================================
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/SDL3-3.2.28/x86_64-w64-mingw32")
set(SDL3_INCLUDE_DIR "${SDL3_ROOT}/include")
set(SDL3_LIB_DIR "${SDL3_ROOT}/lib")
set(SDL3_BIN_DIR "${SDL3_ROOT}/bin")

# ===========================================
# VERIFICATION DES FICHIERS SDL3
# ===========================================
if(NOT EXISTS "${SDL3_LIB_DIR}/libSDL3.dll.a")
    message(FATAL_ERROR "libSDL3.dll.a not found in ${SDL3_LIB_DIR}")
endif()

if(NOT EXISTS "${SDL3_BIN_DIR}/SDL3.dll")
    message(FATAL_ERROR "SDL3.dll not found in ${SDL3_BIN_DIR}")
endif()

message(STATUS "SDL3 include: ${SDL3_INCLUDE_DIR}")
message(STATUS "SDL3 lib: ${SDL3_LIB_DIR}/libSDL3.dll.a")
message(STATUS "SDL3 dll: ${SDL3_BIN_DIR}/SDL3.dll")

# ===========================================
# INCLUDE DIRECTORIES
# ===========================================
include_directories(include)
include_directories(${SDL3_INCLUDE_DIR})

# ===========================================
# SOURCE FILES
# ===========================================
file(GLOB_RECURSE SOURCES "src/*.cpp")

# ===========================================
# EXECUTABLE
# ===========================================
add_executable(TileTwister ${SOURCES})

# ===========================================
# SDL3 IMPORTED LIBRARY
# ===========================================
add_library(SDL3 SHARED IMPORTED)
set_target_properties(SDL3 PROPERTIES
    IMPORTED_LOCATION "${SDL3_BIN_DIR}/SDL3.dll"
    IMPORTED_IMPLIB "${SDL3_LIB_DIR}/libSDL3.dll.a"
    INTERFACE_INCLUDE_DIRECTORIES "${SDL3_INCLUDE_DIR}"
)

target_link_libraries(TileTwister PRIVATE SDL3)

# ===========================================
# COPY SDL3.DLL TO BUILD DIRECTORY
# ===========================================
configure_file(
    "${SDL3_BIN_DIR}/SDL3.dll"
    "${CMAKE_BINARY_DIR}/SDL3.dll"
    COPYONLY
)