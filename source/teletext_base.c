/*********************************************************/
/* teletext_base.c ***************************************/
/*********************************************************/

/* The teletext code is structured in 3 layers:
1. User layer
2. Library layer
3. Base layer
This layer is the base layer and includes core SDL, Font
& file processing functions, #defines and typedefs.
The SDL functions in particular help abstract the Library
layer away from the details of SDL rendering */

#include "teletext_base.h"

/*********************************************************/
/* GENERAL USE *******************************************/
/*********************************************************/

FILE* gfopen(char* fn, char* mode)
{
  FILE            *fp;

  if((fp = fopen(fn, mode)) == NULL){
    fprintf(stderr, "Cannot open file %s\n", fn);
    exit(EXIT_FAILURE);
  }

  return fp;
}

void* gfmalloc(size_t size)
{
  void            *p;

  p = malloc(size);

  if(p == NULL){
    fprintf(stderr, "Malloc failed\n");
    exit(EXIT_FAILURE);
  }

  return p;
}

/*********************************************************/
/* BINARY <-> CODE ***************************************/
/*********************************************************/

hexdec base_bin2code(char c)
{
  hexdec          code;

  code = (hexdec) c + SDL_8BITCOLOUR;

  return code;
}

/* Converts int into an array of 1's & 0's which
can be used to print patterns of sixels. */
void base_int2bin(int num, int sixel[NUM_SIXELS])
{
  int             i;
  if(num > SIXEL_NUMMAX || num < SIXEL_NUMMIN){
    fprintf(stderr, "Invalid sixel integer conversion \n");
    exit(EXIT_FAILURE);
  }
  /* Note this assumes a 2^0, 2^1, 2^2, 2^3, 2^4, 2^5
  structure. For Sixels will need to adjust code number
  coming in to get 2^0, 2^1, 2^2, 2^3, 2^4, 2^6 */
  for(i = 0; i < NUM_SIXELS; i++){
    sixel[i] = num % BIN;
    num = num / BIN;
  }
}

/*********************************************************/
/* FONTS *************************************************/
/*********************************************************/

/* Reads in font file */
void base_ReadFont(fntrow fntdata[FNTCHARS][FNTHEIGHT],
  char *fname)
{
  FILE            *fp;
  size_t          itms;

  fp = gfopen(fname, "rb");

  itms = fread(fntdata, sizeof(fntrow),
            FNTCHARS * FNTHEIGHT, fp);

  if(itms != FNTCHARS * FNTHEIGHT){
    fprintf(stderr, "Cannot open font file %s (%d)\n",
      fname, (int) itms);
    exit(EXIT_FAILURE);
  }

  fclose(fp);
}

/*********************************************************/
/* SDL ***************************************************/
/*********************************************************/

/* Set up a simple (WIDTH, HEIGHT) window. Attempt to hide
the renderer etc. from user. */
void base_SDL_Init(SDL_Simplewin *sw)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
     fprintf(stderr, "\nUnable to initialize SDL:  %s\n",
      SDL_GetError());
     SDL_Quit();
     exit(EXIT_FAILURE);
  }

  /* SDL_bool */
  sw->finished = 0;

  /* SDL_Window */
  sw->win= SDL_CreateWindow("SDL Window",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         WWIDTH, WHEIGHT,
                         SDL_WINDOW_SHOWN);

  if(sw->win == NULL){
     fprintf(stderr,
       "\nUnable to initialize SDL Window:  %s\n",
       SDL_GetError());
     SDL_Quit();
     exit(EXIT_FAILURE);
  }

  /* SDL_Renderer */
  sw->renderer = SDL_CreateRenderer(sw->win, NEG_ONE,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

  if(sw->renderer == NULL){
     fprintf(stderr,
       "\nUnable to initialize SDL Renderer:  %s\n",
       SDL_GetError());
     SDL_Quit();
     exit(EXIT_FAILURE);
  }

  SDL_SetRenderDrawBlendMode(sw->renderer,
    SDL_BLENDMODE_BLEND);

  /* Create texture for display */
  sw->display = SDL_CreateTexture(sw->renderer,
    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
    WWIDTH, WHEIGHT);
  if(sw->display == NULL){
     fprintf(stderr,
       "\nUnable to initialize SDL texture:  %s\n",
       SDL_GetError());
     SDL_Quit();
     exit(EXIT_FAILURE);
  }
  SDL_SetRenderTarget(sw->renderer, sw->display);

  /* Clear screen, & set draw colour to black */
  SDL_SetRenderDrawColor(sw->renderer, SDL_CLRMIN,
    SDL_CLRMIN, SDL_CLRMIN, SDL_CLRMAX);
  SDL_RenderClear(sw->renderer);
}

