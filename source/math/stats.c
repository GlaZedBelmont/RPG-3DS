#include <3ds.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <citro2d.h>
#include <citro3d.h>
#include <math.h>

#include "common.h"
#include "textures.h"
#include "graphics.h"

#include "stats.h"

#include "menu_options.h"

#include "savedata.h"

#include "keyboard.h"

#define name 0
#define level 1
#define exp 2
#define attack 3
#define defense 4
#define magic 5
#define speed 6




player players[4];

C2D_TextBuf StatsTextBuf;
C2D_Text StatsText;

//static int selection = 0;

//player glazy = {"Glazy", 10, 320, {20, 10, 5, 53}};


/*
	{"Glazy", 10, 452, {20, 10, 5, 53}},
	{"Eip", 30, 540, {45, 74, 12, 2}},
	{"Win9x", 60, 210, {80, 20, 78, 20}},
	{"Aerith", 10, 484, {10, 8, 87, 50}}
	
*/

static int selection = 0;

int Stats_Draw() {

//	arrow_offset = 0;

    StatsTextBuf  = C2D_TextBufNew(4096);

    Savedata_Read();

	while(aptMainLoop()) {

		hidScanInput();
		u32 kDown = hidKeysDown();
//		u32 kHeld = hidKeysHeld();

        C2D_TextBufClear(StatsTextBuf);

        char buf[160];
        
        if (kDown & KEY_B) break;


		if (kDown & KEY_A) {
			snprintf(players[selection].Char_name, 20, Keyboard_GetText("New Character", "Enter name"));
			Savedata_Write();
		}
			
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);
		C2D_TargetClear(top, WHITE);

		C2D_DrawImageAt(battle_plains, 0, 0, 0.0f, NULL, 0.5f, 0.5f);
		C2D_DrawRectSolid(20, 20, 0.5f, 360, 200, C2D_Color32(25, 63, 12, 200));

		if ((kDown & KEY_L ||kDown & KEY_LEFT) && selection > 0)
			selection--;

		if ((kDown & KEY_R ||kDown & KEY_RIGHT) && selection < 3)
			selection++;


/*        snprintf(buf, sizeof(buf), stats_text, glazy.Char_name, \
        glazy.lvl, glazy.xp, glazy.stat.atk, glazy.stat.def, glazy.stat.mag, glazy.stat.spe);*/
		snprintf(buf, sizeof(buf), stats_text, players[selection].Char_name, \
        players[selection].lvl, players[selection].xp, players[selection].stats.atk, \
		players[selection].stats.def, players[selection].stats.mag, players[selection].stats.spe);
        
        C2D_TextParse(&StatsText, StatsTextBuf, buf);
        C2D_TextOptimize(&StatsText);

        

		C2D_DrawText(&StatsText, 0, 60.0f, 30.0f, 0.5f, 0.5f, 0.5f);

/*		if (selection == 0) 
			arrow_offset = 0;

		if (selection == 1)
			arrow_offset = 24;

		if (selection == 2)
			arrow_offset = 45;

		if (selection == 3)
			arrow_offset = 69;

		C2D_DrawTriangle(45, 42.0f + arrow_offset, RED, 25, 32.0f + arrow_offset, RED, 25, 52.0f + arrow_offset, RED, 0.5f);
		printf("\x1b[2;0H%i", selection);
		printf("\x1b[3;0H%03i", arrow_offset);*/

        C3D_FrameEnd(0);

	}

	return 0;
}