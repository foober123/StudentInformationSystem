#include "appData.h"
#include "../guiState.h"
#include <cctype>
#include <cstdint>
#include <unordered_map>

ERRORSTATE AppData::addProgramEntry(ProgramDraft draft){
    if(!validateProgramCode(draft.programAbbreviation)) return ERRORSTATE::PROGRAM_CODE_IN_USE;      
    if(!validateProgramCodeFormat(draft.programAbbreviation)) return ERRORSTATE::INVALID_PROGRAM_NAME;
    if(!validateCollegeCode(draft.collegeCode)) return ERRORSTATE::INVALID_COLLEGE;

    Program program;
    program.programAbbreviation = draft.programAbbreviation;
    program.programName = draft.programName;
    program.collegeID = m_collegeCodeToID.at(draft.collegeCode);

    m_programRegistry.insert({m_nextProgramID, program});
    m_programCodeToID.insert({draft.programAbbreviation,m_nextProgramID});
    m_nextProgramID++;
   return ERRORSTATE::NO_ERROR;
};

ERRORSTATE AppData::editProgramEntry(ProgramDraft draft, uint16_t key){
    if(!checkProgramIDValidity(key)) return ERRORSTATE::INVALID_INDEX;
    if(!validateProgramCode(draft.programAbbreviation, key)) return ERRORSTATE::PROGRAM_CODE_IN_USE;      
    if(!validateProgramCodeFormat(draft.programAbbreviation)) return ERRORSTATE::INVALID_PROGRAM_NAME;
    if(!validateCollegeCode(draft.collegeCode)) return ERRORSTATE::INVALID_COLLEGE;

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

bool AppData::validateProgramCode(std::string programCode){
    for(auto& pair : m_programRegistry){
        auto& program = pair.second;
        
        if(programCode == program.programAbbreviation) return false;

    }

    return true;

}

bool AppData::validateProgramCode(std::string programCode, uint16_t key){

    for(auto& pair : m_programRegistry){
        const auto& id = pair.first;
        const auto& program = pair.second;
        if(key == id) continue; 
        if(programCode == program.programAbbreviation) return false;

    }

    return true;

}

bool AppData::validateProgramCodeFormat(std::string programCode){
    if(programCode.empty()) return false;

    for(char& c : programCode){
        if(!(std::isalpha(c) || c == '-' || std::isspace(c))) return false;
    }

    return true;
}

bool AppData::validateCollegeCode(std::string collegeCode){
    auto it = m_collegeCodeToID.find(collegeCode);

    if (it == m_collegeCodeToID.end()) return false;

    return true;
}
