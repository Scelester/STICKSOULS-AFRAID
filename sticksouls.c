#include <dirent.h>
#include <raylib.h>
#include <rlgl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "basic_frame.h"
#include "section_seperator.h"
#include "shitload_of_func.h"

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
				VIOLET);

		//		rlPopMatrix();

		display_text_centered("press anywhere to start the game", 25, 500,
				FULLSCREEN_WIDTH, "black");

		endload = regular_mainframe(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, mousex,
				mousey);

		CreateButton("Host Game", 20, (int[2] ) { 5, 5 }, WHITE,
				FULLSCREEN_WIDTH / 6, FULLSCREEN_HEIGHT - 150, "reactangle", 30,
				20, BLUE);
		CreateButton("Join Game", 20, (int[2] ) { 5, 5 }, WHITE,
				FULLSCREEN_WIDTH - 400, FULLSCREEN_HEIGHT - 150, "reactangle",
				30, 20, RED);

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

	SetMasterVolume(0.3);
	// ====================================================================

	// for loading images

	Texture2D only_soul = LoadTexture("assets/images/soul.png");
	int number_of_soul_sprite = only_soul.width / only_soul.height; // square soul
	float each_soul_width = only_soul.width / number_of_soul_sprite;
	Rectangle only_soul_frect = { 0.0f, 0.0f, each_soul_width,
			(float) only_soul.height };
	Vector2 soul_position = { FULLSCREEN_WIDTH / 2 - (each_soul_width / 2),
			(FULLSCREEN_HEIGHT - FULLSCREEN_HEIGHT / 4) };

	int frame_counter_for_soul = 0;
	int frame_speed_for_soul = 9;
	int current_soul_image_number = 0;

	int soul_moving_count = 0;

	// =====================================================================
	int loops = 0;
	int endgame;
	int actual_game_started = 0;

	// get midlines startng
	int midlines_width[] = { GetRandomValue(FULLSCREEN_WIDTH / 20,
			FULLSCREEN_WIDTH / (10 / 4)), GetRandomValue(FULLSCREEN_WIDTH / 20,
			FULLSCREEN_WIDTH / (10 / 4)), GetRandomValue(FULLSCREEN_WIDTH / 20,
			FULLSCREEN_WIDTH / (10 / 4)) };

	int mid_layers_xpos[3] = { 0, 0, 0 };

	int mid_lines_move_speed[] = { GetRandomValue(2, 10), GetRandomValue(2, 10),
			GetRandomValue(2, 10) };

	int turn[3] = { 0, 0, 0 };

	// top and bottom lines colors
	Color toplinecolor = RED;
	Color bottomlinecolor = BLUE;

	// start game loop
	while (!WindowShouldClose() && sectionmanager == 1) // Detect window close button or ESC key
	{
		frame_counter_for_soul++;

		soul_moving_count++;

		if (frame_counter_for_soul >= (60 / frame_speed_for_soul)) {
			frame_counter_for_soul = 0;
			current_soul_image_number++;

			if (current_soul_image_number > number_of_soul_sprite - 1)
				current_soul_image_number = 0;

			only_soul_frect.x = (float) current_soul_image_number
					* (float) only_soul.width / number_of_soul_sprite;
		}

		if (soul_moving_count >= (60 / frame_speed_for_soul)) {
			if (IsKeyDown(87)) {
				if (soul_position.y > -20) {
					soul_position.y -= 2;
				}

			}
			if (IsKeyDown(83)) {
				if (soul_position.y < FULLSCREEN_HEIGHT - only_soul.height) {
					soul_position.y += 2;
				}
			}
			if (IsKeyDown(65)) {
				if (soul_position.x > 0) {
					soul_position.x -= 4;
				}
			}
			if (IsKeyDown(68)) {
				if (soul_position.x < FULLSCREEN_WIDTH - each_soul_width) {
					soul_position.x += 4;
				}
			};
		};

		// Update
		//----------------------------------------------------------------------------------
		int mousex = GetMouseX();
		int mousey = GetMouseY();

		//----------------------------------------------------------------------------------
		// Begin drawing
		BeginDrawing();

		// draw the bottom line
		DrawLine(0, FULLSCREEN_HEIGHT - 1, FULLSCREEN_WIDTH,
				FULLSCREEN_HEIGHT - 1, bottomlinecolor);

		// own sidelines
		DrawLine(1,FULLSCREEN_HEIGHT/2,1,FULLSCREEN_HEIGHT,bottomlinecolor);
		DrawLine(FULLSCREEN_WIDTH-1,FULLSCREEN_HEIGHT/2,FULLSCREEN_WIDTH-1,FULLSCREEN_HEIGHT,bottomlinecolor);

		// opponent sidelines
		DrawLine(1,0,1,FULLSCREEN_HEIGHT/2,toplinecolor);
		DrawLine(FULLSCREEN_WIDTH-1,0,FULLSCREEN_WIDTH-1,FULLSCREEN_HEIGHT/2,toplinecolor);

		// draw the top line
		DrawLine(0, 0, FULLSCREEN_WIDTH, 1, toplinecolor);


		user_selection_bottom_layer(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT);

		// shooting animations
		if (IsKeyDown(32)) {
			DrawLine(0, FULLSCREEN_HEIGHT - 2, FULLSCREEN_WIDTH,
					FULLSCREEN_HEIGHT - 2, BLUE);
			DrawLine(0, FULLSCREEN_HEIGHT - 3, FULLSCREEN_WIDTH,
					FULLSCREEN_HEIGHT - 3, BLUE);
			DrawLine(0, FULLSCREEN_HEIGHT - 4, FULLSCREEN_WIDTH,
					FULLSCREEN_HEIGHT - 4, BLUE);
			DrawLine(2,FULLSCREEN_HEIGHT/2,2,FULLSCREEN_HEIGHT,bottomlinecolor);
			DrawLine(FULLSCREEN_WIDTH-2,FULLSCREEN_HEIGHT/2,FULLSCREEN_WIDTH-2,FULLSCREEN_HEIGHT,bottomlinecolor);


		}

		// Create zones [blue zone and red zone]

		// remove game name from screen and start the game.
		if (actual_game_started == 0) {

			gamename_window(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, loops);

			if (IsKeyDown(65) || IsKeyDown(68) || IsKeyDown(83)
					|| IsKeyDown(87)) {
				actual_game_started++;
			}
		}

		//	display the background music at top
		display_text_centered(actual_background_music_playing, 20, 0,
				FULLSCREEN_WIDTH, "white");

		// draw soul screen
		DrawTextureRec(only_soul, only_soul_frect, soul_position, BLUE);

		// draw middle moving layer
		if (actual_game_started == 1) {
			mid_section_lines(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, (int[4] ) {
							soul_position.x, soul_position.y, only_soul.width,
							only_soul.height }, midlines_width,
					mid_layers_xpos);

			for (size_t x = 0; x < 3; ++x) {
				if ((mid_layers_xpos[x] + midlines_width[x])
						>= FULLSCREEN_WIDTH) {
					turn[x] = 1;
				}
				if (mid_layers_xpos[x] <= 0) {
					turn[x] = 0;
				};
				if (turn[x] == 1) {
					mid_layers_xpos[x] -= mid_lines_move_speed[x];
				} else if (turn[x] == 0) {
					mid_layers_xpos[x] += mid_lines_move_speed[x];
				}
			}
		}

		// create the close buttons and close it when return value is 1
		endgame = regular_mainframe(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, mousex,
				mousey);

		// change top line color
		if (soul_position.y <= 0) {
			toplinecolor = BLUE;
		} else {
			toplinecolor = RED;
		}

		// End drawing
		EndDrawing();

		// count loops
		loops++;
		//----------------------------------------------------------------------------------

		if (endgame == 1) {
			// break the loop
			break;
		};
	}

	// close audio device
	CloseAudioDevice();

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

/* todo
 *
 *
 * */

