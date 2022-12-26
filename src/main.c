#include "screen.h"

// Have all the init parts of the library in one function.
WINDOW *init_ncurses(void)
{
    WINDOW *win = initscr();	/* Start curses mode and get screen struct. Mostly implied that functions are applied to this specific struct, but some require it anyways. 		  */

	if (win == NULL) {
		return NULL;
	}
	cbreak();					/* Directly print anything instead of just waiting for a \n*/
	noecho();					/* When user writes, nothing is actually written on the terminal, but instead just registered by the program*/
	halfdelay(100);				/* When getch(int ag) is called, return err after ag seconds. Useful for waiting for user input without benchmarking the PC.*/
    keypad(win, true);			/* Allows to get extended inputn such as KEY_LEFT. */
	notimeout(win, TRUE);		/* When user presses ESC, do not wait for another letter. */
	curs_set(FALSE);			/* Hide cursor so that it doesn't blink. */
	return (win);
}

// Free everything before exiting the program.
void end_ncurses(WINDOW *win)
{
	endwin();					/* End curses mode		*/
	delwin(win);				/* Delete the window	*/
}

// Get the offset of the printed message.
int get_offset(t_message *message)
{
	int offset = 0;

	switch (message->pos) {
		case (START):
            break;
        case (CENTER):
			offset -= strlen(message->str) / 2;
			break;
        case (END):
			offset -= strlen(message->str);
			break;
		default:
			dprintf(2, "c_timer: Unknown str_position code.");
            break;
	}
	return (offset);
}

// Print the contents of a screen and refresh.
// BEWARE: The move(y, x) function takes y FIRST and x SECOND
void print_screen(t_screen *screen)
{
	int offset;
	t_message *msg;

	for (int i = 0; screen->stack_messages[i].str != NULL; i += 1) {
		offset = get_offset(&(screen->stack_messages[i]));
		move(screen->stack_messages[i].y, screen->stack_messages[i].x + offset);
		printw(screen->stack_messages[i].str);
	}

	for (t_hmessage *i = screen->heap_messages; i != NULL; i = i->next) {
		msg = &i->message;
		offset = get_offset(msg);
		move(msg->x + offset, msg->y);
		printw(msg->str);
	}
	refresh();
}

int main(void) {
	WINDOW *win = init_ncurses();
	t_screen menu;
	menu.code = MENU;
	menu_stack_messages[0].x = (COLS / 2) - 1;
	menu_stack_messages[1].y = LINES - 2;
	menu.stack_messages = &menu_stack_messages;
	menu.heap_messages = NULL;

	if (win == NULL) {
		dprintf(2, "c_timer: Error initializing window.\n");
		return (1);
	}
	print_screen(&menu);
	getch();					/* Wait for user input */
	end_ncurses(win);
    return (0);
}