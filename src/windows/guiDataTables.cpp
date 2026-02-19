#include "gui.h"
#include "../guiState.h"
#include "../include/imgui.h"
#include "../appData/appData.h"

void drawStudentDataTable(GuiState& guiState, AppData& appdata){
    ImGui::Begin("data");
    if (ImGui::BeginTable("StudentsTable", 7,     ImGuiTableFlags_Borders |
                ImGuiTableFlags_RowBg |
                ImGuiTableFlags_ScrollY |
                ImGuiTableFlags_Resizable))
    {
        // Setup columns
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("First Name");
        ImGui::TableSetupColumn("Last Name");
        ImGui::TableSetupColumn("Program");
        ImGui::TableSetupColumn("College");
        ImGui::TableSetupColumn("Year");
        ImGui::TableSetupColumn("Gender");
        ImGui::TableHeadersRow();


        for (size_t i = 0; i < guiState.displayOrder.size(); i++)
        {
            uint32_t studentID = guiState.displayOrder[i];
            const Student& student = appdata.getStudent(studentID);

            ImGui::TableNextRow();

            bool isSelected = (guiState.selectedStudent == studentID);

            ImGui::TableNextColumn();
            if (ImGui::Selectable(student.ID.c_str(),
                        isSelected,
                        ImGuiSelectableFlags_SpanAllColumns))
            {
                guiState.selectedStudent = studentID;
            }

            ImGui::TableNextColumn();
            ImGui::Text("%s", student.firstName.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%s", student.lastName.c_str());

            const Program& program = appdata.getProgram(student.programID);

            ImGui::TableNextColumn();
            ImGui::Text("%s", program.programAbbreviation.c_str());

            const College& college = appdata.getCollege(program.collegeID);

            ImGui::TableNextColumn();
            ImGui::Text("%s", college.collegeAbreviation.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%d", student.year);

            ImGui::TableNextColumn();
            ImGui::Text("%s", serializeGender(student.gender).c_str());
        }


        ImGui::EndTable();
    }
    ImGui::End();
}

void drawProgramDataTable(GuiState &guiState, AppData &appData){
    ImGui::Begin("data");
    if (ImGui::BeginTable("CollegeTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Code");
        ImGui::TableSetupColumn("College");
        ImGui::TableSetupColumn("Name");
        ImGui::TableHeadersRow();

        for(const auto& [id, program] : appData.getProgramRegistry())
        {

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", program.programAbbreviation.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", appData.getCollege(program.collegeID).collegeName.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", program.programName.c_str());

        }

        ImGui::EndTable();
    }
    ImGui::End();
}

void drawCollegeDataTable(GuiState &guiState, AppData &appData){
    ImGui::Begin("data");
    if (ImGui::BeginTable("CollegeTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("College Code");
        ImGui::TableSetupColumn("Name");
        ImGui::TableHeadersRow();


        for (const auto& [id, college] : appData.getCollegeRegistry())
        {
            bool isSelected = (guiState.selectedCollege == id);

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);

            if (ImGui::Selectable(
                        college.collegeAbreviation.c_str(),
                        isSelected,
                        ImGuiSelectableFlags_SpanAllColumns))
            {
                guiState.selectedCollege = id;
            }

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", college.collegeName.c_str());
        }


        ImGui::EndTable();
    }
    ImGui::End();

}
