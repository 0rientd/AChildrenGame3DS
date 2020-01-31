#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "brew_bgr.h"

u8* buffer_para_som;
u8* buffer_para_som_gato;
u32 size;

int main(int argc, char* argv[]) {

	gfxInitDefault();
	csndInit();
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

			FILE *som_porco = fopen("audio/lion.bin", "rb");
			fseek(som_porco, 0, SEEK_END);
			off_t tamanho_da_musica = ftell(som_porco);
			fseek(som_porco, 0, SEEK_SET);
			buffer_para_som = linearAlloc(tamanho_da_musica);
			off_t bytesRead = fread(buffer_para_som, 1, tamanho_da_musica, som_porco);
			fclose(som_porco);

			csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_ONE_SHOT, 48000, 1.0, 0.0, buffer_para_som, buffer_para_som, tamanho_da_musica);

			linearFree(buffer_para_som);
		
		}

		if (toque.px > 160 && toque.py < 120) {
			printf("\x1b[0;0H");
			printf("O toque da sua caneta corresponde a letra -> B\n");
			
			FILE *som_gato = fopen("audio/cat.bin", "rb");
			fseek(som_gato, 0, SEEK_END);
			off_t tamanho_som_gato = ftell(som_gato);
			fseek(som_gato, 0, SEEK_SET);
			buffer_para_som_gato = linearAlloc(tamanho_som_gato);
			off_t bytesRead = fread(buffer_para_som_gato, 1, tamanho_som_gato, som_gato);
			fclose(som_gato);

			csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_ONE_SHOT, 48000, 1.0, 0.0, buffer_para_som_gato, buffer_para_som_gato, tamanho_som_gato);

			linearFree(buffer_para_som_gato);
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

	csndExit();
	gfxExit();
	return 0;
}
