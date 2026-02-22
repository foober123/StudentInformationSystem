#pragma once
#include <string>

class Vault;
struct GuiState;
struct AppData;
enum class Gender;

struct Student;
struct Program;
struct College;


typedef void (*InputBoxStrategy)(GuiState& , AppData& );

static const char* genderItems[] =
{
    "Male",
    "Female",
    "Other",
};


std::string serializeGender(Gender );
void drawMenuBar(GuiState& , AppData& , Vault& );
void drawEntryDisplay(const GuiState& , AppData& );
void drawTaskBar(GuiState&, AppData&);
void drawCollegeRegistry(AppData& );
void drawProgramRegistry(AppData& );
void drawErrorBox(GuiState& );


void drawStudentEntryDisplay(const GuiState& , AppData& );
void drawProgramEntryDisplay(const GuiState& , AppData& );
void drawCollegeEntryDisplay(const GuiState& , AppData& );

void drawStudentDataTable(GuiState& , AppData&);
void drawProgramDataTable(GuiState& , AppData&);
void drawCollegeDataTable(GuiState& , AppData&);

void drawAddStudentBox(GuiState&, AppData&);
void drawEditStudentBox(GuiState&, AppData&);
void drawDeleteStudentBox(GuiState&, AppData&);

void drawAddProgramBox(GuiState&, AppData&);
void drawEditProgramBox(GuiState&, AppData&);
void drawDeleteProgramBox(GuiState&, AppData&);

void drawAddCollegeBox(GuiState&, AppData&);
void drawEditCollegeBox(GuiState&, AppData&);
void drawDeleteCollegeBox(GuiState&, AppData&);

//DEBUGGING FUNCTIONS
void drawProgramToID(AppData&);
void drawCollegeToID(AppData&);
void drawGuiStateInfo(GuiState&);
