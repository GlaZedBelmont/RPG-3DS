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

#include "sfx.h"

#include "menu_options.h"

int L;

void FadeIn(u8 R, u8 G, u8 B, int speed) {

    for (u8 A = 255; A < 0; A-=speed) {
        C2D_Fade(C2D_Color32(R, G, B, A));
    }

}

void Transition(char *type, int speed, u32 color) {
    int i = 0;
    consoleClear();
    
    while (i < 400 / speed) {
        hidScanInput();

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_SceneBegin(top);
        if (strcmp(type, "rectangle") == 0) {
            C2D_DrawRectSolid(0, 0, 1.0f, speed * i, 240, color);
            C2D_DrawRectSolid(400, 0, 1.0f, speed * -i, 240, color);
        }
        if (strcmp(type, "circle") == 0) {
            C2D_DrawCircleSolid(200, 120, 1.0f, speed * i, color);
        }
        if (strcmp(type, "triangle") == 0) {
            // Horizontal
            C2D_DrawTriangle(0, 0, color, 0, 240, color, speed * i, 120, color,  1.0f);
            C2D_DrawTriangle(400, 0, color, 400, 240, color, 400 - speed * i, 120, color,  1.0f);

            // Vertical
            C2D_DrawTriangle(0, 240, color, 400, 240, color, 200, 240 - speed * i, color, 1.0f);
            C2D_DrawTriangle(0, 0, color, 400, 0, color, 200, 0 + speed * i, color, 1.0f);
        }
        C3D_FrameEnd(0);

        printf("\x1b[1;0H%i\n", i);
        i++;
        
        if (hidKeysDown() & KEY_START) {
            break;
        }
    }
    
}


int FadeOut(u8 i) {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_SceneBegin(top);
    C2D_Fade(C2D_Color32(0, 0, 0, i));
    C3D_FrameEnd(0);
    i++;

    if (i >= 255)
        return 1;
    return 0;
}