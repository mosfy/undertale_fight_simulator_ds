#ifndef UNDERTALE_FIGHT_SIMULATOR
#define UNDERTALE_FIGHT_SIMULATOR

#include <nds.h>
#include "soul_sprite.h"
#include "toriel_bin.h"
#include "background.h"
#include "bouton/act_o.h"
#include "bouton/act_y.h"
#include "bouton/fight_o.h"
#include "bouton/fight_y.h"
#include "bouton/item_o.h"
#include "bouton/item_y.h"
#include "bouton/mercy_o.h"
#include "bouton/mercy_y.h"
#include "ui/digit_0.h"
#include "ui/digit_1.h"
#include "ui/digit_2.h"
#include "ui/digit_3.h"
#include "ui/digit_4.h"
#include "ui/digit_5.h"
#include "ui/digit_6.h"
#include "ui/digit_7.h"
#include "ui/digit_8.h"
#include "ui/digit_9.h"
#include "characters/toriel/toriel0.h"
#include "characters/toriel/toriel1.h"
#include "characters/toriel/toriel2.h"
#include "characters/toriel/toriel3.h"

typedef struct {
	int x, y; // x/y location
    int hp;
	u16* gfx; // oam GFX
} Soul;

typedef struct {
    int number;
	u16* gfx[10]; // oam GFX
} Digit;

typedef struct {
    int x, y;
    u16 *gfx;
} Bouton;

enum Song {
    TORIEL = 0
};

typedef struct
{
    int x;
    int y;

    u16 *gfx[4];

} Toriel;

void toriel_init(Toriel *toriel);

void toriel_update(Toriel *toriel);

// Initialize the soul sprite
void soul_init(Soul* soul, OamState* oam, int max_hp);

// Update soul position and render
void soul_update(Soul* soul, OamState* oam);

// Initialize the top screen buttons
void bouton_init(Bouton bouton[], OamState* oam);

// Render the top screen buttons
void bouton_update(Bouton bouton[]);



void hp_update(Soul* soul, OamState* oam, Digit *digit);

// Initialize the hp on the top screen
void hp_init(Soul* soul, OamState* oam, Digit *digit);

// Play music of the selected boss
void play_music(enum Song song);




#endif