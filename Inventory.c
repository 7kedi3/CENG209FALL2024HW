//23050111032
#include <stdio.h>
#include <stdlib.h>
#include "Inventory.h"

Inventory * createInventory() {
    Inventory * inventory = (Inventory *)malloc(sizeof(Inventory));
    for (int i = 0; i < MAX_ITEMS; i++) {
        inventory->items[i] = NULL;
    }
    inventory->itemCount = 0;
    return inventory;
}

void inventoryDisplay(const Inventory* inventory) {
    if (inventory == NULL) {
        printf("Error allocating memory for Inventory\n");
        return;
    }
    if (inventory->itemCount == 0) {
        printf("Your inventory is empty.\n");
        return;
    }
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (inventory->items[i] != NULL && inventory->items[i]->name != NULL) {
            printf("%d: %s\n", i, inventory->items[i]->name);
        }
    }
}

void addItem(Inventory *inventory, Item* item) {
    if (inventory->itemCount == 8) {
        printf("Inventory is full.\n");
        return;
    }
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (inventory->items[i] == NULL) {
            inventory->items[i] = item;
            break;
        }
    }
    inventory->itemCount++;
}

void removeItem(Player* player, const int index) {
    if (index < 0 || index >= MAX_ITEMS) {
        printf("Index out of bounds\n");
    }
    else {
        printf("Removed item: %s\n", player->inventory->items[index]->name);
        if (player->currentItem == player->inventory->items[index]) { //If the removed item is in use, unequips it
            player->currentItem = NULL;
        }
        free(player->inventory->items[index]);
        player->inventory->items[index] = NULL;
        player->inventory->itemCount--;
    }

}

