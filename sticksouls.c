#include "raylib.h"
#include "section_seperator.c"
#include "basic_frame.c"
#include "time.h"
#include <stdio.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization

    const int screenWidth = 900;
    const int screenHeight = 500;


    InitWindow(0, 0, "Sticksouls : AFRAID");


    ToggleFullscreen();

    int FULLSCREEN_WIDTH = GetMonitorWidth(0);
    int FULLSCREEN_HEIGHT = GetMonitorHeight(0);



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second





    SetExitKey(0); // overide exit key "ESC"
    //--------------------------------------------------------------------------------------
    
    int sectionmanager = 0;



    // loading screen loop
    while (!WindowShouldClose()&&sectionmanager==0)
    {
        int mousex = GetMouseX();
        int mousey = GetMouseY();


        if (IsMouseButtonDown(0)){
            sectionmanager = 1;
        }

        BeginDrawing();

            regular_mainframe(FULLSCREEN_WIDTH,FULLSCREEN_HEIGHT,mousex,mousey);
    
        EndDrawing();
    }
    
    InitAudioDevice();

    // start game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        int mousex = GetMouseX();
        int mousey = GetMouseY();

        

        //----------------------------------------------------------------------------------
        BeginDrawing();
            regular_mainframe(FULLSCREEN_WIDTH,FULLSCREEN_HEIGHT,mousex,mousey);

            Testing_window(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    

    return 0;
}