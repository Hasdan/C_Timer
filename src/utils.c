//
/// Diverse useful functions
//

#include "screen.h"
#include "files.h"

// Append message at the end of the list, or make it the list 
t_message *append_to_list(t_message *begin, t_message *novo)
{
    t_message *curr = begin;

    if (begin == NULL)
        return (novo);
    
    while (curr->next  != NULL)
        curr = curr->next;

    curr->next = novo;
    return (begin);
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

// Free the ENTIRE t_message chined list
void free_chain(t_message *begin)
{
    t_message *next;

    while (begin != NULL) {
        next = begin->next;
        free(begin->str);
        free(begin);
        begin = next;
    }
}