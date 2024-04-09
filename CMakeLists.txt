cmake_minimum_required(VERSION 3.10)

project(Crechendo)

# Déclaration des fichiers sources
file(GLOB SOURCES "src/*.cpp")

# Déclaration des fichiers d'en-tête
include_directories("src")

# Ajout des sous-projets
add_subdirectory(tpls/imgui)
add_subdirectory(tpls/sqlite)

# Configuration de l'exécutable
add_executable(crechendo ${SOURCES})

# Liens avec les bibliothèques tierces
target_link_libraries(crechendo PRIVATE imgui sqlite)