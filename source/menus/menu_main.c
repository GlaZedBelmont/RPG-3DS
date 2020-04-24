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

#include "menu_main.h"

#include "menu_options.h"

#include "stats.h"


#include "sfx.h"

static int MMSelection = 0;

void Main_Menu_TextInit() {

	MainMenuTextBuf  = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer

	C2D_TextParse(&MainMenuText[0], MainMenuTextBuf, main_text);
	// Optimize the static text strings
    C2D_TextOptimize(&MainMenuText[0]); 

} 

void Main_Menu_TextExit() {
	// Delete the text buffers
	C2D_TextBufDelete(MainMenuTextBuf);
}

int Main_Menu_Draw() {

	arrow_offset = 0;

	while(1) {

		hidScanInput();
		u32 kDown = hidKeysDown();
//		u32 kHeld = hidKeysHeld();

		if (kDown & KEY_UP && MMSelection > 0) {
			MMSelection--;
		}

		if (kDown & KEY_DOWN && MMSelection < 4) { // Don't go over the qty of options
			MMSelection++;
		}

		if (kDown & KEY_A) {
			if (MMSelection == 0)
				FadeOut(0, 0, 0, 1);

				//if (config.debug == true) printf("\x1b[4;0HNot implemented yet, so fuck off!");

			if (MMSelection == 1) 
				Stats_Draw();

			if (MMSelection == 2) 
				Options_Draw();

			if (MMSelection == 3)
				//if (config.debug == true) printf("\x1b[6;0HDatagame Community! :blobaww:");

			if (MMSelection == 4)
				break;
			
		}

		if (kDown & KEY_START) break;

/*		if (kHeld & KEY_LEFT) arrow_offset--;

		if (kHeld & KEY_RIGHT) arrow_offset++;*/

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);
		C2D_TargetClear(top, WHITE);

		C2D_DrawImageAt(battle_plains, 0, 0, 0.0f, NULL, 0.5f, 0.5f);
		C2D_DrawRectSolid(20, 20, 0.5f, 360, 200, C2D_Color32(25, 63, 12, 200));
		C2D_DrawText(&MainMenuText[0], 0, 60.0f, 30.0f, 0.5f, 0.75f, 0.75f);

		if (MMSelection == 0) 
			arrow_offset = 0;

		if (MMSelection == 1)
			arrow_offset = 23;

		if (MMSelection == 2)
			arrow_offset = 46;

		if (MMSelection == 3)
			arrow_offset = 69;

		if (MMSelection == 4)
			arrow_offset = 92;

		C2D_DrawTriangle(45, 42.0f + arrow_offset, RED, 25, 32.0f + arrow_offset, RED, 25, 52.0f + arrow_offset, RED, 0.5f);
		C3D_FrameEnd(0);

/*		if (config.debug == true) {
			printf("\x1b[2;0H%i", MMSelection);
			printf("\x1b[3;0H%03i", arrow_offset);
		}*/

	}

	return 0;
}




