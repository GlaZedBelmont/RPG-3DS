#pragma once



C2D_TextBuf DebugTextBuf;
C2D_Text DebugText;


static const char debug_text[] =
	"Stats\n" // 0
	"Music\n" // 1
	"Variables\n" // 2
	"Savedata\n" // 3
	"Quit\n"; // 4

void Debug_Draw();