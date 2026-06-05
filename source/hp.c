#include "undertale_fight_simulator.h"

void hp_init(Soul* soul, OamState* oam, Digit *digit){
    for(int i = 0; i < 10; i++){
        digit->gfx[i] = oamAllocateGfx(oam, SpriteSize_16x16, SpriteColorFormat_256Color);
    }
    dmaCopy(digit_0Tiles, digit->gfx[0], digit_0TilesLen);
    dmaCopy(digit_1Tiles, digit->gfx[1], digit_1TilesLen);
    dmaCopy(digit_2Tiles, digit->gfx[2], digit_2TilesLen);
    dmaCopy(digit_3Tiles, digit->gfx[3], digit_3TilesLen);
    dmaCopy(digit_4Tiles, digit->gfx[4], digit_4TilesLen);
    dmaCopy(digit_5Tiles, digit->gfx[5], digit_5TilesLen);
    dmaCopy(digit_6Tiles, digit->gfx[6], digit_6TilesLen);
    dmaCopy(digit_7Tiles, digit->gfx[7], digit_7TilesLen);
    dmaCopy(digit_8Tiles, digit->gfx[8], digit_8TilesLen);
    dmaCopy(digit_9Tiles, digit->gfx[9], digit_9TilesLen);
}

void hp_update(Soul* soul, OamState* oam, Digit *digit){
    int tens;
    int units;

    units = soul->hp % 10;
    tens = soul->hp / 10;
    
    // Draw the tens, - tens for x cause i dosn't crop well the digit sprite
    oamSet(oam, 11,
           100 - tens , 192-32-16, //x, y 
           1, 5, // priority, palette
           SpriteSize_16x16,
           SpriteColorFormat_256Color,
           digit->gfx[tens],
           -1, false, false, false, false, false);

           // Draw the units, - tens for x cause i dosn't crop well the digit sprite
    oamSet(oam, 10,
           120 - units , 192-32-16, //x, y 
           1, 5, // priority, palette
           SpriteSize_16x16,
           SpriteColorFormat_256Color,
           digit->gfx[units],
           -1, false, false, false, false, false);
}