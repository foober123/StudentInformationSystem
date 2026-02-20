#include "appData.h"
#include "../guiState.h"
#include <cstdint>


void AppData::setCollegeRegistry(std::unordered_map<uint16_t, College> collegeRegistry){
    m_collegeRegistry = collegeRegistry;

    uint16_t maxID = 0;

    for (const auto& [id, college] : m_collegeRegistry)
    {
        // Build secondary index
        m_collegeCodeToID[college.collegeAbreviation] = id;

        if (id > maxID)
            maxID = id;
    }

    m_nextCollegeID = maxID + 1;

};

void AppData::setStudentRecord(std::unordered_map<uint32_t, Student> studentRecord){
    m_studentRecord = studentRecord;
};

void AppData::setProgramRegistry(std::unordered_map<uint16_t, Program> programRegistry){
    m_programRegistry = programRegistry;
    m_programCodeToID.clear();

    uint16_t maxID = 0;

    for (const auto& [id, program] : m_programRegistry)
    {
        // Build secondary index
        m_programCodeToID[program.programAbbreviation] = id;

        if (id > maxID)
            maxID = id;
    }

    m_nextProgramID = maxID + 1;

};



void AppData::initProgramIDCounter(){
    uint32_t maxID = 0;

    for (const auto& [id, program] : m_programRegistry)
    {
        if (id > maxID)
            maxID = id;
    }

    m_nextProgramID = maxID + 1;

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

bool AppData::checkStudentIDValidity(uint32_t id){
    const auto& it = m_studentRecord.find(id);
    if (it == m_studentRecord.end()) return false;

return true;
}

bool AppData::checkProgramIDValidity(uint16_t id){
    const auto& it = m_programRegistry.find(id);
    if (it == m_programRegistry.end()) return false;

return true;
}


bool AppData::checkCollegeIDValidity(uint16_t id){
    const auto& it = m_collegeRegistry.find(id);
    if (it == m_collegeRegistry.end()) return false;

return true;
}
