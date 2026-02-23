#include <string>
#include <unordered_map>
#include <cstdint>

struct StudentDraft;
struct ProgramDraft;
struct CollegeDraft;
enum class ERRORSTATE;

enum class Gender{
Male,
Female,
Other
};

struct College{
std::string collegeName;
std::string collegeAbbreviation; 
};

struct Program{
uint32_t collegeID;
std::string programName;
std::string programAbbreviation;
};

struct Student{
std::string ID;
std::string firstName;
std::string lastName;
uint32_t programID;
int year;
Gender gender;
};

const Student INVALIDSTUDENT = {"Not Found", "Not Found", "Not Found", 65535, 65535, Gender::Other};
const College INVALIDCOLLEGE = {"Not Found", "Not Found"};
const Program INVALIDCOURSE = {65535, "Not Found", "Not Found"};

class AppData{
    public:
    
    StudentDraft makeStudentDraft(uint32_t);
    CollegeDraft makeCollegeDraft(uint32_t);
    ProgramDraft makeProgramDraft(uint32_t);

    void setCollegeRegistry(std::unordered_map<uint32_t, College>);
    void setStudentRecord(std::unordered_map<uint32_t, Student>);
    void setProgramRegistry(std::unordered_map<uint32_t, Program>);

    void initProgramIDCounter(); 
    void initCollegeIDCounter();
    void initStudentIDCounter();
   
    ERRORSTATE addStudentEntry(StudentDraft);
    ERRORSTATE editStudentEntry(StudentDraft, uint32_t); 
    void deleteStudentEntry(uint32_t);

    ERRORSTATE addProgramEntry(ProgramDraft);
    ERRORSTATE editProgramEntry(ProgramDraft, uint32_t);
    ERRORSTATE deleteProgramEntry(uint32_t);

    ERRORSTATE addCollegeEntry(CollegeDraft);
    ERRORSTATE editCollegeEntry(CollegeDraft, uint32_t);
    ERRORSTATE deleteCollege(uint32_t);

    bool checkStudentIDValidity(uint32_t);
    bool checkProgramIDValidity(uint32_t);
    bool checkCollegeIDValidity(uint32_t);

    const std::unordered_map<std::string, uint32_t>& getcollegeCodeToID();
    const std::unordered_map<uint32_t, College>& getCollegeRegistry();
    const std::unordered_map<uint32_t, Program>& getProgramRegistry();

    const std::unordered_map<std::string, uint32_t>& getProgramCodeToID();
    const std::unordered_map<uint32_t, Student>& getStudentRecord();
    
    Program getProgram(uint32_t key);
    College getCollege(uint32_t key);
    Student getStudent(uint32_t key);
    private:
    std::unordered_map<std::string, uint32_t> m_collegeCodeToID;
    std::unordered_map<uint32_t, College> m_collegeRegistry;

    std::unordered_map<std::string, uint32_t> m_programCodeToID;
    std::unordered_map<uint32_t, Program> m_programRegistry;

    std::unordered_map<uint32_t, Student> m_studentRecord; 

    uint32_t m_nextProgramID = 1;
    uint32_t m_nextCollegeID = 1;
    uint32_t m_nextStudentInternalID = 1;



    bool validateRepeatingStudentID(std::string);
    bool validateRepeatingStudentID(std::string, uint32_t);
    bool validateStudentID(std::string);
    bool validateStudentName(std::string);

    bool validateProgramCode(std::string);
    bool validateProgramCode(std::string, uint32_t);
    bool validateProgramCodeFormat(std::string);
    bool validateCollegeCode(std::string);

    bool validateRepeatingCollegeCode(std::string);
    bool validateRepeatingCollegeCode(std::string, uint32_t);
    bool validateCollegeNameFormat(std::string);
};
