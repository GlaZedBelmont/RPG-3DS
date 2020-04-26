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

void FadeOut(u8 R, u8 G, u8 B, u8 A) {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    while(1) {
		alpha+= 5;
		if (alpha > 255) break;
		C2D_Fade(C2D_Color32(0,0,0,alpha));
	}
    C3D_FrameEnd(0);
}