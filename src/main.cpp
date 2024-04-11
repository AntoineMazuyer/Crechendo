#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <sqlite3.h>

#include <etablissements.h>
#include <init.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

using namespace Crechendo;
// Main code
int main(int, char**)
{
    sqlite3 * db;
    int rc;
    rc = sqlite3_open("crechendo.db", &db);
    if (rc) {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    rc = initDb(db);
    if (rc != 0)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de la base de données.\n");
        sqlite3_close(db);
        return 1;
    }

    Etablissements & etablissements = Etablissements::getInstance();
    std::vector< std::string > listeEtablissements = etablissements.listeEtablissements();
    GLFWwindow * window = initGui();
    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        
        {
            // Fenêtre gérant les établissements
            static int counter = 0;

            ImGui::Begin("Établissements");

            for( std::string const etablissement : listeEtablissements ) {
                ImGui::Button(etablissement.c_str(), ImVec2(120, 0));
            }
            if (ImGui::Button("Nouvel établissement"))
                ImGui::OpenPopup("Nouvel établissement");
            if (ImGui::BeginPopupModal("Nouvel établissement", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Information");
                static char nom[32] = ""; ImGui::InputText("Nom de l'établissement", nom, 32);
                static char adresse1[32] = ""; ImGui::InputText("Adresse", adresse1, 32);
                static char adresse2[32] = ""; ImGui::InputText("Complément d'adresse", adresse2, 32);
                static char cp[32] = ""; ImGui::InputText("Code postal", cp, 32);
                static char ville[32] = ""; ImGui::InputText("Ville", ville, 32);
                ImGui::Separator();

                //static int unused_i = 0;
                //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

                static bool dont_ask_me_next_time = false;
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
                ImGui::PopStyleVar();

                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    etablissements.creerEtablissement( nom, adresse1, adresse2, cp, ville);
                    listeEtablissements = etablissements.listeEtablissements();
                    ImGui::CloseCurrentPopup(); }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                ImGui::EndPopup();
            }
            ImGui::End();
        }
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    sqlite3_close(db);
    return 0;
}
