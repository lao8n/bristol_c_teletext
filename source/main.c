/*********************************************************/
/* main.c ************************************************/
/*********************************************************/

/* The teletext code is structured in 3 layers:
1. User layer
2. Library layer
3. Base layer
This layer is user layer the base layers abstracted
away the details of SDL rendering, the library layer
abstracted away any reference to drawing at all. The user
layer includes a user_function which only requires the
user for the font file the binary file and the dimensions
of the binary file*/

#include "teletext_library.h"

#define NUM_ARGS            2
#define ROWS                25
#define COLS                40
#define FIRSTARG            1

void      argc_error(int argc, char **argv);
void      user_function(char *binary_file, char *font_file,
            Arr_Dim dim);

/*********************************************************/
/* MAIN **************************************************/
/*********************************************************/

int main(int argc, char **argv)
{
  Arr_Dim         dim;

  argc_error(argc, argv);
  dim.w = COLS;
  dim.h = ROWS;

  user_function(argv[FIRSTARG], "m7fixed.fnt", dim);

  return EXIT_SUCCESS;
}

/*********************************************************/
/* FUNCTIONS *********************************************/
/*********************************************************/

void argc_error(int argc, char **argv)
{
  if(argc != NUM_ARGS){
    fprintf(stderr, "Error opening %s\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

void user_function(char *binary_file, char *font_file,
  Arr_Dim dim)
{
  FILE            *fp;
  hexdec          *code_array;
  Elem            **e_array;
  fntrow          fntdata[FNTCHARS][FNTHEIGHT];

  fp = gfopen(binary_file, "rb");
  base_ReadFont(fntdata, font_file);
  code_array = lib_codeArr_Init(dim);
  lib_codeArr_ImportBin(fp, code_array, dim);
  e_array = lib_ElemArr_Init(dim);
  lib_code2ElemArr(code_array, e_array, dim);
  lib_ElemArr_Print(fntdata, e_array, dim);
  lib_codeArr_Free(&code_array);
  lib_ElemArr_Free(&e_array, dim);
}
