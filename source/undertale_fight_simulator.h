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
#include "projectiles/fire_02.h"
#include "projectiles/fire_01.h"

typedef struct {
	int x, y; // x/y location
    int hp;
    int invecibel;
    int should_render;
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

typedef enum {
    GAME_TURN_ENEMY = 0,
    GAME_TURN_PLAYER = 1
} GameTurn;

typedef enum {
    ATTACK_PROJECTILE = 0
} EnemyAttack;

typedef struct {
    GameTurn turn;
    EnemyAttack current_attack;
    int turn_timer;
    int current_action; //-1 None, 0 fight, 1 act, 2 item, 3 mercy
} GameManager;

enum Song {
    TORIEL = 0
};

typedef struct
{
    int x;
    int y;

    u16 *gfx[4];

} Toriel;

#define PROJECTILE_MAX 100

typedef struct {
    int x, y;   // position
    int vx, vy; // speed (pixels per frame)
    bool active;
} Projectile;

typedef struct {
    Projectile list[PROJECTILE_MAX];
    u16 *gfx; // shared gfx, same texture/palette for every projectile
} ProjectileSystem;

void toriel_init(Toriel *toriel);

void toriel_update(Toriel *toriel);

void projectile_init(ProjectileSystem* system, OamState* oam);

void projectile_update(ProjectileSystem* system, OamState* oam, Soul* soul, GameManager* manager, int frame);

// Spawn a projectile in the first free slot of the pool (used by attack patterns)
void projectile_spawn(ProjectileSystem* system, int x, int y, int vx, int vy);

// Initialize the soul sprite
void soul_init(Soul* soul, OamState* oam, int max_hp);

// Update soul position and render
void soul_update(Soul* soul, OamState* oam, GameManager* manager, int keys);

// Initialize the top screen buttons
void bouton_init(Bouton bouton[], OamState* oam);

// Render the top screen buttons
void bouton_update(Bouton bouton[], GameManager* manager);



void hp_update(Soul* soul, OamState* oam, Digit *digit);

// Initialize the hp on the top screen
void hp_init(Soul* soul, OamState* oam, Digit *digit);

void game_manager_init(GameManager* manager);
void game_manager_update(GameManager* manager, int keys);

// Play music of the selected boss
void play_music(enum Song song);




#endif