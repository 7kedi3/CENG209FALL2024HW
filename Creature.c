//23050111032

#include <stdio.h>
#include <stdlib.h>
#include "Creature.h"

Creature * generateCreature() {
    char name[30];
    int * health = (int *)malloc(sizeof(int));
    int * armor = (int *)malloc(sizeof(int));
    int * strength = (int *)malloc(sizeof(int));

    snprintf(name, sizeof(name),"SCP-%3d", rand() % 1000);
    *health = rand() % 175+1;
    *armor = rand() % 50+1;
    *strength = rand() % 75+1;
    Creature * creature = createCreature(name, health, armor, strength);
    for (int i = rand() % MAX_ITEMS; i < MAX_ITEMS; i++) {// Fill creature's inventory
        addItem(creature->inventory, generateItem());
    }
    return creature;
}

Creature * createCreature(const char* name, int* health, int* armor, int* strength) {
    Creature * creature = (Creature *) malloc(sizeof(Creature));
    strcpy(creature->name, name);
    creature->health = health;
    creature->armor = armor;
    creature->strength = strength;
    creature->inventory = createInventory();
    return creature;
}

void displayCreature(Creature *creature) {
if (creature == NULL) {
    printf("Something went wrong.\n");
    return;
}
    printf("[%s]\n Health: %d   Armor: %d   Strength: %d",creature->name,*creature->health,*creature->armor,*creature->strength);

}


void lookCreature(const Creature *creature) {
    //If defeated
    if (*creature->health <= 0) {
        if (creature->inventory->itemCount > 0) {
            printf("Inventory:\n");
            for (int i = 0; i < creature->inventory->itemCount; i++) {
                if (creature->inventory->items[i] == NULL) continue;
                printf("%d. %s\n", i, creature->inventory->items[i]->name);
            }
        }
    }
    //If not defeated
    else{
        printf("Not a good idea to reach the creature right now\n");
    }
}

void lootCreature(const Creature *creature, const int index, const Player *player) {
    if (*creature->health <= 0 && creature->inventory->items[index] != NULL) {
        if (player->inventory->itemCount == 8) {
            printf("Your inventory is full.\n");
            return;
        }
        addItem(player->inventory, creature->inventory->items[index]);
        creature->inventory->items[index] = NULL;
    }
    else printf("You can't do that.\n");
}

void attackCreature(const Creature *creature, Player* player, const Item *item) {
    if (item == NULL) {
        printf("Your hands done no damage on the creature, equip a weapon!\n");
        player->health -= *creature->strength / player->armor + 1; //Creature punishes for this action
        printf("Creature dealt (-%d) damage\n",*creature->strength / player->armor + 1);
        return;
    }

    if (item->type == WEAPON) {

        if (*creature->health <= 0) {
            printf("The creature is a lost soul. You can loot its corpse or leave.\n");
        }

        bool hasAmmo = false;
        for (int i = 0; i < MAX_ITEMS; i++) {
            if (player->inventory->items[i] != NULL && player->inventory->items[i]->type == AMMO) {
                hasAmmo = true;
                if (player->inventory->items[i]->quantity > 0)
                    player->inventory->items[i]->quantity--;
                else {
                    //Out of ammo for this slot
                    player->inventory->items[i] == NULL;
                    player->inventory->itemCount--;
                }
                break;
            }
        }
        if (hasAmmo) {
            *creature->health = __max(*creature->health - ((item->quantity * player->strength / *creature->armor) + 1), 0);
            printf("You dealt (-%d) damage.\n",(item->quantity * player->strength / *creature->armor) + 1);
            if (*creature->health > 0) { //Creature is now fighting back.
                player->health -= *creature->strength / player->armor + 1;
                printf("Creature dealt (-%d) damage.\n",*creature->strength / player->armor + 1);
            }
            else printf("Creature has been defeated.\n");
        }
        else printf("You don't have ammo.\n");

    }
    else printf("You can't use this item on this creature.\n");
}

void freeCreature(Creature *creature) {
    free(creature->inventory);
    free(creature->armor);
    free(creature->strength);
    free(creature->health);
    free(creature);
}
