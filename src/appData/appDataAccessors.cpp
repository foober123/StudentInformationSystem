#include "appData.h"
#include "../guiState.h"
#include <cstdint>
#include <unordered_map>

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


const std::unordered_map<std::string, uint16_t>& AppData::getcourseCodeToID(){
    return m_courseCodeToID; 
};

const std::unordered_map<uint32_t, Student>& AppData::getStudentRecord(){
    return m_studentRecord;
};

const std::unordered_map<std::string, uint16_t> AppData::getcollegeCodeToID(){
    return m_collegeCodeToID;
}

const std::unordered_map<uint16_t, College>& AppData::getCollegeRegistry(){
    return m_collegeRegistry;
}

std::unordered_map<uint16_t, Course>& AppData::getCourseRegistry(){
    return m_courseRegistry;    
}; 


