#include "../guiState.h"
#include "gui.h"
#include "../include/imgui.h"
#include "../include/imgui_stdlib.h"
#include "../appData/appData.h"

void drawEditStudentBox(GuiState &guiState, AppData &appData){
    ImGui::Begin("Modify Entry");
    ImGui::Text("Edit Student");
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
        ImGui::Text("ID:");

        ImGui::TableSetColumnIndex(1);
        ImGui::BeginDisabled();
        ImGui::InputText("##ID",
                &guiState.studentDraft.ID, ImGuiInputTextFlags_ReadOnly);
        ImGui::EndDisabled();

        // First Name
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("First Name:");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##FirstName",
                &guiState.studentDraft.firstName);

        // Last Name
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Last Name:");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##LastName",
                &guiState.studentDraft.lastName);

        // Course
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Course:");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##Course",
                &guiState.studentDraft.programCode);

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Year:");

        ImGui::TableSetColumnIndex(1);
        ImGui::InputInt("##Year", &guiState.studentDraft.year, 1, 6);

        // Gender
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Gender:");

        ImGui::TableSetColumnIndex(1);
        ImGui::Combo("##Gender",
                (int*)&guiState.studentDraft.gender,
                genderItems,
                IM_ARRAYSIZE(genderItems));

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
            guiState.currentError = appData.editStudentEntry(guiState.studentDraft, guiState.selectedStudent);
            if(guiState.currentError == ERRORSTATE::NO_ERROR){
            guiState.resetStudentDraft();
            }
        }


        ImGui::End();


    }

}
