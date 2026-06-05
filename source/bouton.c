#include "undertale_fight_simulator.h"

#define BUTTON_COUNT 4
#define BUTTON_X_START -1
#define BUTTON_Y 192-32
#define BUTTON_SPACING 64

void bouton_init(Bouton bouton[], OamState* oam)
{
    const void* tiles[BUTTON_COUNT] = {
        fight_oTiles,
        act_oTiles,
        item_oTiles,
        mercy_oTiles,
    };

    const int lengths[BUTTON_COUNT] = {
        fight_oTilesLen,
        act_oTilesLen,
        item_oTilesLen,
        mercy_oTilesLen,
    };
    
    for (int i = 0; i < BUTTON_COUNT; i++) {
        bouton[i].x = BUTTON_X_START + i * BUTTON_SPACING;
        bouton[i].y = BUTTON_Y;
        bouton[i].gfx = oamAllocateGfx(
            oam,
            SpriteSize_64x32,
            SpriteColorFormat_256Color);
        dmaCopy(tiles[i], bouton[i].gfx, lengths[i]);
    }
}

void bouton_update(Bouton bouton[])
{
    for (int i = 0; i < BUTTON_COUNT; i++) {
        oamSet(&oamMain,
               i+20,
               bouton[i].x,
               bouton[i].y,
               0, i + 1,
               SpriteSize_64x32,
               SpriteColorFormat_256Color,
               bouton[i].gfx,
               -1, false, false, false, false, false);
    }
}
