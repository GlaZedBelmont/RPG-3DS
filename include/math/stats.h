#pragma once



C2D_TextBuf StatsTextBuf;
C2D_Text StatsText;

typedef struct {
    int atk;
    int def;
    int mag;
    int spe;
}stats;

typedef struct {
    char Char_name[20];
    int lvl;
    int xp;
    stats stat;
}player;

static const char stats_text[] =
	"Name : %s\n"
    "Level : %i\n"
    "XP : %i\n" 
	"Attack: %i\n"
	"Defense: %i\n"
	"Magic: %i\n"
	"Speed: %i\n";

extern player glazy;



////////////////



/*int Stats_Read();


int Stats_Write();*/

int Stats_Draw();