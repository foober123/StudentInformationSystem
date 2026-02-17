#include "appData.h"
#include "../guiState.h"
#include <cstdint>


void AppData::setCollegeRegistry(std::unordered_map<uint16_t, College> collegeRegistry){
    m_collegeRegistry = collegeRegistry;
};

void AppData::setStudentRecord(std::unordered_map<uint32_t, Student> studentRecord){
    m_studentRecord = studentRecord;
};

void AppData::setCourseRegistry(std::unordered_map<uint16_t, Course> courseRegistry){
    m_courseRegistry = courseRegistry;
    m_courseCodeToID.clear();

    uint32_t maxID = 0;

    for (const auto& [id, course] : m_courseRegistry)
    {
        // Build secondary index
        m_courseCodeToID[course.courseAbbreviation] = id;

        if (id > maxID)
            maxID = id;
    }

    m_nextCourseID = maxID + 1;

};

void AppData::addStudent(Student student){
    m_studentRecord.insert({m_nextStudentInternalID, student});
}

ERRORSTATE AppData::validateStudentEntry(StudentDraft studentdraft){

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

    
    addStudent(student);
    m_nextStudentInternalID++;

    return ERRORSTATE::NO_ERROR; 

}

ERRORSTATE AppData::validateStudentEntry(StudentDraft studentdraft, int index){
    if(index == -1) return ERRORSTATE::INVALID_INDEX;


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
    if(studentdraft.year < 1) return ERRORSTATE::INVALID_YEAR;

    Student student;

    student.ID = studentdraft.ID;
    student.firstName = studentdraft.firstName;
    student.lastName = studentdraft.lastName;
    student.courseID = 1;
    student.gender = static_cast<Gender>(studentdraft.gender);
    student.year = studentdraft.year;

    m_studentRecord.at(index) = student;
    return ERRORSTATE::NO_ERROR; 

}

const std::unordered_map<std::string, uint16_t>& AppData::getcourseCodeToID(){
    return m_courseCodeToID; 
};



const std::unordered_map<uint32_t, Student>& AppData::getStudentRecord(){
    return m_studentRecord;
};

const std::unordered_map<uint16_t, College>& AppData::getCollegeRegistry(){
    return m_collegeRegistry;
}

std::unordered_map<uint16_t, Course>& AppData::getCourseRegistry(){
    return m_courseRegistry;    
};  

Student AppData::getStudent(uint32_t key){
    if(m_studentRecord.find(key) == m_studentRecord.end()) return INVALIDSTUDENT; 


    return m_studentRecord.at(key);
}

Course AppData::getCourse(uint16_t key){
    if(m_courseRegistry.find(key) == m_courseRegistry.end()) return INVALIDCOURSE; 


    return m_courseRegistry.at(key);
}

College AppData::getCollege(uint16_t key){
    if(m_collegeRegistry.find(key) == m_collegeRegistry.end()) return INVALIDCOLLEGE; 

    return m_collegeRegistry.at(key);
}

void AppData::initCourseIDCounter(){
    uint32_t maxID = 0;

    for (const auto& [id, course] : m_courseRegistry)
    {
        if (id > maxID)
            maxID = id;
    }

    m_nextCourseID = maxID + 1;

}

void AppData::initCollegeIDCounter(){
    uint32_t maxID = 0;

    for (const auto& [id, college] : m_collegeRegistry)
    {
        if (id > maxID)
            maxID = id;
    }

    m_nextCollegeID = maxID + 1;

}

void AppData::initStudentIDCounter(){
    uint32_t maxID = 0;

    for (const auto& [id, student] : m_studentRecord)
    {
        if (id > maxID)
            maxID = id;
    }

    m_nextStudentInternalID = maxID + 1;

}

void AppData::incrementNextStudentInternalID(){
    m_nextStudentInternalID++;
}

void AppData::incrementNextCollegeID(){
    m_nextCollegeID++;
}

void AppData::incrementNextCourseID(){
    m_nextCourseID++;
}

ERRORSTATE AppData::validateCourseEntry(CourseDraft draft){
    return ERRORSTATE::NO_ERROR;
};
