#pragma once
#include <cstdint>
#include <string>
#include <array>
#include <unordered_map>
#include <vector>
#include <assert.h>
#include "windows/gui.h"
#include "guiStateStrategy.h"

struct GuiState;
struct ImGuiTableSortSpecs;

enum class Gender;
struct Student;
struct Program; 
struct College;

enum class ERRORSTATE;


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
std::vector<uint32_t> programDisplayOrder;
std::vector<uint32_t> collegeDisplayOrder;
std::string searchBuffer;

uint32_t selectedStudent;
uint32_t selectedProgram;
uint32_t selectedCollege;

StudentDraft studentDraft;
ProgramDraft programDraft;
CollegeDraft collegeDraft;

//Current Input Box
InputBoxStrategy currentInputBox;
const GuiStrategy* currentStrategy;

ERRORSTATE currentError;

bool showCollegeRegistry;
bool showProgramRegistry;
bool showDebugWindow;

void init();

void resetStudentDraft();
void resetProgramDraft();
void resetCollegeDraft();

uint32_t getSelectedStudent() const;
uint32_t getSelectedProgram() const;
uint32_t getSelectedCollege() const;


void refreshDisplayOrder(const std::unordered_map<uint32_t, Student>&);
void refreshDisplayOrder(const std::unordered_map<uint32_t, Program>&);
void refreshDisplayOrder(const std::unordered_map<uint32_t, College>&);

void rebuildStudentDisplayOrder(AppData&);
void rebuildProgramDisplayOrder(AppData&);
void rebuildCollegeDisplayOrder(AppData&);

void sortStudents(AppData&, ImGuiTableSortSpecs* sortSpecs);
void sortPrograms(AppData&, ImGuiTableSortSpecs* sortSpecs);
void sortColleges(AppData&, ImGuiTableSortSpecs* sortSpecs);

void preloadPendingStudent(uint32_t, AppData&);
void preloadPendingProgram(uint32_t, AppData&);
void preloadPendingCollege(uint32_t, AppData&);
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
    "Invalid ID format. Follow 20XX-XXXX where X are digits",
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
