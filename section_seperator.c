#include "raylib.h"
#include <string.h>

void display_text_centered(char *text, int font_size, int vertical_offset,
		int WIDTH, char *color) {
	char *Dtext = text;

	Color TextColor;

	if (strcmp(color, "black") == 0) {
		TextColor = BLACK;
	} else {
		TextColor = WHITE;
	};

	// finding font width
	int Dtext_width = MeasureText(Dtext, font_size);

	// for centering
	int Dtext_xoffset = WIDTH / 2 - Dtext_width / 2;

	DrawText(Dtext, Dtext_xoffset, vertical_offset, font_size, TextColor);
}

void gamename_window(int WIDTH, int HEIGHT, int loops) {
	int temp_height = 210;

	if (loops <= 60) {
		temp_height = 265 - loops;
	}
	display_text_centered("StickSouls: AFRAID", 20, temp_height, WIDTH,
			"white");

}

int CreateButton(char *label, int fontsize, int padding[2], Color labelcolor,
		int posx, int posy, char *buttonshape, int width, int height,
		Color buttoncolor) {

	int mousex = GetMouseX();
	int mousey = GetMouseY();

	int Labelsize = MeasureText(label, fontsize);

	if (Labelsize > width - padding[0]) {
		width = Labelsize + padding[0] * 2;
	};

	if (height < (fontsize + padding[1])) {
		height = fontsize + padding[1] * 2;
	};

	if ((mousex > posx) && (mousex < (posx + width)) && (mousey > posy)
			&& (mousey < posy + height)) {

		buttoncolor = (Color ) { 140, 140, 140, 255 };

		if (IsMouseButtonDown(0)) {
			buttoncolor = (Color ) { 90, 90, 90, 255 };
		};
	}

	DrawRectangle(posx, posy, width, height, buttoncolor);
	DrawText(label, posx + padding[0], posy + padding[1], fontsize, labelcolor);

	return 0;
}

int mid_section_lines(int screenwith, int screenheight, int soul_dimentions[4],int midlines_width[3],int layers_x_pos[3]) {

	// create random lines
	// there are 4 layers of lines
	// lines can be 5% of full width -to- 30% of the full with
	// moving random speed
	int layers_thickness = 10;
	int number_of_layers = 3;
	int layers_toal_thikness = 100 + (number_of_layers*layers_thickness);
	int next_layer_ypos = (screenheight/2) - (layers_toal_thikness/2);

	for (size_t n = 0; n < number_of_layers; ++n) {
		DrawRectangle(layers_x_pos[n], next_layer_ypos, midlines_width[n] , layers_thickness, PURPLE);
		next_layer_ypos += layers_thickness + layers_toal_thikness/number_of_layers;
	}

	return 0;
}

int user_selection_bottom_layer(int screenwidth,int screenheight) {
	// creates a bottom layer where people can choose ammo type
	// has 9 rectangular box
	// two for showing user heath, coin and selected ammo type
	// other 7 for showing ammos

	int total_number_of_layers = 9;
	struct Color buttoncolor[] = {
							GREEN,
							GRAY,
							BLUE,
							WHITE,
							RED,
							PURPLE,
							GREEN,
							BLUE
						};


	for (size_t n = 0; n < total_number_of_layers; ++n) {
		int xpos_cur_rect = n*(screenwidth/total_number_of_layers);
		DrawRectangleLines(xpos_cur_rect, screenheight-30, screenwidth/total_number_of_layers, 30, buttoncolor[n]);


		BoundingBox x = {1,2};
	}

	return 0;
}

int detect_total_damage_and_drop_coins() {
	return 0;
}

