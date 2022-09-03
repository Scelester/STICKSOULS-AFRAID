#include "raylib.h"
#include "rlgl.h"

#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

#include "section_seperator.c"
#include "basic_frame.c"
#include "shitload_of_func.c"

char background_musics[10][100]; 
int dirlooper = 0;
char actual_background_music_playing[200];

int get_background_music_dir()
{
    DIR *d;
    struct dirent *dir;
    char path[100]="assets/music/background_music";
    d = opendir(path);
    char full_path[1000];
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //Condition to check regular file.
            if(dir->d_type){
                full_path[0]='\0';
                strcat(full_path,dir->d_name);

                if (dirlooper>=2){
                    strcpy(background_musics[dirlooper-2],full_path);
                }
                
                dirlooper++;
            }
        }
        closedir(d);
    }
    return(0);     
}

void song_randomizer(void){
    int random_generated_intereger = rand();
    dirlooper = dirlooper -2;
    strcpy(actual_background_music_playing,background_musics[random_generated_intereger % dirlooper]);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char **argv[])
{   
    srand ( time(NULL) );

    get_background_music_dir();
    

    song_randomizer();
    
    // image and shit
    Image iconimage = LoadImage("assets/images/sticksouls.ico");
    SetWindowIcon(iconimage);
    

    // Initialization

    // const int screenWidth = 900;
    // const int screenHeight = 500;


    InitWindow(0, 0, "Sticksouls : AFRAID");


    ToggleFullscreen();

    const int FULLSCREEN_WIDTH = GetMonitorWidth(0);
    const int FULLSCREEN_HEIGHT = GetMonitorHeight(0);



    SetTargetFPS(90);               // Set our game to run at 60 frames-per-second

    SetExitKey(0); // overide exit key "ESC"
    
    
    //--------------------------------------------------------------------------------------
    
    int sectionmanager = 0;


    float rotation_angle = 0.0f;

    Vector2 vertix_one_of_playTrangle = {FULLSCREEN_WIDTH/3+40,200};
    Vector2 vertix_two_of_playTrangle = {FULLSCREEN_WIDTH/3+40,800};
    Vector2 vertix_three_of_playTrangle = {FULLSCREEN_WIDTH/1.5+120,500};

    int center_position[2] = {
        (vertix_one_of_playTrangle.x+vertix_two_of_playTrangle.x+vertix_three_of_playTrangle.x)/3,
        (vertix_one_of_playTrangle.y+vertix_two_of_playTrangle.y+vertix_three_of_playTrangle.y)/3
        };

    get_each_trangle_rotation(center_position[0], center_position[1], 
                                vertix_one_of_playTrangle.x,vertix_one_of_playTrangle.y,
                                vertix_two_of_playTrangle.x,vertix_two_of_playTrangle.y,
                                vertix_three_of_playTrangle.x,vertix_three_of_playTrangle.y,
                                20);
    
    // loading screen loop
    while (!WindowShouldClose()&&sectionmanager==0)
    {
        int mousex = GetMouseX();
        int mousey = GetMouseY();


        if (IsMouseButtonDown(0)||clock()>=5000000){
            sectionmanager = 1;
        }

        BeginDrawing();

            DrawCircle(591,699,20,BLACK);

            rlPushMatrix();

            rlTranslatef(
                0,
                0,
                0
            );

            DrawTriangle(
                        vertix_one_of_playTrangle,
                        vertix_two_of_playTrangle,
                        vertix_three_of_playTrangle,
                        BLUE
                        );

            rlPopMatrix();

            // display_text_centered("press anywhere to start the game",25,500,FULLSCREEN_WIDTH);

            regular_mainframe(FULLSCREEN_WIDTH,FULLSCREEN_HEIGHT,mousex,mousey);

            rotation_angle += 0.05;





        EndDrawing();
    }
    

    // for audio and music
    InitAudioDevice();


    char fullpath_to_bg_music[300];
    
    fullpath_to_bg_music[0] = '\0';

    strcat(fullpath_to_bg_music,"assets/music/background_music/");
    
    strcat(fullpath_to_bg_music,actual_background_music_playing);
    
    printf("%s\n",fullpath_to_bg_music);

    Sound music = LoadSound(fullpath_to_bg_music);

    PlaySound(music);
    
    SetMasterVolume(0.5);
    
    int loops = 0;

    // start game loop
    while (!WindowShouldClose() && sectionmanager==1)    // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        int mousex = GetMouseX();
        int mousey = GetMouseY();
        
        //----------------------------------------------------------------------------------
        BeginDrawing();
            regular_mainframe(FULLSCREEN_WIDTH,FULLSCREEN_HEIGHT,mousex,mousey);
            
            display_text_centered(actual_background_music_playing,20,0,FULLSCREEN_WIDTH);

            gamename_window(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT,loops);

        EndDrawing();

        loops++;
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    

    return 0;
}