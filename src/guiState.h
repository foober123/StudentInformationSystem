#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <assert.h>

class AppData;
struct GuiState;

enum class Gender;

struct Student;
struct Program; 
struct College;

enum class ERRORSTATE;

typedef void (*InputBoxStrategy)(GuiState& guistate, AppData& appData);
typedef void (*DataTableStrategy)(GuiState& guistate, AppData& appData);

struct StudentDraft{
std::string ID; 
std::string firstName;
std::string lastName;
std::string programCode;
int year = 0;
int gender = 2;

};

struct ProgramDraft{
uint16_t collegeID;
std::string programName;
std::string programAbbreviation;
};


struct GuiState{
std::vector<size_t> displayOrder; 
std::string searchBuffer;
uint32_t selectedStudent;
uint16_t selectedProgram;
uint16_t selectedCollege;


StudentDraft studentDraft;
ProgramDraft programDraft;

InputBoxStrategy inputBoxStrategy;
DataTableStrategy dataTableStrategy;

ERRORSTATE currentError;
std::string errorMessage;

bool showCollegeRegistry;
bool showProgramRegistry;

void init();
void resetStudentDraft();
void defaultSortDisplayOrder(AppData&);
void updateErrorMessage();
void preloadPending(Student,AppData&);
void preloadPending(Program);
void preloadPending(College);
};

enum class ERRORSTATE{
NO_ERROR,
INVALID_STUDENT_ID,
INVALID_NAME,
INVALID_YEAR,
INVALID_COURSE,
INVALID_INDEX,
PROGRAM_IN_USE,
COLLEGE_IN_USE
};


