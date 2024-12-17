//23050111032

#ifndef CREATURE_H
#define CREATURE_H
#include <stdbool.h>
#include "Inventory.h"
#include "Player.h"
#define CREATURE_NAME_LENGTH 30

typedef struct Creature {
    char name[CREATURE_NAME_LENGTH];
    int* health;
    int* armor;
    int* strength;
    Inventory* inventory; //After the creature is defeated, their body can be looted

} Creature;

Creature* generateCreature();
Creature* createCreature(const char* name, int* health, int* armor, int* strength);
void lookCreature(const Creature* creature);
void lootCreature(const Creature* creature, int index, const Player* player);
void attackCreature(const Creature* creature, Player* player, const Item* item);
void displayCreature(Creature* creature);
void freeCreature(Creature* creature);

#endif //CREATURE_H
