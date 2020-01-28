#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "brew_bgr.h"

int main(int argc, char* argv[]) {

	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	printf("O toque da sua caneta corresponde a letra -> ");

	gfxSetDoubleBuffering(GFX_BOTTOM, false); //ler essa parte da documentação ;D

	u8* frame_buffer_for_render_image = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);

	memcpy(frame_buffer_for_render_image, brew_bgr, brew_bgr_size);

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
			printf("O toque da sua caneta corresponde a letra -> ");
		}

		if (kDown & KEY_SELECT) {
			printf("\x1b[0;0H");
			printf(" ");
		}

	}

	gfxExit();
	return 0;
}
