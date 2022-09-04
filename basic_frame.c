#include "raylib.h"

void regular_mainframe(int FULLSCREEN_WIDTH,int FULLSCREEN_HEIGHT,int mouse_xpos,int mouse_ypos){

    ClearBackground(BLACK);

    int closerposx = FULLSCREEN_WIDTH - 20;
        //----------------------------------------------------------------------------------
        

        if ((mouse_xpos >= closerposx -5)&&(mouse_xpos <= closerposx+30)&&(mouse_ypos>=0)&&(mouse_ypos<= 30)){
            DrawRectangle(closerposx - 5,0,30,30,RED);
            SetMouseCursor(4);
            if (IsMouseButtonDown(0)){
                CloseWindow();
            }
        }else{
            SetMouseCursor(0);
        }


        DrawText("x",closerposx,0,30,WHITE);

}