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
    stats stat;
}player;

static const char stats_text[] =
	"Name : %s\n" 
	"Attack: %i\n"
	"Defense: %i\n"
	"Magic: %i\n"
	"Speed: %i\n";


FILE *statfile;


////////////////



int Stats_Read();


int Stats_Write();

int Stats_Draw();