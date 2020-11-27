#include "extension.h"

/*********************************************************/
/* GRAMMAR FUNCTIONS *************************************/
/*********************************************************/

bool grammar_cmp(char *s[], const char *comp)
{
  if(strncmp(*s, comp, strlen(comp)) == 0){
    *s = *s + strlen(comp);
    return true;
  }
  return false;
}

bool grammar_leftsqbracket(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "[")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_rightsqbracket(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "]")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_leftcurlybracket(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "{")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_rightcurlybracket(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "}")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_colon(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, ":")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_font_height(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "font_height")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_font_clr(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "font_clr")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_bckgrnd(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "bckgrnd")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_graphics_clr(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "graphics_clr")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_print_mode(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "print_mode")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_graphics_hold(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "graphics_hold")){
    return true;
  }
  else {
    *s = original;
    return false;
  }
}

bool grammar_height(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "single_ht")
    || grammar_cmp(s, "double_ht")){
    return true;
  }
  else{
    *s = original;
    return false;
  }
}

bool grammar_colour(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "red") || grammar_cmp(s, "green") ||
    grammar_cmp(s, "yellow") || grammar_cmp(s, "blue") ||
    grammar_cmp(s, "magenta") || grammar_cmp(s, "cyan") ||
    grammar_cmp(s, "white")){
    return true;
  }
  else{
    *s = original;
    return false;
  }
}

bool grammar_mode(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "alphanumeric") ||
    grammar_cmp(s, "contiguous") ||
    grammar_cmp(s, "separated")){
    return true;
  }
  else{
    *s = original;
    return false;
  }
}

bool grammar_bckgrnd_mode(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "black") ||
    grammar_cmp(s, "new")){
    return true;
  }
  else{
    *s = original;
    return false;
  }
}

bool grammar_hold(char *s[])
{
  char            *original = *s;

  if(grammar_cmp(s, "hold") || grammar_cmp(s, "release")){
    return true;
  }
  else{
    *s = original;
    return false;
  }
}

/*********************************************************/
/* PARSE FUNCTIONS ***************************************/
/*********************************************************/

bool parse_text(char *s[])
{
  char            *original = *s;
  char            text[MAX_TEXTLENGTH];
  int             num_charsread;

  if((sscanf(*s,
    " %[!£$%&'()*+,-./:;<=>?0-9A-Z#a-z]%n",
    (char *) &text,
    &num_charsread)) == 1){
    *s = *s + num_charsread;
    return true;
  }

  *s = original;
  return false;
}

bool parse_char(char *s[])
{
  char            *original = *s;

  if(!grammar_leftsqbracket(s)){
    *s = original;
    return false;
  }
  if(!parse_text(s)){
    *s = original;
    return false;
  }
  if(!grammar_rightsqbracket(s)){
    *s = original;
    return false;
  }
  return true;
}

bool parse_font_height(char *s[])
{
  char            *original = *s;

  if(!grammar_font_height(s)){
    *s = original;
    return false;
  }
  if(!grammar_colon(s)){
    *s = original;
    return false;
  }
  if(!grammar_height(s)){
    *s = original;
    return false;
  }
  return true;
}

bool parse_font_clr(char *s[])
{
  char            *original = *s;

  if(!grammar_font_clr(s)){
    *s = original;
    return false;
  }
  if(!grammar_colon(s)){
    *s = original;
    return false;
  }
  if(!grammar_colour(s)){
    *s = original;
    return false;
  }
  return true;
}

bool parse_bckgrnd(char *s[])
{
  char            *original = *s;

  if(!grammar_bckgrnd(s)){
    *s = original;
    return false;
  }
  if(!grammar_colon(s)){
    *s = original;
    return false;
  }
  if(!grammar_bckgrnd_mode(s)){
    *s = original;
    return false;
  }
  return true;
}

bool parse_graphics_clr(char *s[])
{
  char            *original = *s;

  if(!grammar_graphics_clr(s)){
    *s = original;
    return false;
  }
  if(!grammar_colon(s)){
    *s = original;
    return false;
  }
  if(!grammar_colour(s)){
    *s = original;
    return false;
  }
  return true;
}

