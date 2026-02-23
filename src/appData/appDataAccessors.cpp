#include "appData.h"
#include "../guiState/guiState.h"
#include <cstdint>
#include <unordered_map>

Student AppData::getStudent(uint32_t key){
    if(m_studentRecord.find(key) == m_studentRecord.end()) return INVALIDSTUDENT; 


    return m_studentRecord.at(key);
}

Program AppData::getProgram(uint32_t key){
    if(m_programRegistry.find(key) == m_programRegistry.end()) return INVALIDCOURSE; 

    return m_programRegistry.at(key);
}

College AppData::getCollege(uint32_t key){
    if(m_collegeRegistry.find(key) == m_collegeRegistry.end()) return INVALIDCOLLEGE; 

    return m_collegeRegistry.at(key);
}


const std::unordered_map<std::string, uint32_t>& AppData::getProgramCodeToID(){
    return m_programCodeToID; 
};

const std::unordered_map<uint32_t, Student>& AppData::getStudentRecord(){
    return m_studentRecord;
};

const std::unordered_map<std::string, uint32_t>& AppData::getcollegeCodeToID(){
    return m_collegeCodeToID;
}

const std::unordered_map<uint32_t, College>& AppData::getCollegeRegistry(){
    return m_collegeRegistry;
}

const std::unordered_map<uint32_t, Program>& AppData::getProgramRegistry(){
    return m_programRegistry;    
}; 


