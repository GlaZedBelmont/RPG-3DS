#include "textures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include <unistd.h>




#include "player.h"
#include "background.h"
#include "tiles.h"

static C2D_SpriteSheet player, background, tiles;

C2D_Image neutral, placeholder, neutralG, neutralCr, thief, knight, knight2, placeholderplayer;
C2D_Image battle_plains, smwback, yeet;
C2D_Image grass_tile64, grass_tile16;

C2D_Image temp;

void texload(){
	player = C2D_SpriteSheetLoad("romfs:/gfx/player.t3x");
	background = C2D_SpriteSheetLoad("romfs:/gfx/background.t3x");
	tiles = C2D_SpriteSheetLoad("romfs:/gfx/tiles.t3x");

	neutral = C2D_SpriteSheetGetImage(player, player_neutral_idx);
	neutralCr = C2D_SpriteSheetGetImage(player, player_neutralCr_idx);
	neutralG = C2D_SpriteSheetGetImage(player, player_neutralG_idx);
//	neutralVi = C2D_SpriteSheetGetImage(player, player_neutralVi_idx);
	thief = C2D_SpriteSheetGetImage(player, player_thief_idx);
	knight = C2D_SpriteSheetGetImage(player, player_knight_idx);
	knight2 = C2D_SpriteSheetGetImage(player, player_knight2_idx);
	placeholderplayer = C2D_SpriteSheetGetImage(player, player_placeholderplayer_idx);


	smwback = C2D_SpriteSheetGetImage(background, background_smwBack_idx);
	yeet = C2D_SpriteSheetGetImage(background, background_yeet_idx);
	battle_plains = C2D_SpriteSheetGetImage(background, background_plains_idx);
	grass_tile64 = C2D_SpriteSheetGetImage(tiles, tiles_grass64x64_idx);
	grass_tile16 = C2D_SpriteSheetGetImage(tiles, tiles_grass16x16_idx);
}

void Textures_Free() {
	C2D_SpriteSheetFree(player);
	C2D_SpriteSheetFree(background);
	C2D_SpriteSheetFree(tiles);
}


void getplayercolor(int color) {


}

