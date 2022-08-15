#include "raylib.h"
#include "section_seperator.c"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 500;


    InitWindow(0, 0, "Sticksouls : AFRAID");


    ToggleFullscreen();

    int FULLSCREEN_WIDTH = GetMonitorWidth(0);
    int FULLSCREEN_HEIGHT = GetMonitorHeight(0);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
       
        SetExitKey(0); // overide exit key "ESC"

        // Update
        //----------------------------------------------------------------------------------
        int mousex = GetMouseX();
        int mousey = GetMouseY();

        int closerposx = FULLSCREEN_WIDTH - 20;
        //----------------------------------------------------------------------------------
        
        if ((mousex >= closerposx -5)&&(mousex <= closerposx+30)&&(mousey>=0)&&(mousey<= 30)){
            DrawRectangle(closerposx - 5,0,30,30,RED);
            SetMouseCursor(4);
            if (IsMouseButtonDown(0)){
                CloseWindow();
            }
        }else{
            SetMouseCursor(0);
        }

        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            DrawText("x",closerposx,0,30,BLACK);

            show_starting_window(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}