#include "undertale_fight_simulator.h"

void soul_init(Soul* soul, OamState* oam, int max_hp) {
	// Initialize soul position
	soul->x = 256 / 2;
	soul->y = 196 / 2;
	
	// Allocate graphics for the soul sprite
	soul->gfx = oamAllocateGfx(oam, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	// Load the soul graphics
	dmaCopy(soul_spriteTiles, soul->gfx, soul_spriteTilesLen);
	dmaCopy(soul_spritePal, SPRITE_PALETTE_SUB, soul_spritePalLen);
	soul->hp = max_hp;
}

void soul_update(Soul* soul, OamState* oam) {
	scanKeys();
	int keys = keysHeld();
	touchPosition touch_pos = { 0 };
	
	// Handle input (touch or keyboard)
	if (keys & KEY_TOUCH) {
		touchRead(&touch_pos);
		if (touch_pos.px > soul->x)
			soul->x = soul->x + 2;
		if (touch_pos.px < soul->x)
			soul->x = soul->x - 2;
		if (touch_pos.py > soul->y)
			soul->y = soul->y + 2;
		if (touch_pos.py < soul->y)
			soul->y = soul->y - 2;
	} else {
		if (keys & KEY_RIGHT)
			soul->x = soul->x + 2;
		if (keys & KEY_LEFT)
			soul->x = soul->x - 2;
		if (keys & KEY_DOWN)
			soul->y = soul->y + 2;
		if (keys & KEY_UP)
			soul->y = soul->y - 2;
		if (keys & KEY_A)
			soul->hp = soul->hp + 1;
	}
	
	// Boundary checking
	if (soul->x > 205 - 8) {
		soul->x = soul->x - 2;
	}
	if (soul->x < 52 + 10) {
		soul->x = soul->x + 2;
	}
	if (soul->y < 20 + 10) {
		soul->y = soul->y + 2;
	}
	if (soul->y > 173 - 8) {
		soul->y = soul->y - 2;
	}
	
	// Render the soul sprite
	oamSet(oam,
		0, // oam entry id
		soul->x - 8, soul->y - 8, // x, y location
		0, 0, // priority, palette
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		soul->gfx, // the oam gfx
		-1, false, false, false, false, false);
	
	oamUpdate(oam);
}
