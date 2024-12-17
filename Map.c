//23050111032

#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

Map * generateMap() {
    //Random seed
    int seed;
    seed = time(NULL);

    Map * map = createMap(seed);
    for (int i = 0; i < ROOM_SIDE; i++) {
        for (int j = 0; j < ROOM_SIDE; j++) {
            map->rooms[i * ROOM_SIDE + j] = generateRoom(map->roomCount);
            map->roomCount++;
        }
    }
    for (int i = 0; i < ROOM_SIDE; i++) {
        for (int j = 0; j < ROOM_SIDE; j++) {
            connectRoom(map, map->rooms[i * ROOM_SIDE + j]);
        }
    }

    //Create player at position 0
    map->player = createPlayer(100, 100);
    map->player->currentRoom = map->rooms[0];

    printf("Map generated successfully\n");
    return map;
}

Map* createMap(int seed) {
    Map *newMap = malloc(sizeof(Map));
    if (newMap == NULL) {
        printf("Error allocating memory for Map\n");
        exit(1);
    }
    newMap->seed = seed;
    newMap->roomCount = 0;
    return newMap;
}

void destroyMap(Map *map) {
}

void addRoom(Map *map, Room *room) {
    //Add the room to the map
    room->rid = map->roomCount;
    map->rooms[map->roomCount] = room;
    map->roomCount++;
}

void removeRoom(Map *map, Room *room) {
}

Room * getRoom(Map *map, int rid) {
    if (rid < 0 || map->rooms[rid] == NULL) {
        return NULL;
    }
    return map->rooms[rid];
}

void printMap(Map *map) {
}

void expandMap(Map *map) {
}

void freeMap(Map* map) {
    if (map == NULL) return;
    if (map->rooms != NULL) {
        for (int i = 0; i < map->roomCount; i++) {
            free(getRoomType(map->rooms[i]));
            free(map->rooms[i]);
        }
    }
    if (map->player != NULL) {
        free(map->player);
    }
    free(map);

}

void saveMap(const Map *map, const char *filename) {
        FILE *file = fopen(filename, "wb"); // Open file in binary write mode
        if (!file) {
            perror("Failed to open file for saving");
            return;
        }

    // Save Player Data
    fwrite(&map->player->armor, sizeof(int), 1, file);
    fwrite(&map->player->health, sizeof(int), 1, file);
    fwrite(&map->player->strength, sizeof(int), 1, file);
    fwrite(&map->player->inventory->itemCount, sizeof(int), 1, file);
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (map->player->inventory->items[i] == NULL) {
            int flag = 0; //This is a flag to indicate rather the slot is NULL (empty) or not. To handle read/write process
            fwrite(&flag, sizeof(int), 1, file);
            continue;
        }
        int flag = 1;
        fwrite(&flag, sizeof(int), 1, file);
        fwrite(&map->player->inventory->items[i]->name, sizeof(char[ITEM_NAME_LENGTH]), 1, file);
        fwrite(&map->player->inventory->items[i]->quantity, sizeof(int), 1, file);
        fwrite(&map->player->inventory->items[i]->type, sizeof(ItemType), 1, file);
    }

    // Save Map Data
    fwrite(&map->seed, sizeof(int), 1, file);
    fwrite(&map->roomCount,sizeof(int), 1, file);

    for (int i = 0; i < ROOM_NUMBER; i++) {
        RoomType tempType = *(map->rooms[i]->type);
        fwrite(&tempType, sizeof(RoomType), 1, file);
        fwrite(&map->rooms[i]->rid, sizeof(int), 1, file);

        int flagItem = 0;
        if (map->rooms[i]->item == NULL) {
            flagItem = 0;
            fwrite(&flagItem, sizeof(int), 1, file);
        }
        else {
            flagItem = 1;
            fwrite(&flagItem, sizeof(int), 1, file);
            fwrite(&map->rooms[i]->item->name, sizeof(char[ITEM_NAME_LENGTH]), 1, file);
            fwrite(&map->rooms[i]->item->quantity, sizeof(int), 1, file);
            fwrite(&map->rooms[i]->item->type, sizeof(ItemType), 1, file);
        }

        int flagCreature = 0;
        if (map->rooms[i]->creature == NULL) {
            flagCreature = 0;
            fwrite(&flagCreature, sizeof(int), 1, file);
        }
        else {
            flagCreature = 1;
            fwrite(&flagCreature, sizeof(int), 1, file);
            fwrite(map->rooms[i]->creature->name, sizeof(char[CREATURE_NAME_LENGTH]), 1, file);
            fwrite(map->rooms[i]->creature->armor, sizeof(int), 1, file);
            fwrite(map->rooms[i]->creature->health, sizeof(int), 1, file);
            fwrite(map->rooms[i]->creature->strength, sizeof(int), 1, file);
            fwrite(&map->rooms[i]->creature->inventory->itemCount, sizeof(int), 1, file);
            for (int j = 0; j < MAX_ITEMS; j++) {
                if (map->rooms[i]->creature->inventory->items[j] == NULL) {
                    int flag = 0; //This is a flag to indicate rather the slot is NULL (empty) or not. To handle read/write process
                    fwrite(&flag, sizeof(int), 1, file);
                    continue;
                }
                int flag = 1;
                fwrite(&flag, sizeof(int), 1, file);
                fwrite(&map->rooms[i]->creature->inventory->items[j]->name, sizeof(char[ITEM_NAME_LENGTH]), 1, file);
                fwrite(&map->rooms[i]->creature->inventory->items[j]->quantity, sizeof(int), 1, file);
                fwrite(&map->rooms[i]->creature->inventory->items[j]->type, sizeof(ItemType), 1, file);
            }
        }
    }

    fwrite(&map->player->currentRoom->rid, sizeof(int), 1, file);  // Current room id, will be read, and assigned on load

    fclose(file);
    printf("Saved successfully (%s)\n", filename);
}

