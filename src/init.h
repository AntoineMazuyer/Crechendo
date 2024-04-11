#ifndef __CRECHENDO__INIT__
#define __CRECHENDO__INIT__

#include <sqlite3.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <etablissements.h>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

namespace Crechendo {
   int initDb(sqlite3* db);

   GLFWwindow * initGui(); 
};

#endif