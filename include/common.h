#pragma once



C2D_TextBuf g_staticBuf, g_dynamicBuf;
C2D_Text g_staticText[3];
C2D_Font font[3];

int arrow_offset;

u8 alpha;

#define TOP_SCREEN_WIDTH  400
#define BOT_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define WHITE                 C2D_Color32(255, 255, 255, 255)
#define BLACK                 C2D_Color32(0, 0, 0, 255)
#define RED                   C2D_Color32(255, 0, 0, 255)
#define BLUE                  C2D_Color32(0, 0, 255, 255)
#define GREEN                 C2D_Color32(0, 255, 0, 255)
#define GRAY                  C2D_Color32(128, 128, 128, 255)
#define YELLOW                C2D_Color32(255, 255, 0, 255)
#define CLEAR                 C2D_Color32(0, 0, 0, 0)
