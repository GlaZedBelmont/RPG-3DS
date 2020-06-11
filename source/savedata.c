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

#include "savedata.h"

#include "stats.h"
#include "menu_options.h"

FILE *file;


int Savedata_Read() {


    file = fopen("sdmc:/savedata.dat", "rb");
    if (file == NULL) { // Maybe the user doesn't have a save :shrug:
        return 1;
    }

    fread(&config, sizeof(config_t), 1, file); // Get the options
    fseek(file, sizeof(config_t), SEEK_SET);
    fread(&players, sizeof(player), 1, file); // Get the players stats
    fclose(file);
    return 0;
}


int Savedata_Write() {


    file = fopen("sdmc:/savedata.dat", "wb");

    fwrite(&config, sizeof(config_t), 1, file); // Write the options
    fwrite(&players, sizeof(players), 1, file); // Write the player's stats
    fclose(file);
    return 0;
}