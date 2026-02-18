#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <assert.h>

class AppData;
struct GuiState;

enum class Gender;

struct Student;
struct Course; 
struct College;

enum class ERRORSTATE;

typedef void (*InputBoxStrategy)(GuiState& guistate, AppData& appData);
typedef void (*DataTableStrategy)(GuiState& guistate, AppData& appData);

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
std::string searchBuffer;
uint32_t selectedStudent;
uint16_t selectedCourse;
uint16_t selectedCollege;


StudentDraft studentDraft;
CourseDraft courseDraft;

InputBoxStrategy inputBoxStrategy;
DataTableStrategy dataTableStrategy;

ERRORSTATE currentError;
std::string errorMessage;

bool showCollegeRegistry;
bool showCourseRegistry;

void init();
void resetStudentDraft();
void defaultSortDisplayOrder(AppData&);
void updateErrorMessage();
void preloadPending(Student,AppData&);
void preloadPending(Course);
void preloadPending(College);
};

enum class ERRORSTATE{
NO_ERROR,
INVALID_STUDENT_ID,
INVALID_NAME,
INVALID_YEAR,
INVALID_COURSE,
INVALID_INDEX
};


