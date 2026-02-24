#include "gui.h"
#include "../guiState/guiState.h"
#include <imgui.h>
#include "../appData/appData.h"

void drawStudentEntryDisplay(const GuiState& guiState, AppData& appData){
    const Student& student = appData.getStudent(guiState.selectedStudent);

    ImGui::Begin("Entry Display");
    if(appData.checkStudentIDValidity(guiState.selectedStudent)){
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("ID: %s", student.ID.c_str());
        ImGui::Text("Name: %s %s", student.firstName.c_str(), student.lastName.c_str());
        ImGui::Text("Program: %s", appData.getProgram(appData.getStudent(guiState.selectedStudent).programID).programName.c_str());
        ImGui::Text("College: %s", appData.getCollege(appData.getProgram(appData.getStudent(guiState.selectedStudent).programID).collegeID).collegeName.c_str());
        ImGui::Text("Year: %d", appData.getStudent(guiState.selectedStudent).year);
        ImGui::Text("Gender: %s",(serializeGender(appData.getStudent(guiState.selectedStudent).gender).c_str()));
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void drawProgramEntryDisplay(const GuiState& guiState, AppData& appData){
    const Program& p = appData.getProgram(guiState.selectedProgram);
    const College& c = appData.getCollege(p.collegeID);

    ImGui::Begin("Entry Display");
    if(appData.checkProgramIDValidity(guiState.selectedProgram)){
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Program Code: %s", p.programAbbreviation.c_str());
        ImGui::Text("Program Name: %s", p.programName.c_str());
        ImGui::Text("College: %s", c.collegeName.c_str());
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}
void drawCollegeEntryDisplay(const GuiState& guiState, AppData& appData){
    const College& c = appData.getCollege(guiState.selectedCollege);

    ImGui::Begin("Entry Display");
    if(appData.checkCollegeIDValidity(guiState.selectedCollege)){
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("College Code: %s", c.collegeAbbreviation.c_str());
        ImGui::Text("College Name: %s", c.collegeName.c_str());
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

