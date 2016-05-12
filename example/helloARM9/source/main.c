#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "draw.h"
#include "hid.h"


void ClearTop() {
	ClearScreen(TOP_SCREEN0, RGB(255, 255, 255));
	ClearScreen(TOP_SCREEN1, RGB(255, 255, 255));
	current_y = 0;
}

void wait_key() {
	Debug("");
	Debug("Press key to continue");
	InputWait();
}

int main() {
	ClearTop();
	Debug("");
	Debug("Hello world from ARM9!");
	wait_key();

	// return control to FIRM ARM9 code (performs firmlaunch)
	return 0;
}