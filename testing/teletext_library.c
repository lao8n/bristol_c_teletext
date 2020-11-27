/*********************************************************/
/* teletext_library.c ************************************/
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

#include "teletext_library.h"

/*********************************************************/
/* CODE => INT *******************************************/
/*********************************************************/

int lib_code2int(hexdec code)
{
  int            num;

  num = code - MIN_CHAR;

  if(num > SIXEL_NUMMAX){
    num = num - CODE_ADJ;
  }

  return num;
}

/*********************************************************/
/* CODE FUNCTIONS ****************************************/
/*********************************************************/

hexdec* lib_codeArr_Init(Arr_Dim dim)
{
  int             x, y;
  hexdec          *code_array;

  /* Allocate memory as a large 1-D array even though we
  will access it using 2-D syntax) */
  code_array = (hexdec *) gfmalloc(sizeof(hexdec) * dim.h
    * dim.w);

  for(y = 0; y < dim.h; y++){
    for(x = 0; x < dim.w; x++){
      code_array[y * dim.w + x] = (hexdec) 0;
    }
  }

  return code_array;
}

void lib_codeArr_Free(hexdec **code_array)
{
  hexdec          *temp;

  temp = *code_array;
  free(temp);
  *code_array = NULL;
}

void lib_codeArr_ImportBin(FILE *fp, hexdec *code_array,
  Arr_Dim dim)
{
  int             x, y, count;
  char            c;
  hexdec          i;

  for(y = 0; y < dim.h; y++){
    for(x = 0; x < dim.w; x++){
      count = fscanf(fp, "%c", &c);
      i = (hexdec) c;
      if(i < 0){
        i = i + (hexdec) HEXDEC_ADJ;
      }
      if(i < HEXDEC_MIN){
        i = i + (hexdec) + HEXDEC_MIN;
      }
      code_array[y * dim.w + x] = i;
      if(count < 1){
        fprintf(stderr, "Error in fscanf \n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

/*********************************************************/
/* ELEM FUNCTIONS ****************************************/
/*********************************************************/

Elem* lib_Elem_Init(void)
{
  Elem* e;

  e = (Elem *) gfmalloc(sizeof(Elem));

  e->code          = 0;
  e->c             = (unsigned char) ' ';
  e->font_height   = single_ht;
  e->font_clr      = white;
  e->bckgrnd_clr   = black;
  e->graphics_clr  = white;
  e->print_mode    = alphanumeric;
  e->graphics_hold = release;

  return e;
}

void lib_Elem_Default(Elem *e)
{
  e->code          = 0;
  e->c             = (unsigned char) ' ';
  e->font_height   = single_ht;
  e->font_clr      = white;
  e->bckgrnd_clr   = black;
  e->graphics_clr  = white;
  e->print_mode    = alphanumeric;
  e->graphics_hold = release;
}

void lib_Elem_Copy(Elem *e, Elem *e_copyfrom)
{
  e->code          = e_copyfrom->code;
  e->c             = e_copyfrom->c;
  e->font_height   = e_copyfrom->font_height;
  e->font_clr      = e_copyfrom->font_clr;
  e->bckgrnd_clr   = e_copyfrom->bckgrnd_clr;
  e->graphics_clr  = e_copyfrom->graphics_clr;
  e->print_mode    = e_copyfrom->print_mode;
  e->graphics_hold = e_copyfrom->graphics_hold;
}

Elem** lib_ElemArr_Init(Arr_Dim dim)
{
  int             x, y;
  /* Pointer to an array of pointers to Elem */
  /* Written in this weird way to be clear, but it is just
  a double pointer Elem** */
  Elem*           *e_array;

  /* Allocate memory as a large 1-D array even though we
  will access it using 2-D syntax) */
  e_array = (Elem **) gfmalloc(sizeof(Elem *) * dim.h
    * dim.w);

  for(y = 0; y < dim.h; y++){
    for(x = 0; x < dim.w; x++){
      e_array[y * dim.w + x] = lib_Elem_Init();
    }
  }

  return e_array;
}

void lib_ElemArr_Free(Elem*** e_array, Arr_Dim dim)
{
  int             x, y;
  Elem            *temp, **temp2;

  for(y = 0; y < dim.h; y++){
    for(x = 0; x < dim.w; x++){
      temp = (*e_array)[y * dim.w + x];
      free(temp);
      (*e_array)[y * dim.w + x] = NULL;
    }
  }
  temp2 = *e_array;
  free(temp2);
  *e_array = NULL;
}

/*********************************************************/
/* CODE => ELEM ******************************************/
/*********************************************************/

void lib_code2Elem_code(Elem *e, hexdec code)
{
  if(code < MIN_CODE || code > MAX_CODE){
    fprintf(stderr, "Invalid hexdec code %d to\n"
      "lib_code2Elem_code\n",
      code);
    exit(EXIT_FAILURE);
  }

  e->code = code;
}

void lib_code2Elem_c(Elem *e, hexdec code)
{
  unsigned char c = (unsigned char) ' ' + code - MIN_CHAR;

  if(code < MIN_CHAR || code > MAX_CHAR){
    fprintf(stderr, "Invalid hexdec code %d to \n"
      "lib_code2Elem_c\n",
      code);
    exit(EXIT_FAILURE);
  }

  e->c = c;
}

void lib_code2Elem_font_height(Elem *e, hexdec code)
{
  Font_Height fnt_height = (Font_Height) code - MIN_HT;

  if(code < MIN_HT || code > MAX_HT){
    fprintf(stderr, "Invalid hexdec code %d to\n"
      "lib_code2Elem_font_height\n",
      code);
    exit(EXIT_FAILURE);
  }
  e->print_mode = alphanumeric;
  e->font_height = fnt_height;
}

void lib_code2Elem_font_clr(Elem *e, hexdec code)
{
  Colour fnt_colour = (Colour) code - MIN_ANCOL;

  if(code < MIN_ANCOL || code > MAX_ANCOL){
    fprintf(stderr, "Invalid hexdec code %d to\n"
      "lib_code2Elem_font_clr\n",
      code);
    exit(EXIT_FAILURE);
  }

  e->font_clr = fnt_colour;
  e->print_mode = alphanumeric;
}
void lib_code2Elem_bckgrnd_clr(Elem *e, hexdec code)
{
  if(code < MIN_BCKGRD || code > MAX_BCKGRD){
    fprintf(stderr, "Invalid hexdec code %d to \n"
      "lib_code2Elem_bckgrnd_clr\n",
      code);
    exit(EXIT_FAILURE);
  }

  if(code == MIN_BCKGRD){
    e->bckgrnd_clr = black;
  }
  else if(code == MAX_BCKGRD){
    e->bckgrnd_clr = e->font_clr;
    e->font_clr = white;
  }
}

void lib_code2Elem_graphics_clr(Elem *e, hexdec code)
{
  Colour graphics_colour = (Colour) code - MIN_GRACOL;

  if(code < MIN_GRACOL || code > MAX_GRACOL){
    fprintf(stderr, "Invalid hexdec code %d to\n"
      "lib_code2Elem_graphics_clr\n",
      code);
    exit(EXIT_FAILURE);
  }

  e->graphics_clr = graphics_colour;
  e->print_mode = contiguous;
}

void lib_code2Elem_print_mode(Elem *e, hexdec code)
{
  if(code < MIN_MODE || code > MAX_MODE){
    fprintf(stderr, "Invalid hexdec code %d to\n"
      "lib_code2Elem_print_mode\n",
      code);
    exit(EXIT_FAILURE);
  }

  if(code == MIN_MODE){
    e->print_mode = contiguous;
  }
  else if(code == MAX_MODE){
    e->print_mode = separated;
  }
}

void lib_code2Elem_graphics_hold(Elem *e, hexdec code)
{
  Hold_Release hold_type = (Hold_Release) code - MIN_HOLD;

  if(code < MIN_HOLD || code > MAX_HOLD){
    fprintf(stderr, "Invalid hexdec code %d to\n"
      "lib_code2Elem_graphics_hold\n",
      code);
    exit(EXIT_FAILURE);
  }

  e->graphics_hold = hold_type;
}

void lib_code2Elem(Elem *e, hexdec code)
{
  if(code > MAX_CODE || code < MIN_CODE){
    fprintf(stderr, "Invalid hexdec code %d to\n"
      "lib_code2Elem\n",
      code);
    exit(EXIT_FAILURE);
  }
  lib_code2Elem_code(e, code);

  /* Control codes */
  if(code >= MIN_CON && code <= MAX_CON){
    /* Print space - to print last then do nothing */
    /* Update control codes */
    if(code >= MIN_HT && code <= MAX_HT){
      lib_code2Elem_font_height(e, code);
    }
    else if(code >= MIN_ANCOL && code <= MAX_ANCOL){
      lib_code2Elem_font_clr(e, code);
    }
    else if(code >= MIN_GRACOL && code <= MAX_GRACOL){
      lib_code2Elem_graphics_clr(e, code);
    }
    else if(code >= MIN_MODE && code <= MAX_MODE){
      lib_code2Elem_print_mode(e, code);
    }
    else if(code >= MIN_BCKGRD && code <= MAX_BCKGRD){
      lib_code2Elem_bckgrnd_clr(e, code);
    }
    else if(code >= MIN_HOLD && code <= MAX_HOLD){
      lib_code2Elem_graphics_hold(e, code);
    }
    else {
      fprintf(stderr, "Unassigned hexdec code %d\n",
        code);
      exit(EXIT_FAILURE);
    }
    /* Print space - to print last then do nothing */
    if(e->graphics_hold == release){
      e->c = (unsigned char) ' ';
    }
  }
  /* Character codes */
  else if(code >= MIN_CHAR && code <= MAX_CHAR){
    lib_code2Elem_c(e, code);
  }
}

void lib_code2ElemArr_fix_htbot(Elem** e_array, Arr_Dim
  dim)
{
  int             x, y;

  for(y = 1; y < dim.h; y++){
    for(x = 0; x < dim.w; x++){
      /* If current cell & cell above are both double
      height then make bottom cell bottom */
      if(e_array[y * dim.w + x]->font_height ==
        double_httop &&
        e_array[y * dim.w + x - dim.w]->font_height ==
        double_httop /*&&
        e_array[y * dim.w + x]->c ==
        e_array[y * dim.w + x - dim.w]-> c */){
        e_array[y * dim.w + x]->font_height = double_htbot;
      }
    }
  }
}

void lib_code2ElemArr(hexdec *code_array, Elem** e_array,
  Arr_Dim dim)
{
  int             x, y;

  for(y = 0; y < dim.h; y++){
    for(x = 0; x < dim.w; x++){
      if(x == 0){
        lib_Elem_Default(e_array[y * dim.w + x]);
      }
      else {
        lib_Elem_Copy(e_array[y * dim.w + x],
          e_array[y * dim.w + x - 1]);
      }
      lib_code2Elem(e_array[y * dim.w + x],
        code_array[y * dim.w + x]);
    }
  }
  lib_code2ElemArr_fix_htbot(e_array, dim);
}

/*********************************************************/
/* ELEM => BASE ******************************************/
/*********************************************************/

SDL_ColourRGB lib_Colour2RGB(Colour clr)
{
  SDL_ColourRGB   colour;

  colour.r = colour.g = colour.b = SDL_CLRMAX;

  switch(clr)
  {
    case red:{
      colour.g = SDL_CLRMIN;
      colour.b = SDL_CLRMIN;
      break;
    }
    case green:{
      colour.r = SDL_CLRMIN;
      colour.b = SDL_CLRMIN;
      break;
    }
    case blue:{
      colour.r = SDL_CLRMIN;
      colour.g = SDL_CLRMIN;
      break;
    }
    case yellow:{
      colour.b = SDL_CLRMIN;
      break;
    }
    case magenta:{
      colour.g = SDL_CLRMIN;
      break;
    }
    case cyan:{
      colour.r = SDL_CLRMIN;
      break;
    }
    case white:{
      break;
    }
    case black:{
      colour.r = SDL_CLRMIN;
      colour.g = SDL_CLRMIN;
      colour.b = SDL_CLRMIN;
      break;
    }
    default:{
      fprintf(stderr, "Invalid draw colour\n");
      exit(EXIT_FAILURE);
    }
  }
  return colour;
}

/*********************************************************/
/* DRAW ELEM *********************************************/
/*********************************************************/

void lib_Elem_DrawChar(SDL_Simplewin *sw, fntrow
  fntdata[FNTCHARS][FNTHEIGHT], Elem *e, SDL_Origin *oxy)
{
  base_SDL_DrawChar(sw, fntdata,
    lib_Colour2RGB(e->font_clr),
    lib_Colour2RGB(e->bckgrnd_clr),
    e->c, oxy, e->font_height);
}

void lib_Elem_DrawSixel(SDL_Simplewin *sw, Elem *e,
  int sixel[NUM_SIXELS], SDL_Origin *oxy)
{
  int             x, y, adj;
  SDL_Dim         dim, dim2;
  SDL_Origin      temp_xy;

  if(e->print_mode == contiguous){
    adj = 0;
  }
  else if(e->print_mode == separated){
    adj = SEPARATED_ADJ;
  }
  else {
    fprintf(stderr, "Invalid SIXEL call\n");
    exit(EXIT_FAILURE);
  }

  dim2.w = FNTWIDTH;
  dim2.h = FNTHEIGHT;
  temp_xy.ox = oxy->ox;
  temp_xy.oy = oxy->oy;
  base_SDL_DrawRect(sw,
    lib_Colour2RGB(e->bckgrnd_clr), &temp_xy, &dim2);

  dim.w = FNTWIDTH / SIXEL_COL - adj;
  dim.h = FNTHEIGHT / SIXEL_ROW - adj;

  for(y = 0; y < SIXEL_ROW; y++){
    for(x = 0; x < SIXEL_COL; x++){
      temp_xy.ox = oxy->ox + x * (dim.w + adj);
      temp_xy.oy = oxy->oy + y * (dim.h + adj);
      if(sixel[y * SIXEL_COL + x] == BIN_1){
        base_SDL_DrawRect(sw,
          lib_Colour2RGB(e->graphics_clr), &temp_xy, &dim);
      }
    }
  }
}

void lib_Elem_Draw(SDL_Simplewin *sw, fntrow
  fntdata[FNTCHARS][FNTHEIGHT], Elem *e, SDL_Origin *oxy)
{
  int             sixel[NUM_SIXELS];
  unsigned char   temp = e->c - ' ' + MIN_CHAR;

  if(e->print_mode == alphanumeric){
    lib_Elem_DrawChar(sw, fntdata, e, oxy);
  }
  else if(e->print_mode == contiguous || e->print_mode ==
    separated){
    if(temp >=  MIN_BLAST && temp <= MAX_BLAST){
      e->font_clr = e->graphics_clr;
      /*
      e->bckgrnd_clr = black;
      */
      lib_Elem_DrawChar(sw, fntdata, e, oxy);
    }
    else if(temp >= MIN_CHAR){
      base_int2bin(lib_code2int(temp), sixel);
      lib_Elem_DrawSixel(sw, e, sixel, oxy);
    }
  }
  else {
    fprintf(stderr, "Invalid print_mode\n");
    exit(EXIT_FAILURE);
  }
}

void lib_ElemArr_Print(fntrow fntdata[FNTCHARS][FNTHEIGHT],
  Elem** e_array, Arr_Dim dim)
{
  SDL_Origin      oxy;
  SDL_Simplewin   sw;
  int             x, y;

  base_SDL_Init(&sw);
  base_SDL_UpdateScreen(&sw);
  for(y = 0; y < dim.h; y++){
    for(x = 0; x < dim.w; x++){
      oxy.oy = y * FNTHEIGHT;
      oxy.ox = x * FNTWIDTH;
      lib_Elem_Draw(&sw, fntdata, e_array[y * dim.w + x],
        &oxy);
      base_SDL_UpdateScreen(&sw);
    }
  }
  while(!sw.finished){
    base_SDL_Events(&sw);
  }
}
