#include "appData.h"
#include "../guiState.h"
#include <cctype>
#include <cstdint>

ERRORSTATE AppData::addStudentEntry(StudentDraft studentdraft){
   if(!validateStudentID(studentdraft.ID)) return ERRORSTATE::INVALID_STUDENT_ID;
    if(!validateRepeatingStudentID(studentdraft.ID)) return ERRORSTATE::STUDENT_ID_IN_USE;
    if(!validateStudentName(studentdraft.firstName)) return ERRORSTATE::INVALID_NAME;
    if(!validateStudentName(studentdraft.lastName)) return ERRORSTATE::INVALID_NAME;

    if(m_programCodeToID.find(studentdraft.programCode) == m_programCodeToID.end()) return ERRORSTATE::INVALID_COURSE; 
    if(studentdraft.year < 1) return ERRORSTATE::INVALID_YEAR;

    Student student;

    student.ID = studentdraft.ID;
    student.firstName = studentdraft.firstName;
    student.lastName = studentdraft.lastName;
    student.programID = m_programCodeToID.at(studentdraft.programCode);
    student.gender = static_cast<Gender>(studentdraft.gender);
    student.year = studentdraft.year;

    
    m_studentRecord.insert({m_nextStudentInternalID, student});
    m_nextStudentInternalID++;

    return ERRORSTATE::NO_ERROR; 

}

ERRORSTATE AppData::editStudentEntry(StudentDraft studentdraft, uint32_t key){
    if(!checkStudentIDValidity(key)) return ERRORSTATE::INVALID_INDEX;
    if(!validateStudentID(studentdraft.ID)) return ERRORSTATE::INVALID_STUDENT_ID;
    if(!validateRepeatingStudentID(studentdraft.ID, key)) return ERRORSTATE::STUDENT_ID_IN_USE;
    if(!validateStudentName(studentdraft.firstName)) return ERRORSTATE::INVALID_NAME;
    if(!validateStudentName(studentdraft.lastName)) return ERRORSTATE::INVALID_NAME;

    if(m_programCodeToID.find(studentdraft.programCode) == m_programCodeToID.end()) return ERRORSTATE::INVALID_COURSE; 
    if(studentdraft.year < 1) return ERRORSTATE::INVALID_YEAR;

    Student student;

    student.ID = studentdraft.ID;
    student.firstName = studentdraft.firstName;
    student.lastName = studentdraft.lastName;
    student.programID = m_programCodeToID.at(studentdraft.programCode);
    student.gender = static_cast<Gender>(studentdraft.gender);
    student.year = studentdraft.year;

    m_studentRecord.at(key) = student;
    return ERRORSTATE::NO_ERROR; 

}



void AppData::deleteStudentEntry(uint32_t key){
    auto it = m_studentRecord.find(key);
    if (it == m_studentRecord.end())
        return;
    m_studentRecord.erase(key);
}

bool AppData::validateStudentID(std::string draftID){
    if(draftID[0] != '2') return false;
    if(draftID[1] != '0') return false;
    if(draftID.length() != 9) return false;
    if(draftID[4] != '-') return false;


    for (int i = 0; i < draftID.length(); i++)
    {

        if (i == 4)
            continue;

        if (!std::isdigit(static_cast<unsigned char>(draftID[i])))
            return false;
    }

    return true;
}

bool AppData::validateStudentName(std::string name){
    if(name.empty()) return false;

    for(auto &ch: name){
        if(std::isdigit(ch)) return false;

    }
    
    return true;
}

bool AppData::validateRepeatingStudentID(std::string id){
    for(auto &pair: m_studentRecord){
        const auto& student = pair.second;

        if(pair.second.ID == id) return false;
    }

    return true;    
}

bool AppData::validateRepeatingStudentID(std::string id, uint32_t key){
    for(auto &pair: m_studentRecord){
        const auto& internalID = pair.first;
        const auto& student = pair.second;

        if(key == internalID) continue;

        if(pair.second.ID == id) return false;
    }

    return true;    
}
