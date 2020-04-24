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

#define name 0
#define attack 1
#define defense 2
#define magic 3
#define speed 4

//static int selection = 0;

player glazy = {"Glazed", {10, 20, 20, 23}}; // Temp variable

int Stats_Read() {

    printf("\x1b[7;0H                             ");

    statfile = fopen("sdmc:/statfile.dat", "rb");
    if (statfile == NULL) {
        printf("\x1b[7;0HNo statfile.dat!");
        return 1;
    }
    fread(&glazy, sizeof(player), 1, statfile);
/*    printf("\x1b[7;0HReading from SD:/statfile.dat");
    printf("\x1b[8;0HName: %s Atk: %d Def: %d", glazy.Char_name, glazy.stat.atk, glazy.stat.def);*/
    fclose(statfile);
    return 0;
}
 
int Stats_Write() {

    printf("\x1b[7;0H                             ");
    printf("\x1b[8;0H                             ");


    statfile = fopen("sdmc:/statfile.dat", "wb");

    fwrite(&glazy, sizeof(player), 1, statfile);
    fclose(statfile);
    printf("\x1b[7;0HStats saved!");
    return 0;
}

int Stats_Draw() {

//	arrow_offset = 0;

    StatsTextBuf  = C2D_TextBufNew(4096);

	while(1) {

		hidScanInput();
		u32 kDown = hidKeysDown();
//		u32 kHeld = hidKeysHeld();

        C2D_TextBufClear(StatsTextBuf);

        char buf[160];
        
        if (kDown & KEY_B) break;
			
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);
		C2D_TargetClear(top, WHITE);

		C2D_DrawImageAt(battle_plains, 0, 0, 0.0f, NULL, 0.5f, 0.5f);
		C2D_DrawRectSolid(20, 20, 0.5f, 360, 200, C2D_Color32(25, 63, 12, 200));


        snprintf(buf, sizeof(buf), stats_text, glazy.Char_name, \
        glazy.stat.atk, glazy.stat.def, glazy.stat.mag, glazy.stat.spe);
        
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