#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "bottom_screen_bgr.h"
#include "top_screen_bgr.h"

u8* buffer_para_som_leao;
u8* buffer_para_som_gato;
u8* buffer_para_som_cachorro;
u8* buffer_para_som_pikachu;

int main(int argc, char* argv[]) {

	gfxInitDefault();
	csndInit();

	gfxSetDoubleBuffering(GFX_BOTTOM, false); //ler essa parte da documentação ;D
	gfxSetDoubleBuffering(GFX_TOP, false);

	u8* frame_buffer_for_render_image_bottom_screen = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	u8* frame_buffer_for_render_image_top_screen = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

	memcpy(frame_buffer_for_render_image_bottom_screen, bottom_screen_bgr, bottom_screen_bgr_size);
	memcpy(frame_buffer_for_render_image_top_screen, top_screen_bgr, top_screen_bgr_size);

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

			FILE *som_leao = fopen("audio/lion.bin", "rb");
			fseek(som_leao, 0, SEEK_END);
			off_t tamanho_da_musica = ftell(som_leao);
			fseek(som_leao, 0, SEEK_SET);
			buffer_para_som_leao = linearAlloc(tamanho_da_musica);
			off_t bytesRead = fread(buffer_para_som_leao, 1, tamanho_da_musica, som_leao);
			fclose(som_leao);

			csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_ONE_SHOT, 48000, 1.0, 0.0, buffer_para_som_leao, buffer_para_som_leao, tamanho_da_musica);

			linearFree(buffer_para_som_leao);
		
		}

		if (toque.px > 160 && toque.py < 120) {
			
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

			FILE *som_pikachu = fopen("audio/pikachu.bin", "rb");
			fseek(som_pikachu, 0, SEEK_END);
			off_t tamanho_som_pikachu = ftell(som_pikachu);
			fseek(som_pikachu, 0, SEEK_SET);
			buffer_para_som_pikachu = linearAlloc(tamanho_som_pikachu);
			off_t bytesRead = fread(buffer_para_som_pikachu, 1, tamanho_som_pikachu, som_pikachu);
			fclose(som_pikachu);

			csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_ONE_SHOT, 48000, 1.0, 0.0, buffer_para_som_pikachu, buffer_para_som_pikachu, tamanho_som_pikachu);

			linearFree(buffer_para_som_pikachu);
		}

		if (toque.px > 160 && toque.py > 120) {

			FILE *som_cachorro = fopen("audio/dog.bin", "rb");
			fseek(som_cachorro, 0, SEEK_END);
			off_t tamanho_som_cachorro = ftell(som_cachorro);
			fseek(som_cachorro, 0, SEEK_SET);
			buffer_para_som_cachorro = linearAlloc(tamanho_som_cachorro);
			off_t bytesRead = fread(buffer_para_som_cachorro, 1, tamanho_som_cachorro, som_cachorro);
			fclose(som_cachorro);

			csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_ONE_SHOT, 61000, 1.0, 0.0, buffer_para_som_cachorro, buffer_para_som_cachorro, tamanho_som_cachorro);

			linearFree(buffer_para_som_cachorro);
		}

		if (toque.px == 0 && toque.py == 0) {
			//Maybe add a bg sound...
		}

	}

	csndExit();
	gfxExit();
	return 0;
}
