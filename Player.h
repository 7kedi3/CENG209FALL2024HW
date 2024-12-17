//23050111032
#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Inventory.h"

struct Room;

typedef struct Player{
    int health;
    int maxHealth;
    int armor;
    int maxArmor;
    int strength;
    Inventory* inventory;
    Item* currentItem;
    struct Room* currentRoom;
} Player;


Player* createPlayer(int maxHealth, int maxArmor);
void useItem(Player* player, int index);
void pickUpItem(const Player* player);
void movePlayer(Player* player, const char* direction);
void displayPlayer(const Player* player);




#endif //PLAYER_H
