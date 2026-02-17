#include "../imgui/imgui_impl_sdl2.h"
#include "../imgui/imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include "settings.h"
#include "windows/gui.h"
#include "guiState.h"
#include "vault/vault.h"
#include "appData/appData.h"

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return -1;
    
    Vault vault(STUDENT_PATH, PROGRAM_PATH, COLLEGE_PATH);
    AppData appData;

    appData.setCollegeRegistry(vault.LoadColleges());
    appData.setCourseRegistry(vault.LoadCourses());
    appData.setStudentRecord(vault.LoadStudents());

    appData.initCollegeIDCounter();
    appData.initCourseIDCounter();
    appData.initStudentIDCounter();


    SDL_Window* window_ptr = SDL_CreateWindow(
            "Shrimple Student Information System", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            1280, 
            720, 
            SDL_WINDOW_SHOWN);

    SDL_SetWindowResizable(window_ptr, SDL_TRUE);

    if(!window_ptr){
        SDL_Quit();
        return -1;
    
    }

    SDL_Renderer* renderer_ptr = SDL_CreateRenderer(window_ptr, -1, 0);

    if(!renderer_ptr){
        SDL_DestroyWindow(window_ptr);
        SDL_Quit();
        return -1;

    }

    // 
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplSDL2_InitForSDLRenderer(
        window_ptr,
        renderer_ptr
            );
    
    ImGui_ImplSDLRenderer2_Init(renderer_ptr);
    GuiState guistate;
    guistate.init();
    guistate.defaultSortDisplayOrder(appData);


    bool running = true;
    bool myBool = false;

    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
            ImGui_ImplSDL2_ProcessEvent(&e);
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
        //PUT GUI STUFF BELOW HERE

        drawMenuBar(guistate); 
        drawTaskBar(guistate);
        drawEntryDisplay(guistate, appData);
        drawStudentDataTable(guistate, appData);
        if(guistate.showCollegeRegistry) drawCollegeRegistry(appData);
        if(guistate.showCourseRegistry) drawCourseRegistry(appData);
        if(guistate.currentError != ERRORSTATE::NO_ERROR) drawErrorBox(guistate);


        if(guistate.inputBoxStrategy != NULL) guistate.inputBoxStrategy(guistate, appData);          


        ImGui::Begin("test");
        ImGui::Text("Selected Student: %d", guistate.selectedStudent);
        ImGui::Checkbox("FAFD", &myBool);

        
        ImGui::End();


        ImGui::Render();

        SDL_SetRenderDrawColor(renderer_ptr, 171, 205, 239, 255);
        SDL_RenderClear(renderer_ptr);

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer_ptr);

        SDL_RenderPresent(renderer_ptr);
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer_ptr);
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();

    return 0;
}

