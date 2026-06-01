#include "music.h"
#include "background.h"

typedef struct {
	int x, y; // x/y lcoation
	u16* gfx; // oam GFX

} Soul;

typedef struct
{
    int x;
    int y;
    int width;
    int height;
    int thickness;
} FightBox;


int main(int argc, char** argv) {
	Soul soul = {256/2, 196/2}; // set the initial x, y location of the sprite

	// Initialize the top screen engine
	videoSetMode(MODE_0_2D);

	// Initialise the botom screen
	videoSetModeSub(MODE_5_2D);
	vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_LCD, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	int bgsub = bgInitSub(0, BgType_Text8bpp, BgSize_T_256x256, 0,1);

	// Load the backgroud that is the box fight
    memcpy(bgGetGfxPtr(bgsub), backgroundTiles, backgroundTilesLen);
    memcpy(bgGetMapPtr(bgsub), backgroundMap, backgroundMapLen);
    memcpy(BG_PALETTE_SUB, backgroundPal, backgroundPalLen);

	// Initialisation of the sprite renderer in top and botom screen
	oamInit(&oamSub, SpriteMapping_1D_32, false);
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	soul.gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	touchPosition touch_pos = { 0 };

	// Read the file soul
	dmaCopy(soulTiles, soul.gfx, soulTilesLen);
	dmaCopy(soulPal, SPRITE_PALETTE_SUB, soulPalLen);

	// Play the song
	enum Song song = TORIEL;
	play_music(song);

	while(1) {
		scanKeys();
		int keys = keysHeld();
		if (keys & KEY_TOUCH)
		{
			touchRead(&touch_pos);
			if(touch_pos.px > soul.x)
				soul.x = soul.x + 2;
			if(touch_pos.px < soul.x)
				soul.x = soul.x - 2;
			if(touch_pos.py > soul.y)
				soul.y = soul.y + 2;
			if(touch_pos.py < soul.y)
				soul.y = soul.y - 2;
		}
		else
		{
			if (keys & KEY_RIGHT) 
				soul.x = soul.x + 2;
			if (keys & KEY_LEFT) 
				soul.x = soul.x - 2;
			if (keys & KEY_DOWN) 
				soul.y = soul.y + 2;
			if (keys & KEY_UP) 
				soul.y = soul.y - 2;
		}
		if (soul.x > 205 - 8)
		{
			soul.x = soul.x - 2;
		}
		if (soul.x < 52 + 10)
		{
			soul.x = soul.x + 2;
		}
		if (soul.y < 20 + 10)
		{
			soul.y = soul.y + 2;
		}
		if (soul.y > 173 - 8)
		{
			soul.y = soul.y - 2;
		}
		oamSet(&oamSub,
			0, // oam entry id
			soul.x - 8, soul.y - 8, // x, y location
			0, 0, // priority, palette
			SpriteSize_16x16,
			SpriteColorFormat_256Color,
			soul.gfx, // the oam gfx
			-1, false, false, false, false, false);
		

		oamUpdate(&oamSub);
		swiWaitForVBlank();
	}
	return 0;
}

