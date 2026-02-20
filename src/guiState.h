#pragma once
#include <cstdint>
#include <string>
#include <array>
#include <unordered_map>
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
std::string programName;
std::string programAbbreviation;
std::string collegeCode;
};

struct CollegeDraft{
std::string collegeName;
std::string collegeCode;

};

struct GuiState{
std::vector<size_t> displayOrder; 
std::vector<uint16_t> programDisplayOrder;
std::string searchBuffer;
uint32_t selectedStudent;
uint16_t selectedProgram;
uint16_t selectedCollege;

StudentDraft studentDraft;
ProgramDraft programDraft;
CollegeDraft collegeDraft;

InputBoxStrategy inputBoxStrategy;

DataTableStrategy dataTableStrategy;
InputBoxStrategy addEntryStrategy;
InputBoxStrategy editEntryStrategy;
InputBoxStrategy deleteEntryStrategy;



ERRORSTATE currentError;

bool showCollegeRegistry;
bool showProgramRegistry;
bool showDebugWindow;

void init();

void resetStudentDraft();
void resetProgramDraft();
void resetCollegeDraft();

void defaultSortDisplayOrder(AppData&);
void defaultSortDisplayOrder(const std::unordered_map<uint16_t, Program>&);

void initStudentStrategies();
void initProgramStrategies();
void initCollegeStrategies();

void preloadPending(StudentDraft);
};

enum class ERRORSTATE{
NO_ERROR,
INVALID_STUDENT_ID,
INVALID_NAME,
INVALID_YEAR,
INVALID_COURSE,
INVALID_INDEX,
STUDENT_ID_IN_USE,
PROGRAM_CODE_IN_USE,
INVALID_PROGRAM_CODE,
INVALID_PROGRAM_NAME,
PROGRAM_IN_USE,
COLLEGE_IN_USE,
INVALID_COLLEGE,
COLLEGE_CODE_IN_USE,

COUNT
};

static const std::array<std::string,
    static_cast<size_t>(ERRORSTATE::COUNT)> errorMessages = {
    "No Errors but you shouldn't be seeing this message",
    "Invalid ID format. Follow XXXX-XXXX where X are digits",
    "Invalid Name. Cannot contain Numbers or Special Characters",
    "Invalid Year. Cannot be negative or zero",
    "Invalid Course. Refer to Program Registry for Codes",
    "Select an entry before you edit",
    "There is another student using this id",
    "There is another program using this code",
    "Program code cannot contain numbers or special characters except '-'",
    "Program name cannot contain numbers or special characters except '-'",
    "There is a student in this program",
    "There is a program in this college",
    "Invalid College. Refer to College Registry for Codes",
    "Another College is using this code"
};

static const std::string toString(ERRORSTATE e) {
    return errorMessages[static_cast<size_t>(e)];
}
