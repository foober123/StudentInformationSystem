#include <string>
#include <unordered_map>
#include <cstdint>

struct StudentDraft;
struct ProgramDraft;
enum class ERRORSTATE;

enum class Gender{
Male,
Female,
Other
};

struct College{
std::string collegeName;
std::string collegeAbreviation; 
};

struct Program{
uint16_t collegeID;
std::string programName;
std::string programAbbreviation;
};

struct Student{
std::string ID;
std::string firstName;
std::string lastName;
uint16_t programID;
int year;
Gender gender;
};

const Student INVALIDSTUDENT = {"Not Found", "Not Found", "Not Found", 65535, 65535, Gender::Other};
const College INVALIDCOLLEGE = {"Not Found", "Not Found"};
const Program INVALIDCOURSE = {65535, "Not Found", "Not Found"};

class AppData{
    public:
    void setCollegeRegistry(std::unordered_map<uint16_t, College>);
    void setStudentRecord(std::unordered_map<uint32_t, Student>);
    void setProgramRegistry(std::unordered_map<uint16_t, Program>);

    void initProgramIDCounter(); 
    void initCollegeIDCounter();
    void initStudentIDCounter();
   
    ERRORSTATE addStudentEntry(StudentDraft);
    ERRORSTATE editStudentEntry(StudentDraft, uint32_t); 
    void deleteStudentEntry(uint32_t);

    ERRORSTATE addProgramEntry(ProgramDraft);
    ERRORSTATE editProgramEntry(ProgramDraft, uint16_t);
    ERRORSTATE deleteProgramEntry(uint16_t);

    const std::unordered_map<std::string, uint16_t> getcollegeCodeToID();
    const std::unordered_map<uint16_t, College>& getCollegeRegistry();
    std::unordered_map<uint16_t, Program>& getProgramRegistry();

    const std::unordered_map<std::string, uint16_t>& getProgramCodeToID();
    const std::unordered_map<uint32_t, Student>& getStudentRecord();
    
    Program getProgram(uint16_t key);
    College getCollege(uint16_t key);
    Student getStudent(uint32_t key);
    private:
    std::unordered_map<std::string, uint16_t> m_collegeCodeToID;
    std::unordered_map<uint16_t, College> m_collegeRegistry;

    std::unordered_map<std::string, uint16_t> m_programCodeToID;
    std::unordered_map<uint16_t, Program> m_programRegistry;

    uint16_t m_nextProgramID = 1;
    uint16_t m_nextCollegeID = 1;
    uint32_t m_nextStudentInternalID = 1;
    std::unordered_map<uint32_t, Student> m_studentRecord; 

};
