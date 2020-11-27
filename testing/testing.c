#include "testing.h"

int main(void)
{
  testing_base();
  testing_library();

  return(EXIT_SUCCESS);
}

/*********************************************************/
/* TEST BASE FUNCTIONS ***********************************/
/*********************************************************/

void testing_base(void)
{
  int             *x, *x_temp;
  int             i, j;
  int             sixel[NUM_SIXELS] = {0};
  fntrow          fntdata[FNTCHARS][FNTHEIGHT];
  SDL_Simplewin   sw;
  SDL_ColourRGB   colour, fnt_clr, bckgrnd_clr;
  SDL_Origin      oxy;
  SDL_Dim         dim;


  printf(
    "*************************************************\n");
  printf("START:  testing_base\n\n");

  /* TEST: gfmalloc **************************************/

  printf("TEST:   No error messages from gfmalloc\n");
  x = (int *) gfmalloc(sizeof(int));
  x_temp = x;
  free(x);
  x_temp = NULL;
  assert(x_temp == NULL);

  printf("WORKS:  gfmalloc\n\n");


  /* TEST: gfopen & base_ReadFont ************************/

  printf("TEST:   No error messages from font import\n");
  base_ReadFont(fntdata, "m7fixed.fnt");

  printf("WORKS:  gfopen\n");
  printf("WORKS:  base_ReadFont\n\n");

  /* TEST: base_bin2code *********************************/

  printf("TEST:   Binary converts correctly to hexdec\n");
  /* There is no nice way to test this because C doesn't
  allow binary literals */
  i = HEXDEC_MIN;
  for(j = BIN_MIN; j <= BIN_MAX; j++){
    assert(i == base_bin2code((char) j));
    i++;
  }

  printf("WORKS:  base_bin2code\n\n");

  /* TEST: base_int2bin *********************************/

  printf("TEST:   Selected integers convert to binary\n"
    "        matrix correctly\n");

  /* Note here binary is backwards i.e. */
  /* 2^0 2^1 2^2 2^3 2^4 2^5 */
  /* Test 0 = [0, 0, 0, 0, 0, 0] */
  base_int2bin(TESTNUM_0, sixel);
  for(i = SIXEL_0; i < NUM_SIXELS; i++){
    assert(BIN_0 == sixel[i]);
  }
  /* Test 1 = [1, 0, 0, 0, 0, 0] */
  base_int2bin(TESTNUM_1, sixel);
  assert(BIN_1 == sixel[SIXEL_0]);
  for(i = SIXEL_1; i < NUM_SIXELS; i++){
    assert(BIN_0 == sixel[i]);
  }
  /* Test 2 = [0, 1, 0, 0, 0, 0] */
  base_int2bin(TESTNUM_2, sixel);
  assert(BIN_0 == sixel[SIXEL_0]);
  assert(BIN_1 == sixel[SIXEL_1]);
  for(i = SIXEL_2; i < NUM_SIXELS; i++){
    assert(BIN_0 == sixel[i]);
  }
  /* Test 4 = [0, 0, 1, 0, 0, 0] */
  base_int2bin(TESTNUM_4, sixel);
  for(i = SIXEL_0; i <= SIXEL_1; i++){
    assert(BIN_0 == sixel[i]);
  }
  assert(BIN_1 == sixel[SIXEL_2]);
  for(i = SIXEL_3; i < NUM_SIXELS; i++){
    assert(BIN_0 == sixel[i]);
  }
  /* Test 8 = [0, 0, 0, 1, 0, 0] */
  base_int2bin(TESTNUM_8, sixel);
  for(i = SIXEL_0; i <= SIXEL_2; i++){
    assert(BIN_0 == sixel[i]);
  }
  assert(BIN_1 == sixel[SIXEL_3]);
  for(i = SIXEL_4; i < NUM_SIXELS; i++){
    assert(BIN_0 == sixel[i]);
  }
  /* Test 16 = [0, 0, 0, 0, 1, 0] */
  base_int2bin(TESTNUM_16, sixel);
  for(i = SIXEL_0; i <= SIXEL_3; i++){
    assert(BIN_0 == sixel[i]);
  }
  assert(BIN_1 == sixel[SIXEL_4]);
  assert(BIN_0 == sixel[SIXEL_5]);
  /* Test 32 = [0, 0, 0, 0, 0, 1] */
  base_int2bin(TESTNUM_32, sixel);
  for(i = SIXEL_0; i <= SIXEL_4; i++){
    assert(BIN_0 == sixel[i]);
  }
  assert(BIN_1 == sixel[SIXEL_5]);
  /* Test 11 = [1, 1, 0, 1, 0, 0] */
  base_int2bin(TESTNUM_11, sixel);
  assert(BIN_1 == sixel[SIXEL_0]);
  assert(BIN_1 == sixel[SIXEL_1]);
  assert(BIN_0 == sixel[SIXEL_2]);
  assert(BIN_1 == sixel[SIXEL_3]);
  assert(BIN_0 == sixel[SIXEL_4]);
  assert(BIN_0 == sixel[SIXEL_5]);
  /* Test 29 = [1, 0, 1, 1, 1, 0] */
  base_int2bin(TESTNUM_29, sixel);
  assert(BIN_1 == sixel[SIXEL_0]);
  assert(BIN_0 == sixel[SIXEL_1]);
  assert(BIN_1 == sixel[SIXEL_2]);
  assert(BIN_1 == sixel[SIXEL_3]);
  assert(BIN_1 == sixel[SIXEL_4]);
  assert(BIN_0 == sixel[SIXEL_5]);
  /* Test 41 = [1, 0, 0, 1, 0, 1] */
  base_int2bin(TESTNUM_41, sixel);
  assert(BIN_1 == sixel[SIXEL_0]);
  assert(BIN_0 == sixel[SIXEL_1]);
  assert(BIN_0 == sixel[SIXEL_2]);
  assert(BIN_1 == sixel[SIXEL_3]);
  assert(BIN_0 == sixel[SIXEL_4]);
  assert(BIN_1 == sixel[SIXEL_5]);
  /* Test 63 = [1, 1, 1, 1, 1, 1] */
  base_int2bin(TESTNUM_63, sixel);
  assert(BIN_1 == sixel[SIXEL_0]);
  assert(BIN_1 == sixel[SIXEL_1]);
  assert(BIN_1 == sixel[SIXEL_2]);
  assert(BIN_1 == sixel[SIXEL_3]);
  assert(BIN_1 == sixel[SIXEL_4]);
  assert(BIN_1 == sixel[SIXEL_5]);

  printf("WORKS:  base_int2bin\n\n");

  /* TEST: base_SDL_Init *********************************/

  printf("TEST:   Window appears\n");
  base_SDL_Init(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("WORKS:  base_SDL_Init\n\n");

  /* TEST: base_SDL_UpdateScreen *************************/

  printf("TEST:   Black window appears\n");
  base_SDL_Init(&sw);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("WORKS:  base_SDL_UpdateScreen\n\n");

  /* TEST: base_SDL_Events *******************************/

  printf("TEST:   Mouseclick exits window\n");
  base_SDL_Init(&sw);
  base_SDL_UpdateScreen(&sw);
  while(!sw.finished){
    base_SDL_Events(&sw);
  }

  printf("WORKS:  base_SDL_Events\n\n");

  /* TEST: base_SDL_SetDrawColour ************************/

  printf("TEST:   Draw a white 50x50 square in the top\n"
    "        left-hand corner\n");
  base_SDL_Init(&sw);
  base_SDL_UpdateScreen(&sw);
  colour.r = SDL_CLRMAX;
  colour.g = SDL_CLRMAX;
  colour.b = SDL_CLRMAX;
  base_SDL_SetDrawColour(&sw, colour);
  oxy.ox = 0;
  oxy.oy = 0;
  dim.w = LENGTH_50;
  dim.h = LENGTH_50;
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw a red, then green, then blue\n"
    "        50x50 square in the top left-hand corner\n");
  base_SDL_Init(&sw);
  base_SDL_UpdateScreen(&sw);
  /* Set to red */
  colour.g = SDL_CLRMIN;
  colour.b = SDL_CLRMIN;
  base_SDL_SetDrawColour(&sw, colour);
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  /* Set to green */
  colour.r = SDL_CLRMIN;
  colour.g = SDL_CLRMAX;
  base_SDL_SetDrawColour(&sw, colour);
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  /* Set to blue */
  colour.g = SDL_CLRMIN;
  colour.b = SDL_CLRMAX;
  base_SDL_SetDrawColour(&sw, colour);
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw a yellow, then magenta, then cyan\n"
    "        50x50 square in the top left-hand corner\n");
  base_SDL_Init(&sw);
  base_SDL_UpdateScreen(&sw);
  /* Set to yellow */
  colour.r = SDL_CLRMAX;
  colour.g = SDL_CLRMAX;
  colour.b = SDL_CLRMIN;
  base_SDL_SetDrawColour(&sw, colour);
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  /* Set to magenta */
  colour.g = SDL_CLRMIN;
  colour.b = SDL_CLRMAX;
  base_SDL_SetDrawColour(&sw, colour);
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  /* Set to cyan */
  colour.r = SDL_CLRMIN;
  colour.g = SDL_CLRMAX;
  base_SDL_SetDrawColour(&sw, colour);
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("WORKS:  base_SDL_SetDrawColour\n\n");

  /* TEST: base_SDL_DrawRect *****************************/

  printf("TEST:   Draw a white 100x100 square in the top\n"
    "        left-hand corner\n");
  base_SDL_Init(&sw);
  colour.r = SDL_CLRMAX;
  base_SDL_SetDrawColour(&sw, colour);
  dim.w = LENGTH_100;
  dim.h = LENGTH_100;
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw a white 100x50 rectangle in the\n"
    "        top left-hand corner\n");
  base_SDL_Init(&sw);
  base_SDL_UpdateScreen(&sw);
  dim.h = LENGTH_50;
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw a white 100x100 square in the \n"
    "        each of the other three corners\n");
  base_SDL_Init(&sw);
  base_SDL_UpdateScreen(&sw);
  dim.h = LENGTH_100;
  oxy.ox = WWIDTH - LENGTH_100;
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  oxy.oy = WHEIGHT - LENGTH_100;
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  oxy.ox = 0;
  base_SDL_DrawRect(&sw, colour, &oxy, &dim);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("WORKS:  base_SDL_DrawRect\n\n");

  /* TEST: base_SDL_DrawChar *****************************/

  printf("TEST:   Draw a white 'A'\n");
  /*Set font to white, background to black */
  base_SDL_Init(&sw);
  fnt_clr.r = SDL_CLRMAX;
  fnt_clr.g = SDL_CLRMAX;
  fnt_clr.b = SDL_CLRMAX;
  bckgrnd_clr.r = SDL_CLRMIN;
  bckgrnd_clr.g = SDL_CLRMIN;
  bckgrnd_clr.b = SDL_CLRMIN;
  oxy.oy = 0;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, single_ht);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw a red, then green, then blue\n"
  "        'A'\n");

  /* Set font to red */
  base_SDL_Init(&sw);
  fnt_clr.g = SDL_CLRMIN;
  fnt_clr.b = SDL_CLRMIN;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, single_ht);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  /* Set font to green */
  fnt_clr.r = SDL_CLRMIN;
  fnt_clr.g = SDL_CLRMAX;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, single_ht);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  /* Set font to blue */
  fnt_clr.g = SDL_CLRMIN;
  fnt_clr.b = SDL_CLRMAX;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, single_ht);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw a white 'A' with a red, then \n"
    "        green, then blue background\n");
  /* Set background to red */
  base_SDL_Init(&sw);
  fnt_clr.r = SDL_CLRMAX;
  fnt_clr.g = SDL_CLRMAX;
  bckgrnd_clr.r = SDL_CLRMAX;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, single_ht);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  /* Set background to green */
  bckgrnd_clr.r = SDL_CLRMIN;
  bckgrnd_clr.g = SDL_CLRMAX;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, single_ht);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  /* Set background to blue */
  bckgrnd_clr.g = SDL_CLRMIN;
  bckgrnd_clr.b = SDL_CLRMAX;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, single_ht);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw top of a double height 'A',\n");
  base_SDL_Init(&sw);
  bckgrnd_clr.b = SDL_CLRMIN;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, double_httop);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw bottom of a double height 'A',\n");
  base_SDL_Init(&sw);
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, double_htbot);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("TEST:   Draw a double height 'A',\n");
  base_SDL_Init(&sw);
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, double_httop);
  oxy.oy = FNTHEIGHT;
  base_SDL_DrawChar(&sw, fntdata, fnt_clr, bckgrnd_clr,
  'A', &oxy, double_htbot);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();

  printf("WORKS:  base_SDL_DrawChar\n\n");

  printf("FINISH: testing_base\n\n");
  printf(
    "*************************************************\n");
  printf("\n\n");
}

