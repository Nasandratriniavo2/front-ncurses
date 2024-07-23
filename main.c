#include <ncurses.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
enum menu_principale{
	MENU,
	CHECK,
	RETURN,
	PARCOURIR,
	OPTION,
	QUITTER
};
enum check_and_return{
	tmp,
	by_num,
	by_name,
	go_back
};

enum options{
	temporary,
	langue,
	theme,
	zetinareo,
	back
};
enum langue{
	temp,
	francais,
	anglais,
	malagasy,
	goback
};
int menu(WINDOW* win,int count, ...); 
int main(int argc,char** argv)
{
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	menu:
	switch(menu(stdscr,6," MENU PRINCIPALE ","check","return","parcourir","option","quitter"))			//ngeza ndrindra
	{
		case CHECK:																						//si check
		clear();
		check:
		switch(menu(stdscr,4,"check","by numero", "by name","go back"))									//faire switch
		{
			case by_num:
			clear();
			printw("petafana eto le algo an le by numero");
			refresh();
			napms(2000);
			clear();
			goto check;
			break;
			case by_name:
			clear();
			printw("petafana eto le algo an le by name");
			refresh();
			napms(2000);
			clear();
			goto check;
			break;
			case go_back:
			clear();
			refresh();
			goto menu;
			break;
		}
		break;
		case RETURN:																//si return
		clear();
		retourner:
		switch(menu(stdscr,4,"return","by numero", "by name","go back"))			//choisir entre ...
		{
			case by_num:
			clear();
			printw("petafana eto le algo an le by numero");
			refresh();
			napms(2000);
			clear();
			goto retourner;
			break;
			case by_name:
			clear();
			printw("petafana eto le algo an le by name");
			refresh();
			napms(2000);
			clear();
			goto retourner;
			break;
			case go_back:
			clear();
			refresh();
			goto menu;
			break;
		}break;
		case PARCOURIR:														//si parcourir
		clear();
		parcourir:
		switch(menu(stdscr,4,"parcourir","by numero", "by name","go back"))		//choisir entre
		{
			case by_num:
			clear();
			printw("petafana eto le algo an le by numero");
			refresh();
			napms(2000);
			clear();
			goto parcourir;
			break;
			case by_name:
			clear();
			printw("petafana eto le algo an le by name");
			refresh();
			napms(2000);
			clear();
			goto parcourir;
			break;
			case go_back:
			clear();
			refresh();
			goto menu;
			break;
		}
		break;
		case OPTION:																		//si option
		clear();
		option:
		switch (menu(stdscr,5,"OPTIONS" , "langue", "theme", "de ze tinareo","go_back")){		//choisir entre : 
			case langue:																		// langue
			switch(menu(stdscr,5,"langue","francais" , "anglais" , "malagasy","go back"))
			{
				case francais:
				printw("vous avez choisis le francaise");
				refresh();
				napms(2000);
				clear();
				goto menu;
				break;
				case anglais:
				printw("you choose english ");
				refresh();
				napms(2000);
				clear();
				goto menu;
				break;
				case malagasy:
				printw("teny malagasy no nosafidinao");
				napms(2000);
				clear();
				goto menu;
				break;
				case goback:
				clear();
				refresh();
				goto menu;
				break;
			}
			case theme:
			clear();
			printw("theme milay be");
			refresh();
			napms(2000);
			clear();
			goto option;
			break;
			case zetinareo:
			clear();
			printw("tena ze tinareo");
			refresh();
			napms(2000);
			clear();
			goto option;
			break;
			case back:
			clear();
			refresh();
			goto menu;
			break;
		}
		break;
		case QUITTER:
		clear();
		printw("fermeture du prorgamme...");
		refresh();
		napms(2000);
		break;
	}
	endwin();
	return 0;
}

int menu(WINDOW* win,int count, ...)
{
	keypad(win,true);
	va_list arg;
	va_start(arg,count);
	start_color();
	init_pair (1,COLOR_BLACK,COLOR_YELLOW);
	init_pair (2,COLOR_YELLOW,COLOR_BLACK);
	
	char **argument=(char**)malloc(count*sizeof(char*));;
	int i,c,heighlight=1,y,x;
	getmaxyx(stdscr,y,x);
	for(i=0; i<count ; i++)
	{
		argument[i]=(char*)malloc(200*sizeof(char));
		sprintf(argument[i],"%s" , va_arg(arg, char*));
	}
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win,0,x/2-22,"﴾﴾﴾﴾﴾﴾﴾﴾ %s ﴿﴿﴿﴿﴿﴿﴿﴿\n\n\n", argument[0]);		//titre
		for (i = 1; i < count; i++) {
        if (i == heighlight)
            wattron(win, COLOR_PAIR(1) | A_BOLD | A_DIM);  
		else
			wbkgd(stdscr, COLOR_PAIR(2));		//arrrière plan
            wattron(win, COLOR_PAIR(2));
			WINDOW *window = subwin(win, 4, x - 25, i * 4, 10);  
			box(window, 0, 0);
			mvwprintw(win, i * 4 + 1, x / 2 - 10, "༺   %s ༻", argument[i]);
			wrefresh(window);
			delwin(window);
        wattroff(win, A_BOLD | A_DIM);
        wrefresh(win);
		}
	
	 while((c=getch())!='\n')
	{
		switch (c)
	{
		case KEY_UP:
			heighlight-=(heighlight==1)? 0:1;
			break;
		
		case KEY_DOWN:
			heighlight+=(heighlight==count-1)? 0:1;
			break;
	}for (i = 1; i < count; i++) {
        if (i == heighlight)
            wattron(win, COLOR_PAIR(1) | A_BOLD | A_DIM);  
		else
			wbkgd(stdscr, COLOR_PAIR(2));				//arrrière plan
            wattron(win, COLOR_PAIR(2));
			WINDOW *window = subwin(win, 4, x - 25, i * 4, 10);  
			box(window, 0, 0);
			mvwprintw(win, i * 4 + 1, x / 2 - 10, "༺   %s ༻", argument[i]);
			wrefresh(window);
			delwin(window);
        wattroff(win, A_BOLD | A_DIM);
        wrefresh(win);
		}
	}
	va_end(arg);
	return heighlight;
}	
