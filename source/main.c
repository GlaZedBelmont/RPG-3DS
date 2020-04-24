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


bool grounded = false, dead = false, pausegame = false, debug = true;
float posY, posX, Vmomajust = 0, Vmomentum = 0, ajustpY = 0, ajustoY = 0, Hmomentum = 0, ajustpX = 0, ajustoX = 0, offsetX = 0, offsetY = 0;
/*float acc[4] = {1, 0.6f, 0.4f, 0.3f};
float dec[4] = {2, 2.8f, 2.4f, 3.75f};*/

int temphorz, tempvert, aapress = 0;

bool LRpress = false;

int a = 0;
int i = 0;
bool init = false;


float current_menu; // See menus.txt for info :P


typedef struct {
    float x;
    float y;
    u32 currentlyPressed; // not sure how the 3ds handles that but you could use this for buttons like abyx
} inputs;

void Ajustoffset(char* vartoajust, float offsetofvar){ // Scrolling
	if (strcmp(vartoajust, "X") == 0) offsetX = offsetX + offsetofvar;
	if (strcmp(vartoajust, "Y") == 0) offsetY = offsetY + offsetofvar;
	if (strcmp(vartoajust, "pY") == 0) posY = posY + offsetofvar;
	if (strcmp(vartoajust, "pX") == 0) posX = posX + offsetofvar;
}

int keysmove(int select){
	circlePosition pos;
	hidCircleRead(&pos);
	int directX = 0, directY = 0, result = 0;
    //hidScanInput();
	u32 kDown = hidKeysDown();
	u32 kHeld = hidKeysHeld();
	if (select == 1){

        if (pos.dx > 80 || kHeld & KEY_DRIGHT) 
            directX = 1;
        else if (pos.dx < -80 || kHeld & KEY_DLEFT)
            directX = -1;


        if (pos.dy > 80 || kHeld & KEY_DUP) 
            directY = 1;
        else if (pos.dy < -80 || kHeld & KEY_DDOWN)
            directY = -1;

        if (directX == -1 && directY == 0)  // Refer to a numberpad, 5 is unused
            result = 4; //left
        else if (directX == 0 && directY == -1)
            result = 2; //down
        else if (directX == 1 && directY == 0)
            result = 6; //right
        else if (directX == 0 && directY == 1)
            result = 8; //up
        else if (directX == -1 && directY == -1)
            result = 1; //downleft
        else if (directX == -1 && directY == 1)
            result = 7; //upleft
        else if (directX == 1 && directY == -1)
            result = 3; //downright
        else if (directX == 1 && directY == 1)
            result = 9; //upright
    }

	if (select == 2){
		if (kHeld && KEY_A) result = 1;
	}
	return result;
}

/*float calcHmomentum(float posX, float offsetX) { // Horizontal speed
    LRpress = false;
    int keysres = keysmove(1);
    if ((keysres >= 2 || keysres <= 8) && keysres != 5 && keysres != 0)
        LRpress = true;

    if (LRpress == true) {
        if (grounded == true) {
            if (keysmove(1) == 7) 
                Hmomentum = Hmomentum - acc[1];
            else if (keysmove(1) == 3)
                Hmomentum = Hmomentum + acc[1];
        }
        else if (grounded == false) {
            if (keysmove(1) == 7)
                Hmomentum = Hmomentum - acc[2];
            else if (keysmove(1) == 3)
                Hmomentum = Hmomentum + acc[2];
        }
    }

    else if (LRpress == false && Hmomentum != 0) {
        if (Hmomentum > 0.7f)
            Hmomentum = Hmomentum - 0.2f;
    	if (Hmomentum < -0.7f)
            Hmomentum = Hmomentum + 0.2f;
    	if (Hmomentum > -0.7f && Hmomentum < 0.7f)
            Hmomentum = 0;
    }

    if (Hmomentum > 5)
        Hmomentum = 5;
    else if (Hmomentum < -5)
        Hmomentum = -5;

    Ajustoffset("X", ajustoX);
    Ajustoffset("pX", ajustpX);
    ajustpX = 0, ajustoX = 0;

    float temphmom = 0;
    temphmom = Hmomentum;
    return temphmom;
    
}

float calcVmomentum(float locY, float offsetY, int apress, float boost){
    //printf("%f\n", offsetY);
	if (Vmomajust != 0) Vmomentum = Vmomentum + Vmomajust;

 	if (locY < 100 && Vmomentum < 0) { 
        ajustpY = ajustpY - Vmomentum;
        ajustoY = ajustoY + Vmomentum;
    }
    else if (locY < 100 && Vmomentum == 0) {
        ajustpY = ajustpY + 1;
        ajustoY = ajustoY - 1;
    }
    if (locY > 160 && offsetY < 0 && Vmomentum > 0) {
        ajustpY = ajustpY - Vmomentum;
        ajustoY = ajustoY + Vmomentum;
    }
	else if (locY > 160 && offsetY < 0 && Vmomentum == 0) {
        ajustpY = ajustpY - 1;
        ajustoY = ajustoY + 1; }

	int season = 4;
	
    if (grounded == true && apress == 1 && season == 4) Vmomentum = Vmomentum - 3.0f;
    else if (grounded == true && apress == 1 && season == 1) Vmomentum = Vmomentum - 5.0f;
    else if (grounded == true && apress == 1) Vmomentum = Vmomentum - 4.0f;
    else if ((keysmove(2) == 1) && season == 3 && Vmomentum > 0)  Vmomentum = Vmomentum - 0.12f;

    if (offsetY > 0) ajustoY = ajustoY - offsetY;

 	if (grounded == true && Vmomentum > 0)
        Vmomentum = 0;
 	if (grounded == false) 
        Vmomentum = Vmomentum + 0.15f;

 	grounded = false;

    Ajustoffset("Y", ajustoY);
    Ajustoffset("pY", ajustpY);
    ajustpY = 0, ajustoY = 0, Vmomajust = 0;

    float tempvmom = 0;
    tempvmom = Vmomentum + boost;
    printf("\x1b[6;0H%f\n", boost);
    return tempvmom;
}*/





