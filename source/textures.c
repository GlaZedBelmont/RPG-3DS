#include "textures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include <unistd.h>

#include "blob.h"

#include "background.h"

static C2D_SpriteSheet blob;

static C2D_SpriteSheet background;

C2D_Image temp;

void texload(){
	blob = C2D_SpriteSheetLoad("romfs:/gfx/blob.t3x");
	background = C2D_SpriteSheetLoad("romfs:/gfx/background.t3x");

	neutral = C2D_SpriteSheetGetImage(blob, blob_neutral_idx);
	neutralCr = C2D_SpriteSheetGetImage(blob, blob_neutralCr_idx);
	neutralG = C2D_SpriteSheetGetImage(blob, blob_neutralG_idx);
//	neutralVi = C2D_SpriteSheetGetImage(blob, blob_neutralVi_idx);
	smwback = C2D_SpriteSheetGetImage(background, background_smwBack_idx);
	yeet = C2D_SpriteSheetGetImage(background, background_yeet_idx);
	battle_plains = C2D_SpriteSheetGetImage(background, background_plains_idx);
}

void Textures_Free() {
	C2D_SpriteSheetFree(blob);
	C2D_SpriteSheetFree(background);
}


void getplayercolor(int color) {


}

