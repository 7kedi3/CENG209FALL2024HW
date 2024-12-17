//23050111032

#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"

#define MAX_ITEMS 8

struct Player;

typedef struct Inventory{
    int itemCount;
    Item* items[MAX_ITEMS];



} Inventory;

Inventory* createInventory();
void inventoryDisplay(const Inventory* inventory);
void addItem(Inventory* inventory, Item* item);
void removeItem(struct Player* player, int index);


#endif //INVENTORY_H
