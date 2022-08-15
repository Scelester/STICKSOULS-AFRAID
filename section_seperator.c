#include "raylib.h"


void display_text_centered(char* text,int font_size,int vertical_offset,int WIDTH){
    char* Dtext = text;

    // finding font width
    int Dtext_width = MeasureText(Dtext,font_size);
    
    // for centering
    int Dtext_xoffset = WIDTH/2 - Dtext_width/2;

    DrawText(Dtext, Dtext_xoffset, vertical_offset, font_size, BLACK);
}


void show_starting_window(int WIDTH, int HEIGHT){
    
    display_text_centered("StickSouls: AFRAID",20,200,WIDTH);

}