#include "../guiState.h"
#include "gui.h"

#include "../include/imgui.h"
#include "../include/imgui_stdlib.h"

#include "../appData/appData.h"

void drawMenuBar(GuiState& guiState){
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Database"))
            {
                ImGui::Checkbox("Show College Registry", &guiState.showCollegeRegistry);
                ImGui::Checkbox("Show Program Registry", &guiState.showCourseRegistry);
                if (ImGui::MenuItem("Exit")) {}

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Entries"))
            {
                if(ImGui::MenuItem("Add Entry")){}
                if(ImGui::MenuItem("Edit Entry")){}
                if(ImGui::MenuItem("Delete Entry")){}

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }


}

std::string serializeGender(Gender gender){
    switch(gender){
        case Gender::Male: return "Male";
        case Gender::Female: return "Female";
        case Gender::Other: return "Other";
    }
    return "N/A";
}


void drawStudentDataTable(GuiState& guiState, const AppData& appdata){
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

            
        for(int i = 0; i < guiState.displayOrder.size(); i++){
            int studentIndex = guiState.displayOrder[i];
            const Student& student = appdata.studentRecord[studentIndex]; 

            ImGui::TableNextRow();
            bool isSelected = (guiState.selectedStudent == studentIndex);

            ImGui::TableNextColumn();
            if (ImGui::Selectable(student.ID.c_str(),
                           isSelected,
                           ImGuiSelectableFlags_SpanAllColumns))
            {
                guiState.selectedStudent = studentIndex;
            }
            
            //ImGui::TableNextColumn();
            //ImGui::Text("%s", appdata.studentRecord[guiState.displayOrder[i]].ID.c_str());

            
            ImGui::TableNextColumn();
            ImGui::Text("%s", appdata.studentRecord[guiState.displayOrder[i]].firstName.c_str());

                
            ImGui::TableNextColumn();
            ImGui::Text("%s", appdata.studentRecord[guiState.displayOrder[i]].lastName.c_str());

                
            ImGui::TableNextColumn();
            ImGui::Text("%s", appdata.courseRegistry.at(appdata.studentRecord[guiState.displayOrder[i]].courseID).courseAbbreviation.c_str());

                
            ImGui::TableNextColumn();
            ImGui::Text("%s", appdata.collegeRegistry[appdata.courseRegistry.at(appdata.studentRecord[guiState.displayOrder[i]].courseID).collegeID].collegeAbreviation.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%d", appdata.studentRecord[guiState.displayOrder[i]].year);


            ImGui::TableNextColumn();
            ImGui::Text("%s", serializeGender(appdata.studentRecord[guiState.displayOrder[i]].gender).c_str());
        }


        ImGui::EndTable();
    }
    ImGui::End();

}

void drawTaskBar(GuiState& guiState){
        ImGui::Begin("taskbar", NULL, ImGuiWindowFlags_NoTitleBar);
        ImGui::InputText("Search", &guiState.searchBuffer);
        ImGui::End();
}

void drawEntryDisplay(const GuiState& guiState, const AppData& appData){
        ImGui::Begin("Entry Display");
        if(guiState.selectedStudent > -1){
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("ID: %s", appData.studentRecord[guiState.selectedStudent].ID.c_str());
        ImGui::Text("Name: %s %s", appData.studentRecord[guiState.selectedStudent].firstName.c_str(), appData.studentRecord[guiState.selectedStudent].lastName.c_str());
        ImGui::Text("Program: %s", appData.courseRegistry.at(appData.studentRecord[guiState.selectedStudent].courseID).courseName.c_str());
        ImGui::SetWindowFontScale(1.0f);
        }
        ImGui::End();
}

void drawCollegeRegistry(AppData& appData){
{
    ImGui::Begin("College Registry");
    if (ImGui::BeginTable("CollegeTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("College Name");
        ImGui::TableSetupColumn("Abbreviation");
        ImGui::TableHeadersRow();

        for (const College& college : appData.collegeRegistry)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%u", college.collegeID);

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", college.collegeName.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", college.collegeAbreviation.c_str());
        }

        ImGui::EndTable();
    }
    ImGui::End();
}

}

void drawCourseRegistry(AppData &appData){
    ImGui::Begin("Course Registry");
    if (ImGui::BeginTable("CollegeTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Program ID");
        ImGui::TableSetupColumn("College");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Abbreviation");
        ImGui::TableHeadersRow();

        for(int i = 0; i < appData.courseRegistry.size(); i++)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%u", appData.courseRegistry.at(i).courseID);

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", appData.collegeRegistry[appData.courseRegistry.at(i).collegeID].collegeName.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", appData.courseRegistry.at(i).courseName.c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%s", appData.courseRegistry.at(i).courseAbbreviation.c_str());
        }

        ImGui::EndTable();
    }
    ImGui::End();
}