/*int platcoll(int locX, int locY, float posX, float posY, int pWidth, int pHeight) { // loc = platform, pos = player, pWidth/pHeight = dimensions
    //printf("%i\n", locX + pWidth);
    C2D_DrawRectSolid(locX, locY, 0.5f, pWidth, 1, GREEN); // Top line
    C2D_DrawRectSolid(locX, locY + pHeight , 0.5f, pWidth, 1, GREEN); // Bottom line
    C2D_DrawRectSolid(locX, locY, 0.5f, 1, pHeight, GREEN); // Left line
    C2D_DrawRectSolid(locX + pWidth, locY, 0.5f, 1, pHeight, GREEN); // Right line

    //if (posX < locX + pWidth) printf()


    if ((posX < locX + pWidth && posX > locX) || (posX + blob.width > locX && posX < locX + pWidth)) { // Is the player between the left and right hitboxes of a platform // // if blob.left is past   // posX < locX + topright && posX + blob.width > locX
        printf("\x1b[7;0H                                 ");
        printf("\x1b[8;0H                                 ");
        printf("\x1b[9;0H                                 ");
        printf("\x1b[10;0H                                 ");
        if (posY + blob.height >= locY + 2 && posY <= locY + pHeight) {
        //    posY = locY;

            // Check if player touched left side or right side
            if (posX + blob.width > locX && posX + blob.width < locX + pWidth / 2) { // Left
                Hmomentum = -Hmomentum;
                //printf("\x1b[7;0H                                 ");
                printf("\x1b[7;0HPlayer is touching the left side");
            }
            else if (posX < locX + pWidth && posX > locX + pWidth / 2) { // Right
                Hmomentum = -Hmomentum;
                //printf("\x1b[9;0H                                 ");
                printf("\x1b[9;0HPlayer is touching the right side");
            }
            //posX = locX;
        }

        if (posY + blob.height >= locY) { // Did the player go through the platform

            if (posY + blob.height <= locY + pHeight / 2) { // Is the player on top? aka "higher" than the top
                posY = locY - 5;
                grounded = true;
               // printf("\x1b[8;0H                                 ");
                printf("\x1b[8;0HPlayer is touching the top");
                Vmomentum = 0;
            }

            else if (posY <= locY + pHeight && posY >= locY + pHeight -2) { // Is the player under? aka approx height of platform - blob height which equal ~10-15
                posY = locY + 32;
              //  printf("\x1b[10;0H                                 ");
                printf("\x1b[10;0HPlayer is touching the bottom");
                Vmomentum = 0.15f;
            }
        }
    }
    
    // Use posY to check the top of blob
    // Use posY + blob.height to check the bottom of blob
    // Use posX to check the left of blob
    // Use posX + blob.width to check the right of blob


    return 0;
}*/
////////////////////////////////////


// Ah shit, here we go again!

int main(int argc, char **argv)
{

    gfxInitDefault();
	gfxSetDoubleBuffering(GFX_TOP, false);
	gfxSetDoubleBuffering(GFX_BOTTOM, false);
	romfsInit();



    // Citro stuff
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    texload();
    Main_Menu_TextInit();

    float size = 2.0f;


    int sizeX = 1;
    int sizeY = 1;

 
    //if (config.debug == true) consoleInit(GFX_BOTTOM, NULL);


    while (aptMainLoop())
    {
    /*    hidScanInput();
        
        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();
        u32 kUp = hidKeysUp(); */



        
        if (Main_Menu_Draw() == 0) break;
    
    

        gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
    Main_Menu_TextExit();
    Textures_Free();
	C2D_Fini();
	C3D_Fini();
	romfsExit();
	gfxExit();
	return 0;
}