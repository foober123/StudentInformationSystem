#include <string>
#include <vector>
#include <assert.h>
#include "guiState.h"
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
                errorMessage = "Invalid Name. Cannot Contain Numbers";
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
        }

    }

}

void GuiState::preloadPending(Student student, AppData& appData){
studentDraft.ID = student.ID;
studentDraft.firstName = student.firstName;
studentDraft.lastName = student.lastName;
studentDraft.gender = static_cast<int>(student.gender);
studentDraft.courseCode = appData.getCourse(student.courseID).courseAbbreviation; 
studentDraft.year = student.year;
}

void GuiState::init(){
selectedStudent = 0;
selectedCollege = 0;
selectedCourse = 0;

searchBuffer = "";
displayOrder = {}; 
currentError = ERRORSTATE::NO_ERROR;

dataTableStrategy = NULL;
inputBoxStrategy = NULL;

showCollegeRegistry = false;
showCourseRegistry = false;
}

void GuiState::resetStudentDraft(){
studentDraft.ID.clear();
studentDraft.firstName.clear();
studentDraft.lastName.clear();
studentDraft.courseCode.clear();
studentDraft.year = 0;
studentDraft.gender = 2;

}
