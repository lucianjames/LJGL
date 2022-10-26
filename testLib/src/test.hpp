// This test program uses ncurses to display hello world	
#include <ncurses.h>

void helloWorld(){
	initscr();
	printw("Hello World!");
	refresh();
	getch();
	endwin();
}
