//
/// Header for functions of all files.
//

#pragma once

#include "screen.h"

// main.c
void end_ncurses(t_master *master);

// init_screens.c
WINDOW *init_ncurses(void);
void init_master(t_master *master);

// utils.c
t_message *append_to_list(t_message *begin, t_message *novo);
int get_offset(t_message *message);
void free_chain(t_message *begin);
