#include "../guiState.h"
#include "gui.h"
#include "../include/imgui.h"
#include "../appData/appData.h"

void drawDeleteStudentBox(GuiState & guiState, AppData & appData){
    ImGui::Begin("Delete Student");
    ImGui::Text("Are you sure?");
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
        appData.deleteStudentEntry(guiState.selectedStudent);
        guiState.inputBoxStrategy = NULL;
        guiState.defaultSortDisplayOrder(appData);
        guiState.selectedStudent = 0;
    }


    ImGui::End();

} 
