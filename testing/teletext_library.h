/*********************************************************/
/* teletext_library.h ************************************/
/*********************************************************/

/* The teletext code is structured in 3 layers:
1. User layer
2. Library layer
3. Base layer
This layer is the library layer and includes array related
functions, structures to store the data and specialised
SDL functions e.g. for sixels
The Draw functions abstract the user layer away from 
any SDL functions whatsoever, so the user layer only deals
with the code import and Elem array structures*/

#include "teletext_base.h"

typedef enum Colour {red, green, yellow, blue, magenta,
  cyan, white, black} Colour;
typedef enum Mode {alphanumeric, contiguous, separated}
  Mode;
typedef enum Hold_Release {hold, release} Hold_Release;


struct Elem{
  hexdec         code;
  unsigned char  c;
  Font_Height    font_height;
  Colour         font_clr;
  Colour         bckgrnd_clr;
  Colour         graphics_clr;
  Mode           print_mode;
  Hold_Release   graphics_hold;
};
typedef struct Elem Elem;

/* CODE => INT *******************************************/

#define MIN_CHAR            160
#define MAX_CHAR            255
#define CODE_ADJ            32

int            lib_code2int(hexdec code);

/* CODE FUNCTIONS ****************************************/

struct Arr_Dim{
  int             w;
  int             h;
};
typedef struct Arr_Dim Arr_Dim;

hexdec*        lib_codeArr_Init(Arr_Dim dim);
void           lib_codeArr_Free(hexdec **code_array);
void           lib_codeArr_ImportBin(FILE *fp, hexdec
                 *code_array, Arr_Dim dim);

/* ELEM FUNCTIONS ****************************************/

Elem*          lib_Elem_Init(void);
void           lib_Elem_Default(Elem *e);
void           lib_Elem_Copy(Elem *e, Elem *e_copyfrom);
Elem**         lib_ElemArr_Init(Arr_Dim dim);
void           lib_ElemArr_Free(Elem*** e_array,
                 Arr_Dim dim);

/* CODE => ELEM ******************************************/

#define MIN_CODE            128
#define MIN_CON             129
#define MIN_ANCOL           129
#define MAX_ANCOL           135
#define MIN_HT              140
#define MAX_HT              141
#define MIN_GRACOL          145
#define MAX_GRACOL          151
#define MIN_MODE            153
#define MAX_MODE            154
#define MIN_BCKGRD          156
#define MAX_BCKGRD          157
#define MIN_HOLD            158
#define MAX_HOLD            159
#define MAX_CON             159
#define MIN_BLAST           192
#define MAX_BLAST           223
#define MAX_CODE            255

void           lib_code2Elem_code(Elem *e, hexdec code);
void           lib_code2Elem_c(Elem *e, hexdec code);
void           lib_code2Elem_font_height(Elem *e, hexdec
                 code);
void           lib_code2Elem_font_clr(Elem *e, hexdec
                 code);
void           lib_code2Elem_bckgrnd_clr(Elem *e, hexdec
                 code);
void           lib_code2Elem_graphics_clr(Elem *e, hexdec
                 code);
void           lib_code2Elem_print_mode(Elem *e, hexdec
                 code);
void           lib_code2Elem_graphics_hold(Elem *e, hexdec
                 code);
void           lib_code2Elem(Elem *e, hexdec code);
void           lib_code2ElemArr_fix_htbot(Elem** e_array,
                 Arr_Dim dim);
void           lib_code2ElemArr(hexdec *code_array,
                 Elem** e_array, Arr_Dim dim);


/* ELEM => BASE ******************************************/

SDL_ColourRGB  lib_Colour2RGB(Colour clr);

/* DRAW ELEM *********************************************/

#define SIXEL_COL           2
#define SIXEL_ROW           3
#define BIN_0               0
#define BIN_1               1
#define SEPARATED_ADJ       2

void           lib_Elem_DrawChar(SDL_Simplewin *sw,
                 fntrow fntdata[FNTCHARS][FNTHEIGHT],
                 Elem *e, SDL_Origin *oxy);
void           lib_Elem_DrawSixel(SDL_Simplewin *sw,
                 Elem *e, int sixel[NUM_SIXELS],
                 SDL_Origin *oxy);
void           lib_Elem_Draw(SDL_Simplewin *sw,
                 fntrow fntdata[FNTCHARS][FNTHEIGHT],
                 Elem *e, SDL_Origin *oxy);
void           lib_ElemArr_Print(fntrow
                 fntdata[FNTCHARS][FNTHEIGHT], Elem**
                 e_array, Arr_Dim dim);
