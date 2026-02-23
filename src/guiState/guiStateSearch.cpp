#include "guiState.h"
#include "../appData/appData.h"
#include "../windows/gui.h"
#include <string>
#include <algorithm>

void GuiState::rebuildStudentDisplayOrder(AppData& appData){
    displayOrder.clear();

    std::string query = searchBuffer;
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);

    for (const auto& [internalID, student] : appData.getStudentRecord())
    {
        bool match = false;

        switch(studentSearchField)
        {
            case StudentSearchField::All:
                {
                    std::string searchable =
                        student.ID + " " +
                        student.firstName + " " +
                        student.lastName + " " +
                        appData.getProgram(student.programID).programAbbreviation + " " +
                        std::to_string(student.year) + " " +
                        serializeGender(student.gender);

                    std::transform(searchable.begin(), searchable.end(),
                            searchable.begin(), ::tolower);
                    match = searchable.find(query) != std::string::npos;
                    break;
                }
            case StudentSearchField::StudentID:
                {
                    std::string field = student.ID;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case StudentSearchField::FirstName:
                {
                    std::string field = student.firstName;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case StudentSearchField::LastName:
                {
                    std::string field = student.lastName;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case StudentSearchField::ProgramCode:
                {
                    std::string field = appData.getProgram(student.programID).programAbbreviation;
                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case StudentSearchField::CollegeCode:
                {
                    std::string field = appData.getCollege(appData.getProgram(student.programID).collegeID).collegeAbbreviation;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case StudentSearchField::Gender:
                {
                    std::string field = serializeGender(student.gender);
                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case StudentSearchField::Year:
                {
                    std::string field = std::to_string(student.year);

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }

        }
        if (query.empty() || match) displayOrder.push_back(internalID);
    }

}
void GuiState::rebuildProgramDisplayOrder(AppData& appData){
    programDisplayOrder.clear();

    std::string query = searchBuffer;
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);

    for (const auto& [internalID, program] : appData.getProgramRegistry())
    {
        bool match = false;

        switch(programSearchField){
            case ProgramSearchField::All:
                {
                    std::string searchable =
                        program.programAbbreviation + " " +
                        appData.getCollege(program.collegeID).collegeAbbreviation + " " +
                        program.programName;

                    std::transform(searchable.begin(), searchable.end(),
                            searchable.begin(), ::tolower);

                    match = searchable.find(query) != std::string::npos;
                    break;
                }
            case ProgramSearchField::ProgramName:
                {
                    std::string field = program.programName;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case ProgramSearchField::ProgramCode:
                {
                    std::string field = program.programAbbreviation;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case ProgramSearchField::CollegeCode:
                { 
                    std::string field = appData.getCollege(internalID).collegeAbbreviation;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
        }
        if (query.empty() || match) programDisplayOrder.push_back(internalID);
    }

}

void GuiState::rebuildCollegeDisplayOrder(AppData& appData){
    collegeDisplayOrder.clear();

    std::string query = searchBuffer;
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);

    for (const auto& [internalID, college] : appData.getCollegeRegistry())
    {
        bool match = false;

        switch(collegeSearchField){

            case CollegeSearchField::All:
                {
                    std::string searchable =
                        college.collegeAbbreviation + " " +
                        college.collegeName;

                    std::transform(searchable.begin(), searchable.end(),
                            searchable.begin(), ::tolower);

                    match = searchable.find(query) != std::string::npos;
                    break;
                }
            case CollegeSearchField::CollegeCode:
                {   
                    std::string field = college.collegeAbbreviation;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }
            case CollegeSearchField::CollegeName:
                {   
                    std::string field = college.collegeName;

                    std::transform(field.begin(), field.end(),
                            field.begin(), ::tolower);

                    match = field.find(query) != std::string::npos;
                    break;
                }

        }

        if (query.empty() || match) collegeDisplayOrder.push_back(internalID);
    }

}
