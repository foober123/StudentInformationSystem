#include "gui.h"
#include "../guiState.h"
#include "../include/imgui.h"
#include "../appData/appData.h"


void drawStudentDataTable(GuiState& guiState, AppData& appdata){
    ImGui::Begin("data");
    ImVec2 tableSize = ImVec2(0.0f, ImGui::GetContentRegionAvail().y);
    if (ImGui::BeginTable("StudentsTable", 7, 
                ImGuiTableFlags_Borders |
                ImGuiTableFlags_RowBg |
                ImGuiTableFlags_ScrollY |
                ImGuiTableFlags_Sortable |
                ImGuiTableFlags_Resizable, tableSize))
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

        if (ImGuiTableSortSpecs* sortSpecs = ImGui::TableGetSortSpecs())
        {
            if (sortSpecs->SpecsDirty)
            {
                guiState.sortStudents(appdata, sortSpecs);

                sortSpecs->SpecsDirty = false;
            }
        }

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
    ImVec2 tableSize = ImVec2(0.0f, ImGui::GetContentRegionAvail().y);
    if (ImGui::BeginTable("ProgramTable", 3,
                ImGuiTableFlags_Borders |
                ImGuiTableFlags_RowBg |
                ImGuiTableFlags_ScrollY |
                ImGuiTableFlags_Sortable |
                ImGuiTableFlags_Resizable, tableSize))
    {
        ImGui::TableSetupColumn("Code");
        ImGui::TableSetupColumn("College");
        ImGui::TableSetupColumn("Name");
        ImGui::TableHeadersRow();
   
        if (ImGuiTableSortSpecs* sortSpecs = ImGui::TableGetSortSpecs())
        {
            if (sortSpecs->SpecsDirty)
            {
                guiState.sortPrograms(appData, sortSpecs);

                sortSpecs->SpecsDirty = false;
            }
        }

        for(size_t id : guiState.programDisplayOrder){
            bool isSelected = (guiState.selectedProgram == id);
            const auto& program = appData.getProgram(id);

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);

            if (ImGui::Selectable(
                        program.programAbbreviation.c_str(),
                        isSelected,
                        ImGuiSelectableFlags_SpanAllColumns))
            {
                guiState.selectedProgram = id;
            }

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", appData.getCollege(program.collegeID).collegeAbreviation.c_str());

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
