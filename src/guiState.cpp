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

void GuiState::updateErrorMessage(){
    {
        switch (currentError) {
            case ERRORSTATE::NO_ERROR:
                errorMessage = "No Errors but you shouldn't be seeing this message";
                break;

            case ERRORSTATE::INVALID_NAME:
                errorMessage = "Invalid Name. Cannot contain Numbers or Special Characters";
                break;

            case ERRORSTATE::INVALID_STUDENT_ID:
                errorMessage = "Invalid ID format. Follow XXXX-XXXX where X are digits";
                break;

            case ERRORSTATE::INVALID_YEAR:
                errorMessage = "Invalid Year. Cannot Be Negative";
                break;

            case ERRORSTATE::INVALID_COURSE:
                errorMessage = "Invalid Course. Refer to Program Registry for Codes";
                break;

            case ERRORSTATE::INVALID_INDEX:
                errorMessage = "Select an entry before you edit";
                break;

            case ERRORSTATE::STUDENT_ID_IN_USE:
                errorMessage = "There is another student using this id";
                break;

            case ERRORSTATE::PROGRAM_IN_USE:
                errorMessage = "There is at least one student in this program. Edit that student or delete it";
                break;

            case ERRORSTATE::COLLEGE_IN_USE:
                errorMessage = "There is at lease one program in this college. Edit that program or delete it";
                break;
        }

    }

}

void GuiState::preloadPending(Student student, AppData& appData){
studentDraft.ID = student.ID;
studentDraft.firstName = student.firstName;
studentDraft.lastName = student.lastName;
studentDraft.gender = static_cast<int>(student.gender);
studentDraft.programCode = appData.getProgram(student.programID).programAbbreviation; 
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
