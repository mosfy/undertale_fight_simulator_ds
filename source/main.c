#include "undertale_fight_simulator.h"


void game_manager_init(GameManager* manager) {
	manager->turn = GAME_TURN_ENEMY;
	manager->current_attack = ATTACK_PROJECTILE;
	manager->turn_timer = 0;
}

void game_manager_update(GameManager* manager, int keys) {
	if (manager->turn == GAME_TURN_ENEMY) {
		manager->turn_timer++;
		if (manager->turn_timer >= 600) {
			manager->turn = GAME_TURN_PLAYER;
			manager->turn_timer = 0;
		}
	}

	if (manager->turn == GAME_TURN_PLAYER && (keys & KEY_A)) {
		manager->turn = GAME_TURN_ENEMY;
		manager->turn_timer = 0;
		manager->current_attack = ATTACK_PROJECTILE;
	}
}

int main(int argc, char** argv) {
	int frame = 0;
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
	oamInit(&oamSub, SpriteMapping_1D_128, true);
	oamInit(&oamMain, SpriteMapping_1D_128, true);

	vramSetBankF(VRAM_F_LCD);
	vramSetBankI(VRAM_I_LCD);

	dmaCopy(toriel0Pal, VRAM_F_EXT_SPR_PALETTE[0], toriel0PalLen);
	dmaCopy(fight_oPal,  VRAM_F_EXT_SPR_PALETTE[1], act_oPalLen);
	dmaCopy(act_oPal,  VRAM_F_EXT_SPR_PALETTE[2], act_oPalLen);
	dmaCopy(item_oPal,  VRAM_F_EXT_SPR_PALETTE[3], act_oPalLen);
	dmaCopy(mercy_oPal,  VRAM_F_EXT_SPR_PALETTE[4], act_oPalLen);
	dmaCopy(digit_0Pal,  VRAM_F_EXT_SPR_PALETTE[5], digit_0PalLen);
	dmaCopy(digit_1Pal,  VRAM_F_EXT_SPR_PALETTE[6], digit_1PalLen);
	dmaCopy(digit_2Pal,  VRAM_F_EXT_SPR_PALETTE[7], digit_2PalLen);
	dmaCopy(digit_3Pal,  VRAM_F_EXT_SPR_PALETTE[8], digit_3PalLen);
	dmaCopy(digit_4Pal,  VRAM_F_EXT_SPR_PALETTE[9], digit_4PalLen);
	dmaCopy(digit_5Pal,  VRAM_F_EXT_SPR_PALETTE[10], digit_5PalLen);
	dmaCopy(digit_6Pal,  VRAM_F_EXT_SPR_PALETTE[11], digit_6PalLen);
	dmaCopy(digit_7Pal,  VRAM_F_EXT_SPR_PALETTE[12], digit_7PalLen);
	dmaCopy(digit_8Pal,  VRAM_F_EXT_SPR_PALETTE[13], digit_8PalLen);
	dmaCopy(digit_9Pal,  VRAM_F_EXT_SPR_PALETTE[14], digit_9PalLen);
	
	dmaCopy(soul_spritePal,  VRAM_I_EXT_SPR_PALETTE[0], soul_spritePalLen);
	dmaCopy(fire_01Pal,  VRAM_I_EXT_SPR_PALETTE[1], fire_01PalLen);


	// Map some VRAM to be used as extended palettes
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);

	// Initialize the soul sprite and buttons
	Soul soul = {0};
	Toriel toriel = {0};
	Bouton bouton[4] = {0};
	Digit digit = {0};
	ProjectileSystem projectile = {0};
	GameManager game_manager = {0};
	projectile_init(&projectile, &oamSub);
	soul_init(&soul, &oamSub, 20);
	toriel_init(&toriel);
	bouton_init(bouton, &oamMain);
	hp_init(&soul, &oamMain, &digit);
	game_manager_init(&game_manager);
	

	// Play the song
	enum Song song = TORIEL;
	play_music(song);

	while(1) {
		scanKeys();
		int keys = keysHeld();
		game_manager_update(&game_manager, keys);
		soul_update(&soul, &oamSub, &game_manager, keys);
		toriel_update(&toriel);
		bouton_update(bouton);
		hp_update(&soul, &oamMain, &digit);
		projectile_update(&projectile, &oamSub, &soul, &game_manager, frame);
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		frame++;
		//swapbit pour eviter overflow
		swiWaitForVBlank();
	}
	return 0;
}

