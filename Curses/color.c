#include <curses.h>

int main(int argc, char** argv)
{
	initscr();
	if (start_color() == OK) {
		init_pair(1, COLOR_RED, COLOR_GREEN);
		attron(COLOR_PAIR(1));
		move(LINES / 2, COLS / 2);
		waddstr(stdscr, "Yet another Hello World!");
		attroff(COLOR_PAIR(1));
	} else {
		waddstr(stdscr, "Can not init color!");
	}

	refresh();
	getch();
	endwin();

	return 0;
}
