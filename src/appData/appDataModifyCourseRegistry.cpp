#include "appData.h"
#include "../guiState.h"
#include <cstdint>
#include <unordered_map>

ERRORSTATE AppData::addCourseEntry(CourseDraft draft){
    Course course;
    course.courseAbbreviation = draft.courseAbbreviation;
    course.courseName = draft.courseName;
    course.collegeID = draft.collegeID;

    m_courseRegistry.insert({m_nextCourseID, course});
    m_nextCourseID++;
    return ERRORSTATE::NO_ERROR;
};

ERRORSTATE AppData::editCourseEntry(CourseDraft draft, uint16_t key){

    auto& course = m_courseRegistry.at(key);

    m_courseCodeToID.erase(course.courseAbbreviation);

    course.courseName = draft.courseName;
    course.courseAbbreviation = draft.courseAbbreviation;
    course.collegeID = draft.collegeID;

    m_courseCodeToID[draft.courseAbbreviation] = key;

    return ERRORSTATE::NO_ERROR;
};

void AppData::deleteCourseEntry(uint16_t key){
    auto it = m_courseRegistry.find(key);
    if (it == m_courseRegistry.end())
        return;

    m_courseCodeToID.erase(it->second.courseAbbreviation);
    m_courseRegistry.erase(it);

}
