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

#include "fs.h"


// Maybe I can universalize this code to work with other stuff so I can merge OptionsRead and StatsRead together :thonk:

/*void FileRead(FILE *file, void * st) {

    printf("\x1b[7;0H                             ");

    file = fopen("sdmc:/optionsfile.dat", "rb");
    if (file == NULL) {
        printf("\x1b[7;0HNo optionsfile.dat!");
        return 1;
    }
    
    struct config;
    fread(&st, sizeof(st), 1, file);
    printf("\x1b[7;0HReading from SD:/optionsfile.dat");
    printf("\x1b[8;0HSound: %s Debug: %s", config.sound ? "true" : "false", config.debug ? "true" : "false");
    fclose(file);
    return 0;
}*/