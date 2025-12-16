cmake_minimum_required(VERSION 3.10)
project(SFMLTest VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Chemin SFML MinGW64
set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")

# Inclure dossier include
include_directories("include")

# Tous les fichiers source
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Exécutable normal (pas WIN32)
add_executable(SFMLDoc ${SOURCES})


# Lien SFML (dynamique)
find_package(SFML 3 COMPONENTS System Window Graphics Audio Network REQUIRED)
target_link_libraries(SFMLDoc PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)