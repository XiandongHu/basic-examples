#include <curses.h>

int main(int argc, char** argv)
{
	initscr();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	move(LINES / 2, COLS / 2);
	waddstr(stdscr, "Hello World!");
	refresh();
	getch();
	endwin();

	return 0;
}
