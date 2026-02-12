#pragma once
#include <string>
#include <vector>
#include <assert.h>

struct GuiState{
std::vector<size_t> displayOrder; 
int selectedStudent;
std::string searchBuffer;

bool showCollegeRegistry;
bool showCourseRegistry;

void init(){
selectedStudent = -1;
searchBuffer = "";
displayOrder = {}; 

showCollegeRegistry = false;
showCourseRegistry = false;
}

void defaultSortDisplayOrder(int students){
    assert(students > 0); 


    for(int i = 0; i < students; i++){
    displayOrder.push_back(i);
    }

}

};
