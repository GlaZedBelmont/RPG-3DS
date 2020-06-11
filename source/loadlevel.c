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
#include "loadlevel.h"

#include "music.h"

#include "sfx.h"


#include "combat.h"

float posX, posY, zoom, offsetX, offsetY, step;
bool zoomed;


char *transition_types[3] = {
    "rectangle",
    "circle",
    "triangle",
};

void Ajustoffset(char* vartoajust, float offsetofvar){ // Scrolling
	if (strcmp(vartoajust, "X") == 0) offsetX = offsetX + offsetofvar;
	if (strcmp(vartoajust, "Y") == 0) offsetY = offsetY + offsetofvar;
	if (strcmp(vartoajust, "pY") == 0) posY = posY + offsetofvar;
	if (strcmp(vartoajust, "pX") == 0) posX = posX + offsetofvar;
}


void loadOverworld()
{
    int i = 0;
    zoomed = true;
    zoom = 1.0f;

    posX = 0;
    posY = 0;
    offsetX = 0;
    offsetY = 0;
    PrintConsole bottomScreen;
    consoleInit(GFX_BOTTOM, &bottomScreen);


    while(true)
    {
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_SceneBegin(top);
        C2D_TargetClear(top, WHITE);
        
        hidScanInput();
        touchPosition touchPos;
        hidTouchRead(&touchPos);
        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();
        //u32 kUp   = hidKeysUp();

        if (kDown & KEY_START)
            break;

        if (kHeld & KEY_B) {
            step = 2.0f;
        }
        else {
            step = 1.0f;
        }

        if (kHeld & KEY_L) {
        /*    zoom = 1.0f;
            zoomed = false;*/
            drawMap(offsetX, offsetY);
        }
        else {
            //zoom = 2.0f;
            zoomed = true;
        }
        if (zoomed) {
            if (kHeld & KEY_DUP) {
                offsetY -= step;
            }
            if (kHeld & KEY_DDOWN) {
                offsetY += step;
            }
            if (kHeld & KEY_DLEFT) {
                offsetX -= step;
            }
            if (kHeld & KEY_DRIGHT) {
                offsetX += step;
            }
        }

       

        if (kDown & KEY_R) {
            if (i >= 2)
                i = 0;
            else
                i++;
        }

        //posX = zoomed ? 180 : 191;
        //posY = zoomed ? 75  : 98;
        posX = 168;
        posY = 72;

        if (offsetX <= -posX - 16)
            offsetX = -posX - 16;

        if (offsetY <= -posY - 32)
            offsetY = -posY -32;

        consoleSelect(&bottomScreen);
        consoleClear();
        printf("Zoom: %.2f\nOffsetX: %.2f\nOffsetY: %.2f\nPosX: %.2f\nPosY: %.2f\n", zoom, offsetX, offsetY, posX, posY);
        //printf("\x1b[28;0H%i   %i\n", touchPos.px, touchPos.py);
        printf("Transition: %s\n", transition_types[i]);
        printf("CPU:     %6.2f%%\n", C3D_GetProcessingTime()*6.0f);
		printf("GPU:     %6.2f%%\n", C3D_GetDrawingTime()*6.0f);
		printf("CmdBuf:  %6.2f%%\n", C3D_GetCmdBufUsage()*100.0f);

        //if (touch.p)


        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 16; ++j) {
                C2D_DrawImageAt(grass_tile64, (64 * zoom) * i - offsetX, (64 * zoom) * j - offsetY, 0.0f, NULL, zoom, zoom);
                C2D_DrawLine(0, (64 * zoom) * j - offsetY, BLACK, 400, (64 * zoom) * j - offsetY, BLACK, 2.0f, 0.1f);  // Outlines
                C2D_DrawLine((64 * zoom) * i - offsetX, 0, BLACK, (64 * zoom) * i - offsetX, 240, BLACK, 2.0f, 0.1f);
            }
        }
