// 
/// Header for the main structures and enums
//

// All screens consist of many strings written on different places, and this struct aims at automating the printing of each screen regardless of what needs to be printed.
// The main issue might be that some strings overlap others, but for such a simple programm this should not be an issue.

#pragma once

#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Code of the associated screen.
// Size is here to have the null-terminated array of 
enum screen_code {
    MENU = 0,
    USE = 1,
    TIMER_SELECT = 2,
    TIMER = 3,
    SCREEN_ARRAY_SIZE
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
    struct s_message *next;
} t_message;

// All the srings in one struct
typedef struct s_screen {
    int code;                   /* The code of the struct associated with the screen. */
    t_message *messages;
} t_screen;

typedef struct s_master {
    WINDOW *win;     /* The window */
    int current;        /* The screen we are in. */
    int timer;          /* The timer, if there is one. */
    t_screen screens[SCREEN_ARRAY_SIZE];
} t_master;
