#include "../guiState.h"
#include "gui.h"

#include "../include/imgui.h"
#include "../include/imgui_stdlib.h"

#include "../appData/appData.h"
#include "../vault/vault.h"


void drawMenuBar(GuiState& guiState, AppData& appData, Vault& vault){
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Database"))
        {
            if(ImGui::MenuItem("Save File")){
                vault.saveStudents(appData.getStudentRecord());
            }
            ImGui::Checkbox("Show College Registry", &guiState.showCollegeRegistry);
            ImGui::Checkbox("Show Program Registry", &guiState.showCourseRegistry);
            if (ImGui::MenuItem("Exit")) {}

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Entries"))
        {
            ImGui::Text("Student");
            ImGui::Separator();
            if(ImGui::MenuItem("Add Entry")){
                guiState.resetStudentDraft();
                guiState.inputBoxStrategy = drawAddStudentBox;
            }

            if(ImGui::MenuItem("Edit Entry")){
                guiState.preloadPending(appData.getStudent(guiState.selectedStudent),appData);
                guiState.inputBoxStrategy = drawEditStudentBox;
            }

            if(ImGui::MenuItem("Delete Entry")){guiState.inputBoxStrategy = drawDeleteStudentBox;}

            ImGui::Text("Program");
            ImGui::Separator();
            if(ImGui::MenuItem("Add Program")){} 
            if(ImGui::MenuItem("Edit Program")){} 
            if(ImGui::MenuItem("Delete Program")){}  

            ImGui::Text("College");
            ImGui::Separator();
            if(ImGui::MenuItem("Add College")){} 
            if(ImGui::MenuItem("Edit College")){} 
            if(ImGui::MenuItem("Delete College")){} 

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

void drawTaskBar(GuiState& guiState){
    ImGui::Begin("taskbar", NULL, ImGuiWindowFlags_NoTitleBar);
    ImGui::InputText("Search", &guiState.searchBuffer);
    ImGui::End();
}

void drawEntryDisplay(const GuiState& guiState, AppData& appData){
    const Student& student = appData.getStudent(guiState.selectedStudent);

    ImGui::Begin("Entry Display");
    if(guiState.selectedStudent > 0){
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("ID: %s", student.ID.c_str());
        ImGui::Text("Name: %s %s", student.firstName.c_str(), student.lastName.c_str());
        ImGui::Text("Program: %s", appData.getCourse(appData.getStudent(guiState.selectedStudent).courseID).courseName.c_str());
        ImGui::Text("College: %s", appData.getCollege(appData.getCourse(appData.getStudent(guiState.selectedStudent).courseID).collegeID).collegeName.c_str());
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

            for (const auto& pair : appData.getCollegeRegistry())
            {
                const auto& id = pair.first;
                const auto& college = pair.second;

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

        for(const auto& pair : appData.getCourseRegistry())
        {
            const auto& id = pair.first;
            const auto& course = pair.second;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%u", course.courseID);

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", appData.getCollege(course.collegeID).collegeName.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", course.courseName.c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%s", course.courseAbbreviation.c_str());
        }

        ImGui::EndTable();
    }
    ImGui::End();
}

void drawErrorBox(GuiState &guiState){
    ImGui::Begin("Error");
    ImGui::Text("%s", guiState.errorMessage.c_str());

    ImVec2 buttonSize = ImVec2(90, 0); 

    ImVec2 windowSize = ImGui::GetWindowSize();

    float padding = 10.0f;
    ImVec2 pos = ImVec2(
            windowSize.x - buttonSize.x - padding,
            windowSize.y - ImGui::GetFrameHeight() - padding
            );

    ImGui::SetCursorPos(pos);

    if (ImGui::Button("Close", buttonSize))
    {
        guiState.currentError = ERRORSTATE::NO_ERROR;
        guiState.updateErrorMessage();
        ImGui::CloseCurrentPopup();
    }

    pos = ImVec2(
            windowSize.x - buttonSize.x * 2 - padding * 2,
            windowSize.y - ImGui::GetFrameHeight() - padding
            );
    ImGui::End();
}

void drawCourseToID(AppData &appData){
    ImGui::Begin("CourseCodeToID");
    if (ImGui::BeginTable("fa", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Abbreviation");
        ImGui::TableSetupColumn("ID");
        ImGui::TableHeadersRow();

        for(const auto& pair : appData.getcourseCodeToID())
        {
            const auto& course = pair.first;
            const auto& id = pair.second;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", course.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%u", id);

        }

        ImGui::EndTable();
    }
    ImGui::End();

}

void drawCollegeToID(AppData &appData){
    ImGui::Begin("CollegeCodeToID");
    if (ImGui::BeginTable("fa", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Abbreviation");
        ImGui::TableSetupColumn("ID");
        ImGui::TableHeadersRow();

        for(const auto& pair : appData.getcollegeCodeToID())
        {
            const auto& course = pair.first;
            const auto& id = pair.second;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", course.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%u", id);

        }

        ImGui::EndTable();
    }
    ImGui::End();

}
