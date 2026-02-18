#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

struct Student;
struct Program;
struct College;
enum class Gender;

class Vault{
    public:
        explicit Vault(std::string studentFilePath, std::string courseFilePath, std::string collegeFilePath);

        std::unordered_map<uint32_t,Student> LoadStudents();
        std::unordered_map<uint16_t, College> LoadColleges();
        std::unordered_map<uint16_t, Program> LoadCourses();


        bool saveStudents(const std::unordered_map<uint32_t,Student>& studentList);
    private:
        Gender ParseGender(std::string field);
        char SerializeGender(Gender gender);
     
        std::string m_studentFilePath;
        std::string m_programFilePath;
        std::string m_collegeFilePath;



};

