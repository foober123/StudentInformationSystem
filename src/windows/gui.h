#pragma once
#include <string>

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
void drawStudentDataTable(GuiState& guiState, AppData& appdata);
void drawMenuBar(GuiState& guistate);
void drawEntryDisplay(const GuiState& guiState, AppData& appData);
void drawTaskBar(GuiState& guistate);
void drawCollegeRegistry(AppData& appdata);
void drawCourseRegistry(AppData& appdata);
void drawErrorBox(GuiState& guiState);

void drawAddStudentBox(GuiState& guiState, AppData& appData);
void drawEditStudentBox(GuiState&, AppData&);
void drawDeleteStudentBox(GuiState&, AppData&);

//DEBUGGING FUNCTIONS
void drawCourseToID(AppData& appData);
