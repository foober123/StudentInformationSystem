#include <string>
#include <unordered_map>
#include <cstdint>

struct StudentDraft;
struct CourseDraft;
enum class ERRORSTATE;

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
    void setCollegeRegistry(std::unordered_map<uint16_t, College>);
    void setStudentRecord(std::unordered_map<uint32_t, Student>);
    void setCourseRegistry(std::unordered_map<uint16_t, Course>);

    void initCourseIDCounter(); 
    void initCollegeIDCounter();
    void initStudentIDCounter();
   
    ERRORSTATE addStudentEntry(StudentDraft);
    ERRORSTATE editStudentEntry(StudentDraft, uint32_t); 
    void deleteStudentEntry(uint32_t);

    ERRORSTATE addCourseEntry(CourseDraft);
    ERRORSTATE editCourseEntry(CourseDraft, uint16_t);
    void deleteCourseEntry(uint16_t);


    //Used for Editing where the index is the address of the student
    const std::unordered_map<std::string, uint16_t> getcollegeCodeToID();
    const std::unordered_map<uint16_t, College>& getCollegeRegistry();
    std::unordered_map<uint16_t, Course>& getCourseRegistry();

    const std::unordered_map<std::string, uint16_t>& getcourseCodeToID();
    const std::unordered_map<uint32_t, Student>& getStudentRecord();
    
    Course getCourse(uint16_t key);
    College getCollege(uint16_t key);
    Student getStudent(uint32_t key);
    private:
    std::unordered_map<std::string, uint16_t> m_collegeCodeToID;
    std::unordered_map<uint16_t, College> m_collegeRegistry;

    std::unordered_map<std::string, uint16_t> m_courseCodeToID;
    std::unordered_map<uint16_t, Course> m_courseRegistry;

    uint16_t m_nextCourseID = 1;
    uint16_t m_nextCollegeID = 1;
    uint32_t m_nextStudentInternalID = 1;
    std::unordered_map<uint32_t, Student> m_studentRecord; 

};