/* Gobble all events & ignore most */
void base_SDL_Events(SDL_Simplewin *sw)
{
  SDL_Event       event;

  while(SDL_PollEvent(&event))
  {
      switch (event.type){
         case SDL_QUIT:
         case SDL_MOUSEBUTTONDOWN:
         case SDL_KEYDOWN:
            sw->finished = 1;
      }
   }
}

/* Housekeeping to do with the render buffer & updating the
screen */
void base_SDL_UpdateScreen(SDL_Simplewin *sw)
{
  SDL_SetRenderTarget(sw->renderer, NULL);
  SDL_RenderCopy(sw->renderer, sw->display, NULL, NULL);
  SDL_RenderPresent(sw->renderer);
  SDL_SetRenderTarget(sw->renderer, sw->display);
}

/* Trivial wrapper to avoid complexities of renderer &
alpha channels */
void base_SDL_SetDrawColour(SDL_Simplewin *sw,
  SDL_ColourRGB colour)
{
  SDL_SetRenderDrawColor(sw->renderer, colour.r,
    colour.g, colour.b, SDL_ALPHA_OPAQUE);
}

/* Wrapper to draw graphics for sixels etc. */
void base_SDL_DrawRect(SDL_Simplewin *sw, SDL_ColourRGB
  colour, SDL_Origin *oxy, SDL_Dim *dim)
{
  SDL_Rect        rect;

  rect.w = dim->w;
  rect.h = dim->h;
  rect.x = oxy->ox;
  rect.y = oxy->oy;
  base_SDL_SetDrawColour(sw, colour);
  SDL_RenderFillRect(sw->renderer, &rect);
}

/* Wrapper to draw characters */
void base_SDL_DrawChar(SDL_Simplewin *sw, fntrow
  fntdata[FNTCHARS][FNTHEIGHT], SDL_ColourRGB fnt_clr,
  SDL_ColourRGB bckgrnd_clr, unsigned char chr, SDL_Origin
  *oxy, Font_Height fnt_height)
{
  unsigned int    x, y, min, max, multiplier;

  /* Single height */
  if(fnt_height == single_ht){
    min = 0;
    max = FNTHEIGHT;
    multiplier = 1;
  }
  /* Double height top */
  else if(fnt_height == double_httop){
    min = 0;
    max = FNTHEIGHT / FNTDOUBLE;
    multiplier = FNTDOUBLE;
  }
  /* Double height bot */
  else if (fnt_height == double_htbot){
    min = FNTHEIGHT / FNTDOUBLE;
    max = FNTHEIGHT;
    multiplier = FNTDOUBLE;
  }
  else {
    fprintf(stderr,
      "\nInvalid font height\n");
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  for(y = min; y < max; y++){
    for(x = 0; x < FNTWIDTH; x++){
      if(fntdata[chr - FNT1STCHAR][y] >>
        (FNTWIDTH - 1 - x) & 1){
        base_SDL_SetDrawColour(sw, fnt_clr);
      }
      else {
        base_SDL_SetDrawColour(sw, bckgrnd_clr);
      }
      SDL_RenderDrawPoint(sw->renderer, oxy->ox + x,
        oxy->oy + multiplier * (y - min));
      if(fnt_height == double_httop ||
        fnt_height == double_htbot){
        SDL_RenderDrawPoint(sw->renderer, oxy->ox + x,
          oxy->oy + multiplier * (y - min) + 1);
      }
    }
  }
}
