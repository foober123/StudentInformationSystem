#include "appData.h"
#include "../guiState.h"
#include <cstdint>

StudentDraft AppData::makeStudentDraft(uint32_t id){
    StudentDraft s;
    auto it = m_collegeRegistry.find(id);
    if (it == m_collegeRegistry.end()) return s;

    const auto& student = m_studentRecord.at(id);
    s.ID = student.ID;
    s.firstName = student.firstName;
    s.lastName = student.lastName;
    s.programCode = m_programRegistry.at(student.programID).programAbbreviation;
    s.gender = static_cast<int>(student.gender);
    s.year = student.year;
    return s;
}

CollegeDraft AppData::makeCollegeDraft(uint16_t id){
    CollegeDraft c;
    const auto& college = m_collegeRegistry.at(id);
    c.collegeCode = college.collegeAbreviation;
    c.collegeName = college.collegeName;

    return c;
}
