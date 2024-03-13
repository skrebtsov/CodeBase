#ifndef CHAR_H
#define CHAR_H

#define CHAR_BS   0x08
#define CHAR_TAB  0x09
#define CHAR_ESC  0x1B

#define CHAR_A  0x80 //'А'
#define CHAR_a  0xA0 //'а'
#define CHAR_Ya 0x9F //'Я'
#define CHAR_ya 0xEF //'я'
#define CHAR_Yu 0x9E //'Ю'
#define CHAR_yu 0xEE //'ю'
#define CHAR_B  0x82 //'В'
#define CHAR_M  0x8C //'М'
#define CHAR_C  0x91 //'С'
#define CHAR_Pe 0x8F //'П'
#define CHAR_pe 0xAF //'п'
#define CHAR_Re 0x90 //'Р'
#define CHAR_re 0xE0 //'р'
#define CHAR_Jo 0xF0 //'Ё'
#define CHAR_jo 0xF1 //'ё'
#define CHAR_FE 0xFE //'■'
#define CHAR_DD 0xDD //'▌'
#define CHAR_B0 0xB0 //'░'
#define CHAR_B1 0xB1 //'▒'
#define CHAR_B2 0xB2 //'▓'
#define CHAR_DB 0xDB //'█'
#define CHAR_C4 0xC4 //'─'
#define CHAR_C3 0xC3 //'├'
#define CHAR_B4 0xB4 //'┤'

char chrupr866( char c);
char chrlwr866( char c);

#endif
