#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

enum class Gender{
Male,
Female,
Other
};

struct College{
uint16_t collegeID;
std::string collegeName;
std::string collegeAbreviation; 

};

struct Course{
uint16_t courseID;
uint16_t collegeID;
std::string courseName;
std::string courseAbbreviation;

};

struct Student{
std::string ID;
std::string firstName;
std::string lastName;
uint16_t courseID;
int year;
Gender gender;
};

struct AppData{
    std::vector<College> collegeRegistry;
    std::unordered_map<uint16_t, Course> courseRegistry;

    std::vector<Student> studentRecord;

};


