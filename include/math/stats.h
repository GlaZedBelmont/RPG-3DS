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
	"Name : \n" 
	"Attack: \n"
	"Defense: \n"
	"Magic: \n"
	"Speed: \n";


FILE *statfile;


////////////////



int StatsRead();


int StatsWrite();

void Stats_TextInit();

void Stats_TextExit();

int Stats_Draw();