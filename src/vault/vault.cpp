#include "vault.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdint>
#include "../appData/appData.h"
#include "../trim.h"

Vault::Vault(std::string studentFilePath, std::string courseFilePath, std::string collegeFilePath){
    m_studentFilePath = studentFilePath; 
    m_collegeFilePath = collegeFilePath;
    m_courseFilePath = courseFilePath;

}

Gender Vault::ParseGender(std::string field){
    if(field == "M") return Gender::Male;
    if(field == "F") return Gender::Female;

    return Gender::Other;

}

char Vault::SerializeGender(Gender gender){
    switch(gender){
        case Gender::Male: return 'M'; 
        case Gender::Female: return 'F';
        case Gender::Other: return 'O';
    }

    return 'O';
}

 std::unordered_map<uint16_t, College> Vault::LoadColleges(){
    std::unordered_map<uint16_t, College>  colleges;

    std::ifstream file(m_collegeFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return colleges;
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;

        College c{};

        // CollegeID
        std::getline(ss, field, ',');
        c.collegeID = static_cast<uint16_t>(std::stoi(field));

        // CollegeName
        std::getline(ss, field, ',');
        c.collegeName = trim(field);

        // CollegeAbbreviation
        std::getline(ss, field, ',');
        c.collegeAbreviation = trim(field);

        colleges.insert({c.collegeID, c});
    }
    


    return colleges;
}

 std::unordered_map<uint32_t,Student> Vault::LoadStudents(){
    std::unordered_map<uint32_t,Student>  students;

    std::ifstream file(m_studentFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return students;
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;
        uint32_t internalID;

        Student c{};

        std::getline(ss, field, ',');
        internalID = static_cast<uint32_t>(std::stoi(field));

        std::getline(ss, field, ',');
        c.ID = trim(field);    

        std::getline(ss, field, ',');
        c.firstName = trim(field);

        std::getline(ss, field, ',');
        c.lastName = trim(field);

        std::getline(ss, field, ',');
        c.courseID = static_cast<uint16_t>(std::stoi(field));
     
        std::getline(ss, field, ',');
        c.year = static_cast<uint16_t>(std::stoi(field));

        std::getline(ss, field, ',');
        c.gender = ParseGender(field);


        students.insert({internalID, c});
    }



    return students;
};

std::unordered_map<uint16_t, Course> Vault::LoadCourses(){
    std::unordered_map<uint16_t, Course> courses;

    std::ifstream file(m_courseFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return courses;
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;

        Course c{};

        std::getline(ss, field, ',');
        c.courseID = static_cast<uint16_t>(std::stoi(field));

        std::getline(ss, field, ',');
        c.collegeID = static_cast<uint16_t>(std::stoi(field));

        std::getline(ss, field, ',');
        c.courseName = trim(field);

        std::getline(ss, field, ',');
        c.courseAbbreviation = trim(field);
        
        courses.insert({c.courseID, c});
    }


    return courses;
};

bool Vault::saveStudents(const std::unordered_map<uint32_t,Student>& studentRecord){
    std::ofstream file(m_studentFilePath);
    if (!file.is_open())
        return false;

    // Write header
    file << "Internal_ID, ID,FirstName,LastName,CourseID,Year,Gender\n";

    for (const auto& pair : studentRecord)
    {
        const auto& internalID = pair.first;
        const auto& s = pair.second;

        {
            file
                << internalID << ","
                << s.ID << ","
                << s.firstName << ","
                << s.lastName << ","
                << s.courseID << ","
                << s.year << ","
                << SerializeGender(s.gender)
                << "\n";
        }
    }
    return true;
};
