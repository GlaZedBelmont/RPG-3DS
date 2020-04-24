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

static int selection = 0;

FILE *optionfile;

config_t config;

const char unsaved_changes_warning[] = 
    "You have unsaved changes\n"
    "Would you like to save them?\n"
    "A - Yes    B - No";

const char config_file[] =
    "Settings\n\n"
	"   Sound = %s\n"
	"   Debug = %s";



int Options_Read() {

    //if (config.debug == true) consoleInit(GFX_BOTTOM, NULL);

    optionfile = fopen("sdmc:/optionsfile.dat", "rb");
    if (optionfile == NULL) {
        //if (config.debug == true) printf("\x1b[7;0HNo optionsfile.dat!");
        return 1;
    }
    fread(&config, sizeof(config_t), 1, optionfile);

/*    if (config.debug == true) {
        printf("\x1b[7;0HReading from SD:/optionsfile.dat");
        printf("\x1b[8;0HSound: %s Debug: %s", config.sound ? "true" : "false", config.debug ? "true" : "false");
    }*/

    fclose(optionfile);
    return 0;
}

int Options_Write() {

    //if (config.debug == true) consoleInit(GFX_BOTTOM, NULL);


    optionfile = fopen("sdmc:/optionsfile.dat", "wb");

    fwrite(&config, sizeof(config_t), 1, optionfile);
    fclose(optionfile);
    //if (config.debug == true) printf("\x1b[7;0HOptions saved!");
    return 0;
}


void Options_Draw() {

    OptionsTextBuf = C2D_TextBufNew(4096);
    arrow_offset = 0;

    int unsaved_changes = 0;

    Options_Read();

    //if (config.debug == true) consoleInit(GFX_BOTTOM, NULL);

    while(1) {
        
        hidScanInput();
        u32 kDown = hidKeysDown();
		//u32 kHeld = hidKeysHeld();

        C2D_TextBufClear(OptionsTextBuf);

        char buf[160];


        if (kDown & KEY_B) {
            if (unsaved_changes != 0) {
                C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
                C2D_SceneBegin(top);
                C2D_DrawRectSolid(20, 20, 0.5f, 360, 150, C2D_Color32(25, 63, 12, 250));
                C2D_TextBuf USWbuf  = C2D_TextBufNew(2048);

                C2D_Text USW;

                C2D_TextParse(&USW, USWbuf, unsaved_changes_warning);
                C2D_TextOptimize(&USW); 
                C2D_DrawText(&USW, 0, 80.0f, 30.0f, 0.5f, 0.75f, 0.75f);

                C2D_SceneBegin(bottom);
                //C2D_TargetClear(bottom, CLEAR);
                C2D_DrawRectSolid(0, 0, 0.5f, BOT_SCREEN_WIDTH, SCREEN_HEIGHT, C2D_Color32(25, 25, 25, 255));
                C3D_FrameEnd(0);

                while(1) {
                    svcSleepThread(32);
                    hidScanInput();
                    u32 kDown = hidKeysDown();
                    u32 kHeld = hidKeysHeld();

                    if (kDown & KEY_A) {
                        Options_Write();
                        break;
                    }
                    if (kDown & KEY_B) break;
                }
                
            }
            break;
        }

        if (kDown & KEY_UP && selection > 0)
            selection--;

        if (kDown & KEY_DOWN && selection < 1)
            selection++;

        if (kDown & KEY_A) {
            unsaved_changes = 1;
			if (selection == 0)
                config.sound = !config.sound;

			if (selection == 1)
                config.debug = !config.debug;
			
		}

        if (selection == 0) 
			arrow_offset = 45;

		if (selection == 1)
			arrow_offset = 68;

        if (kDown & KEY_Y) {
            Options_Read(); // Debug 
        }

        if (kDown & KEY_X) {
            Options_Write();
        }


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



