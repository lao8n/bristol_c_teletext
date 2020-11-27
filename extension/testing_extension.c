#include "testing_extension.h"

int main(void)
{
  testing_grammar();
  testing_parse();
  testing_parse2code();
  testing_instructions();

  return(EXIT_SUCCESS);
}

void testing_grammar(void)
{
  char            input[MAX_STRINGSIZE];
  char            *copy;

  printf(
    "*************************************************\n");
  printf("START:  testing_grammar\n\n");

  /* TEST: grammar_cmp ***********************************/

  printf("TEST:   Test grammar compare with asserts\n");
  strcpy(input, "[");
  copy = input;
  assert(grammar_cmp(&copy, "[") == true);
  assert(grammar_cmp(&copy, "]") == false);

  printf("WORKS:  grammar_cmp\n\n");

  /* TEST: grammar_leftsqbracket *************************/
  /* TEST: grammar_rightsqbracket ************************/

  printf("TEST:   Test left & right square bracket with \n"
    "        asserts\n");

  strcpy(input, "[");
  copy = input;
  assert(grammar_leftsqbracket(&copy) == true);
  assert(grammar_rightsqbracket(&copy) == false);
  strcpy(input, "]");
  copy = input;
  assert(grammar_leftsqbracket(&copy) == false);
  assert(grammar_rightsqbracket(&copy) == true);

  printf("WORKS:  grammar_leftsqbracket\n");
  printf("WORKS:  grammar_rightsqbracket\n\n");

  /* TEST: grammar_leftcurlybracket **********************/
  /* TEST: grammar_rightcurlybracket *********************/

  printf("TEST:   Test left & right curly bracket with \n"
    "        asserts\n");

  strcpy(input, "{");
  copy = input;
  assert(grammar_leftcurlybracket(&copy) == true);
  assert(grammar_rightcurlybracket(&copy) == false);
  strcpy(input, "}");
  copy = input;
  assert(grammar_leftcurlybracket(&copy) == false);
  assert(grammar_rightcurlybracket(&copy) == true);

  printf("WORKS:  grammar_leftcurlybracket\n");
  printf("WORKS:  grammar_rightcurlybracket\n\n");

  /* TEST: grammar_colon *********************************/

  printf("TEST:   Test grammar colon with asserts\n");

  strcpy(input, ":");
  copy = input;
  assert(grammar_colon(&copy) == true);
  strcpy(input, ";");
  copy = input;
  assert(grammar_colon(&copy) == false);

  printf("WORKS:  grammar_colon\n\n");

  /* TEST: grammar_font_height ***************************/

  printf("TEST:   Test grammar font_height with asserts\n");

  strcpy(input, "font_height");
  copy = input;
  assert(grammar_font_height(&copy) == true);
  strcpy(input, "not font height");
  copy = input;
  assert(grammar_font_height(&copy) == false);

  printf("WORKS:  grammar_font_height\n\n");

  /* TEST: grammar_font_clr ******************************/

  printf("TEST:   Test grammar font_clr with asserts\n");

  strcpy(input, "font_clr");
  copy = input;
  assert(grammar_font_clr(&copy) == true);
  strcpy(input, "not font clr");
  copy = input;
  assert(grammar_font_clr(&copy) == false);

  printf("WORKS:  grammar_font_clr\n\n");

  /* TEST: grammar_bckgrnd *******************************/

  printf("TEST:   Test grammar bckgrnd with\n"
  "        asserts\n");

  strcpy(input, "bckgrnd");
  copy = input;
  assert(grammar_bckgrnd(&copy) == true);
  strcpy(input, "not bckgrnd clr");
  copy = input;
  assert(grammar_bckgrnd(&copy) == false);

  printf("WORKS:  grammar_bckgrnd\n\n");

  /* TEST: grammar_graphics_clr **************************/

  printf("TEST:   Test grammar graphics_clr with\n"
  "        asserts\n");

  strcpy(input, "graphics_clr");
  copy = input;
  assert(grammar_graphics_clr(&copy) == true);
  strcpy(input, "not graphics clr");
  copy = input;
  assert(grammar_graphics_clr(&copy) == false);

  printf("WORKS:  grammar_graphics_clr\n\n");

  /* TEST: grammar_print_mode ****************************/

  printf("TEST:   Test grammar print_mode with\n"
  "        asserts\n");

  strcpy(input, "print_mode");
  copy = input;
  assert(grammar_print_mode(&copy) == true);
  strcpy(input, "not print mode");
  copy = input;
  assert(grammar_print_mode(&copy) == false);

  printf("WORKS:  grammar_print_mode\n\n");

  /* TEST: grammar_graphics_hold **************************/

  printf("TEST:   Test grammar graphics_hold with\n"
  "        asserts\n");

  strcpy(input, "graphics_hold");
  copy = input;
  assert(grammar_graphics_hold(&copy) == true);
  strcpy(input, "not graphics hold");
  copy = input;
  assert(grammar_graphics_hold(&copy) == false);

  printf("WORKS:  grammar_graphics_hold\n\n");

  /* TEST: grammar_height ********************************/

  printf("TEST:   Test grammar height with asserts\n");
  strcpy(input, "single_ht");
  copy = input;
  assert(grammar_height(&copy) == true);
  strcpy(input, "double_ht");
  copy = input;
  assert(grammar_height(&copy) == true);
  strcpy(input, "not height");
  copy = input;
  assert(grammar_height(&copy) == false);

  printf("WORKS:  grammar_height\n\n");

  /* TEST: grammar_colour ********************************/

  printf("TEST:   Test grammar colour with asserts\n");
  strcpy(input, "red");
  copy = input;
  assert(grammar_colour(&copy) == true);
  strcpy(input, "green");
  copy = input;
  assert(grammar_colour(&copy) == true);
  strcpy(input, "yellow");
  copy = input;
  assert(grammar_colour(&copy) == true);
  strcpy(input, "blue");
  copy = input;
  assert(grammar_colour(&copy) == true);
  strcpy(input, "magenta");
  copy = input;
  assert(grammar_colour(&copy) == true);
  strcpy(input, "cyan");
  copy = input;
  assert(grammar_colour(&copy) == true);
  strcpy(input, "white");
  copy = input;
  assert(grammar_colour(&copy) == true);
  strcpy(input, "orange");
  copy = input;
  assert(grammar_colour(&copy) == false);

  printf("WORKS:  grammar_colour\n\n");

  /* TEST: grammar_mode **********************************/

  printf("TEST:   Test grammar mode with asserts\n");
  strcpy(input, "alphanumeric");
  copy = input;
  assert(grammar_mode(&copy) == true);
  strcpy(input, "contiguous");
  copy = input;
  assert(grammar_mode(&copy) == true);
  strcpy(input, "separated");
  copy = input;
  assert(grammar_mode(&copy) == true);
  strcpy(input, "not mode");
  copy = input;
  assert(grammar_mode(&copy) == false);

  printf("WORKS:  grammar_mode\n\n");

  /* TEST: grammar_hold **********************************/

  printf("TEST:   Test grammar hold with asserts\n");
  strcpy(input, "hold");
  copy = input;
  assert(grammar_hold(&copy) == true);
  strcpy(input, "release");
  copy = input;
  assert(grammar_hold(&copy) == true);
  strcpy(input, "not hold");
  copy = input;
  assert(grammar_mode(&copy) == false);

  printf("WORKS:  grammar_hold\n\n");


  printf("FINISH: testing_grammar\n\n");
  printf(
    "*************************************************\n");
  printf("\n\n");
}

