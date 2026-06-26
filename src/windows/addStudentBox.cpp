#include "../guiState/guiState.h"
#include "gui.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include "../appData/appData.h"
#include "../imguiSpecialCallbacks/callbacks.h"

void drawAddStudentBox(GuiState &guiState, AppData &appData){
    ImGui::SetNextWindowDockID(0, ImGuiCond_Always);
    ImGui::Begin("Modify Entry", nullptr, ImGuiWindowFlags_NoDocking);
 
    ImGui::Text("Add Student");
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
        ImGui::InputText("##ID",
                &guiState.studentDraft.ID, ImGuiInputTextFlags_CharsDecimal);

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
        ImGui::Text("Program Code:");

        ImGui::TableSetColumnIndex(1);
        /*
        ImGui::InputText("##ProgramCode",
                &guiState.studentDraft.programCode, ImGuiInputTextFlags_CallbackCharFilter, LetterAndDashCallback);
        */

        /*
        if (ImGui::BeginCombo("##ProgramCode", (guiState.studentDraft.programCode).c_str()))
        {
            for (auto program : appData.getProgramRegistry())
            {
                auto& programInternalID = program.first;
                auto& programStruct = program.second;

                bool isSelected = (guiState.studentDraft.programCode == programStruct.programAbbreviation);
                if (ImGui::Selectable(programStruct.programAbbreviation.c_str(), isSelected))
                {
                    guiState.studentDraft.programCode = programStruct.programAbbreviation;
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        */
      static std::string searchText;

        if (ImGui::BeginCombo("##Program Code", guiState.studentDraft.programCode.c_str()))
        {
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::InputTextWithHint(
                "##SearchProgram",
                "Search...",
                &searchText
            );

            ImGui::Separator();

            for (const auto& [programInternalID, programStruct] : appData.getProgramRegistry())
            {
                const std::string& abbreviation = programStruct.programAbbreviation;

                // Filter
                if (!searchText.empty())
                {
                    if (abbreviation.find(searchText) == std::string::npos)
                        continue;
                }

                bool isSelected = (guiState.studentDraft.programCode == abbreviation);

                if (ImGui::Selectable(abbreviation.c_str(), isSelected))
                {
                    guiState.studentDraft.programCode = abbreviation;
                    searchText.clear(); // Optional: clear after selecting
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }

        

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Year:");

        ImGui::TableSetColumnIndex(1);

        int currentIndex = guiState.studentDraft.year - 1;

        if (ImGui::BeginCombo("##Year", std::to_string(guiState.studentDraft.year).c_str()))
        {
            for (int i = 1; i <= 5; i++)
            {
                bool isSelected = (guiState.studentDraft.year == i);
                if (ImGui::Selectable(std::to_string(i).c_str(), isSelected))
                {
                    guiState.studentDraft.year = i;
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        
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
            guiState.currentInputBox = NULL;
        }

        pos = ImVec2(
                windowSize.x - buttonSize.x * 2 - padding * 2,
                windowSize.y - ImGui::GetFrameHeight() - padding
                );

        ImGui::SetCursorPos(pos);

        if (ImGui::Button("Confirm", buttonSize))
        {
            guiState.currentError = appData.addStudentEntry(guiState.studentDraft);
            if(guiState.currentError == ERRORSTATE::NO_ERROR){
            guiState.isDirty = true;
            guiState.resetStudentDraft();
            guiState.refreshDisplayOrder(appData.getStudentRecord());
            }
        }


        ImGui::End();


    }

}
