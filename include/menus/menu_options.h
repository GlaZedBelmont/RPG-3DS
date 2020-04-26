#pragma once


C2D_TextBuf OptionsTextBuf;
C2D_Text OptionsText;


typedef struct {
    bool sound;
    bool debug;
}config_t;

extern config_t config;


/*int Options_Read();

int Options_Write();*/


void Options_Draw();


