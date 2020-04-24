#pragma once



C2D_TextBuf MainMenuTextBuf;
C2D_Text MainMenuText[1];

static const char main_text[] =
	"Play\n"
	"Stats\n"
	"Options\n"
	"Credits\n"
	"Quit\n";
	


void Main_Menu_TextInit();


void Main_Menu_TextExit();

int Main_Menu_Draw();