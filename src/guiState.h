#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <assert.h>

class AppData;
struct GuiState;
enum class Gender;

typedef void (*InputBoxStrategy)(GuiState& guistate, AppData& appData);


enum class ERRORSTATE{
NO_ERROR,
INVALID_STUDENT_ID,
INVALID_NAME,
INVALID_YEAR,
INVALID_COURSE,
INVALID_INDEX
};


struct StudentDraft{
std::string ID; 
std::string firstName;
std::string lastName;
std::string courseCode;
int year = 0;
int gender = 2;

};

struct CourseDraft{
uint16_t collegeID;
std::string courseName;
std::string courseAbbreviation;
};

struct GuiState{
std::vector<size_t> displayOrder; 
uint32_t selectedStudent;
std::string searchBuffer;

StudentDraft studentDraft;
CourseDraft courseDraft;

InputBoxStrategy inputBoxStrategy;
ERRORSTATE currentError;
std::string errorMessage;

bool showCollegeRegistry;
bool showCourseRegistry;

void init(){
selectedStudent = 0;
searchBuffer = "";
displayOrder = {}; 
inputBoxStrategy = NULL;
currentError = ERRORSTATE::NO_ERROR;

showCollegeRegistry = false;
showCourseRegistry = false;
}

void resetDraft(){
studentDraft.ID.clear();
studentDraft.firstName.clear();
studentDraft.lastName.clear();
studentDraft.courseCode.clear();
studentDraft.year = 0;
studentDraft.gender = 2;

}

void defaultSortDisplayOrder(AppData&);

void updateErrorMessage(){
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

};
