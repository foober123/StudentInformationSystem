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

dataTableStrategy = drawStudentDataTable;
inputBoxStrategy = NULL;

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
