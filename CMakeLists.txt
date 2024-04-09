cmake_minimum_required(VERSION 3.10)

project(Crechendo)

# Déclaration des fichiers sources
file(GLOB SOURCES "src/*.cpp")

# Déclaration des fichiers d'en-tête
include_directories("src")

# Configuration sqlite
include_directories("tpls/sqlite")
set(SQLITE3_SOURCE_DIR "${CMAKE_SOURCE_DIR}/tpls/sqlite")
add_library(sqlite3 SHARED "${SQLITE3_SOURCE_DIR}/sqlite3.c")

# Configuration imgui
include_directories("tpls/imgui")
include_directories("tpls/imgui/backends")
set(IMGUI_SOURCE_DIR "${CMAKE_SOURCE_DIR}/tpls/imgui")
file(GLOB IMGUI_SOURCES "${IMGUI_SOURCE_DIR}/*.cpp")
set(IMGUI_BACKEND ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp)
add_library(imgui SHARED ${IMGUI_SOURCES} ${IMGUI_BACKEND})


# Configuration de l'exécutable
add_executable(crechendo ${SOURCES})

# Liens avec les bibliothèques tierces
target_link_libraries(crechendo PRIVATE sqlite3 imgui glfw GL)