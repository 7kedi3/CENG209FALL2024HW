//23050111032

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

#include <string.h>

Item * generateItem() {

    char name[ITEM_NAME_LENGTH];
    int randomNum;
    Item * item = NULL;

    ItemType itemtype = (ItemType)(rand() % ITEM_TYPE_AMOUNT);

    switch (itemtype) {
        case WEAPON:
            randomNum = rand() % 30 + 1;
            sprintf(name, "Weapon-%d", randomNum);
            item = createItem(name, randomNum, itemtype);
            break;
        case ARMOR:
            randomNum = rand() % 10 + 1;
            sprintf(name, "Armor-%d", randomNum);
            item = createItem(name, randomNum, itemtype);
            break;
        case HEALTH:
            randomNum = rand() % 65 + 1;
            sprintf(name, "Medkit-%d", randomNum);
            item = createItem(name, randomNum, itemtype);
            break;
        case KEYCARD:
            randomNum = rand() % 5 + 1;
            sprintf(name, "Keycard-%d", randomNum);
            item = createItem(name, randomNum, itemtype);
            break;
        case STRENGTH:
            randomNum = rand() % 15 + 1;
            sprintf(name, "Potion-%d", randomNum);
            item = createItem(name, randomNum, itemtype);
            break;
        case AMMO:
            randomNum = rand() % 7 + 1;
            sprintf(name, "Ammo (%d)", randomNum);
            item = createItem(name, randomNum, itemtype);
            break;
    }
    return item;

}

Item * createItem(const char *name, int quantity, ItemType type) {
    Item * item = (Item *)malloc(sizeof(Item));
    strcpy(item->name, name);
    item->quantity = quantity;
    item->type = type;
    return item;
}

void sellItem(Item *item) {
}