void testing_parse(void)
{
  char            input[MAX_STRINGSIZE];
  char            *copy;

  printf(
    "*************************************************\n");
  printf("START:  testing_parse\n\n");

  /* TEST: parse_text ************************************/

  printf("TEST:   Test parsing of text with asserts\n");
  strcpy(input, "abcdefghijklmnopqrstuvwxyz");
  copy = input;
  assert(parse_text(&copy) == true);
  strcpy(input, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  copy = input;
  assert(parse_text(&copy) == true);
  strcpy(input, "0123456789");
  copy = input;
  assert(parse_text(&copy) == true);
  strcpy(input, " !£$%&'()*+,-./:;<=>?#∥");
  copy = input;
  assert(parse_text(&copy) == true);
  strcpy(input, "`_|");
  copy = input;
  assert(parse_text(&copy) == false);

  printf("WORKS:  parse_text\n\n");

  /* TEST: parse_char ************************************/

  printf("TEST:   Test parsing of character commands \n"
  "        with asserts\n");
  strcpy(input, "aA0!");
  copy = input;
  assert(parse_char(&copy) == false);
  strcpy(input, "[aA0!]");
  copy = input;
  assert(parse_char(&copy) == true);

  printf("WORKS:  parse_char\n\n");

  /* TEST: parse_font_height *****************************/

  printf("TEST:   Test parsing of font_height commands \n"
  "        with asserts\n");
  strcpy(input, "font_height:single_ht");
  copy = input;
  assert(parse_font_height(&copy) == true);
  strcpy(input, "font_height:double_ht");
  copy = input;
  assert(parse_font_height(&copy) == true);
  strcpy(input, "font_height:double_ht");
  copy = input;
  assert(parse_font_height(&copy) == true);
  strcpy(input, "font_clr:red");
  copy = input;
  assert(parse_font_height(&copy) == false);

  printf("WORKS:  parse_font_height\n\n");

  /* TEST: parse_font_clr ********************************/

  printf("TEST:   Test parsing of font_clr commands \n"
  "        with asserts\n");
  strcpy(input, "font_clr:red");
  copy = input;
  assert(parse_font_clr(&copy) == true);
  strcpy(input, "font_clr:green");
  copy = input;
  assert(parse_font_clr(&copy) == true);
  strcpy(input, "font_height:double_ht");
  copy = input;
  assert(parse_font_clr(&copy) == false);

  printf("WORKS:  parse_font_clr\n\n");


  /* TEST: parse_bckgrnd *****************************/

  printf("TEST:   Test parsing of bckgrnd commands \n"
  "        with asserts\n");
  strcpy(input, "bckgrnd:black");
  copy = input;
  assert(parse_bckgrnd(&copy) == true);
  strcpy(input, "bckgrnd:new");
  copy = input;
  assert(parse_bckgrnd(&copy) == true);
  strcpy(input, "font_height:double_ht");
  copy = input;
  assert(parse_bckgrnd(&copy) == false);

  printf("WORKS:  parse_bckgrnd\n\n");

  /* TEST: parse_graphics_clr ****************************/

  printf("TEST:   Test parsing of graphics_clr commands \n"
  "        with asserts\n");
  strcpy(input, "graphics_clr:red");
  copy = input;
  assert(parse_graphics_clr(&copy) == true);
  strcpy(input, "graphics_clr:green");
  copy = input;
  assert(parse_graphics_clr(&copy) == true);
  strcpy(input, "font_height:double_ht");
  copy = input;
  assert(parse_graphics_clr(&copy) == false);

  printf("WORKS:  parse_graphics_clr\n\n");

  /* TEST: parse_print_mode ******************************/

  printf("TEST:   Test parsing of print_mode commands \n"
  "        with asserts\n");
  strcpy(input, "print_mode:contiguous");
  copy = input;
  assert(parse_print_mode(&copy) == true);
  strcpy(input, "print_mode:alphanumeric");
  copy = input;
  assert(parse_print_mode(&copy) == true);
  strcpy(input, "font_height:double_ht");
  copy = input;
  assert(parse_print_mode(&copy) == false);

  printf("WORKS:  parse_print_mode\n\n");

  /* TEST: parse_graphics_hold ***************************/

  printf("TEST:   Test parsing of graphics_hold \n"
  "        commands with asserts\n");
  strcpy(input, "graphics_hold:hold");
  copy = input;
  assert(parse_graphics_hold(&copy) == true);
  strcpy(input, "graphics_hold:release");
  copy = input;
  assert(parse_graphics_hold(&copy) == true);
  strcpy(input, "font_height:double_ht");
  copy = input;
  assert(parse_graphics_hold(&copy) == false);

  printf("WORKS:  parse_graphics_hold\n\n");

  /* TEST: parse_control *********************************/

  printf("TEST:   Test parsing of control commands \n"
  "        with asserts\n");
  /* font_height */
  strcpy(input, "font_height:single_ht");
  copy = input;
  assert(parse_control(&copy) == false);
  strcpy(input, "{font_height:single_ht}");
  copy = input;
  assert(parse_control(&copy) == true);
  /* font_clr */
  strcpy(input, "font_clr:red");
  copy = input;
  assert(parse_control(&copy) == false);
  strcpy(input, "{font_clr:red}");
  copy = input;
  assert(parse_control(&copy) == true);
  /* bckgrnd */
  strcpy(input, "bckgrnd:black");
  copy = input;
  assert(parse_control(&copy) == false);
  strcpy(input, "{bckgrnd:black}");
  copy = input;
  assert(parse_control(&copy) == true);
  /* graphics_clr */
  strcpy(input, "graphics_clr:red");
  copy = input;
  assert(parse_control(&copy) == false);
  strcpy(input, "{graphics_clr:red}");
  copy = input;
  assert(parse_control(&copy) == true);
  /* print_mode*/
  strcpy(input, "print_mode:alphanumeric");
  copy = input;
  assert(parse_control(&copy) == false);
  strcpy(input, "{print_mode:alphanumeric}");
  copy = input;
  assert(parse_control(&copy) == true);
  /* graphics_hold*/
  strcpy(input, "graphics_hold:release");
  copy = input;
  assert(parse_control(&copy) == false);
  strcpy(input, "{graphics_hold:release}");
  copy = input;
  assert(parse_control(&copy) == true);

  printf("WORKS:  parse_control\n\n");

  /* TEST: parse_orfail **********************************/

  printf("TEST:   Test parsing of commands \n"
  "        with asserts\n");
  strcpy(input, "[fontheight:red]");
  copy = input;
  assert(parse_orfail(&copy) == true);
  strcpy(input, "{font_height:red}");
  copy = input;
  assert(parse_orfail(&copy) == false);
  strcpy(input, "{font_clr:red}");
  copy = input;
  assert(parse_orfail(&copy) == true);

  printf("WORKS:  parse_orfail\n\n");

  printf("FINISH: testing_parse\n\n");
  printf(
    "*************************************************\n");
  printf("\n\n");
}

void testing_parse2code(void)
{
  char            input[MAX_STRINGSIZE];
  char            *copy;
  Arr_Dim         dim;
  hexdec          *code_array;

  printf(
    "*************************************************\n");
  printf("START:  testing_parse2code\n\n");

  /* TEST: parse2code_font_height ************************/

  printf("TEST:   Test parse2code_font_height with \n"
  "        asserts\n");

  strcpy(input, "{font_height:single_ht}");
  copy = input;
  assert(parse2code_font_height(&copy) == MIN_HT);
  strcpy(input, "{font_height:double_ht}");
  copy = input;
  assert(parse2code_font_height(&copy) == MAX_HT);

  printf("WORKS:  parse2code_font_height\n\n");

  /* TEST: parse2code_font_clr ***************************/

  printf("TEST:   Test parse2code_font_clr with \n"
  "        asserts\n");

  strcpy(input, "{font_clr:red}");
  copy = input;
  assert(parse2code_font_clr(&copy) == MIN_ANCOL);
  strcpy(input, "{font_clr:blue}");
  copy = input;
  assert(parse2code_font_clr(&copy) == MIN_ANCOL +
    CODE_ADD_3);
  strcpy(input, "{font_clr:white}");
  copy = input;
  assert(parse2code_font_clr(&copy) == MAX_ANCOL);

  printf("WORKS:  parse2code_font_clr\n\n");

  /* TEST: parse2code_bckgrnd ****************************/

  printf("TEST:   Test parse2code_bckgrnd with \n"
  "        asserts\n");

  strcpy(input, "{bckgrnd:black}");
  copy = input;
  assert(parse2code_bckgrnd(&copy) == MIN_BCKGRD);
  strcpy(input, "{bckgrnd:new}");
  copy = input;
  assert(parse2code_bckgrnd(&copy) == MAX_BCKGRD);

  printf("WORKS:  parse2code_bckgrnd\n\n");

  /* TEST: parse2code_graphics_clr ***********************/

  printf("TEST:   Test parse2code_graphics_clr with \n"
  "        asserts\n");

  strcpy(input, "{graphics_clr:red}");
  copy = input;
  assert(parse2code_graphics_clr(&copy) == MIN_GRACOL);
  strcpy(input, "{graphics_clr:blue}");
  copy = input;
  assert(parse2code_graphics_clr(&copy) == MIN_GRACOL +
    CODE_ADD_3);
  strcpy(input, "{graphics_clr:white}");
  copy = input;
  assert(parse2code_graphics_clr(&copy) == MAX_GRACOL);

  printf("WORKS:  parse2code_graphics_clr\n\n");

  /* TEST: parse2code_print_mode *************************/

  printf("TEST:   Test parse2code_print_mode with \n"
  "        asserts\n");

  strcpy(input, "{print_mode:contiguous}");
  copy = input;
  assert(parse2code_print_mode(&copy) == MIN_MODE);
  strcpy(input, "{print_mode:separated}");
  copy = input;
  assert(parse2code_print_mode(&copy) == MAX_MODE);

  printf("WORKS:  parse2code_print_mode\n\n");

  /* TEST: parse2code_graphics_hold **********************/

  printf("TEST:   Test parse2code_graphics_hold with \n"
  "        asserts\n");

  strcpy(input, "{graphics_hold:hold}");
  copy = input;
  assert(parse2code_graphics_hold(&copy) == MIN_HOLD);
  strcpy(input, "{graphics_hold:release}");
  copy = input;
  assert(parse2code_graphics_hold(&copy) == MAX_HOLD);

  printf("WORKS:  parse2code_graphics_hold\n\n");

  /* TEST: parse2code_control ****************************/

  printf("TEST:   Test parse2code_control with \n"
  "        asserts\n");

  strcpy(input, "{font_height:single_ht}");
  copy = input;
  assert(parse2code_control(&copy) == MIN_HT);
  strcpy(input, "{font_clr:red}");
  copy = input;
  assert(parse2code_control(&copy) == MIN_ANCOL);
  strcpy(input, "{bckgrnd:black}");
  copy = input;
  assert(parse2code_control(&copy) == MIN_BCKGRD);
  strcpy(input, "{graphics_clr:red}");
  copy = input;
  assert(parse2code_control(&copy) == MIN_GRACOL);
  strcpy(input, "{print_mode:contiguous}");
  copy = input;
  assert(parse2code_control(&copy) == MIN_MODE);
  strcpy(input, "{graphics_hold:release}");
  copy = input;
  assert(parse2code_control(&copy) == MAX_HOLD);

  printf("WORKS:  parse2code_control\n\n");

  /* TEST: parse2code_char ****************************/

  printf("TEST:   Test parse2code_char with \n"
  "        asserts\n");

  strcpy(input, " ");
  copy = input;
  assert(parse2code_char(copy) == MIN_CHAR);
  strcpy(input, "A");
  copy = input;
  assert(parse2code_char(copy) == TEST_193);
  strcpy(input, "a");
  copy = input;
  assert(parse2code_char(copy) == TEST_225);

  printf("WORKS:  parse2code_char\n\n");

  /* TEST: parse2codeArr ****************************/

  printf("TEST:   Test {font_clr:red} & {font_clr:blue}\n"
  "        map to 129 and 132 with asserts\n");
  dim.h = ARRAY_1;
  dim.w = ARRAY_5;
  code_array = lib_codeArr_Init(dim);
  strcpy(input, "{font_clr:red} {font_clr:blue}");
  copy = input;
  parse2codeArr(&copy, code_array);
  assert(code_array[ARRAY_0] == TEST_129);
  assert(code_array[ARRAY_1] == TEST_132);
  lib_codeArr_Free(&code_array);
  printf("TEST:   Test [abcdefghijklmnopqrstuvwxyz]\n"
  "        maps to codeArr with asserts\n");
  dim.w = ARRAY_100;
  code_array = lib_codeArr_Init(dim);
  strcpy(input, "[abcdefghijklmnopqrstuvwxyz]");
  copy = input;
  parse2codeArr(&copy, code_array);
  assert(code_array[ARRAY_0] == TEST_225);
  assert(code_array[ARRAY_25] == TEST_250);
  printf("TEST:   Test char & control\n"
  "        maps to codeArr with asserts\n");
  dim.w = ARRAY_100;
  code_array = lib_codeArr_Init(dim);
  strcpy(input, "{font_clr:red} [abcde]");
  copy = input;
  parse2codeArr(&copy, code_array);
  assert(code_array[ARRAY_0] == TEST_129);
  assert(code_array[ARRAY_1] == TEST_225);
  assert(code_array[ARRAY_5] == TEST_229);
  printf("WORKS:  parse2codeArr\n\n");

  printf("FINISH: testing_parse2code\n\n");
  printf(
    "*************************************************\n");
  printf("\n\n");
}


void testing_instructions(void)
{
  char            input[MAX_STRINGSIZE];
  char            *copy;

  printf(
    "*************************************************\n");
  printf("START:  testing_instructions\n\n");

  /* TEST: instructions_print ****************************/

  printf("TEST:   Test {font_clr:red} & {font_clr:blue}\n"
  "        with print statements\n");
  strcpy(input, "{font_clr:red} {font_clr:blue}");
  copy = input;
  instructions_print(&copy);
  printf("TEST:   Test {font_clr:red} printed but\n"
  "        not invalid [font_clr:blue]\n");
  strcpy(input, "{font_clr:red} [font_clr:blue]");
  copy = input;
  instructions_print(&copy);

  printf("WORKS:  instructions_print\n\n");

  /* TEST: instructions2teletext *************************/

  printf("TEST:   {font_clr:red}\n"
  "        [abcdefghijklmnopqrstuvwxyz]\n");
  strcpy(input,
    "{font_clr:red} [abcdefghijklmnopqrstuvwxyz]");
  copy = input;
  instructions2teletext(&copy);
  printf("TEST:   {font_clr:blue} {bckgrnd:new}\n"
  "        [abcdefghijklmnopqrstuvwxyz]\n"
  "        {bckgrnd:black}\n");
  strcpy(input,
    "{font_clr:blue} {bckgrnd:new} \
    [abcdefghijklmnopqrstuvwxyz] {bckgrnd:black}");
  copy = input;
  instructions2teletext(&copy);
  printf("TEST:   {font_height:double_ht}\n"
  "        [123456789012345678901234567890123456789]\n"
  "        {font_height:double_ht}\n"
  "        [123456789012345678901234567890123456789]\n");
  strcpy(input,
    "{font_height:double_ht} \
    [123456789012345678901234567890123456789] \
    {font_height:double_ht} \
    [123456789012345678901234567890123456789]");
  copy = input;
  instructions2teletext(&copy);
  printf("TEST:   {graphics_clr:magenta}\n"
  "        {print_mode:contiguous}\n"
  "        [123456789]\n");
  strcpy(input,
    "{graphics_clr:magenta} \
    {print_mode:contiguous} \
    [123456789]");
  copy = input;
  instructions2teletext(&copy);
  printf("TEST:   {graphics_clr:yellow}\n"
  "        {print_mode:separated}\n"
  "        [123456789]\n");
  strcpy(input,
    "{graphics_clr:yellow} \
    {print_mode:separated} \
    [123456789]");
  copy = input;
  instructions2teletext(&copy);

  printf("WORKS:  instructions2teletext\n\n");

  printf("FINISH: instructions_print\n\n");
  printf(
    "*************************************************\n");
  printf("\n\n");
}