Map* loadMap(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for saving");
        return NULL;
    }

    Map* loadMap = malloc(sizeof(Map));
    loadMap->player = createPlayer(100,100);
    loadMap->player->currentItem = NULL;

    //Load player
    fread(&loadMap->player->armor, sizeof(int), 1, file);
    fread(&loadMap->player->health, sizeof(int), 1, file);
    fread(&loadMap->player->strength, sizeof(int), 1, file);
    fread(&loadMap->player->inventory->itemCount, sizeof(int), 1, file);
    for (int i = 0 ; i < MAX_ITEMS; i++) {
        int flag = 0;
        fread(&flag, sizeof(int), 1, file);
        if (flag == 0) {
            loadMap->player->inventory->items[i] = NULL;
        }
        else if (flag == 1) {
            Item* loadItem = createItem("NULL", 0, 0);
            loadMap->player->inventory->items[i] = loadItem;
            fread(&loadMap->player->inventory->items[i]->name, sizeof(char[ITEM_NAME_LENGTH]), 1, file);
            fread(&loadMap->player->inventory->items[i]->quantity, sizeof(int), 1, file);
            fread(&loadMap->player->inventory->items[i]->type, sizeof(ItemType), 1, file);
        }
    }

    //Load Map
    fread(&loadMap->seed, sizeof(int), 1, file);
    fread(&loadMap->roomCount,sizeof(int), 1, file);
    for (int i = 0; i < ROOM_NUMBER; i++) {
        Room* loadRoom = createRoom(0);
        loadMap->rooms[i] = loadRoom;
        RoomType tempType = 0;
        fread(&tempType, sizeof(RoomType), 1, file);
        RoomType* typePtr = (RoomType*)malloc(sizeof(RoomType));
        *typePtr = tempType;
        loadMap->rooms[i]->type = typePtr;
        fread(&loadMap->rooms[i]->rid, sizeof(int), 1, file);
        int flagItem = 0;
        fread(&flagItem, sizeof(int), 1, file);
        if (flagItem == 1) {
            Item* loadItem = createItem("NULL", 0, 0);
            loadMap->rooms[i]->item = loadItem;
            fread(&loadMap->rooms[i]->item->name, sizeof(char[ITEM_NAME_LENGTH]), 1, file);
            fread(&loadMap->rooms[i]->item->quantity, sizeof(int), 1, file);
            fread(&loadMap->rooms[i]->item->type, sizeof(ItemType), 1, file);
        }
        else if (flagItem == 0) {
            Item* loadItem = NULL;
        }

        int flagCreature = 0;
        fread(&flagCreature, sizeof(int), 1, file);
        if (flagCreature == 1) {
            int* cHealth = (int*) malloc(sizeof(int));
            int* cStrength = (int *)malloc(sizeof(int));
            int* cArmor = (int *)malloc(sizeof(int));
            *cHealth = 1;
            *cStrength = 1;
            *cArmor = 1;
            Creature * loadCreature = createCreature("NULL", cHealth, cArmor, cStrength);
            loadMap->rooms[i]->creature = NULL;
            loadMap->rooms[i]->creature = loadCreature;
            fread(loadMap->rooms[i]->creature->name, sizeof(char[CREATURE_NAME_LENGTH]), 1, file);
            fread(loadMap->rooms[i]->creature->armor, sizeof(int), 1, file);
            fread(loadMap->rooms[i]->creature->health, sizeof(int), 1, file);
            fread(loadMap->rooms[i]->creature->strength, sizeof(int), 1, file);
            fread(&loadMap->rooms[i]->creature->inventory->itemCount, sizeof(int), 1, file);

            for (int j = 0; j < MAX_ITEMS; j++) {
                int flag = 0;
                fread(&flag, sizeof(int), 1, file);
                if (flag == 1) {
                    Item* loadItem = createItem("NULL", 0, 0);
                    loadMap->rooms[i]->creature->inventory->items[j] = loadItem;
                    fread(&loadMap->rooms[i]->creature->inventory->items[j]->name, sizeof(char[ITEM_NAME_LENGTH]), 1, file);
                    fread(&loadMap->rooms[i]->creature->inventory->items[j]->quantity, sizeof(int), 1, file);
                    fread(&loadMap->rooms[i]->creature->inventory->items[j]->type, sizeof(ItemType), 1, file);

                }
                else if (flag == 0) {
                    loadMap->rooms[i]->creature->inventory->items[j] = NULL;
                }
            }

        }
        else if (flagCreature == 0) {
            loadMap->rooms[i]->creature = NULL;
        }
    }

    int currentRoomID = -1;
    fread(&currentRoomID, sizeof(int), 1, file);
    loadMap->player->currentRoom = loadMap->rooms[currentRoomID]; //Put player in last position

    for (int i = 0; i < ROOM_SIDE; i++) { //Connect all rooms
        for (int j = 0; j < ROOM_SIDE; j++) {
            connectRoom(loadMap, loadMap->rooms[i * ROOM_SIDE + j]);
        }
    }

    fclose(file);
    printf("Load successful (%s)\n", filename);
    return loadMap;
}
