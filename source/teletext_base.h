/*********************************************************/
/* teletext_base.h ***************************************/
/*********************************************************/

/* The teletext code is structured in 3 layers:
1. User layer
2. Library layer
3. Base layer
This layer is the base layer and includes core SDL, Font
& file processing functions, #defines and typedefs
The SDL functions in particular help abstract the Library
layer away from the details of SDL rendering*/

#include "SDL2/SDL.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* GENERAL USE *******************************************/
#define BYTE                8
#define NEG_ONE             -1

FILE*         gfopen(char* fn, char* mode);
void*         gfmalloc(size_t size);

/* BINARY <-> CODE ***************************************/
typedef int                 hexdec;
#define HEXDEC_ADJ          256
#define HEXDEC_MIN          128
#define HEXDEC_MAX          255
#define BIN_MIN             -128
#define BIN_MAX             -1
#define BIN                 2
#define NUM_COL             40
#define NUM_ROW             25
#define NUM_SIXELS          6
#define SIXEL_NUMMIN        0
#define SIXEL_NUMMAX        63

hexdec         base_bin2code(char c);
void           base_int2bin(int num, int
                 sixel[NUM_SIXELS]);

/* FONTS *************************************************/
typedef unsigned short  fntrow;
#define FNTWIDTH        (sizeof(fntrow) * BYTE)
#define FNTHEIGHT       18
#define FNTCHARS        96
#define FNT1STCHAR      32
#define FNTDOUBLE       2

typedef enum Font_Height {single_ht, double_httop,
              double_htbot} Font_Height;

void           base_ReadFont(fntrow
                 fontdata[FNTCHARS][FNTHEIGHT],
                 char *fname);

/* SDL ***************************************************/
#define SDL_8BITCOLOUR  256
#define SDL_CLRMAX      255
#define SDL_CLRMIN      0
#define WWIDTH          800
#define WHEIGHT         600
#define SDL_DELAYSHORT  10
#define SDL_DELAYMEDIUM 500
#define SDL_DELAYLONG   2000

struct SDL_Simplewin{
  SDL_bool        finished;
  SDL_Window      *win;
  SDL_Renderer    *renderer;
  SDL_Texture     *display;
};
typedef struct SDL_Simplewin SDL_Simplewin;

struct SDL_ColourRGB{
  Uint8           r;
  Uint8           g;
  Uint8           b;
};
typedef struct SDL_ColourRGB SDL_ColourRGB;

struct SDL_Dim{
  int             w;
  int             h;
};
typedef struct SDL_Dim SDL_Dim;

struct SDL_Origin{
  int             ox;
  int             oy;
};
typedef struct SDL_Origin SDL_Origin;

void           base_SDL_Init(SDL_Simplewin *sw);
void           base_SDL_Events(SDL_Simplewin *sw);
void           base_SDL_UpdateScreen(SDL_Simplewin *sw);
void           base_SDL_SetDrawColour(SDL_Simplewin *sw,
                 SDL_ColourRGB colour);
void           base_SDL_DrawRect(SDL_Simplewin *sw,
                 SDL_ColourRGB colour,
                 SDL_Origin *oxy, SDL_Dim *dim);
void           base_SDL_DrawChar(SDL_Simplewin *sw, fntrow
                 fntdata[FNTCHARS][FNTHEIGHT],
                 SDL_ColourRGB fnt_clr, SDL_ColourRGB
                 bckgrnd_clr, unsigned char chr,
                 SDL_Origin *oxy, Font_Height fnt_height);
