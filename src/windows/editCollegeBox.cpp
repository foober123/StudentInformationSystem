#include "../guiState/guiState.h"
#include "gui.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include "../appData/appData.h"

void drawEditCollegeBox(GuiState &guiState, AppData &appData){
    ImGui::SetNextWindowDockID(0, ImGuiCond_Always);
    ImGui::Begin("Modify Entry", nullptr, ImGuiWindowFlags_NoDocking);
    ImGui::Text("Edit College");
    ImGui::Separator();
    if (ImGui::BeginTable("StudentForm", 2,
                ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 120.0f);
        ImGui::TableSetupColumn("Field", ImGuiTableColumnFlags_WidthStretch);

        // ID
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("College Code:");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##CollegeCode",
                &guiState.collegeDraft.collegeCode, ImGuiInputTextFlags_CharsUppercase);

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("College Name:");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##ProgramName",
                &guiState.collegeDraft.collegeName);



        ImGui::EndTable();



        ImVec2 buttonSize = ImVec2(120, 0); 

        ImVec2 windowSize = ImGui::GetWindowSize();

        float padding = 10.0f;
        ImVec2 pos = ImVec2(
                windowSize.x - buttonSize.x - padding,
                windowSize.y - ImGui::GetFrameHeight() - padding
                );

        ImGui::SetCursorPos(pos);

        if (ImGui::Button("Cancel", buttonSize))
        {
            guiState.currentInputBox = NULL;
        }

        pos = ImVec2(
                windowSize.x - buttonSize.x * 2 - padding * 2,
                windowSize.y - ImGui::GetFrameHeight() - padding
                );

        ImGui::SetCursorPos(pos);

        if (ImGui::Button("Confirm", buttonSize))
        {
            guiState.currentError = appData.editCollegeEntry(guiState.collegeDraft, guiState.selectedCollege);
            if(guiState.currentError == ERRORSTATE::NO_ERROR){ 
                guiState.resetCollegeDraft();
                guiState.isDirty = true;
            }
        }


        ImGui::End();


    }

}
