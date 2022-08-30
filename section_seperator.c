#include "raylib.h"


void display_text_centered(char* text,int font_size,int vertical_offset,int WIDTH){
    char* Dtext = text;

    // finding font width
    int Dtext_width = MeasureText(Dtext,font_size);
    
    // for centering
    int Dtext_xoffset = WIDTH/2 - Dtext_width/2;

    DrawText(Dtext, Dtext_xoffset, vertical_offset, font_size, BLACK);
}




void gamename_window(int WIDTH, int HEIGHT,int loops){
    int temp_height = 210;
    
    if (loops<=60)
    {
        temp_height= 265 - loops;
    }
    display_text_centered("StickSouls: AFRAID",20,temp_height,WIDTH);

}