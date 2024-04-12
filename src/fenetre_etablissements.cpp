#include <fenetre_etablissements.h>
#include <etablissements.h>

#include "imgui.h"

namespace Crechendo {
    void fenetreEtablissements()
    {
        Etablissements & etablissements = Etablissements::getInstance();
        ImGui::Begin("Établissements", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        std::vector<std::string> listeEtablissements = etablissements.listeEtablissements();

        ImGui::BeginGroup();
        for (std::string const etablissement : listeEtablissements)
        {
            ImGui::Button(etablissement.c_str(), ImVec2(120, 120));
            if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
            {
                if (ImGui::Selectable("Supprimer"))
                    etablissements.supprimerEtablissement(etablissement);
                if (ImGui::Button("Close"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }
            ImGui::SameLine();
        }
        if (ImGui::Button("+", ImVec2(120, 120)))
        {
            ImGui::OpenPopup("Nouvel établissement");
        }
        ImGui::SetItemTooltip("Ajouter un nouvel établissement");
        ImGui::EndGroup();
        if (ImGui::BeginPopupModal("Nouvel établissement", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Information");
            static char nom[32] = "";
            ImGui::InputText("Nom de l'établissement", nom, 32);
            static char adresse1[32] = "";
            ImGui::InputText("Adresse", adresse1, 32);
            static char adresse2[32] = "";
            ImGui::InputText("Complément d'adresse", adresse2, 32);
            static char cp[32] = "";
            ImGui::InputText("Code postal", cp, 32);
            static char ville[32] = "";
            ImGui::InputText("Ville", ville, 32);
            ImGui::Separator();
            if (ImGui::Button("OK", ImVec2(120, 0)))
            {
                etablissements.creerEtablissement(nom, adresse1, adresse2, cp, ville);
                nom[0] = '\0';
                adresse1[0] = '\0';
                adresse2[0] = '\0';
                cp[0] = '\0';
                ville[0] = '\0';
                ImGui::CloseCurrentPopup();
            }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::End();
    }
};
