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


void FadeIn(u8 R, u8 G, u8 B, int speed) {

    for (u8 A = 255; A < 0; A-=speed) {
        C2D_Fade(C2D_Color32(R, G, B, A));
    }

}

void FadeOut(u8 R, u8 G, u8 B, int speed) {
    u8 A = 0;
    int N;

    while(A != 255) {

        C2D_Fade(C2D_Color32(R, G, B, A));
        svcSleepThread(16);
        N++;
        int n = (int)(log(N) / log(5));
		if (pow(5, n) == N) A++;
    }

}