bool parse_print_mode(char *s[])
{
  char            *original = *s;

  if(!grammar_print_mode(s)){
    *s = original;
    return false;
  }
  if(!grammar_colon(s)){
    *s = original;
    return false;
  }
  if(!grammar_mode(s)){
    *s = original;
    return false;
  }
  return true;
}

bool parse_graphics_hold(char *s[])
{
  char            *original = *s;

  if(!grammar_graphics_hold(s)){
    *s = original;
    return false;
  }
  if(!grammar_colon(s)){
    *s = original;
    return false;
  }
  if(!grammar_hold(s)){
    *s = original;
    return false;
  }
  return true;
}

bool parse_control(char *s[])
{
  char            *original = *s;

  if(!grammar_leftcurlybracket(s)){
    *s = original;
    return false;
  }
  if(!parse_font_height(s) && !parse_font_clr(s) &&
    !parse_bckgrnd(s) && !parse_graphics_clr(s) &&
    !parse_print_mode(s) && !parse_graphics_hold(s)){
    *s = original;
    return false;
  }
  if(!grammar_rightcurlybracket(s)){
    *s = original;
    return false;
  }
  return true;
}

bool parse_orfail(char *s[])
{
  char            *original = *s;

  if(parse_control(s)){
    return true;
  }
  else if(parse_char(s)){
    return true;
  }
  *s = original;
  return false;
}

/*********************************************************/
/* PARSE 2 CODE ******************************************/
/*********************************************************/

hexdec parse2code_font_height(char *s[])
{
  hexdec          code = MIN_HT;

  if(grammar_cmp(s, "{font_height:single_ht}")){
    code = MIN_HT;
  }
  else if(grammar_cmp(s, "{font_height:double_ht}")){
    code = MAX_HT;
  }

  return code;
}

hexdec parse2code_font_clr(char *s[])
{
  hexdec          code = MIN_ANCOL;

  if(grammar_cmp(s, "{font_clr:red}")){
    ;
  }
  else if(grammar_cmp(s, "{font_clr:green}")){
    code += CODE_ADD_1;
  }
  else if(grammar_cmp(s, "{font_clr:yellow}")){
    code += CODE_ADD_2;
  }
  else if(grammar_cmp(s, "{font_clr:blue}")){
    code += CODE_ADD_3;
  }
  else if(grammar_cmp(s, "{font_clr:magenta}")){
    code += CODE_ADD_4;
  }
  else if(grammar_cmp(s, "{font_clr:cyan}")){
    code += CODE_ADD_5;
  }
  else if(grammar_cmp(s, "{font_clr:white}")){
    code = MAX_ANCOL;
  }

  return code;
}

hexdec parse2code_bckgrnd(char *s[])
{
  hexdec          code = MIN_BCKGRD;

  if(grammar_cmp(s, "{bckgrnd:black}")){
    ;
  }
  else if(grammar_cmp(s, "{bckgrnd:new}")){
    code = MAX_BCKGRD;
  }

  return code;
}

hexdec parse2code_graphics_clr(char *s[])
{
  hexdec          code = MIN_GRACOL;

  if(grammar_cmp(s, "{graphics_clr:red}")){
    ;
  }
  else if(grammar_cmp(s, "{graphics_clr:green}")){
    code += CODE_ADD_1;
  }
  else if(grammar_cmp(s, "{graphics_clr:yellow}")){
    code += CODE_ADD_2;
  }
  else if(grammar_cmp(s, "{graphics_clr:blue}")){
    code += CODE_ADD_3;
  }
  else if(grammar_cmp(s, "{graphics_clr:magenta}")){
    code += CODE_ADD_4;
  }
  else if(grammar_cmp(s, "{graphics_clr:cyan}")){
    code += CODE_ADD_5;
  }
  else if(grammar_cmp(s, "{graphics_clr:white}")){
    code = MAX_GRACOL;
  }

  return code;
}

