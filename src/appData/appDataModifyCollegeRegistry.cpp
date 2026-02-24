#include "appData.h"
#include "../guiState/guiState.h"
#include <cctype>
#include <cstdint>
#include <unordered_map>



ERRORSTATE AppData::addCollegeEntry(CollegeDraft draft){
    if(!validateRepeatingCollegeCode(draft.collegeCode)) return ERRORSTATE::COLLEGE_CODE_IN_USE;
    if(!validateCollegeNameFormat(draft.collegeName)) return ERRORSTATE::INVALID_PROGRAM_NAME;

    College college;
    college.collegeAbbreviation = draft.collegeCode;
    college.collegeName = draft.collegeName;

    m_collegeRegistry.insert({m_nextCollegeID, college});
    m_collegeCodeToID.insert({draft.collegeCode,m_nextCollegeID});
    m_nextCollegeID++;
    return ERRORSTATE::NO_ERROR;
}

ERRORSTATE AppData::editCollegeEntry(CollegeDraft draft, uint32_t key){
    if(!checkCollegeIDValidity(key)) return ERRORSTATE::INVALID_INDEX;
    if(!validateRepeatingCollegeCode(draft.collegeCode, key)) return ERRORSTATE::COLLEGE_CODE_IN_USE;
    if(!validateCollegeNameFormat(draft.collegeName)) return ERRORSTATE::INVALID_PROGRAM_NAME;

    auto& college = m_collegeRegistry.at(key);

    m_collegeCodeToID.erase(college.collegeAbbreviation);

    college.collegeName = draft.collegeName;
    college.collegeAbbreviation = draft.collegeCode;

    m_collegeCodeToID[draft.collegeCode] = key;

    return ERRORSTATE::NO_ERROR;
}

ERRORSTATE AppData::deleteCollege(uint32_t key){
    auto it = m_collegeRegistry.find(key);
    if (it == m_collegeRegistry.end()) return ERRORSTATE::INVALID_INDEX;

    for(const auto& [id,program] : m_programRegistry){
        if(program.collegeID == key) return ERRORSTATE::COLLEGE_IN_USE;
    }


    m_collegeCodeToID.erase(it->second.collegeAbbreviation);
    m_collegeRegistry.erase(key);

    return ERRORSTATE::NO_ERROR;


}

bool AppData::validateCollegeNameFormat(std::string name){
    if(name.empty()) return false;

    for(char& c : name){
        if(!(std::isalpha(c) || c == '-' || std::isspace(c) || c == ',' || c == '&')) return false;
    }

    return true;
}

bool AppData::validateRepeatingCollegeCode(std::string code){
    for(const auto& [id, college]: m_collegeRegistry){
        if(code == college.collegeAbbreviation) return false;

    }

    return true;
}

bool AppData::validateRepeatingCollegeCode(std::string code, uint32_t key){
    for(const auto& [id, college]: m_collegeRegistry){
        if(key == id) continue;
        if(code == college.collegeAbbreviation) return false;

    }

    return true;
}
