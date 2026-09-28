#include "undertale_fight_simulator.h"

// Fight box bounds (same as the soul's boundary checks in soul.c)
#define PROJECTILE_BOX_LEFT   60
#define PROJECTILE_BOX_RIGHT  200
#define PROJECTILE_BOX_TOP    26
#define PROJECTILE_BOX_BOTTOM 167

void projectile_init(ProjectileSystem* system, OamState* oam) {
    // Every projectile shares the same tiles/palette, so we only need one gfx slot
    system->gfx = oamAllocateGfx(oam, SpriteSize_16x16, SpriteColorFormat_256Color);
    dmaCopy(fire_01Tiles, system->gfx, fire_01TilesLen);

    for (int i = 0; i < PROJECTILE_MAX; i++) {
        system->list[i].active = false;
    }
}

void projectile_spawn(ProjectileSystem* system, int x, int y, int vx, int vy) {
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (!system->list[i].active) {
            system->list[i].x = x;
            system->list[i].y = y;
            system->list[i].vx = vx;
            system->list[i].vy = vy;
            system->list[i].active = true;
            return;
        }
    }
}

void projectile_update(ProjectileSystem* system, OamState* oam, Soul* soul, GameManager* manager, int frame) {
    if (manager->turn != GAME_TURN_ENEMY) {
        for (int i = 0; i < PROJECTILE_MAX; i++) {
            Projectile* p = &system->list[i];
            p->active = false;
            oamSet(oam, 10 + i, 0, 0, 0, 1, SpriteSize_16x16, SpriteColorFormat_256Color, system->gfx, -1, false, true, false, false, false);
        }
        oamUpdate(oam);
        return;
    }

    if (manager->current_attack == ATTACK_PROJECTILE && frame % 30 == 0) {
        projectile_spawn(system, 150, 25, 3 - frame % 7, 1 - frame % 4);
    }
    
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        Projectile* p = &system->list[i];
        int oam_id = 10 + i;

        if (p->active) {
            p->x += p->vx;
            p->y += p->vy;

            if (p->x < PROJECTILE_BOX_LEFT) {
                p->vx = -p->vx;
            }
            if (p->x > PROJECTILE_BOX_RIGHT) {
                p->vx = -p->vx;
            }
            if (p->y < PROJECTILE_BOX_TOP) {
                p->y = PROJECTILE_BOX_TOP;
                p->vy = -p->vy;
            }
            if (p->y > PROJECTILE_BOX_BOTTOM) {
                p->vy = 0;
            }
            if (p->x-8 <= soul->x && p->x+8 >= soul->x && p->y-8 <= soul->y && p->y+8 >= soul->y && soul->invecibel == 0)
            {
                soul->hp -= 5;
                soul->invecibel = 60;
            } 
        }
    

        oamSet(oam, oam_id,
               p->x - 8, p->y - 8, // x, y
               0, 1, // priority, palette (fire_01, same for all projectiles)
               SpriteSize_16x16,
               SpriteColorFormat_256Color,
               system->gfx,
               -1, false, !p->active, false, false, false);
    }

    oamUpdate(oam);
}
