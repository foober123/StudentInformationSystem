#pragma once
#include <string>

struct GuiState;
struct AppData;
enum class Gender;

std::string serializeGender(Gender gender);
void drawStudentDataTable(GuiState& guiState, AppData& appdata);
void drawMenuBar(GuiState& guistate);
void drawEntryDisplay(const GuiState& guiState, AppData& appData);
void drawTaskBar(GuiState& guistate);
void drawCollegeRegistry(AppData& appdata);
void drawCourseRegistry(AppData& appdata);


