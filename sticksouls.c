#include <dirent.h>
#include <raylib.h>
#include <rlgl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "basic_frame.c"
#include "section_seperator.c"
#include "shitload_of_func.c"

char background_musics[10][100];
int dirlooper = 0;
char actual_background_music_playing[200];

int get_background_music_dir() {
	DIR *d;
	char path[100] = "assets/music/background_music";
	struct dirent *dir;
	d = opendir(path);
	char full_path[1000];
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			//Condition to check regular file.
			if (dir->d_type) {
				full_path[0] = '\0';
				strcat(full_path, dir->d_name);

				if (dirlooper >= 2) {
					strcpy(background_musics[dirlooper - 2], full_path);
				}

				dirlooper++;
			}
		}
		closedir(d);
	}
	return (0);
}

void song_randomizer(void) {
	int random_generated_intereger = rand();
	dirlooper = dirlooper - 2;
	strcpy(actual_background_music_playing,
			background_musics[random_generated_intereger % dirlooper]);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char **argv[]) {
	// get random number from time
	srand(time(NULL));

	// for background_music
	get_background_music_dir();

	// set the random number
	song_randomizer();

	// image icon and shit
	Image iconimage = LoadImage("assets/images/sticksouls.ico");
	SetWindowIcon(iconimage);

	// Initialization

	// const int screenWidth = 900;
	// const int screenHeight = 500;

	InitWindow(0, 0, "Sticksouls : AFRAID");

	ToggleFullscreen();

	const int FULLSCREEN_WIDTH = GetMonitorWidth(0);
	const int FULLSCREEN_HEIGHT = GetMonitorHeight(0);

	SetTargetFPS(90);             // Set our game to run at 60 frames-per-second

	SetExitKey(0); // overide exit key "ESC"

	//--------------------------------------------------------------------------------------

	// section changer

	int sectionmanager = 0;
	// ======================================================================================

	// shape(triangle manager)
	Vector2 vertix_one_of_playTrangle = { FULLSCREEN_WIDTH / 3 + 40, 200 };
	Vector2 vertix_two_of_playTrangle = { FULLSCREEN_WIDTH / 3 + 40, 800 };
	Vector2 vertix_three_of_playTrangle = { FULLSCREEN_WIDTH / 1.5 + 120, 500 };

	int center_position[2] = { (vertix_one_of_playTrangle.x
			+ vertix_two_of_playTrangle.x + vertix_three_of_playTrangle.x) / 3,
			(vertix_one_of_playTrangle.y + vertix_two_of_playTrangle.y
					+ vertix_three_of_playTrangle.y) / 3 };

	// loading screen loop

	int trangle_time_counter = clock();
	int endload = 0;

	while (!WindowShouldClose() && sectionmanager == 0) {

		int mousex = GetMouseX();
		int mousey = GetMouseY();

		if (IsMouseButtonDown(0) || clock() >= 5000000) {
			sectionmanager = 1;
		}

		BeginDrawing();

//		rlPushMatrix();

		rlTranslatef(0, 0, 0);

		DrawTriangle(vertix_one_of_playTrangle, vertix_two_of_playTrangle,
				vertix_three_of_playTrangle,
				BLUE);

//		rlPopMatrix();

		display_text_centered("press anywhere to start the game", 25, 500,
				FULLSCREEN_WIDTH, "black");

		endload = regular_mainframe(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, mousex,
				mousey);

		EndDrawing();

		if ((clock() - trangle_time_counter) >= 500) {
			trangle_time_counter = clock();
			float *new_trangle_pos_list = get_each_trangle_rotation(
					center_position[0], center_position[1],
					vertix_one_of_playTrangle.x, vertix_two_of_playTrangle.x,
					vertix_three_of_playTrangle.x, vertix_one_of_playTrangle.y,
					vertix_two_of_playTrangle.y, vertix_three_of_playTrangle.y,
					1);

			vertix_one_of_playTrangle.x = new_trangle_pos_list[0];
			vertix_one_of_playTrangle.y = new_trangle_pos_list[1];
			vertix_two_of_playTrangle.x = new_trangle_pos_list[2];
			vertix_two_of_playTrangle.y = new_trangle_pos_list[3];
			vertix_three_of_playTrangle.x = new_trangle_pos_list[4];
			vertix_three_of_playTrangle.y = new_trangle_pos_list[5];
		};

		if (endload == 1) {
			break;
		}

	}

	//==========================================================================

	// for audio and music
	InitAudioDevice();

	char fullpath_to_bg_music[300];

	fullpath_to_bg_music[0] = '\0';

	strcat(fullpath_to_bg_music, "assets/music/background_music/");

	strcat(fullpath_to_bg_music, actual_background_music_playing);

	printf("%s\n", fullpath_to_bg_music);

	Sound music = LoadSound(fullpath_to_bg_music);

	PlaySound(music);

	SetMasterVolume(0.5);
	// ====================================================================

	// for loading images

	Texture2D only_soul = LoadTexture("assets/images/soul.png");
	Rectangle only_soul_frect = {0.0f,0.0f,(float)only_soul.width/23,(float)only_soul.height};


	int frame_counter_for_soul = 0;
	int frame_speed_for_soul = 20;
	int soul_image_number = 0;


	// =====================================================================
	int loops = 0;
	int endgame;



	// start game loop
	while (!WindowShouldClose() && sectionmanager == 1) // Detect window close button or ESC key
	{
		frame_counter_for_soul++;

		if (frame_counter_for_soul>=(60/frame_speed_for_soul))
		{
			frame_counter_for_soul = 0;
			soul_image_number++;

			if (soul_image_number > 22) soul_image_number = 0;

			only_soul_frect.x = (float)soul_image_number*(float)only_soul.width/23;

		}

		// Update
		//----------------------------------------------------------------------------------
		int mousex = GetMouseX();
		int mousey = GetMouseY();

		//----------------------------------------------------------------------------------
		BeginDrawing();

		endgame = regular_mainframe(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, mousex,
				mousey);

		display_text_centered(actual_background_music_playing, 20, 0,
				FULLSCREEN_WIDTH, "white");

		gamename_window(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, loops);

		DrawTextureRec(only_soul, only_soul_frect, (Vector2){500,300}, WHITE);


		EndDrawing();

		loops++;
		//----------------------------------------------------------------------------------

		if (endgame == 1) {
			break;
		};
	}

	CloseAudioDevice();

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
