#include <cstdint>
#include <string>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "guiState.h"
#include "../windows/gui.h"
#include "../appData/appData.h"
#include "guiStateStrategies.h"
#include <imgui.h>

uint32_t GuiState::getSelectedStudent() const{return selectedStudent;};
uint32_t GuiState::getSelectedProgram() const{return selectedProgram;};
uint32_t GuiState::getSelectedCollege() const{return selectedCollege;};


void GuiState::refreshDisplayOrder(const std::unordered_map<uint32_t, Student>& studentRecord){
    displayOrder.clear();

    for (const auto& [id, student] : studentRecord){
        displayOrder.push_back(id);
    }
}


void GuiState::refreshDisplayOrder(const std::unordered_map<uint32_t, Program>& programRegistry){
    programDisplayOrder.clear();

    for (const auto& [id, program] : programRegistry){
        programDisplayOrder.push_back(id);
    }
}

void GuiState::refreshDisplayOrder(const std::unordered_map<uint32_t, College>& collegeRegistry){
    collegeDisplayOrder.clear();

    for (const auto& [id, college] : collegeRegistry){
        collegeDisplayOrder.push_back(id);
    }

};

void GuiState::preloadPendingCollege(uint32_t id, AppData& appData){
    collegeDraft = appData.makeCollegeDraft(id);
}

void GuiState::preloadPendingStudent(uint32_t id, AppData& appData){
    studentDraft = appData.makeStudentDraft(id);
}

void GuiState::preloadPendingProgram(uint32_t id, AppData& appData){
    programDraft = appData.makeProgramDraft(id);
}


void GuiState::init(){
isDirty = false;

selectedStudent = 0;
selectedCollege = 0;
selectedProgram = 0;

resetStudentDraft();
resetProgramDraft();
resetCollegeDraft();

studentSearchField = StudentSearchField::All;
programSearchField = ProgramSearchField::All;
collegeSearchField = CollegeSearchField::All;


searchBuffer = "";
displayOrder = {}; 

currentError = ERRORSTATE::NO_ERROR;
currentInputBox = NULL;
currentStrategy = &studentStrategy;

showCollegeRegistry = false;
showProgramRegistry = false;
showDebugWindow = false;
}

void GuiState::resetStudentDraft(){
studentDraft.ID.clear();
studentDraft.firstName.clear();
studentDraft.lastName.clear();
studentDraft.programCode.clear();
studentDraft.year = 1;
studentDraft.gender = 2;

}

void GuiState::resetProgramDraft(){
programDraft.programAbbreviation.clear();
programDraft.programName.clear();
programDraft.collegeCode.clear();

}

void GuiState::resetCollegeDraft(){
collegeDraft.collegeCode.clear();
collegeDraft.collegeName.clear();

}


