#include "../guiState.h"
#include "gui.h"
#include "../include/imgui.h"
#include "../include/imgui_stdlib.h"
#include "../appData/appData.h"

void drawEditProgramBox(GuiState &guiState, AppData &appData){
    ImGui::Begin("Modify Entry");
    ImGui::Text("Edit Program");
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
        ImGui::Text("Program Code:");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##ProgramCode",
                &guiState.programDraft.programAbbreviation);

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Program Name");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##ProgramName",
                &guiState.programDraft.programName);

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("College Code:");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##CollegeCode",
                &guiState.programDraft.collegeCode);


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
            guiState.inputBoxStrategy = NULL;
        }

        pos = ImVec2(
                windowSize.x - buttonSize.x * 2 - padding * 2,
                windowSize.y - ImGui::GetFrameHeight() - padding
                );

        ImGui::SetCursorPos(pos);

        if (ImGui::Button("Confirm", buttonSize))
        {
            guiState.currentError = appData.editProgramEntry(guiState.programDraft, guiState.selectedProgram);
            if(guiState.currentError == ERRORSTATE::NO_ERROR){
            guiState.resetProgramDraft();
            guiState.defaultSortDisplayOrder(appData.getProgramRegistry());            
            }
        }


        ImGui::End();


    }

}

