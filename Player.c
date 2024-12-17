//23050111032
#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "Room.h"
#include <math.h>


Player * createPlayer(int maxHealth, int maxArmor) {
    Player *player = (Player *)malloc(sizeof(Player));
    player->health = maxHealth;
    player->maxHealth = maxHealth;
    player->armor = 1;
    player->maxArmor = maxArmor;
    player->strength = 5;
    player->inventory = createInventory();
    player->currentItem;
    return player;
}



void movePlayer(Player *player, const char* direction) {
    if (strcmp(direction, "north") == 0 || strcmp(direction, "n") == 0) {
        if (player->currentRoom->north != NULL) {
            player->currentRoom = player->currentRoom->north;
            printf("You have moved north.\n");
        }
        else printf("You can't go there.\n");
    }
    else if (strcmp(direction, "south") == 0 || strcmp(direction, "s") == 0) {
        if (player->currentRoom->south != NULL) {
            player->currentRoom = player->currentRoom->south;
            printf("You have moved south.\n");
        }
        else printf("You can't go there.\n");
    }
    else if (strcmp(direction, "east") == 0 || strcmp(direction, "e") == 0) {
        if (player->currentRoom->east != NULL) {
            player->currentRoom = player->currentRoom->east;
            printf("You have moved east.\n");
        }
        else printf("You can't go there.\n");
    }
    else if (strcmp(direction, "west") == 0 || strcmp(direction, "w") == 0) {
        if (player->currentRoom->west != NULL) {
            player->currentRoom = player->currentRoom->west;

            printf("You have moved west.\n");
        }
        else printf("You can't go there.\n");
    }
    else
    printf("Invalid direction!\n");

}

void useItem(Player *player, const int index) {
    if (index < MAX_ITEMS && index >= 0) {
        if (player->inventory->items[index] == NULL) {
            printf("No item in this slot.\n");
            return;
        }
        if (player->inventory->items[index]->type == WEAPON) { // EQUIPS WEAPON
            player->currentItem = player->inventory->items[index];
            printf("You have equipped: %s\n", player->inventory->items[index]->name);
        }
        else if (player->inventory->items[index]->type == ARMOR) {
            player->armor = __min(player->armor + player->inventory->items[index]->quantity , player->maxArmor); // Max armor
            printf("You wore the armor. (+%d)\n", player->inventory->items[index]->quantity);
            player->inventory->items[index] = NULL;
            player->inventory->itemCount--;
        }
        else if (player->inventory->items[index]->type == HEALTH) {
            player->health = __min(player->health + player->inventory->items[index]->quantity , player->maxHealth); // Max health
            printf("You healed. (+%d)\n", player->inventory->items[index]->quantity);
            player->inventory->items[index] = NULL;
            player->inventory->itemCount--;
        }
        else if (player->inventory->items[index]->type == STRENGTH) {
            player->strength += player->inventory->items[index]->quantity; // No limit for strength, get buff.
            printf("You used the strength potion. (+%d)\n", player->inventory->items[index]->quantity);
            player->inventory->items[index] = NULL;
            player->inventory->itemCount--;
        }
        else if (player->inventory->items[index]->type == KEYCARD) {
            if (*player->currentRoom->type != WARHEAD) {
                printf("Nothing present to use the keycard on.\n");
            }
            else if (player->inventory->items[index]->quantity < 4) {
                printf("Access tier doesn't meet the requirement for this scanner.");
            }
            else { // Player uses the keycard and detonates the facility. Kind of like a neutral ending where all creatures die, along with the player.
                printf("\nYou slowly take steps towards the keycard scanner. Your journey flashes in your mind, but you remember... \nAll the things will come to an end.\nYou have detonated the warhead. The whole facility; including all creatures, structures and YOU have vaporized.\n");
                player->health = 0;
            }
        }
        else if (player->inventory->items[index]->type == AMMO) printf("Ammo is automatically used with your weapon!\n");

    else printf("Not a valid item type.\n");
    }

}

void pickUpItem(const Player *player) {
    if (player->currentRoom->item == NULL) {
        printf("There is nothing present to pick up.");
        return;
    }
    else if (player->inventory->itemCount >= MAX_ITEMS) {
        printf("You can't hold any more items!");
        return;
    }
    else {
        addItem(player->inventory, player->currentRoom->item);
        printf("You have picked up the item: %s\n", player->currentRoom->item->name);
        player->currentRoom->item = NULL;

    }

}

void displayPlayer(const Player *player) {
    printf("[Player]\nHealth: %d/%d   Armor: %d/%d   Strength: %d   Current Weapon: %s\n", player->health, player->maxHealth, player->armor,player->maxArmor, player->strength, (player->currentItem == NULL ? "Unarmed" : player->currentItem->name));
}


