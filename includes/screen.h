// 
/// screen.h
//

// All screens consist of many strings written on different places, and this struct aims at automating the printing of each screen regardless of what needs to be printed.
// The main issue might be that some strings overlap others, but for such a simple programm this should not be an issue.

#pragma once

#include <ncurses.h>
#include <string.h>
#include <stdio.h>

// Code of the associated screen
enum screen_code {
    MENU = 0,
    USE = 1,
    TIMER_SELECT = 2,
    TIMER = 3
};

// Is the position the beginning, the center, or the end of the string?
enum str_position {
    NONE = 0,
    START = 1,
    CENTER = 2,
    END = 3
};

// Single message, along with where it should be printed on the screen.
typedef struct s_message {
    char *str;
    int x;
    int y;
    int pos;
    /* Since there these come in a definite number in the stack, we just hzve them as a NULL-terminated array. */
} t_message;

typedef struct s_hmessage {
    t_message message;
    struct s_hmessage *next;    /* Since we want to be able to add strings at runtime, we have this as a linked list. */
} t_hmessage;

t_message menu_stack_messages[] = {
    {"C Timer", 0, 2, CENTER},
    {"By Stepan Smirnov", 4, 0, START},
    {NULL, 0, 0, NONE}
};

// All the srings in one struct
typedef struct s_screen {
    int code;
    t_hmessage *heap_messages;   /* The messages that can change, i.e. time, selected or not, etc...*/
    t_message *stack_messages;  /* A buch of messages that are static and will never be changed */
} t_screen;