hexdec parse2code_print_mode(char *s[])
{
  hexdec          code = MIN_MODE;

  if(grammar_cmp(s, "{print_mode:contiguous}")){
    ;
  }
  else if(grammar_cmp(s, "{print_mode:separated}")){
    code = MAX_MODE;;
  }

  return code;
}


hexdec parse2code_graphics_hold(char *s[])
{
  hexdec          code = MIN_HOLD;

  if(grammar_cmp(s, "{graphics_hold:hold}")){
    ;
  }
  else if(grammar_cmp(s, "{graphics_hold:release}")){
    code = MAX_HOLD;
  }

  return code;
}

hexdec parse2code_control(char *s[])
{
  hexdec          code = 0;
  char            temp[MAX_TEXTLENGTH], *temp_ptr;
  int             trim_len;

  trim_len = (int) strlen(*s) - TRIM;
  sscanf(*s, "{%s", (char *) temp);
  temp[trim_len] = '\0';
  temp_ptr = temp;

  if(parse_font_height(&temp_ptr)){
    code = parse2code_font_height(s);
  }
  else if(parse_font_clr(&temp_ptr)){
    code = parse2code_font_clr(s);
  }
  else if(parse_bckgrnd(&temp_ptr)){
    code = parse2code_bckgrnd(s);
  }
  else if(parse_graphics_clr(&temp_ptr)){
    code = parse2code_graphics_clr(s);
  }
  else if(parse_print_mode(&temp_ptr)){
    code = parse2code_print_mode(s);
  }
  else if(parse_graphics_hold(&temp_ptr)){
    code = parse2code_graphics_hold(s);
  }

  return code;
}

hexdec parse2code_char(char s[])
{
  hexdec          code = MIN_CHAR;

  code += (int) *s - ' ';

  return code;
}

void parse2codeArr(char *s[], hexdec *code_array)
{
  char            temp[MAX_TEXTLENGTH];
  char            *temp_ptr = temp;
  int             num_charsread;
  int             trim_len, i;

  while(sscanf(*s, "%s%n", temp, &num_charsread) == 1){
    *s += num_charsread;
    temp_ptr = temp;
    if(parse_orfail(&temp_ptr) == true){
      temp_ptr = temp;
      if(parse_control(&temp_ptr) == true){
        temp_ptr = temp;
        *code_array = parse2code_control(&temp_ptr);
        code_array++;
      }
      else if(parse_char(&temp_ptr) == true){
        temp_ptr = temp;
        trim_len = (int) strlen(temp_ptr) - TRIM;
        temp_ptr = temp_ptr + sizeof(char);
        temp_ptr[trim_len] = '\0';
        for(i = 0; i < trim_len; i++){
          *code_array = parse2code_char(&temp_ptr[i]);
          code_array++;
        }
      }
    }
  }
}

/*********************************************************/
/* INSTRUCTION FUNCTIONS *********************************/
/*********************************************************/

void instructions_print(char *s[])
{
  char            temp[MAX_TEXTLENGTH];
  char            *temp_ptr = temp;
  int             num_charsread;


  while(sscanf(*s, "%s%n", temp, &num_charsread) == 1){
    *s += num_charsread;
    temp_ptr = temp;
    if(parse_orfail(&temp_ptr) == true){
      printf("PRINT:  ");
      printf("%s\n", temp);
    }
  }
}

void instructions2teletext(char *s[])
{
  Arr_Dim         dim;
  hexdec          *code_array;
  fntrow          fntdata[FNTCHARS][FNTHEIGHT];
  Elem            **e_array;

  dim.w = NUM_COL;
  dim.h = NUM_ROW;

  base_ReadFont(fntdata, "m7fixed.fnt");
  code_array = lib_codeArr_Init(dim);
  parse2codeArr(s, code_array);
  e_array = lib_ElemArr_Init(dim);
  lib_code2ElemArr(code_array, e_array, dim);
  lib_ElemArr_Print(fntdata, e_array, dim);
  lib_codeArr_Free(&code_array);
  lib_ElemArr_Free(&e_array, dim);
}
