#include "undertale_fight_simulator.h"


int main(int argc, char** argv) {
	// Initialize the top screen engine
	videoSetMode(MODE_5_2D);

	// Initialise the botom screen
	videoSetModeSub(MODE_5_2D);
	vramSetPrimaryBanks(VRAM_A_MAIN_SPRITE, VRAM_B_MAIN_BG, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	int bgsub = bgInitSub(0, BgType_Text8bpp, BgSize_T_256x256, 0,1);

	// Load the backgroud that is the box fight
    memcpy(bgGetGfxPtr(bgsub), backgroundTiles, backgroundTilesLen);
    memcpy(bgGetMapPtr(bgsub), backgroundMap, backgroundMapLen);
    memcpy(BG_PALETTE_SUB, backgroundPal, backgroundPalLen);

	// Initialisation of the sprite renderer in top and botom screen
	oamInit(&oamSub, SpriteMapping_1D_32, false);
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	// Initialize the soul sprite and buttons
	Soul soul = {0};
	Toriel toriel = {0};
	Bouton bouton[4] = {0};
	soul_init(&soul, &oamSub);
	bouton_init(bouton, &oamMain);
	toriel_init(&toriel);

	// Play the song
	enum Song song = TORIEL;
	play_music(song);

	while(1) {
		soul_update(&soul, &oamSub);
		bouton_update(bouton);
		toriel_update(&toriel);
		oamUpdate(&oamMain);
		swiWaitForVBlank();
	}
	return 0;
}

