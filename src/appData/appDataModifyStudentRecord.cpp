#include "appData.h"
#include "../guiState.h"
#include <cstdint>

ERRORSTATE AppData::addStudentEntry(StudentDraft studentdraft){

    if(studentdraft.ID.length() != 9) return ERRORSTATE::INVALID_STUDENT_ID;
    if(studentdraft.ID[4] != '-') return ERRORSTATE::INVALID_STUDENT_ID;


    for (int i = 0; i < studentdraft.ID.length(); i++)
    {
        if (i == 4)
            continue;

        if (!std::isdigit(static_cast<unsigned char>(studentdraft.ID[i])))
            return ERRORSTATE::INVALID_STUDENT_ID;
    }
    
    if(studentdraft.firstName.empty()) return ERRORSTATE::INVALID_NAME;
    if(studentdraft.lastName.empty()) return ERRORSTATE::INVALID_NAME;
    if(m_courseCodeToID.find(studentdraft.courseCode) == m_courseCodeToID.end()) return ERRORSTATE::INVALID_COURSE; 
    if(studentdraft.year < 1) return ERRORSTATE::INVALID_YEAR;

    Student student;

    student.ID = studentdraft.ID;
    student.firstName = studentdraft.firstName;
    student.lastName = studentdraft.lastName;
    student.courseID = m_courseCodeToID.at(studentdraft.courseCode);
    student.gender = static_cast<Gender>(studentdraft.gender);
    student.year = studentdraft.year;

    
    m_studentRecord.insert({m_nextStudentInternalID, student});
    m_nextStudentInternalID++;

    return ERRORSTATE::NO_ERROR; 

}

ERRORSTATE AppData::editStudentEntry(StudentDraft studentdraft, uint32_t key){
    if(key == 0) return ERRORSTATE::INVALID_INDEX;


    if(studentdraft.ID.length() != 9) return ERRORSTATE::INVALID_STUDENT_ID;
    if(studentdraft.ID[4] != '-') return ERRORSTATE::INVALID_STUDENT_ID;


    for (int i = 0; i < studentdraft.ID.length(); i++)
    {
        if (i == 4)
            continue;

        if (!std::isdigit(static_cast<unsigned char>(studentdraft.ID[i])))
            return ERRORSTATE::INVALID_STUDENT_ID;
    }
    
    if(studentdraft.firstName.empty()) return ERRORSTATE::INVALID_NAME;
    if(studentdraft.lastName.empty()) return ERRORSTATE::INVALID_NAME;
    if(m_courseCodeToID.find(studentdraft.courseCode) == m_courseCodeToID.end()) return ERRORSTATE::INVALID_COURSE; 
    if(studentdraft.year < 1) return ERRORSTATE::INVALID_YEAR;

    Student student;

    student.ID = studentdraft.ID;
    student.firstName = studentdraft.firstName;
    student.lastName = studentdraft.lastName;
    student.courseID = m_courseCodeToID.at(studentdraft.courseCode);
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
