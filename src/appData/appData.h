#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>


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



const Student INVALIDSTUDENT = {"Not Found", "Not Found", "Not Found", 65535, 65535, Gender::Other};
const College INVALIDCOLLEGE = {65535, "Not Found", "Not Found"};
const Course INVALIDCOURSE = {65535, 65535, "Not Found", "Not Found"};


class AppData{
    public:
    void setCollegeRegistry(std::vector<College>);
    void setStudentRecord(std::vector<Student>);
    void setCourseRegistry(std::unordered_map<uint16_t, Course>);
   
    const std::vector<Student>& getStudentRecord();
    const std::vector<College>& getCollegeRegistry();
    std::unordered_map<uint16_t, Course>& getCourseRegistry();          

    Student getStudent(int index);

    private:
    std::vector<College> m_collegeRegistry;
    std::unordered_map<uint16_t, Course> m_courseRegistry;
    std::vector<Student> m_studentRecord;



};
