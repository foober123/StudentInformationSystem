#include "gui.h"
#include "../guiState.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include "../appData/appData.h"

void drawStudentSearchControls(GuiState& guiState)
{
    const char* labels[] = {
        "All Fields",
        "Student ID",
        "First Name",
        "Last Name",
        "ProgramCode",
        "CollegeCode",
        "Year",
        "Gender"
    };

    int current = static_cast<int>(guiState.studentSearchField);

    if (ImGui::Combo("Search By", &current, labels, IM_ARRAYSIZE(labels)))
    {
        guiState.studentSearchField =
            static_cast<StudentSearchField>(current);
    }
}

void drawProgramSearchControls(GuiState& guiState)
{
    const char* labels[] = {
        "All Fields",
        "Program Code",
        "College Code",
        "Program Name"
    };

    int current = static_cast<int>(guiState.programSearchField);

    if (ImGui::Combo("Search By", &current, labels, IM_ARRAYSIZE(labels)))
    {
        guiState.programSearchField =
            static_cast<ProgramSearchField>(current);
    }
}


void drawCollegeSearchControls(GuiState& guiState)
{
    const char* labels[] = {
        "All Fields",
        "College Code",
        "College Name"

    };

    int current = static_cast<int>(guiState.collegeSearchField);

    if (ImGui::Combo("Search By", &current, labels, IM_ARRAYSIZE(labels)))
    {
        guiState.collegeSearchField =
            static_cast<CollegeSearchField>(current);
    }
}
