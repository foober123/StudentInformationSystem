#include "appData.h"
void AppData::setCollegeRegistry(std::vector<College> collegeRegistry){
    m_collegeRegistry = collegeRegistry;
};

void AppData::setStudentRecord(std::vector<Student> studentRecord){
    m_studentRecord = studentRecord;
};

void AppData::setCourseRegistry(std::unordered_map<uint16_t, Course> courseRegistry){
    m_courseRegistry = courseRegistry;
};

const std::vector<Student>& AppData::getStudentRecord(){
    return m_studentRecord;
};

const std::vector<College>& AppData::getCollegeRegistry(){
    return m_collegeRegistry;
}

std::unordered_map<uint16_t, Course>& AppData::getCourseRegistry(){
    return m_courseRegistry;    
};  

Student AppData::getStudent(int index){
    if(index > m_studentRecord.size() - 1) return INVALIDSTUDENT;
    if(index < 0) return INVALIDSTUDENT;

    return m_studentRecord[index];
}
