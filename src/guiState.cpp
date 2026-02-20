#include <cstdint>
#include <string>
#include <vector>
#include <assert.h>
#include "guiState.h"
#include "windows/gui.h"
#include "appData/appData.h"

void GuiState::defaultSortDisplayOrder(AppData& appData){
    displayOrder.clear();

    for (const auto& [id, student] : appData.getStudentRecord()){
        displayOrder.push_back(id);
    }
}

void GuiState::defaultSortDisplayOrder(const std::unordered_map<uint16_t, Program>& programRegistry){
    programDisplayOrder.clear();

    for (const auto& [id, program] : programRegistry){
        programDisplayOrder.push_back(id);
    }
}

void GuiState::preloadPending(StudentDraft student){

studentDraft.ID = student.ID;
studentDraft.firstName = student.firstName;
studentDraft.lastName = student.lastName;
studentDraft.gender = static_cast<int>(student.gender);
studentDraft.programCode = student.programCode;
studentDraft.year = student.year;

}

void GuiState::init(){
selectedStudent = 0;
selectedCollege = 0;
selectedProgram = 0;

searchBuffer = "";
displayOrder = {}; 
currentError = ERRORSTATE::NO_ERROR;

inputBoxStrategy = NULL;
initStudentStrategies();


showCollegeRegistry = false;
showProgramRegistry = false;
showDebugWindow = false;
}

void GuiState::resetStudentDraft(){
studentDraft.ID.clear();
studentDraft.firstName.clear();
studentDraft.lastName.clear();
studentDraft.programCode.clear();
studentDraft.year = 0;
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

void GuiState::initStudentStrategies(){
dataTableStrategy = drawStudentDataTable;
addEntryStrategy = drawAddStudentBox;
editEntryStrategy = drawEditStudentBox;
deleteEntryStrategy = drawDeleteStudentBox;
}

void GuiState::initProgramStrategies(){
dataTableStrategy = drawProgramDataTable;
addEntryStrategy = drawAddProgramBox;
editEntryStrategy = drawEditProgramBox;
deleteEntryStrategy = drawDeleteProgramBox;
}

void GuiState::initCollegeStrategies(){
dataTableStrategy = drawCollegeDataTable;
addEntryStrategy = drawAddCollegeBox;
editEntryStrategy = drawEditCollegeBox;
deleteEntryStrategy = drawDeleteCollegeBox;
}
