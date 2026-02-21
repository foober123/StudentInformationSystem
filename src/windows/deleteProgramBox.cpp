#include "../guiState.h"
#include "gui.h"
#include <imgui.h>
#include "../appData/appData.h"

void drawDeleteProgramBox(GuiState & guiState, AppData & appData){
    ImGui::Begin("Delete Entry");
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
        guiState.currentError = appData.deleteProgramEntry(guiState.selectedProgram);
        guiState.currentInputBox = NULL;
        guiState.selectedProgram = 0;
        guiState.refreshDisplayOrder(appData.getProgramRegistry());
    }


    ImGui::End();

}
