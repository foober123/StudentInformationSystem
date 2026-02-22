#include "appData/appData.h"
#include "guiState.h"
#include "guiStateStrategy.h"
#include "guiStateStrategies.h"
#include "windows/gui.h"

const GuiStrategy studentStrategy = {
    drawAddStudentBox, 
    drawEditStudentBox, 
    drawDeleteStudentBox, 
    drawStudentDataTable, 
    drawStudentEntryDisplay, 
    &AppData::checkStudentIDValidity, 
    &GuiState::getSelectedStudent,
    &GuiState::preloadPendingStudent,
    &GuiState::rebuildStudentDisplayOrder
};

const GuiStrategy programStrategy = {
    drawAddProgramBox, 
    drawEditProgramBox, 
    drawDeleteProgramBox, 
    drawProgramDataTable, 
    drawProgramEntryDisplay, 
    &AppData::checkProgramIDValidity, 
    &GuiState::getSelectedProgram,
    &GuiState::preloadPendingProgram,
    &GuiState::rebuildProgramDisplayOrder
};

const GuiStrategy collegeStrategy = {
    drawAddCollegeBox, 
    drawEditCollegeBox, 
    drawDeleteCollegeBox, 
    drawCollegeDataTable, 
    drawCollegeEntryDisplay, 
    &AppData::checkCollegeIDValidity, 
    &GuiState::getSelectedCollege,
    &GuiState::preloadPendingCollege,
    &GuiState::rebuildCollegeDisplayOrder

};
