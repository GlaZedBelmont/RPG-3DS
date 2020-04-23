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




void DrawOptions() {
    
    char buf[160];
    int test = 0;

    while(1) {
        
        hidScanInput();
        u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();


        if (kDown & KEY_B) break;

        if (kDown & KEY_UP) test++;
        if (kDown & KEY_DOWN) test--;


        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_SceneBegin(top);
		C2D_TargetClear(top, WHITE);

		C2D_DrawImageAt(battle_plains, 0, 0, 0.0f, NULL, 0.5f, 0.5f);
		C2D_DrawRectSolid(20, 20, 0.5f, 360, 200, C2D_Color32(25, 63, 12, 200));

        snprintf(buf, sizeof(buf), "Test value = %03i", test);
        C2D_TextParse(&OptionsText, g_dynamicBuf, buf);
        C2D_TextOptimize(&OptionsText);
        C2D_DrawText(&OptionsText, 0, 60.0f, 30.0f, 0.5f, 0.5f, 0.5f);

        C3D_FrameEnd(0);
    }

}