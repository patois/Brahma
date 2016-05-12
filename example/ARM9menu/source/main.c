#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "draw.h"
#include "hid.h"
#include "textmenu.h"

void ioDelay(u32);

void ClearTop() {
	ClearScreen(TOP_SCREEN0, RGB(255, 255, 255));
	ClearScreen(TOP_SCREEN1, RGB(255, 255, 255));
	current_y = 0;
}

void newline(int count) {
	int i;
	for(i=0; i<count; i++)
		Debug("");
}

void wait_key() {
	Debug("");
	Debug("Press key to continue");
	InputWait();
}

int who_am_i(int idx, void *param) {
	newline(1);		
	Debug("Hi, from menu item %d", idx+1);
	if (param)
		Debug("Number of Tetris games played %d", *(u32 *)param);
	return 0;
}

int fake_tetris(int idx, void *param) {
	if (param)
		(*(u32 *)param)++;
	int i;
	for(i=0; i<12; i++) {
		ClearTop();
		newline(i);
		Debug(" _ _");
		Debug("|_|_|");
		Debug("  |_|");
		Debug("  |_|");
		ioDelay(100000);
	}	
	ClearTop();
	newline(1);
	Debug("         GAME OVER        :-D");
	
	return 0;
}

int print_menu (int idx, struct menu_t *menu) {
	int i;
	int newidx;
	int count = menu_get_element_count(menu);
	
	newidx = menu_update_index(idx, menu);

	for (i=0; i<count; i++) {
		if (newidx == i)
			Debug("[ %s ]", menu_get_element_name(i, menu));
		else
			Debug("  %s  ", menu_get_element_name(i, menu));
	}
	
	return newidx;	
}

int print_main_menu(int idx, struct menu_t *menu) {
	int newidx = 0;

	newline(1);
	Debug("Text menu example for 3DS");
	newline(2);
	Debug("===========================");
	newidx = print_menu(idx, menu);
	Debug("===========================");	
	newline(1);
	Debug("A:     Confirm");
	Debug("START: Boot firmware");
	
	return newidx;
}

struct menu_t main_menu = {
	4,
	{
		{"Fake Tetris", &fake_tetris},
		{"Hello a", &who_am_i},
		{"Hello b", &who_am_i},
		{"Hello c", &who_am_i}
	}
};

int main() {
	u32 pad_state;
	int menuidx = 0;
	u32 num_calls = 0;

	while (true) {
		ClearTop();

		menuidx = print_main_menu(menuidx, &main_menu);		
		pad_state = InputWait();

		if (pad_state & BUTTON_START) {
			break;
		}
		else if (pad_state & BUTTON_A) {
			ClearTop();
			menu_execute_function(menuidx, &main_menu, &num_calls);
			wait_key();
		}
		else if (pad_state & BUTTON_UP) {
			menuidx--;
		}
		else if (pad_state & BUTTON_DOWN) {
			menuidx++;
		}
	}

	// return control to FIRM ARM9 code (performs firmlaunch)
	return 0;
}