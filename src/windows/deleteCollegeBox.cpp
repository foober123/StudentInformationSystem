#include "../guiState/guiState.h"
#include "gui.h"
#include <imgui.h>
#include "../appData/appData.h"

void drawDeleteCollegeBox(GuiState & guiState, AppData & appData){
    ImGui::SetNextWindowDockID(0, ImGuiCond_Always);
    ImGui::Begin("Modify Entry", nullptr, ImGuiWindowFlags_NoDocking);
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
        guiState.currentInputBox = NULL;
    }

    pos = ImVec2(
            windowSize.x - buttonSize.x * 2 - padding * 2,
            windowSize.y - ImGui::GetFrameHeight() - padding
            );

    ImGui::SetCursorPos(pos);

    if (ImGui::Button("Confirm", buttonSize))
    {
        guiState.currentError = appData.deleteCollege(guiState.selectedCollege);
        if(guiState.currentError == ERRORSTATE::NO_ERROR){
        guiState.refreshDisplayOrder(appData.getCollegeRegistry());
        guiState.currentInputBox = NULL;
        guiState.selectedCollege = 0;
        }
    }


    ImGui::End();

}
