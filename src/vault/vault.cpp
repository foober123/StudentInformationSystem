#include "vault.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdint>
#include "../appData/appData.h"

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

std::vector<College> Vault::LoadColleges(){
    std::vector<College> colleges;

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
        c.collegeName = field;

        // CollegeAbbreviation
        std::getline(ss, field, ',');
        c.collegeAbreviation = field;

        colleges.push_back(c);
    }
    


    return colleges;
}

std::vector<Student> Vault::LoadStudents(){
    std::vector<Student> students;

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

        Student c{};

        std::getline(ss, field, ',');
        c.ID = field;    

        std::getline(ss, field, ',');
        c.firstName = field;

        std::getline(ss, field, ',');
        c.lastName = field;

        std::getline(ss, field, ',');
        c.courseID = static_cast<uint16_t>(std::stoi(field));
     
        std::getline(ss, field, ',');
        c.year = static_cast<uint16_t>(std::stoi(field));

        std::getline(ss, field, ',');
        c.gender = ParseGender(field);


        students.push_back(c);
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
        c.courseName = field;

        std::getline(ss, field, ',');
        c.courseAbbreviation = field;
        
        courses.insert({c.courseID, c});
    }


    return courses;
};

bool Vault::saveStudents(std::vector<Student>& studentList){
    std::ofstream file(m_studentFilePath);
    if (!file.is_open())
        return false;

    // Write header
    file << "ID,FirstName,LastName,CourseID,Year,Gender\n";

    for (const Student& s : studentList)
    {
        file
            << s.ID << ","
            << s.firstName << ","
            << s.lastName << ","
            << s.courseID << ","
            << s.year << ","
            << SerializeGender(s.gender)
            << "\n";
    }

    return true;

};
