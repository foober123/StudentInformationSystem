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

void AppData::setCourseRegistry(std::unordered_map<uint16_t, Course> courseRegistry){
    m_courseRegistry = courseRegistry;
    m_courseCodeToID.clear();

    uint16_t maxID = 0;

    for (const auto& [id, course] : m_courseRegistry)
    {
        // Build secondary index
        m_courseCodeToID[course.courseAbbreviation] = id;

        if (id > maxID)
            maxID = id;
    }

    m_nextCourseID = maxID + 1;

};



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


