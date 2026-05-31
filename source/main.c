#include "music.h"

typedef struct {
	int x, y; // x/y lcoation
	u16* gfx; // oam GFX

} Soul;

int main(int argc, char** argv) {
	Soul soul = {256/2, 196/2}; // set the initial x, y location of the sprite

	// Initialize the top screen engine
	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_SPRITE);

	// Initialise the botom screen
	videoSetModeSub(MODE_0_2D);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	// Initialisation of the sprite renderer in top and botom screen
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	soul.gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	dmaCopy(soulTiles, soul.gfx, soulTilesLen);
	dmaCopy(soulPal, SPRITE_PALETTE_SUB, soulPalLen);
	enum Song song = TORIEL;
	play_music(song);

	while(1) {
		scanKeys();
		int keys = keysHeld();

		if (keys & KEY_RIGHT) 
			soul.x = soul.x + 2;
		if (keys & KEY_LEFT) 
			soul.x = soul.x - 2;
		if (keys & KEY_DOWN) 
			soul.y = soul.y + 2;
		if (keys & KEY_UP) 
			soul.y = soul.y - 2;

		oamSet(&oamSub,
			0, // oam entry id
			soul.x, soul.y, // x, y location
			0, 0, // priority, palette
			SpriteSize_16x16,
			SpriteColorFormat_256Color,
			soul.gfx, // the oam gfx
			-1, false, false, false, false, false);


		swiWaitForVBlank();
		oamUpdate(&oamSub);
	}
	return 0;
}

