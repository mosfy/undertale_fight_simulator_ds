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
	oamInit(&oamMain, SpriteMapping_1D_128, true);

	vramSetBankF(VRAM_F_LCD);

	dmaCopy(toriel0Pal, VRAM_F_EXT_SPR_PALETTE[0], toriel0PalLen);
	dmaCopy(fight_oPal,  VRAM_F_EXT_SPR_PALETTE[1], act_oPalLen);
	dmaCopy(act_oPal,  VRAM_F_EXT_SPR_PALETTE[2], act_oPalLen);
	dmaCopy(item_oPal,  VRAM_F_EXT_SPR_PALETTE[3], act_oPalLen);
	dmaCopy(mercy_oPal,  VRAM_F_EXT_SPR_PALETTE[4], act_oPalLen);
	dmaCopy(digit_0Pal,  VRAM_F_EXT_SPR_PALETTE[5], digit_0PalLen);


	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	// Initialize the soul sprite and buttons
	Soul soul = {0};
	Toriel toriel = {0};
	Bouton bouton[4] = {0};
	Digit digit = {0};
	soul_init(&soul, &oamSub, 20);
	toriel_init(&toriel);
	bouton_init(bouton, &oamMain);
	hp_init(&soul, &oamMain, &digit);

	// Play the song
	enum Song song = TORIEL;
	play_music(song);

	while(1) {
		soul_update(&soul, &oamSub);
		toriel_update(&toriel);
		bouton_update(bouton);
		hp_update(&soul, &oamMain, &digit);
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		swiWaitForVBlank();
	}
	return 0;
}

