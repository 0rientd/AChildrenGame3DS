#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	printf("O toque da sua caneta corresponde a letra -> ");

	while (aptMainLoop())
	{
		gfxFlushBuffers();
		gfxSwapBuffers();

		gspWaitForVBlank();

		hidScanInput();

		touchPosition toque;
		hidTouchRead(&toque);

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;

		if (toque.px < 160 && toque.py < 120 && toque.px != 0 && toque.py != 0) {
			printf("\x1b[0;0H");
			printf("O toque da sua caneta corresponde a letra -> A\n");
		}

		if (toque.px > 160 && toque.py < 120) {
			printf("\x1b[0;0H");
			printf("O toque da sua caneta corresponde a letra -> B\n");
		}

		if (toque.px < 160 && toque.py > 120) {
			printf("\x1b[0;0H");
			printf("O toque da sua caneta corresponde a letra -> C\n");
		}

		if (toque.px > 160 && toque.py > 120) {
			printf("\x1b[0;0H");
			printf("O toque da sua caneta corresponde a letra -> D\n");
		}

		if (toque.px == 0 && toque.py == 0) {
			printf("\x1b[0;0H");
			printf("O toque da sua caneta corresponde a letra -> ")
		}

		if (kDown & KEY_SELECT) {
			printf("\x1b[0;0H");
			printf(" ");
		}

	}

	gfxExit();
	return 0;
}
