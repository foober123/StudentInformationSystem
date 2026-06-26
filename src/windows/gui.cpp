#include "../guiState/guiState.h"
#include "gui.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include "../vault/vault.h"
#include "../appData/appData.h"
#include "../guiState/guiStateStrategies.h"

void drawMenuBar(GuiState& guiState, AppData& appData, Vault& vault){
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Database"))
        {
            if(ImGui::MenuItem("Save File")){
                vault.saveStudents(appData.getStudentRecord());
                vault.savePrograms(appData.getProgramRegistry());
                vault.saveColleges(appData.getCollegeRegistry());
                guiState.isDirty = false;
            }
            ImGui::Checkbox("Show College Registry", &guiState.showCollegeRegistry);
            ImGui::Checkbox("Show Program Registry", &guiState.showProgramRegistry);
            if (ImGui::MenuItem("Exit")) {}

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Entries"))
        {
            ImGui::Text("Student");
            ImGui::Separator();
            if(ImGui::MenuItem("Add Entry")){
                guiState.resetStudentDraft();
                guiState.currentInputBox = drawAddStudentBox;
            }

            if(ImGui::MenuItem("Edit Entry")){
                if(appData.checkStudentIDValidity(guiState.selectedStudent)){
                guiState.preloadPendingStudent(guiState.selectedStudent, appData);
                guiState.currentInputBox = drawEditStudentBox;
                }
                else{
                guiState.currentError = ERRORSTATE::INVALID_INDEX;
                }
            }

            if(ImGui::MenuItem("Delete Entry")){
                if(appData.checkStudentIDValidity(guiState.selectedStudent)){
                    guiState.currentInputBox = drawDeleteStudentBox;
                }
                else{
                    guiState.currentError = ERRORSTATE::INVALID_INDEX;
                }
            }

            ImGui::Text("Program");
            ImGui::Separator();
            if(ImGui::MenuItem("Add Program")){guiState.currentInputBox = drawAddProgramBox;} 
            if(ImGui::MenuItem("Edit Program")){
                if(appData.checkProgramIDValidity(guiState.selectedProgram)){
                guiState.preloadPendingProgram(guiState.selectedProgram, appData);
                guiState.currentInputBox = drawEditProgramBox;
                }
                else guiState.currentError = ERRORSTATE::INVALID_INDEX;

            } 
            if(ImGui::MenuItem("Delete Program")){
                if(appData.checkProgramIDValidity(guiState.selectedProgram)){
                guiState.preloadPendingCollege(guiState.selectedProgram, appData);
                guiState.currentInputBox = drawDeleteProgramBox;
                }
                else guiState.currentError = ERRORSTATE::INVALID_INDEX;

            }  

            ImGui::Text("College");
            ImGui::Separator();
            if(ImGui::MenuItem("Add College")){guiState.currentInputBox = drawAddCollegeBox;} 
            if(ImGui::MenuItem("Edit College")){
                if(appData.checkCollegeIDValidity(guiState.selectedCollege)){
                    guiState.preloadPendingCollege(guiState.selectedCollege, appData);
                    guiState.currentInputBox = drawEditCollegeBox;
                } 
                else guiState.currentError = ERRORSTATE::INVALID_INDEX;
            } 
            if(ImGui::MenuItem("Delete College")){
                if(appData.checkCollegeIDValidity(guiState.selectedCollege)){
                    guiState.currentInputBox = drawDeleteCollegeBox;
                }
                else guiState.currentError = ERRORSTATE::INVALID_INDEX;
            } 

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }


}

std::string serializeGender(Gender gender){
    switch(gender){
        case Gender::Male: return "Male";
        case Gender::Female: return "Female";
        case Gender::Other: return "Other";
    }
    return "N/A";
}

void drawTaskBar(GuiState& guiState, AppData& appData, Vault& vault){
    ImGui::Begin("taskbar", NULL, ImGuiWindowFlags_NoTitleBar);


    if (ImGui::BeginTable("TaskBarLayout", 2, ImGuiTableFlags_SizingStretchProp)){
        ImGui::TableSetupColumn("Left", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Right", ImGuiTableColumnFlags_WidthFixed, 420.0f);
        ImGui::TableNextColumn();

        ImGui::BeginDisabled(!guiState.isDirty);

        if (ImGui::Button("Save"))
        {
            vault.saveStudents(appData.getStudentRecord());
            vault.savePrograms(appData.getProgramRegistry());
            vault.saveColleges(appData.getCollegeRegistry());

            guiState.isDirty = false;
        }

        ImGui::EndDisabled();

        ImGui::SameLine();

        if(ImGui::Button("Student")){
            guiState.currentStrategy = &studentStrategy;
        }

        ImGui::SameLine();

        if(ImGui::Button("Program")){
            guiState.currentStrategy = &programStrategy;
        }

        ImGui::SameLine();

        if(ImGui::Button("College")){
            guiState.currentStrategy = &collegeStrategy;
        }

        ImGui::SameLine();

        if(ImGui::Button("Add")){
            guiState.currentInputBox = guiState.currentStrategy->addEntryStrategy;
        }

        ImGui::SameLine();

        if(ImGui::Button("Edit")){
            uint32_t id = (guiState.*guiState.currentStrategy->IDStrategy)();

            if((appData.*guiState.currentStrategy->validator)(id)){
                (guiState.*guiState.currentStrategy->draftSettingStrategy)(id, appData);
                guiState.currentInputBox = guiState.currentStrategy->editEntryStrategy;

            }
            else{
                guiState.currentError = ERRORSTATE::INVALID_INDEX;
            }


        }

        ImGui::SameLine();

        if(ImGui::Button("Delete")){

            uint32_t id = (guiState.*guiState.currentStrategy->IDStrategy)();

            if((appData.*guiState.currentStrategy->validator)(id)){
                guiState.currentInputBox = guiState.currentStrategy->deleteEntryStrategy;

            }
            else{
                guiState.currentError = ERRORSTATE::INVALID_INDEX;
            }

        }

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(250);
        if(ImGui::InputText("##Search", &guiState.searchBuffer)){(guiState.*guiState.currentStrategy->searchStrategy)(appData);};
        ImGui::PopItemWidth();

        ImGui::SameLine();

        ImGui::PushItemWidth(150);
        guiState.currentStrategy->searchFieldStrategy(guiState);
        ImGui::PopItemWidth();

        ImGui::EndTable();
    }

    ImGui::End();
}

void drawEntryDisplay(const GuiState& guiState, AppData& appData){
    const Student& student = appData.getStudent(guiState.selectedStudent);

    ImGui::Begin("Entry Display");
    if(appData.checkStudentIDValidity(guiState.selectedStudent)){
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("ID: %s", student.ID.c_str());
        ImGui::Text("Name: %s %s", student.firstName.c_str(), student.lastName.c_str());
        ImGui::Text("Program: %s", appData.getProgram(appData.getStudent(guiState.selectedStudent).programID).programName.c_str());
        ImGui::Text("College: %s", appData.getCollege(appData.getProgram(appData.getStudent(guiState.selectedStudent).programID).collegeID).collegeName.c_str());
        ImGui::SetWindowFontScale(1.0f);
    }
    ImGui::End();
}

void drawCollegeRegistry(AppData& appData){
    {
        ImGui::Begin("College Registry");
        if (ImGui::BeginTable("CollegeTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("College Name");
            ImGui::TableSetupColumn("Abbreviation");
            ImGui::TableHeadersRow();

            for (const auto& pair : appData.getCollegeRegistry())
            {
                const auto& id = pair.first;
                const auto& college = pair.second;

                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%u", id);

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", college.collegeName.c_str());

                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", college.collegeAbbreviation.c_str());
            }

            ImGui::EndTable();
        }
        ImGui::End();
    }

}

void drawProgramRegistry(AppData &appData){
    ImGui::Begin("Program Registry");
    if (ImGui::BeginTable("CollegeTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Program ID");
        ImGui::TableSetupColumn("College");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Abbreviation");
        ImGui::TableHeadersRow();

        for(const auto& pair : appData.getProgramRegistry())
        {
            const auto& id = pair.first;
            const auto& program = pair.second;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%u", id);

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", appData.getCollege(program.collegeID).collegeName.c_str());

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s", program.programName.c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%s", program.programAbbreviation.c_str());
        }

        ImGui::EndTable();
    }
    ImGui::End();
}

void drawErrorBox(GuiState &guiState){
    ImGui::SetNextWindowDockID(0, ImGuiCond_Always);
    ImGui::Begin("Error", nullptr, ImGuiWindowFlags_NoDocking);
 
    ImGui::Text("%s", toString(guiState.currentError).c_str());

    ImVec2 buttonSize = ImVec2(90, 0); 

    ImVec2 windowSize = ImGui::GetWindowSize();

    float padding = 10.0f;
    ImVec2 pos = ImVec2(
            windowSize.x - buttonSize.x - padding,
            windowSize.y - ImGui::GetFrameHeight() - padding
            );

    ImGui::SetCursorPos(pos);

    if (ImGui::Button("Close", buttonSize))
    {
        guiState.currentError = ERRORSTATE::NO_ERROR;
    }

    pos = ImVec2(
            windowSize.x - buttonSize.x * 2 - padding * 2,
            windowSize.y - ImGui::GetFrameHeight() - padding
            );
    ImGui::End();
}

void drawProgramToID(AppData &appData){
    ImGui::Begin("ProgramCodeToID");
    if (ImGui::BeginTable("fa", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Abbreviation");
        ImGui::TableSetupColumn("ID");
        ImGui::TableHeadersRow();

        for(const auto& pair : appData.getProgramCodeToID())
        {
            const auto& program = pair.first;
            const auto& id = pair.second;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", program.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%u", id);

        }

        ImGui::EndTable();
    }
    ImGui::End();

}

void drawCollegeToID(AppData &appData){
    ImGui::Begin("CollegeCodeToID");
    if (ImGui::BeginTable("fa", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Abbreviation");
        ImGui::TableSetupColumn("ID");
        ImGui::TableHeadersRow();

        for(const auto& pair : appData.getcollegeCodeToID())
        {
            const auto& program = pair.first;
            const auto& id = pair.second;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", program.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%u", id);

        }

        ImGui::EndTable();
    }
    ImGui::End();

}

void drawGuiStateInfo(GuiState &guiState){
    uint32_t currID = (guiState.*guiState.currentStrategy->IDStrategy)();
    ImGui::Begin("Gui State Information");
        ImGui::Text("Selected Student Internal ID: %d", guiState.selectedStudent);
        ImGui::Text("Selected Program Internal ID: %d", guiState.selectedProgram);
        ImGui::Text("Selected College Internal ID: %d", guiState.selectedCollege);
        ImGui::Text("Current Selected Index: %d", currID);
        ImGui::Separator();
        ImGui::Text("Student Display Order Size: %d", static_cast<int>(guiState.displayOrder.size()));


    ImGui::End();
}

void drawAppDataStatus(AppData& appData)
{

    ImGui::Begin("StatusPanel");

    ImGui::Text("System Status");
    ImGui::Separator();
    ImGui::Text("Total Colleges %d", static_cast<int>(appData.getCollegeRegistry().size()));
    ImGui::Text("Total Programs %d", static_cast<int>(appData.getProgramRegistry().size()));
    ImGui::Text("Total Students %d", static_cast<int>(appData.getStudentRecord().size()));

    std::unordered_map<uint32_t, int> programsPerCollege;
    std::unordered_map<uint32_t, int> studentsPerCollege;

    // Count programs
    for (const auto& [id, program] : appData.getProgramRegistry())
    {
        programsPerCollege[program.collegeID]++;
    }

    // Count students (via program → college)
    for (const auto& [id, student] : appData.getStudentRecord())
    {
        const auto& program = appData.getProgram(student.programID);
        studentsPerCollege[program.collegeID]++;
    }

    ImGui::Separator();
    ImGui::Text("Colleges");
    ImGui::Separator();

    for (const auto& [collegeID, college] : appData.getCollegeRegistry())
    {
        int pCount = programsPerCollege[collegeID];
        int sCount = studentsPerCollege[collegeID];

        ImGui::Spacing();
        ImGui::Text("%s", college.collegeAbbreviation.c_str());
        ImGui::BulletText("Programs: %d", pCount);
        ImGui::BulletText("Students: %d", sCount);
    }

    ImGui::End();
}
