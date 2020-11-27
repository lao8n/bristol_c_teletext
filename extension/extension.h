#include "teletext_library.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_STRINGSIZE      1000
#define MAX_TEXTLENGTH      100

/* GRAMMAR FUNCTIONS */
bool           grammar_cmp(char *s[], const char *comp);
bool           grammar_leftsqbracket(char *s[]);
bool           grammar_rightsqbracket(char *s[]);
bool           grammar_leftcurlybracket(char *s[]);
bool           grammar_rightcurlybracket(char *s[]);
bool           grammar_colon(char *s[]);
bool           grammar_font_height(char *s[]);
bool           grammar_font_clr(char *s[]);
bool           grammar_bckgrnd(char *s[]);
bool           grammar_graphics_clr(char *s[]);
bool           grammar_print_mode(char *s[]);
bool           grammar_graphics_hold(char *s[]);
bool           grammar_height(char *s[]);
bool           grammar_colour(char *s[]);
bool           grammar_bckgrnd_mode(char *s[]);
bool           grammar_mode(char *s[]);
bool           grammar_hold(char *s[]);

/* PARSE FUNCTIONS */
bool           parse_text(char *s[]);
bool           parse_char(char *s[]);
bool           parse_font_height(char *s[]);
bool           parse_font_clr(char *s[]);
bool           parse_bckgrnd(char *s[]);
bool           parse_graphics_clr(char *s[]);
bool           parse_print_mode(char *s[]);
bool           parse_graphics_hold(char *s[]);
bool           parse_control(char *s[]);
bool           parse_orfail(char *s[]);


#define CODE_ADD_1          1
#define CODE_ADD_2          2
#define CODE_ADD_3          3
#define CODE_ADD_4          4
#define CODE_ADD_5          5
#define CODE_ADD_6          6
#define TRIM                2
#define TEST_129            129
#define TEST_132            132
#define TEST_193            193
#define TEST_225            225
#define TEST_229            229
#define TEST_250            250
#define ARRAY_0             0
#define ARRAY_1             1
#define ARRAY_5             5
#define ARRAY_25            25
#define ARRAY_100           100

/* PARSE 2 CODE */
hexdec         parse2code_font_height(char *s[]);
hexdec         parse2code_font_clr(char *s[]);
hexdec         parse2code_bckgrnd(char *s[]);
hexdec         parse2code_graphics_clr(char *s[]);
hexdec         parse2code_print_mode(char *s[]);
hexdec         parse2code_graphics_hold(char *s[]);
hexdec         parse2code_control(char *s[]);
hexdec         parse2code_char(char s[]);
void           parse2codeArr(char *s[], hexdec
                 *code_array);

/* INSTRUCTION FUNCTIONS */
void           instructions_print(char *s[]);
void           instructions2teletext(char *s[]);