/*********************************************************/
/* TEST LIBRARY FUNCTIONS ********************************/
/*********************************************************/

void testing_library(void)
{
  Elem            *e, *e_copyfrom;
  Elem            **e_array;
  hexdec          *code_array;
  Arr_Dim         dim;
  int             x, y;
  Colour          clr;
  SDL_Simplewin   sw;
  SDL_ColourRGB   colour;
  SDL_Origin      oxy;
  fntrow          fntdata[FNTCHARS][FNTHEIGHT];
  int             sixel[NUM_SIXELS];
  int             i, j;

  printf(
    "*************************************************\n");
  printf("START:  testing_library\n\n");

  /* Load fonts */
  base_ReadFont(fntdata, "m7fixed.fnt");

  /* TEST: lib_code2int **********************************/

  printf("TEST:   Codes converted to 0-63 ints\n");
  j = TESTNUM_0;
  for(i = TESTNUM_160; i <= TESTNUM_191; i++){
    assert(lib_code2int(i) == j);
    j++;
  }
  for(i = TESTNUM_224; i <= TESTNUM_255; i++){
    assert(lib_code2int(i) == j);
    j++;
  }

  printf("WORKS:  lib_code2int\n\n");

  /* TEST: lib_codeArr_Init ******************************/

  printf("TEST:   Initialised code Array passes\n"
  "        asserts\n");
  dim.w = ARRAY_5;
  dim.h = ARRAY_5;
  code_array = lib_codeArr_Init(dim);
  for(x = 0; x < dim.w; x++){
    for(y = 0; y < dim.h; y++){
      assert(code_array[y * dim.w + x] == (hexdec) 0);
    }
  }

  printf("WORKS:  lib_codeArr_Init\n\n");

  /* TEST: lib_codeArr_Free ******************************/

  printf("TEST:   Free code Array & check NULL\n"
  "        asserts\n");
  lib_codeArr_Free(&code_array);
  assert(code_array == NULL);

  printf("WORKS:  lib_codeArr_Free\n\n");

  /* TEST: lib_Elem_Init *********************************/

  printf("TEST:   Initialised Elem* passes asserts\n");
  e = lib_Elem_Init();
  assert(e->code == 0);
  assert(e->c == ' ');
  assert(e->font_height == single_ht);
  assert(e->font_clr == white);
  assert(e->bckgrnd_clr == black);
  assert(e->graphics_clr == white);
  assert(e->print_mode == alphanumeric);
  assert(e->graphics_hold == release);
  free(e);

  printf("WORKS:  lib_Elem_Init\n\n");

  /* TEST: lib_Elem_Default ******************************/

  printf("TEST:   Default Elem* passes asserts\n");
  e = lib_Elem_Init();
  e->code = 1;
  e->c = ' ' + 1;
  e->font_height = double_httop;
  e->font_clr = yellow;
  e->bckgrnd_clr = yellow;
  e->graphics_clr = yellow;
  e->print_mode = separated;
  e->graphics_hold = hold;
  lib_Elem_Default(e);
  assert(e->code == 0);
  assert(e->c == ' ');
  assert(e->font_height == single_ht);
  assert(e->font_clr == white);
  assert(e->bckgrnd_clr == black);
  assert(e->graphics_clr == white);
  assert(e->print_mode == alphanumeric);
  assert(e->graphics_hold == release);
  free(e);

  printf("WORKS:  lib_Elem_Default\n\n");

  /* TEST: lib_Elem_Copy *********************************/

  printf("TEST:   Copy Elem* passes asserts\n");
  e = lib_Elem_Init();
  e_copyfrom = lib_Elem_Init();
  e_copyfrom->code = 1;
  e_copyfrom->c = ' ' + 1;
  e_copyfrom->font_height = double_httop;
  e_copyfrom->font_clr = yellow;
  e_copyfrom->bckgrnd_clr = yellow;
  e_copyfrom->graphics_clr = yellow;
  e_copyfrom->print_mode = separated;
  e_copyfrom->graphics_hold = hold;
  lib_Elem_Copy(e, e_copyfrom);
  assert(e->code == 1);
  assert(e->c == ' ' + 1);
  assert(e->font_height == double_httop);
  assert(e->font_clr == yellow);
  assert(e->bckgrnd_clr == yellow);
  assert(e->graphics_clr == yellow);
  assert(e->print_mode == separated);
  assert(e->graphics_hold == hold);
  free(e);
  free(e_copyfrom);

  printf("WORKS:  lib_Elem_Copy\n\n");


  /* TEST: lib_ElemArr_Init ******************************/

  printf("TEST:   Initialised Elem Array passes\n"
  "        asserts\n");

  dim.w = ARRAY_5;
  dim.h = ARRAY_6;
  e_array = lib_ElemArr_Init(dim);
  for(x = 0; x < dim.w; x++){
    for(y = 0; y < dim.h; y++){
      assert(e_array[y * dim.w + x]->code == 0);
      assert(e_array[y * dim.w + x]->c == ' ');
      assert(e_array[y * dim.w + x]->font_height ==
        single_ht);
      assert(e_array[y * dim.w + x]->font_clr == white);
      assert(e_array[y * dim.w + x]->bckgrnd_clr == black);
      assert(e_array[y * dim.w + x]->graphics_clr ==
        white);
      assert(e_array[y * dim.w + x]->print_mode ==
        alphanumeric);
      assert(e_array[y * dim.w + x]->graphics_hold ==
        release);
    }
  }

  printf("WORKS:  lib_ElemArr_Init\n\n");

  /* TEST: lib_ElemArr_Free ******************************/

  printf("TEST:   Free Elem Array & check NULL\n"
  "        asserts\n");
  lib_ElemArr_Free(&e_array, dim);
  assert(e_array == NULL);

  printf("WORKS:  lib_ElemArr_Free\n\n");

  /* TEST: lib_code2Elem_code ****************************/

  printf("TEST:   Update Elem code\n");
  e = lib_Elem_Init();
  for(i = TESTNUM_128; i <= TESTNUM_255; i++){
    lib_code2Elem_code(e, i);
    assert(e->code == i);
  }
  free(e);

  printf("WORKS:  lib_code2Elem_code\n\n");

  /* TEST: lib_code2Elem_c *******************************/

  printf("TEST:   Update Elem c\n");
  e = lib_Elem_Init();
  for(i = TESTNUM_160; i <= TESTNUM_255; i++){
    lib_code2Elem_c(e, i);
    assert(e->c == ' ' + i - TESTNUM_160);
  }
  free(e);

  printf("WORKS:  lib_code2Elem_c\n\n");

  /* TEST: lib_code2Elem_font_height *********************/

  printf("TEST:   Update Elem font_height\n");
  e = lib_Elem_Init();
  lib_code2Elem_font_height(e, TESTNUM_140);
  assert(e->font_height == single_ht);
  lib_code2Elem_font_height(e, TESTNUM_141);
  assert(e->font_height == double_httop);
  free(e);

  printf("WORKS:  lib_code2Elem_font_height\n\n");

  /* TEST: lib_code2Elem_font_clr ************************/
  /* TEST: lib_code2Elem_bckgrnd_clr *********************/

  printf("TEST:   Update Elem font_clr\n");
  printf("TEST:   Update Elem bckgrnd_clr\n");
  e = lib_Elem_Init();
  /* Test red */
  e->print_mode = contiguous;
  lib_code2Elem_font_clr(e, TESTNUM_129);
  assert(e->font_clr == red);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem_bckgrnd_clr(e, TESTNUM_157);
  assert(e->bckgrnd_clr == red);
  /* Test green */
  e->print_mode = contiguous;
  lib_code2Elem_font_clr(e, TESTNUM_130);
  assert(e->font_clr == green);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem_bckgrnd_clr(e, TESTNUM_157);
  assert(e->bckgrnd_clr == green);
  /* Test yellow */
  e->print_mode = contiguous;
  lib_code2Elem_font_clr(e, TESTNUM_131);
  assert(e->font_clr == yellow);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem_bckgrnd_clr(e, TESTNUM_157);
  assert(e->bckgrnd_clr == yellow);
  /* Test blue */
  e->print_mode = contiguous;
  lib_code2Elem_font_clr(e, TESTNUM_132);
  assert(e->font_clr == blue);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem_bckgrnd_clr(e, TESTNUM_157);
  assert(e->bckgrnd_clr == blue);
  /* Test magenta */
  e->print_mode = contiguous;
  lib_code2Elem_font_clr(e, TESTNUM_133);
  assert(e->font_clr == magenta);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem_bckgrnd_clr(e, TESTNUM_157);
  assert(e->bckgrnd_clr == magenta);
  /* Test cyan */
  e->print_mode = contiguous;
  lib_code2Elem_font_clr(e, TESTNUM_134);
  assert(e->font_clr == cyan);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem_bckgrnd_clr(e, TESTNUM_157);
  assert(e->bckgrnd_clr == cyan);
  /* Test white */
  e->print_mode = contiguous;
  lib_code2Elem_font_clr(e, TESTNUM_135);
  assert(e->font_clr == white);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem_bckgrnd_clr(e, TESTNUM_157);
  assert(e->bckgrnd_clr == white);
  /* Test black */
  lib_code2Elem_bckgrnd_clr(e, TESTNUM_156);
  assert(e->bckgrnd_clr == black);
  free(e);

  printf("WORKS:  lib_code2Elem_font_clr\n\n");
  printf("WORKS:  lib_code2Elem_bckgrnd_clr\n\n");

  /* TEST: lib_code2Elem_graphics_clr ********************/

  printf("TEST:   Update Elem graphics_clr\n");
  e = lib_Elem_Init();
  /* Test red */
  e->print_mode = alphanumeric;
  lib_code2Elem_graphics_clr(e, TESTNUM_145);
  assert(e->graphics_clr == red);
  assert(e->print_mode == contiguous);
  /* Test green */
  e->print_mode = alphanumeric;
  lib_code2Elem_graphics_clr(e, TESTNUM_146);
  assert(e->graphics_clr == green);
  assert(e->print_mode == contiguous);
  /* Test yellow */
  e->print_mode = alphanumeric;
  lib_code2Elem_graphics_clr(e, TESTNUM_147);
  assert(e->graphics_clr == yellow);
  assert(e->print_mode == contiguous);
  /* Test blue */
  e->print_mode = alphanumeric;
  lib_code2Elem_graphics_clr(e, TESTNUM_148);
  assert(e->graphics_clr == blue);
  assert(e->print_mode == contiguous);
  /* Test magenta */
  e->print_mode = alphanumeric;
  lib_code2Elem_graphics_clr(e, TESTNUM_149);
  assert(e->graphics_clr == magenta);
  assert(e->print_mode == contiguous);
  /* Test cyan */
  e->print_mode = alphanumeric;
  lib_code2Elem_graphics_clr(e, TESTNUM_150);
  assert(e->graphics_clr == cyan);
  assert(e->print_mode == contiguous);
  /* Test white */
  e->print_mode = alphanumeric;
  lib_code2Elem_graphics_clr(e, TESTNUM_151);
  assert(e->graphics_clr == white);
  assert(e->print_mode == contiguous);
  free(e);

  printf("WORKS:  lib_code2Elem_graphics_clr\n\n");

  /* TEST: lib_code2Elem_print_mode **********************/

  printf("TEST:   Update Elem print_mode\n");
  e = lib_Elem_Init();
  lib_code2Elem_print_mode(e, TESTNUM_153);
  assert(e->print_mode == contiguous);
  lib_code2Elem_print_mode(e, TESTNUM_154);
  assert(e->print_mode == separated);
  free(e);

  printf("WORKS:  lib_code2Elem_print_mode\n\n");

  /* TEST: lib_code2Elem_graphics_hold *******************/

  printf("TEST:   Update Elem graphics_hold\n");
  e = lib_Elem_Init();
  lib_code2Elem_graphics_hold(e, TESTNUM_158);
  assert(e->graphics_hold == hold);
  lib_code2Elem_graphics_hold(e, TESTNUM_159);
  assert(e->graphics_hold == release);
  free(e);

  printf("WORKS:  lib_code2Elem_graphics_hold\n\n");

  /* TEST: lib_code2Elem *********************************/

  printf("TEST:   Update Elem\n");
  e = lib_Elem_Init();
  /* Test code update */
  for(i = TESTNUM_129; i <= TESTNUM_255; i++){
    if(i != TESTNUM_136 && i != TESTNUM_137 &&
       i != TESTNUM_138 && i != TESTNUM_139 &&
       i != TESTNUM_142 && i != TESTNUM_143 &&
       i != TESTNUM_144 && i != TESTNUM_152 &&
       i != TESTNUM_152 && i != TESTNUM_155){
      lib_code2Elem(e, i);
      assert(e->code == i);
    }
  }
  /* Test c update */
  for(i = TESTNUM_160; i <= TESTNUM_255; i++){
    lib_code2Elem(e, i);
    assert(e->c == ' ' + i - TESTNUM_160);
  }
  /* Test font height */
  lib_code2Elem(e, TESTNUM_140);
  assert(e->font_height == single_ht);
  lib_code2Elem(e, TESTNUM_141);
  assert(e->font_height == double_httop);
  e = lib_Elem_Init();
  /* Test font colour & background colour */
  /* Test red */
  e->print_mode = contiguous;
  lib_code2Elem(e, TESTNUM_129);
  assert(e->font_clr == red);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem(e, TESTNUM_157);
  assert(e->bckgrnd_clr == red);
  /* Test green */
  e->print_mode = contiguous;
  lib_code2Elem(e, TESTNUM_130);
  assert(e->font_clr == green);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem(e, TESTNUM_157);
  assert(e->bckgrnd_clr == green);
  /* Test yellow */
  e->print_mode = contiguous;
  lib_code2Elem(e, TESTNUM_131);
  assert(e->font_clr == yellow);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem(e, TESTNUM_157);
  assert(e->bckgrnd_clr == yellow);
  /* Test blue */
  e->print_mode = contiguous;
  lib_code2Elem(e, TESTNUM_132);
  assert(e->font_clr == blue);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem(e, TESTNUM_157);
  assert(e->bckgrnd_clr == blue);
  /* Test magenta */
  e->print_mode = contiguous;
  lib_code2Elem(e, TESTNUM_133);
  assert(e->font_clr == magenta);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem(e, TESTNUM_157);
  assert(e->bckgrnd_clr == magenta);
  /* Test cyan */
  e->print_mode = contiguous;
  lib_code2Elem(e, TESTNUM_134);
  assert(e->font_clr == cyan);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem(e, TESTNUM_157);
  assert(e->bckgrnd_clr == cyan);
  /* Test white */
  e->print_mode = contiguous;
  lib_code2Elem(e, TESTNUM_135);
  assert(e->font_clr == white);
  assert(e->print_mode == alphanumeric);
  lib_code2Elem(e, TESTNUM_157);
  assert(e->bckgrnd_clr == white);
  /* Test black */
  lib_code2Elem(e, TESTNUM_156);
  assert(e->bckgrnd_clr == black);
  /* Test graphics colour */
  /* Test red */
  e->print_mode = alphanumeric;
  lib_code2Elem(e, TESTNUM_145);
  assert(e->graphics_clr == red);
  assert(e->print_mode == contiguous);
  /* Test green */
  e->print_mode = alphanumeric;
  lib_code2Elem(e, TESTNUM_146);
  assert(e->graphics_clr == green);
  assert(e->print_mode == contiguous);
  /* Test yellow */
  e->print_mode = alphanumeric;
  lib_code2Elem(e, TESTNUM_147);
  assert(e->graphics_clr == yellow);
  assert(e->print_mode == contiguous);
  /* Test blue */
  e->print_mode = alphanumeric;
  lib_code2Elem(e, TESTNUM_148);
  assert(e->graphics_clr == blue);
  assert(e->print_mode == contiguous);
  /* Test magenta */
  e->print_mode = alphanumeric;
  lib_code2Elem(e, TESTNUM_149);
  assert(e->graphics_clr == magenta);
  assert(e->print_mode == contiguous);
  /* Test cyan */
  e->print_mode = alphanumeric;
  lib_code2Elem(e, TESTNUM_150);
  assert(e->graphics_clr == cyan);
  assert(e->print_mode == contiguous);
  /* Test white */
  e->print_mode = alphanumeric;
  lib_code2Elem(e, TESTNUM_151);
  assert(e->graphics_clr == white);
  assert(e->print_mode == contiguous);
  /* Test print mode */
  lib_code2Elem(e, TESTNUM_153);
  assert(e->print_mode == contiguous);
  lib_code2Elem(e, TESTNUM_154);
  assert(e->print_mode == separated);
  /* Test hold-release */
  lib_code2Elem(e, TESTNUM_158);
  assert(e->graphics_hold == hold);
  lib_code2Elem(e, TESTNUM_159);
  assert(e->graphics_hold == release);
  free(e);

  printf("WORKS:  lib_code2Elem\n\n");

  /* TEST: lib_code2ElemArr_fix_htbot ********************/

  printf("TEST:   Fix htbot\n");
  dim.w = ARRAY_1;
  dim.h = ARRAY_2;
  e_array = lib_ElemArr_Init(dim);
  for(x = 0; x < dim.w; x++){
    for(y = 0; y < dim.h; y++){
      e_array[y * dim.w + x]->font_height = double_httop;
    }
  }
  lib_code2ElemArr_fix_htbot(e_array, dim);
  assert(e_array[TESTNUM_0]->font_height == double_httop);
  assert(e_array[TESTNUM_1]->font_height == double_htbot);

  printf("WORKS:  lib_code2ElemArr_fix_htbot\n\n");

  /* TEST: lib_code2ElemArr ******************************/

  printf("TEST:   Code Array maps to Elem Array\n"
    "        correctly\n");
  dim.w = ARRAY_4;
  dim.h = ARRAY_2;
  code_array = lib_codeArr_Init(dim);
  code_array[ARRAY_0] = TESTNUM_154;
  code_array[ARRAY_1] = TESTNUM_211;
  code_array[ARRAY_2] = TESTNUM_141;
  code_array[ARRAY_3] = TESTNUM_248;
  code_array[ARRAY_4] = TESTNUM_134;
  code_array[ARRAY_5] = TESTNUM_141;
  code_array[ARRAY_6] = TESTNUM_141;
  code_array[ARRAY_7] = TESTNUM_157;
  e_array = lib_ElemArr_Init(dim);
  lib_code2ElemArr(code_array, e_array, dim);
  /* Test 154 = Separated Graphics */
  assert(e_array[ARRAY_0]->code == TESTNUM_154);
  assert(e_array[ARRAY_0]->c == ' ');
  assert(e_array[ARRAY_0]->font_height == single_ht);
  assert(e_array[ARRAY_0]->font_clr == white);
  assert(e_array[ARRAY_0]->bckgrnd_clr == black);
  assert(e_array[ARRAY_0]->graphics_clr == white);
  assert(e_array[ARRAY_0]->print_mode == separated);
  assert(e_array[ARRAY_0]->graphics_hold == release);
  /* Test 211 = 'S' */
  assert(e_array[ARRAY_1]->code == TESTNUM_211);
  assert(e_array[ARRAY_1]->c == 'S');
  assert(e_array[ARRAY_1]->font_height == single_ht);
  assert(e_array[ARRAY_1]->font_clr == white);
  assert(e_array[ARRAY_1]->bckgrnd_clr == black);
  assert(e_array[ARRAY_1]->graphics_clr == white);
  assert(e_array[ARRAY_1]->print_mode == separated);
  assert(e_array[ARRAY_1]->graphics_hold == release);
  /* Test 141 = Double Height */
  assert(e_array[ARRAY_2]->code == TESTNUM_141);
  assert(e_array[ARRAY_2]->c == ' ');
  assert(e_array[ARRAY_2]->font_height == double_httop);
  assert(e_array[ARRAY_2]->font_clr == white);
  assert(e_array[ARRAY_2]->bckgrnd_clr == black);
  assert(e_array[ARRAY_2]->graphics_clr == white);
  assert(e_array[ARRAY_2]->print_mode == alphanumeric);
  assert(e_array[ARRAY_2]->graphics_hold == release);
  /* Test 248 = 'x' */
  assert(e_array[ARRAY_3]->code == TESTNUM_248);
  assert(e_array[ARRAY_3]->c == 'x');
  assert(e_array[ARRAY_3]->font_height == double_httop);
  assert(e_array[ARRAY_3]->font_clr == white);
  assert(e_array[ARRAY_3]->bckgrnd_clr == black);
  assert(e_array[ARRAY_3]->graphics_clr == white);
  assert(e_array[ARRAY_3]->print_mode == alphanumeric);
  assert(e_array[ARRAY_3]->graphics_hold == release);
  /* Test 134 = Cyan alphanumeric */
  assert(e_array[ARRAY_4]->code == TESTNUM_134);
  assert(e_array[ARRAY_4]->c == ' ');
  assert(e_array[ARRAY_4]->font_height == single_ht);
  assert(e_array[ARRAY_4]->font_clr == cyan);
  assert(e_array[ARRAY_4]->bckgrnd_clr == black);
  assert(e_array[ARRAY_4]->graphics_clr == white);
  assert(e_array[ARRAY_4]->print_mode == alphanumeric);
  assert(e_array[ARRAY_4]->graphics_hold == release);
  /* Test 141 = Double Height */
  assert(e_array[ARRAY_5]->code == TESTNUM_141);
  assert(e_array[ARRAY_5]->c == ' ');
  assert(e_array[ARRAY_5]->font_height == double_httop);
  assert(e_array[ARRAY_5]->font_clr == cyan);
  assert(e_array[ARRAY_5]->bckgrnd_clr == black);
  assert(e_array[ARRAY_5]->graphics_clr == white);
  assert(e_array[ARRAY_5]->print_mode == alphanumeric);
  assert(e_array[ARRAY_5]->graphics_hold == release);
  /* Test 141 = Double Height Bottom*/
  assert(e_array[ARRAY_6]->code == TESTNUM_141);
  assert(e_array[ARRAY_6]->c == ' ');
  assert(e_array[ARRAY_6]->font_height == double_htbot);
  assert(e_array[ARRAY_6]->font_clr == cyan);
  assert(e_array[ARRAY_6]->bckgrnd_clr == black);
  assert(e_array[ARRAY_6]->graphics_clr == white);
  assert(e_array[ARRAY_6]->print_mode == alphanumeric);
  assert(e_array[ARRAY_6]->graphics_hold == release);
  /* Test 157 = Background colour*/
  assert(e_array[ARRAY_7]->code == TESTNUM_157);
  assert(e_array[ARRAY_7]->c == ' ');
  assert(e_array[ARRAY_7]->font_height == double_htbot);
  assert(e_array[ARRAY_7]->font_clr == white);
  assert(e_array[ARRAY_7]->bckgrnd_clr == cyan);
  assert(e_array[ARRAY_7]->graphics_clr == white);
  assert(e_array[ARRAY_7]->print_mode == alphanumeric);
  assert(e_array[ARRAY_7]->graphics_hold == release);

  printf("WORKS:  lib_code2ElemArr\n\n");


  /* TEST: lib_Colour2RGB ********************************/

  printf("TEST:   Assert colours convert to RGB\n"
    "        correctly\n");
  /* Test red */
  clr = red;
  colour = lib_Colour2RGB(clr);
  assert(colour.r == SDL_CLRMAX);
  assert(colour.g == SDL_CLRMIN);
  assert(colour.b == SDL_CLRMIN);
  /* Test green */
  clr = green;
  colour = lib_Colour2RGB(clr);
  assert(colour.r == SDL_CLRMIN);
  assert(colour.g == SDL_CLRMAX);
  assert(colour.b == SDL_CLRMIN);
  /* Test blue */
  clr = blue;
  colour = lib_Colour2RGB(clr);
  assert(colour.r == SDL_CLRMIN);
  assert(colour.g == SDL_CLRMIN);
  assert(colour.b == SDL_CLRMAX);
  /* Test yellow */
  clr = yellow;
  colour = lib_Colour2RGB(clr);
  assert(colour.r == SDL_CLRMAX);
  assert(colour.g == SDL_CLRMAX);
  assert(colour.b == SDL_CLRMIN);
  /* Test magenta */
  clr = magenta;
  colour = lib_Colour2RGB(clr);
  assert(colour.r == SDL_CLRMAX);
  assert(colour.g == SDL_CLRMIN);
  assert(colour.b == SDL_CLRMAX);
  /* Test cyan */
  clr = cyan;
  colour = lib_Colour2RGB(clr);
  assert(colour.r == SDL_CLRMIN);
  assert(colour.g == SDL_CLRMAX);
  assert(colour.b == SDL_CLRMAX);
  /* Test white */
  clr = white;
  colour = lib_Colour2RGB(clr);
  assert(colour.r == SDL_CLRMAX);
  assert(colour.g == SDL_CLRMAX);
  assert(colour.b == SDL_CLRMAX);
  /* Test black */
  clr = black;
  colour = lib_Colour2RGB(clr);
  assert(colour.r == SDL_CLRMIN);
  assert(colour.g == SDL_CLRMIN);
  assert(colour.b == SDL_CLRMIN);

  printf("WORKS:  lib_Colour2RGB\n\n");


  /* TEST: lib_Elem_DrawChar *****************************/

  printf("TEST:   Draw a white 'A'\n");
  e = lib_Elem_Init();
  e->c = 'A';
  base_SDL_Init(&sw);
  oxy.ox = 0;
  oxy.oy = 0;
  lib_Elem_DrawChar(&sw, fntdata, e, &oxy);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();
  free(e);

  printf("WORKS:  lib_Elem_DrawChar\n\n");

  /* TEST: lib_Elem_DrawSixel ****************************/

  printf("TEST:   Draw all possible contiguous sixels\n");
  e = lib_Elem_Init();
  oxy.ox = 0;
  oxy.oy = 0;
  e->print_mode = contiguous;
  base_SDL_Init(&sw);
  for(i = TESTNUM_0; i < TESTNUM_32; i++){
    oxy.ox = oxy.ox + FNTWIDTH;
    base_int2bin(i, sixel);
    lib_Elem_DrawSixel(&sw, e, sixel, &oxy);
    base_SDL_UpdateScreen(&sw);
  }
  SDL_Delay(SDL_DELAYLONG);
  oxy.ox = 0;
  oxy.oy = FNTHEIGHT;
  for(i = TESTNUM_32; i < TESTNUM_64; i++){
    oxy.ox = oxy.ox + FNTWIDTH;
    base_int2bin(i, sixel);
    lib_Elem_DrawSixel(&sw, e, sixel, &oxy);
    base_SDL_UpdateScreen(&sw);
  }
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();
  free(e);

  printf("TEST:   Draw all possible separated sixels\n");
  e = lib_Elem_Init();
  oxy.ox = 0;
  oxy.oy = 0;
  e->print_mode = separated;
  base_SDL_Init(&sw);
  for(i = TESTNUM_0; i < TESTNUM_32; i++){
    oxy.ox = oxy.ox + FNTWIDTH;
    base_int2bin(i, sixel);
    lib_Elem_DrawSixel(&sw, e, sixel, &oxy);
    base_SDL_UpdateScreen(&sw);
  }
  SDL_Delay(SDL_DELAYLONG);
  oxy.ox = 0;
  oxy.oy = FNTHEIGHT;
  for(i = TESTNUM_32; i < TESTNUM_64; i++){
    oxy.ox = oxy.ox + FNTWIDTH;
    base_int2bin(i, sixel);
    lib_Elem_DrawSixel(&sw, e, sixel, &oxy);
    base_SDL_UpdateScreen(&sw);
  }
  SDL_Delay(SDL_DELAYLONG);
  free(e);

  printf("WORKS:  lib_Elem_DrawSixel\n\n");


/* TEST: lib_Elem_DrawChar *****************************/

  printf("TEST:   Draw a white 'g'\n");
  e = lib_Elem_Init();
  e->c = 'g';
  e->code = TESTNUM_231;
  base_SDL_Init(&sw);
  oxy.ox = 0;
  oxy.oy = 0;
  lib_Elem_Draw(&sw, fntdata, e, &oxy);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);

  printf("TEST:   Draw a red contiguous sixel\n");
  oxy.ox = oxy.ox + FNTWIDTH;
  e->graphics_clr = red;
  e->print_mode = contiguous;
  lib_Elem_Draw(&sw, fntdata, e, &oxy);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);

  printf("TEST:   Draw a red separated sixel\n");
  oxy.ox = oxy.ox + FNTWIDTH;
  e->print_mode = separated;
  lib_Elem_Draw(&sw, fntdata, e, &oxy);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);

  printf("TEST:   Draw a red blastthrough 'G'\n");
  oxy.ox = oxy.ox + FNTWIDTH;
  e->c = 'G';
  e->code = TESTNUM_231;
  e->print_mode = separated;
  lib_Elem_Draw(&sw, fntdata, e, &oxy);
  base_SDL_UpdateScreen(&sw);
  SDL_Delay(SDL_DELAYLONG);
  SDL_Quit();
  free(e);

  printf("WORKS:  lib_Elem_DrawChar\n\n");



  /* TEST: lib_ElemArr_Print *****************************/

  printf("TEST:   Print out separated graphics with\n"
    "        colour change & blastthrough\n"
    "        Note mouse-click required to exit\n");

  dim.w = ARRAY_8;
  dim.h = ARRAY_1;
  code_array = lib_codeArr_Init(dim);
  /* Separated Graphics */
  code_array[ARRAY_0] = TESTNUM_154;
  /* Yellow Graphics */
  code_array[ARRAY_1] = TESTNUM_147;
  /* Print Sixel */
  code_array[ARRAY_2] = TESTNUM_237;
  /* Blastthrough <- */
  code_array[ARRAY_3] = TESTNUM_219;
  /* Hold graphics */
  code_array[ARRAY_4] = TESTNUM_158;
  /* Print Sixel */
  code_array[ARRAY_5] = TESTNUM_246;
  /* Red Graphics */
  code_array[ARRAY_6] = TESTNUM_145;
  /* Blastthrough K */
  code_array[ARRAY_7] = TESTNUM_203;
  e_array = lib_ElemArr_Init(dim);
  lib_code2ElemArr(code_array, e_array, dim);
  lib_ElemArr_Print(fntdata, e_array, dim);

  printf("WORKS:  lib_ElemArr_Print\n\n");


  printf("FINISH: testing_library\n\n");
  printf(
    "*************************************************\n");
  printf("\n\n");

}
