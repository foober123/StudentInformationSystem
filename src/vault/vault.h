#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

struct Student;
struct Course;
struct College;
enum class Gender;

class Vault{
    public:
        explicit Vault(std::string studentFilePath, std::string courseFilePath, std::string collegeFilePath);
        std::vector<Student> LoadStudents();
        //std::vector<Course> LoadCourses(std::string filePath);
        std::vector<College> LoadColleges();
        std::unordered_map<uint16_t, Course> LoadCourses();
        
        bool saveStudents(std::vector<Student>& studentList);
    private:
        Gender ParseGender(std::string field);
        char SerializeGender(Gender gender);
     
        std::string m_studentFilePath;
        std::string m_courseFilePath;
        std::string m_collegeFilePath;



};

