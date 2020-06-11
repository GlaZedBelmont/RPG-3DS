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

#include "menu_debug.h"

#include "savedata.h"

#include "stats.h"

#include "music.h"

#include "maths.h"

#include "sfx.h"

#include "loadlevel.h"

C2D_TextBuf DebugTextBuf;
C2D_Text DebugText;

static int selection = 0;

//int arrow_offset;

void Debug_Draw() {

    DebugTextBuf = C2D_TextBufNew(4096);
    arrow_offset = 0;

    Savedata_Read();

    consoleInit(GFX_BOTTOM, NULL);


    while(aptMainLoop()) {
        
        hidScanInput();
        u32 kDown = hidKeysDown();
		//u32 kHeld = hidKeysHeld();

        C2D_TextBufClear(DebugTextBuf);

        char buf[160];


        if (kDown & KEY_B) 
            break;

        if (kDown & KEY_UP && selection > 0)
            selection--;

        if (kDown & KEY_DOWN && selection < 4)
            selection++;

        if (kDown & KEY_A) {

            if (selection == 0)
                Stats_Draw();

            if (selection == 1) {
                stopAudio();
                initAudio();
            }
                // Music_Draw();

            if (selection == 2) {
                int r = calcDamage(10, 94, 50, 11, 10);
                printf("Damage: %i\n", r);

            //    GetRandomInt(0, 100); something like a way to edit the stats to test attack power and all that?
            }

            if (selection == 3) {
                //Debug_Savedata_Draw();
            }
            if (selection == 4)
                break;
		}

        if (kDown & KEY_Y) {
            Savedata_Read(); // Debug 
        }

        if (kDown & KEY_X) {
            Savedata_Write();
        }

        if (selection == 0) 
			arrow_offset = 0;

		if (selection == 1)
			arrow_offset = 23;

        if (selection == 2)
			arrow_offset = 46;

        if (selection == 3)
			arrow_offset = 68;

        if (selection == 4)
			arrow_offset = 90;

        


        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);
		C2D_TargetClear(top, WHITE);

		C2D_DrawImageAt(battle_plains, 0, 0, 0.0f, NULL, 0.5f, 0.5f);
		C2D_DrawRectSolid(20, 20, 0.5f, 360, 200, C2D_Color32(25, 63, 12, 200));
        C2D_DrawRectangle(40, 40, 0.4f, 340, 180, C2D_Color32(15, 38, 7, 100), C2D_Color32(15, 38, 7, 100), C2D_Color32(15, 38, 7, 100), C2D_Color32(15, 38, 7, 100));



        snprintf(buf, sizeof(buf), debug_text);
        C2D_TextParse(&DebugText, DebugTextBuf, buf);
        C2D_TextOptimize(&DebugText);

        C2D_DrawText(&DebugText, 0, 60.0f, 30.0f, 0.5f, 0.75f, 0.75f);

        C2D_DrawTriangle(60, 42.0f + arrow_offset, RED, 40, 32.0f + arrow_offset, RED, 40, 52.0f + arrow_offset, RED, 0.5f);

        C3D_FrameEnd(0);
    }

}