#include "appData.h"
#include "../guiState.h"
#include <cstdint>
#include <unordered_map>

ERRORSTATE AppData::addProgramEntry(ProgramDraft draft){
    Program program;
    program.programAbbreviation = draft.programAbbreviation;
    program.programName = draft.programName;
    program.collegeID = m_collegeCodeToID.at(draft.collegeCode);

    m_programRegistry.insert({m_nextProgramID, program});
    m_nextProgramID++;
    return ERRORSTATE::NO_ERROR;
};

ERRORSTATE AppData::editProgramEntry(ProgramDraft draft, uint16_t key){

    auto& program = m_programRegistry.at(key);

    m_programCodeToID.erase(program.programAbbreviation);

    program.programName = draft.programName;
    program.programAbbreviation = draft.programAbbreviation;
    program.collegeID = m_collegeCodeToID.at(draft.collegeCode);

    m_programCodeToID[draft.programAbbreviation] = key;

    return ERRORSTATE::NO_ERROR;
};

ERRORSTATE AppData::deleteProgramEntry(uint16_t key){
    for(const auto& pair : m_studentRecord){
        const auto& student = pair.second;

        if(student.programID == key) return ERRORSTATE::PROGRAM_IN_USE;

    }

    auto it = m_programRegistry.find(key);
    if (it == m_programRegistry.end()) return ERRORSTATE::INVALID_INDEX;

    m_programCodeToID.erase(it->second.programAbbreviation);
    m_programRegistry.erase(it);

    return ERRORSTATE::NO_ERROR;

}
