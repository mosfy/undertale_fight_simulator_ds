#include "undertale_fight_simulator.h"

#define BUTTON_COUNT 4
#define BUTTON_X_START 10
#define BUTTON_Y 100
#define BUTTON_SPACING 50

void bouton_init(Bouton bouton[], OamState* oam)
{
    const void* tiles[BUTTON_COUNT] = {
        act_oBitmap,
        fight_oBitmap,
        item_oBitmap,
        mercy_oBitmap,
    };

    const int lengths[BUTTON_COUNT] = {
        act_oBitmapLen,
        fight_oBitmapLen,
        item_oBitmapLen,
        mercy_oBitmapLen,
    };

    dmaCopy(act_oPal, SPRITE_PALETTE, act_oPalLen);

    for (int i = 0; i < BUTTON_COUNT; i++) {
        bouton[i].x = BUTTON_X_START + i * BUTTON_SPACING;
        bouton[i].y = BUTTON_Y;
        bouton[i].gfx = oamAllocateGfx(
            oam,
            SpriteSize_32x16,
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
               0, 0,
               SpriteSize_32x16,
               SpriteColorFormat_256Color,
               bouton[i].gfx,
               -1, false, false, false, false, false);
    }
}
