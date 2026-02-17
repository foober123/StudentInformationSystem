#include "appData.h"
#include "../guiState.h"
#include <cstdint>
#include <unordered_map>

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