/*        for (int j = 0; j < 30; ++j) {
            for (int i = 0; i < 50; ++i) {
                C2D_DrawImageAt(grass_tile64, (32 * zoom) * i - offsetX, (32 * zoom) * j - offsetY, 0.0f, NULL, zoom / 2, zoom / 2);
                C2D_DrawLine(0, (64 * zoom) * j - offsetY, BLACK, 400, (64 * zoom) * j - offsetY, BLACK, 2.0f, 0.1f);  // Outlines
                C2D_DrawLine((64 * zoom) * i - offsetX, 0, BLACK, (64 * zoom) * i - offsetX, 240, BLACK, 2.0f, 0.1f);
            }
        }*/

/*        for (int i = 0; i < 1500; ++i) {
            C2D_DrawImageAt(grass_tile64, (32 * zoom) * (int)(i / 30) - offsetX, (32 * zoom) * (int)(i / 50) - offsetY, 0.0f, NULL, zoom, zoom);
            C2D_DrawLine(0, (64 * zoom) * j - offsetY, BLACK, 400, (64 * zoom) * j - offsetY, BLACK, 2.0f, 0.1f);  // Outlines
            C2D_DrawLine((64 * zoom) * i - offsetX, 0, BLACK, (64 * zoom) * i - offsetX, 240, BLACK, 2.0f, 0.1f);
        }*/

        C2D_DrawLine(0, 120, RED, 400, 120, RED, 2.0f, 0.2f);
        C2D_DrawLine(200, 0, RED, 200, 240, RED, 2.0f, 0.2f);
        C2D_DrawImageAt(placeholderplayer, posX, posY, 0.3f, NULL, zoom, zoom);
        
        C3D_FrameEnd(0);

        if (kDown & KEY_Y) {
            Transition(transition_types[i], 10, BLACK);
        }
    }
}



void drawMap(int posX, int posY)
{
    PrintConsole bottomScreen;
    consoleInit(GFX_BOTTOM, &bottomScreen);

    while(true)
    {
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_SceneBegin(top);
        C2D_TargetClear(top, WHITE);
        
        hidScanInput();
        touchPosition touchPos;
        hidTouchRead(&touchPos);
        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();
        u32 kUp   = hidKeysUp();

        if (kUp & KEY_L)
            break;

        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < 15; ++j) {
                C2D_DrawRectSolid(32 * i, 32 * j, 0.0f, 32, 32, C2D_Color32(70, 135, 80, 255));
                //C2D_DrawImageAt(grass_tile64, (32 * zoom) * i, (32 * zoom) * j, 0.0f, NULL, zoom / 2, zoom / 2);
                C2D_DrawLine(0, 16 * j, BLACK, 400, 16 * j, BLACK, 2.0f, 0.1f);  // Outlines
                C2D_DrawLine(16 * i, 0, BLACK, 16 * i, 240, BLACK, 2.0f, 0.1f);
                
            }
        }

/*        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < 15; ++j) {
                //C2D_DrawCircleSolid(16 * i + 8, 16 * j + 8, 0.2f, 4, BLACK);
                
            }
        }*/
        ;

        consoleSelect(&bottomScreen);
        consoleClear();
        printf("posX: %d\nposY: %d\n", (posX / 64), ((posY + 8) / 64));
        printf("CPU:     %6.2f%%\n", C3D_GetProcessingTime()*6.0f);
		printf("GPU:     %6.2f%%\n", C3D_GetDrawingTime()*6.0f);
		printf("CmdBuf:  %6.2f%%\n", C3D_GetCmdBufUsage()*100.0f);
        //printf("\x1b[28;0H%i   %i\n", touchPos.px, touchPos.py);
        
        C2D_DrawCircleSolid(((posX / 64) * 16) + 40, (((posY + 8) / 64) * 16) + 24, 0.2f, 4, BLACK);
//        C2D_DrawLine(0, 120, RED, 400, 120, RED, 2.0f, 0.5f);
//        C2D_DrawLine(200, 0, RED, 200, 240, RED, 2.0f, 0.5f);

        
        //C2D_DrawImageAt(knight2, posX, posY, 0.5f, NULL, zoom, zoom);
        
        C3D_FrameEnd(0);
    }
}       