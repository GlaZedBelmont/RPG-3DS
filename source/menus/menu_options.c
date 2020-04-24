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



FILE *optionfile;

config_t config;

const char *config_file =
	"Config_ver = \n"
	"Sound = \n"
	"Debug = ";



int OptionsRead() {

    printf("\x1b[7;0H                             ");

    optionfile = fopen("sdmc:/optionsfile.dat", "rb");
    if (optionfile == NULL) {
        printf("\x1b[7;0HNo optionsfile.dat!");
        return 1;
    }
    fread(&config, sizeof(config_t), 1, optionfile);
    printf("\x1b[7;0HReading from SD:/optionsfile.dat");
    printf("\x1b[8;0HSound: %s Debug: %s", config.sound ? "true" : "false", config.debug ? "true" : "false");
    fclose(optionfile);
    return 0;
}

int OptionsWrite() {

    printf("\x1b[7;0H                             ");
    printf("\x1b[8;0H                             ");


    optionfile = fopen("sdmc:/optionsfile.dat", "wb");

    fwrite(&config, sizeof(config_t), 1, optionfile);
    fclose(optionfile);
    printf("\x1b[7;0HOptions saved!");
    return 0;
}


void DrawOptions() {

    int test = 0;
    OptionsTextBuf  = C2D_TextBufNew(4096);

    config.sound = true;

    while(1) {
        
        hidScanInput();
        u32 kDown = hidKeysDown();
		//u32 kHeld = hidKeysHeld();

        C2D_TextBufClear(OptionsTextBuf);

        char buf[160];


        if (kDown & KEY_B) break;

        if (kDown & KEY_UP) test++;
        if (kDown & KEY_DOWN) test--;


        if (kDown & KEY_A) {
            OptionsRead();
        }

        if (kDown & KEY_X) {
            OptionsWrite();
        }


        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);
		C2D_TargetClear(top, WHITE);

		C2D_DrawImageAt(battle_plains, 0, 0, 0.0f, NULL, 0.5f, 0.5f);
		C2D_DrawRectSolid(20, 20, 0.5f, 360, 200, C2D_Color32(25, 63, 12, 200));



        snprintf(buf, sizeof(buf), config_file);
        C2D_TextParse(&OptionsText, OptionsTextBuf, buf);
        C2D_TextOptimize(&OptionsText);

        C2D_DrawText(&OptionsText, 0, 60.0f, 30.0f, 0.5f, 0.5f, 0.5f);

        C3D_FrameEnd(0);
    }

}



