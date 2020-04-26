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

#include "menu_options.h"

#include "savedata.h"

static int selection = 0;

config_t config;

const char saved_changes_prompt[] = 
    "Changes were saved!\n"
    "Press A or B to dismiss";



const char config_file[] =
    "Settings\n\n"
	"   Sound = %s\n"
	"   Debug = %s\n\n"
    "   Save";


void Options_Draw() {

    OptionsTextBuf = C2D_TextBufNew(4096);
    arrow_offset = 0;


    Savedata_Read();


    while(1) {
        
        hidScanInput();
        u32 kDown = hidKeysDown();
		//u32 kHeld = hidKeysHeld();

        C2D_TextBufClear(OptionsTextBuf);

        char buf[160];


        if (kDown & KEY_B) break;

        if (kDown & KEY_UP && selection > 0)
            selection--;

        if (kDown & KEY_DOWN && selection < 2)
            selection++;

        if (kDown & KEY_A) {
			if (selection == 0)
                config.sound = !config.sound;

			if (selection == 1)
                config.debug = !config.debug;

            if (selection == 2) {
                Savedata_Write();
                    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
                    C2D_SceneBegin(top);
                    C2D_DrawRectSolid(20, 20, 0.5f, 360, 150, C2D_Color32(25, 63, 12, 250));
                    C2D_TextBuf USWbuf  = C2D_TextBufNew(2048);

                    C2D_Text USW;

                    C2D_TextParse(&USW, USWbuf, saved_changes_prompt);
                    C2D_TextOptimize(&USW); 
                    C2D_DrawText(&USW, 0, 80.0f, 30.0f, 0.5f, 0.75f, 0.75f);
                    C3D_FrameEnd(0);

                while(1) {
                    hidScanInput();

                    if (hidKeysDown() & KEY_A || hidKeysDown() & KEY_B) break;

                }
            }
		}

        if (selection == 0) 
			arrow_offset = 45;

		if (selection == 1)
			arrow_offset = 68;

        if (selection == 2)
			arrow_offset = 115;

        if (kDown & KEY_Y) {
            Savedata_Read(); // Debug 
        }

/*        if (kDown & KEY_X) {
            Savedata_Write();
        }*/


        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);
		C2D_TargetClear(top, WHITE);

		C2D_DrawImageAt(battle_plains, 0, 0, 0.0f, NULL, 0.5f, 0.5f);
		C2D_DrawRectSolid(20, 20, 0.5f, 360, 200, C2D_Color32(25, 63, 12, 200));



        snprintf(buf, sizeof(buf), config_file, config.sound ? "Enabled" : "Disabled", config.debug ? "Enabled" : "Disabled");
        C2D_TextParse(&OptionsText, OptionsTextBuf, buf);
        C2D_TextOptimize(&OptionsText);

        C2D_DrawText(&OptionsText, 0, 60.0f, 30.0f, 0.5f, 0.75f, 0.75f);

        C2D_DrawTriangle(60, 42.0f + arrow_offset, RED, 40, 32.0f + arrow_offset, RED, 40, 52.0f + arrow_offset, RED, 0.5f);

        C3D_FrameEnd(0);
    }

}



