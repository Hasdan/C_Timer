//
/// Starting point of the program.
//

#include "screen.h"
#include "files.h"

// Free all remaining t_message structs
void free_messages(t_master *master)
{
	for (int i = 0; i < SCREEN_ARRAY_SIZE; i += 1) {
		free_chain(master->screens[i].messages);
	}
}

// Free everything before exiting the program.
void end_ncurses(t_master *master)
{
	endwin();					/* End curses mode		*/
	delwin(master->win);		/* Delete the window	*/
	master->win = NULL;
}

// Print the contents of a screen and refresh.
// BEWARE: The move(y, x) function takes y FIRST and x SECOND
void print_screen(t_screen *screen)
{
	int offset;

	for (t_message *i = screen->messages; i != NULL; i = i->next) {
		offset = get_offset(i);
		move(i->y, i->x + offset);
		printw(i->str);
	}
	refresh();
}

int main(void) {
	t_master master;

	init_master(&master);
	if (master.win == NULL) {
		dprintf(2, "c_timer: Error initializing window.\n");
		return (1);
	}
	print_screen(&master.screens[master.current]);
	getch();					/* Wait for user input */
	free_messages(&master);
	end_ncurses(&master);
    return (0);
}