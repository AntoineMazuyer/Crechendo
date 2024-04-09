cmake_minimum_required(VERSION 3.10)

project(Crechendo)

# Déclaration des fichiers sources
file(GLOB SOURCES "src/*.cpp")

# Déclaration des fichiers d'en-tête
include_directories("src")
include_directories("tpls")

# Configuration sqlite
set(SQLITE3_SOURCE_DIR "${CMAKE_SOURCE_DIR}/tpls/sqlite")

add_library(sqlite3 "${SQLITE3_SOURCE_DIR}/sqlite3.c")


# Configuration de l'exécutable
add_executable(crechendo ${SOURCES})

# Liens avec les bibliothèques tierces
target_link_libraries(crechendo PRIVATE sqlite)