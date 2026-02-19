#pragma once
#include <string>

class Vault;
struct GuiState;
struct AppData;
enum class Gender;


typedef void (*InputBoxStrategy)(GuiState& guistate, AppData& appData);

static const char* genderItems[] =
{
    "Male",
    "Female",
    "Other",
};


std::string serializeGender(Gender gender);
void drawMenuBar(GuiState& guistate, AppData& appData, Vault& vault);
void drawEntryDisplay(const GuiState& guiState, AppData& appData);
void drawTaskBar(GuiState& guistate);
void drawCollegeRegistry(AppData& appdata);
void drawProgramRegistry(AppData& appdata);
void drawErrorBox(GuiState& guiState);


void drawStudentDataTable(GuiState& guiState, AppData& appdata);
void drawProgramDataTable(GuiState& guiState, AppData& appdata);
void drawCollegeDataTable(GuiState& guiState, AppData& appdata);


void drawAddStudentBox(GuiState& guiState, AppData& appData);
void drawEditStudentBox(GuiState&, AppData&);
void drawDeleteStudentBox(GuiState&, AppData&);

void drawAddProgramBox(GuiState&, AppData&);

//DEBUGGING FUNCTIONS
void drawProgramToID(AppData&);
void drawCollegeToID(AppData&);
void drawGuiStateInfo(GuiState&);
