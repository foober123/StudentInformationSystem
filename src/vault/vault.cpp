#include "vault.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdint>
#include "../appData/appData.h"
#include "../parsingHelpers.h"

Vault::Vault(std::string studentFilePath, std::string programFilePath, std::string collegeFilePath){
    m_studentFilePath = studentFilePath; 
    m_collegeFilePath = collegeFilePath;
    m_programFilePath = programFilePath;

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
        auto fields = parseCSVLine(line);
        uint32_t internalID;

        College c{};

        if (fields.size() < 3)
            continue;

        internalID = static_cast<uint16_t>(std::stoi(fields[0]));
        c.collegeName = trim(fields[1]);
        c.collegeAbreviation = trim(fields[2]);

        colleges.insert({internalID, c});
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

        auto fields = parseCSVLine(line);

        if (fields.size() < 7)
            continue; // or handle error properly

        uint32_t internalID = static_cast<uint32_t>(std::stoi(fields[0]));

        Student s{};

        s.ID        = trim(fields[1]);
        s.firstName = trim(fields[2]);
        s.lastName  = trim(fields[3]);
        s.programID = static_cast<uint16_t>(std::stoi(fields[4]));
        s.year      = static_cast<uint16_t>(std::stoi(fields[5]));
        s.gender    = ParseGender(trim(fields[6]));

        students.insert({ internalID, s });
    }

    return students;
};

std::unordered_map<uint16_t, Program> Vault::LoadCourses(){
    std::unordered_map<uint16_t, Program> programs;

    std::ifstream file(m_programFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return programs;
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        auto fields = parseCSVLine(line);

        if (fields.size() < 4)
            continue; // or handle error properly

        uint32_t internalID = static_cast<uint16_t>(std::stoi(fields[0]));

        Program c{};
        c.collegeID = static_cast<uint16_t>(std::stoi(fields[1]));
        c.programName = trim(fields[2]);
        c.programAbbreviation = trim(fields[3]);
        
        programs.insert({internalID, c});
    }


    return programs;
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
                << escapeCSV(s.firstName) << ","
                << escapeCSV(s.lastName) << ","
                << s.programID << ","
                << s.year << ","
                << SerializeGender(s.gender)
                << "\n";
        }
    }
    return true;
};

bool Vault::savePrograms(const std::unordered_map<uint16_t,Program>& programRegistry){
    std::ofstream file(m_programFilePath);
    if (!file.is_open())
        return false;

    // Write header
    file << "Internal_ID, CollegeID,ProgramName,ProgramCode\n";

    for (const auto& [internalID, program] : programRegistry)
    {

        {
            file
                << internalID << ","
                << program.collegeID << ","
                << escapeCSV(program.programName) << ","
                << escapeCSV(program.programAbbreviation)
                << "\n";
        }
    }
    return true;
};

bool Vault::saveColleges(const std::unordered_map<uint16_t,College>& collegeRegistry){
    std::ofstream file(m_programFilePath);
    if (!file.is_open())
        return false;

    // Write header
    file << "Internal_ID, CollegeID,ProgramName,ProgramCode\n";

    for (const auto& [internalID, college] : collegeRegistry)
    {

        {
            file
                << internalID << ","
                << escapeCSV(college.collegeName) << ","
                << escapeCSV(college.collegeAbreviation)
                << "\n";
        }
    }
    return true;
};
