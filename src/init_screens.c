//
/// Where you initialize the master struct and it's components.
//

#include "screen.h"
#include "files.h"

// Have all the init parts of the library in one function.
WINDOW *init_ncurses(void)
{
    WINDOW *win = initscr();	/* Start curses mode and get screen struct. Mostly implied that functions are applied to this specific struct, but some require it anyways. 		  */

	if (win == NULL) {
		return NULL;
	}
	cbreak();					/* Directly print anything instead of just waiting for a \n*/
	noecho();					/* When user writes, nothing is actually written on the terminal, but instead just registered by the program*/
	halfdelay(10);				/* When getch(int ag) is called, return err after ag seconds. Useful for waiting for user input without benchmarking the PC.*/
    keypad(win, true);			/* Allows to get extended inputn such as KEY_LEFT. */
	notimeout(win, TRUE);		/* When user presses ESC, do not wait for another letter. */
	curs_set(FALSE);			/* Hide cursor so that it doesn't blink. */
	return (win);
}

// Set a screen once all changes have been applied.
void init_screen(t_master *master, int code, t_message array[])
{
    t_message *begin = NULL;
    t_message *novo = NULL;

    for (int i = 0; array[i].str != NULL; i++) {
        novo = malloc(sizeof(t_message));
        novo->str = strdup(array[i].str);
        novo->x = array[i].x;
        novo->y = array[i].y;
        novo->pos = array[i].pos;
        novo->next = NULL;
        begin = append_to_list(begin, novo);
    }
    master->screens[code].code = code;
    master->screens[code].messages = begin;
}

// Apply changes to the menu array.
void init_menu(t_master *master)
{
    t_message menu_stack_messages[] = {
        {"C Timer", (COLS / 2) - 1, 2, CENTER, NULL},
        {"By Stepan Smirnov", 4, LINES - 2, START, NULL},
        {NULL, 0, 0, NONE, NULL}
    };

    init_screen(master, MENU, (t_message *) &menu_stack_messages);
}

// Initialize master struct.
void init_master(t_master *master)
{
    t_message none[] = {
        {NULL, 0, 0, NONE, NULL}
    };

    master->timer = 0;
    master->current = MENU;
    master->win = init_ncurses();
    dprintf(2, "c_timer: Dimentions: %d %d\n", COLS, LINES);

    init_menu(master);
    init_screen(master, USE, none);
    init_screen(master, TIMER_SELECT, none);
    init_screen(master, TIMER, none);

}