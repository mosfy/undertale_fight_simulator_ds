#include "undertale_fight_simulator.h"

void toriel_init(Toriel *toriel)
{
    toriel->x = 60;
    toriel->y = 20;

    toriel->gfx[0] = oamAllocateGfx(
        &oamMain,
        SpriteSize_64x64,
        SpriteColorFormat_256Color);

    toriel->gfx[1] = oamAllocateGfx(
        &oamMain,
        SpriteSize_64x64,
        SpriteColorFormat_256Color);

    toriel->gfx[2] = oamAllocateGfx(
        &oamMain,
        SpriteSize_64x64,
        SpriteColorFormat_256Color);

    toriel->gfx[3] = oamAllocateGfx(
        &oamMain,
        SpriteSize_64x64,
        SpriteColorFormat_256Color);

    dmaCopy(toriel0Tiles, toriel->gfx[0], toriel0TilesLen);
    dmaCopy(toriel1Tiles, toriel->gfx[1], toriel1TilesLen);
    dmaCopy(toriel2Tiles, toriel->gfx[2], toriel2TilesLen);
    dmaCopy(toriel3Tiles, toriel->gfx[3], toriel3TilesLen);
}

void toriel_update(Toriel *toriel)
{
    int x = toriel->x;
    int y = toriel->y;

    oamSet(&oamMain, 0,
           x, y,
           0, 0,
           SpriteSize_64x64,
           SpriteColorFormat_256Color,
           toriel->gfx[0],
           -1, false, false, false, false, false);

    oamSet(&oamMain, 1,
           x + 64, y,
           0, 0,
           SpriteSize_64x64,
           SpriteColorFormat_256Color,
           toriel->gfx[1],
           -1, false, false, false, false, false);

    oamSet(&oamMain, 2,
           x, y + 64,
           0, 0,
           SpriteSize_64x64,
           SpriteColorFormat_256Color,
           toriel->gfx[2],
           -1, false, false, false, false, false);

    oamSet(&oamMain, 3,
           x + 64, y + 64,
           0, 0,
           SpriteSize_64x64,
           SpriteColorFormat_256Color,
           toriel->gfx[3],
           -1, false, false, false, false, false);
}