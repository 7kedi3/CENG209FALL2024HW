//23050111032
#include <stdio.h>
#include <stdlib.h>
#include "Map.c"
#include "Inventory.c"
#include "Item.c"
#include "Player.c"
#include "Creature.c"
#include "Room.c"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//TODO: Better index
//TODO: Seed



int main(void) {


    char command[32];
    int index;
    Map* site02;

    //Main menu
    while (1) {
        printf("Welcome to SITE-02. The site has experienced multiple keter and euclid level containment breaches.\n You are stuck in the facility, seeking a way out of this massive labyrinth. If there is so...\n\n"
           " 1. New Game\n 2. Load Game\n9. Exit Game\n\nPlease select action: ");
        scanf("%s", command);
        if (strcmp(command, "9") == 0 || strcmp(command, "quit") == 0) {
            printf("Exiting the game. Goodbye!\n");
            exit(0);
        }
        else if (strcmp(command, "1") == 0 || strcmp(command, "new") == 0 || strcmp(command, "n") == 0) {
            site02 = generateMap();
            addItem(site02->player->inventory, createItem("COM-03",3,WEAPON));
            clearScreen();
            break;
        }
        else if (strcmp(command, "2") == 0 || strcmp(command, "load") == 0 || strcmp(command, "l") == 0) {
            printf("File path: ");
            scanf("%s", command);
            site02 = loadMap(command);
            if (site02 == NULL) {
                printf("Save file does not exist.\n");
                continue;
            }
            break;
        }
        else {
            clearScreen();
            printf("Invalid command. Please try again.\n");
        }
    }

    //Where the game runs
    while (1) {
        // Display player status and current room
        printf("\n");

        if (site02->player->health <= 0) {
            printf("GAME OVER\n");
            scanf("%s", command);
            freeMap(site02);
            break;
        }

        displayPlayer(site02->player);



        printf("\n1. Move\n2. Look\n3. Inventory\n4. Pickup\n5. Engage\n\n8. Save Game\n9. Quit\nSelect action: ");
        scanf("%s", command);
        if (strcmp(command, "9") == 0 || strcmp(command, "quit") == 0) {
            printf("Exiting the game. Goodbye!\n");
            freeMap(site02);
            break;
        }
        if (strcmp(command, "8") == 0 || strcmp(command, "save") == 0) {
            printf("Select path: ");
            scanf("%s", command);
            saveMap(site02, command);
            continue;
        }
        if (strcmp(command, "1") == 0 || strcmp(command, "move") == 0) {
            clearScreen();
            printf("north, south, east, west\nDirection:");
            scanf("%s", command);
            // Move player based on command
            clearScreen();
            movePlayer(site02->player, command);
        }
        if (strcmp(command, "2") == 0 || strcmp(command, "look") == 0) {
            clearScreen();
            displayRoom(site02->player->currentRoom);
        }
        if (strcmp(command, "3") == 0 || strcmp(command, "inventory") == 0) {
            clearScreen();
            inventoryDisplay(site02->player->inventory);
            printf("\n1. Use\n2. Remove\n0. Back\n");
            scanf("%s", command);
            if (strcmp(command, "1") == 0 || strcmp(command, "use") == 0) {
                if (scanf("%d", &index) != 1) { // Read integer input and validate
                    printf("Invalid input.\n");
                    continue;
                }
                clearScreen();
                useItem(site02->player, index);
            }
                if (strcmp(command, "2") == 0 || strcmp(command, "remove") == 0) {
                    if (scanf("%d", &index) != 1) { // Read integer input and validate
                        printf("Invalid input.\n");
                        continue;
                    }
                    clearScreen();
                    removeItem(site02->player, index);
                }
                if (strcmp(command, "0") == 0 || strcmp(command, "back") == 0) {
                    clearScreen();
                    continue;
                }
        }
        if (strcmp(command, "4") == 0 || strcmp(command, "pickup") == 0) {
            clearScreen();
            pickUpItem(site02->player);
        }
        if (strcmp(command, "5") == 0 || strcmp(command, "engage") == 0) {
            clearScreen();
            if (site02->player->currentRoom->creature == NULL) {
                printf("There is nobody present in this room.");
            }
            else {
                while (site02->player->currentRoom->creature != NULL && site02->player->health > 0) {
                    displayPlayer(site02->player);
                    printf("\n");
                    displayCreature(site02->player->currentRoom->creature);
                    printf("\n");
                    printf("\n1. Attack\n2. Inventory\n3. Loot\n4. Search\n\n0. %s\n\nSelect action: ", (*site02->player->currentRoom->creature->health <= 0 ? "Leave" : "Bail"));
                    scanf("%s", command);
                    clearScreen();
                    if (strcmp(command, "1") == 0 || strcmp(command, "attack") == 0) {
                        clearScreen();
                        attackCreature(site02->player->currentRoom->creature, site02->player, site02->player->currentItem);
                    }
                    if (strcmp(command, "2") == 0 || strcmp(command, "inventory") == 0) {
                        clearScreen();
                        inventoryDisplay(site02->player->inventory);
                        printf("\n1. Use\n2. Remove\n0. Back\n");
                        scanf("%s", command);
                        if (strcmp(command, "1") == 0 || strcmp(command, "use") == 0) {
                            if (scanf("%d", &index) != 1) { // Read integer input and validate
                                printf("Invalid input.\n");
                                continue;
                            }
                            clearScreen();
                            useItem(site02->player, index);
                        }
                            if (strcmp(command, "2") == 0 || strcmp(command, "remove") == 0) {
                                if (scanf("%d", &index) != 1) { // Read integer input and validate
                                    printf("Invalid input.\n");
                                    continue;
                                }
                                clearScreen();
                                removeItem(site02->player, index);
                            }
                            if (strcmp(command, "0") == 0 || strcmp(command, "back") == 0) {
                                clearScreen();
                                continue;
                            }
                    }
                    if (strcmp(command, "3") == 0 || strcmp(command, "loot") == 0) {
                        if (scanf("%d", &index) != 1) { // Read integer input and validate
                            printf("Invalid input.\n");
                            continue;
                        }
                        clearScreen();
                        lootCreature(site02->player->currentRoom->creature, index, site02->player);
                    }
                    if (strcmp(command, "4") == 0 || strcmp(command, "search") == 0) {
                        clearScreen();
                        lookCreature(site02->player->currentRoom->creature);
                    }
                    if (strcmp(command, "0") == 0 || strcmp(command, "bail") == 0 || strcmp(command, "leave") == 0) {
                        clearScreen();
                        printf("You left the creature.\n");
                        break;
                    }
                }
            }
        }


    }


}

