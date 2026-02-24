#include "guiState.h"
#include "../appData/appData.h"
#include "../windows/gui.h"
#include <algorithm>
#include <imgui.h>


void GuiState::sortStudents(AppData& appData, ImGuiTableSortSpecs* sortSpecs){
    if (sortSpecs->SpecsCount == 0)
        return;

    const ImGuiTableColumnSortSpecs* spec = &sortSpecs->Specs[0];
    bool ascending = (spec->SortDirection == ImGuiSortDirection_Ascending);

    auto& students = appData.getStudentRecord();

    std::sort(displayOrder.begin(), displayOrder.end(),
            [&](uint32_t a, uint32_t b)
            {
            const Student& s1 = students.at(a);
            const Student& s2 = students.at(b);

            bool result = false;

            switch (spec->ColumnIndex)
            {
            case 0: result = s1.ID < s2.ID; break;
            case 1: result = s1.firstName < s2.firstName; break;
            case 2: result = s1.lastName < s2.lastName; break;
            case 3: result = s1.programID < s2.programID; break;
            case 4: result = appData.getProgram(s1.programID).collegeID < appData.getProgram(s2.programID).collegeID;
            case 5: result = s1.year < s2.year; break;
            default: result = s1.ID < s2.ID; break;
            }

            switch (spec->ColumnIndex)
            {
            case 0:
            return ascending
                ? (s1.ID < s2.ID)
                : (s2.ID < s1.ID);

            case 1:
            return ascending
                ? (s1.firstName < s2.firstName)
                : (s2.firstName < s1.firstName);

            case 2:
            return ascending
                ? (s1.lastName < s2.lastName)
                : (s2.lastName < s1.lastName);
            
            case 3:
            return ascending
                ? (s1.programID < s2.programID)
                : (s2.programID < s1.programID);

            case 4:
            return ascending
               ? (appData.getProgram(s1.programID).collegeID < appData.getProgram(s2.programID).collegeID)
               : (appData.getProgram(s2.programID).collegeID < appData.getProgram(s1.programID).collegeID);

            case 5:
            return ascending
                ? (s1.year < s2.year)
                : (s2.year < s1.year);

            case 6: 
            return ascending
                ? (s1.gender < s2.gender)
                : (s2.gender < s1.gender);

            default:
            return ascending
                ? (s1.ID < s2.ID)
                : (s2.ID < s1.ID);
            }
            });
}

void GuiState::sortPrograms(AppData& appData, ImGuiTableSortSpecs* sortSpecs){
    if (sortSpecs->SpecsCount == 0)
        return;

    const ImGuiTableColumnSortSpecs* spec = &sortSpecs->Specs[0];
    bool ascending = (spec->SortDirection == ImGuiSortDirection_Ascending);

    auto& programs = appData.getProgramRegistry();

    std::sort(programDisplayOrder.begin(), programDisplayOrder.end(),
            [&](uint32_t a, uint32_t b)
            {
            const Program& s1 = programs.at(a);
            const Program& s2 = programs.at(b);


            bool result = false;

            switch (spec->ColumnIndex)
            {
            case 0: result = s1.programAbbreviation < s2.programAbbreviation; break;
            case 1: result = s1.collegeID < s2.collegeID; break;
            case 2: result = s1.programName < s2.programName; break;
            default: result = s1.programAbbreviation < s2.programAbbreviation; break;
            }

            switch (spec->ColumnIndex)
            {
            case 0:
            return ascending
                ? (s1.programAbbreviation < s2.programAbbreviation)
                : (s2.programAbbreviation < s1.programAbbreviation);

            case 1:
            return ascending
                ? (s1.collegeID < s2.collegeID)
                : (s2.collegeID < s1.collegeID);
            case 2:
            return ascending
                ? (s1.programName < s2.programName)
                : (s2.programName < s1.programName);
            
            default:
            return ascending
                ? (s1.programAbbreviation < s2.programAbbreviation)
                : (s2.programAbbreviation < s1.programAbbreviation);


            }
            });

}

void GuiState::sortColleges(AppData& appData, ImGuiTableSortSpecs* sortSpecs){
    if (sortSpecs->SpecsCount == 0)
        return;

    const ImGuiTableColumnSortSpecs* spec = &sortSpecs->Specs[0];
    bool ascending = (spec->SortDirection == ImGuiSortDirection_Ascending);

    auto& colleges = appData.getCollegeRegistry();

    std::sort(collegeDisplayOrder.begin(), collegeDisplayOrder.end(),
            [&](uint32_t a, uint32_t b)
            {
            const College& s1 = colleges.at(a);
            const College& s2 = colleges.at(b);


            bool result = false;

            switch (spec->ColumnIndex)
            {
            case 0: result = s1.collegeAbbreviation < s2.collegeAbbreviation; break;
            case 1: result = s1.collegeName < s2.collegeName; break;
            default: result = s1.collegeAbbreviation < s2.collegeAbbreviation; break;
            }

            switch (spec->ColumnIndex)
            {
            case 0:
            return ascending
                ? (s1.collegeAbbreviation < s2.collegeAbbreviation)
                : (s2.collegeAbbreviation < s1.collegeAbbreviation);

            case 2:
            return ascending
                ? (s1.collegeName < s2.collegeName)
                : (s2.collegeName < s1.collegeName);
            
            default:
            return ascending
                ? (s1.collegeAbbreviation < s2.collegeAbbreviation)
                : (s2.collegeAbbreviation < s1.collegeAbbreviation);


            }
            });

}


