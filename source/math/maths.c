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

#include "maths.h"


int GetRandomInt(int min, int max) {

    srand(time(NULL) * svcGetSystemTick());
    int r = rand() % (max+1 - min) + min;

    return r;

}



int isCriticalHit(int target) {


    if (GetRandomInt(0, 100) >= target) return 2;
    else return 1;

}


int calcDamage(int level, int AtkStat, int AtkPwr, int EneDef, int Type) {

    int damage = (((((((((
        2 * level * isCriticalHit(95))
        / 5 + 2)
        * AtkStat * AtkPwr) 
        / EneDef) / 50) + 2)
        * Type / 10)
        * GetRandomInt(217, 255)) 
        / 255);


//    int damage = (((((((((2 * level * isCriticalHit(95))/ 5 + 2) * AtkStat * AtkPwr) / EneDef) / 50) + 2) * Type / 10) * GetRandomInt(217, 255)) / 255);

    return damage;
}