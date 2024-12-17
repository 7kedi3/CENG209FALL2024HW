//23050111032

#include <stdio.h>
#include <stdlib.h>
#include "Room.h"

#include <signal.h>
#include <string.h>

Room * generateRoom(const int rid) {
        RoomType* roomType = (RoomType*)malloc(sizeof(RoomType));
        *roomType = (RoomType)(rand() % ROOM_TYPE_COUNT);
        const int creatureChance = rand() % 100;
        const int itemChance = rand() % 100;
        Room * room = (Room*)malloc(sizeof(Room));
        switch (*roomType) {
                case ARMORY:
                        room = createRoom(roomType);
                        if (creatureChance < 12) room->creature = generateCreature();
                        room->item = createItem("One rusty steel marble", 1, AMMO); // Guaranteed ammo
                        break;
                case LOOT:
                        room = createRoom(roomType);
                        if (creatureChance < 6) room->creature = generateCreature();
                        room->item = generateItem();
                        break;
                case HALL:
                        room = createRoom(roomType);
                        if (creatureChance < 62) room->creature = generateCreature();
                        if (itemChance < 5) room->item = generateItem();
                        break;
                case TESLA:
                        room = createRoom(roomType);
                        if (creatureChance < 82) room->creature = generateCreature();
                        break;
                case AIRLOCK:
                        room = createRoom(roomType); // Guaranteed to have a creature
                        room->creature = generateCreature();
                        break;
                case WARHEAD:
                        room = createRoom(roomType);
                        break;
                case SHOP:
                        room = createRoom(roomType);
                        if (itemChance < 80) room->item = generateItem();
                        break;
                case GENERIC:
                        room = createRoom(roomType);
                        if (creatureChance < 20) room->creature = generateCreature();
                        if (itemChance < 40) room->item = generateItem();
                        break;

        }
        room->rid = rid; //Assign rid
        return room;
}

Room* createRoom(RoomType *type) {
        Room *newRoom = (Room *)malloc(sizeof(Room));
        if (newRoom == NULL) {
                printf("Failed to allocate room structure\n");
                exit(1);
        }
        // Initial values
        newRoom->east = NULL;
        newRoom->west = NULL;
        newRoom->south = NULL;
        newRoom->north = NULL;
        newRoom->creature = NULL; //DEV NOTE: Creature ve Item'ı generateRoomdan buraya taşıyıp direkt NULL olarak atanınca, sıkıntı çözüldü.
        newRoom->item = NULL; //DEV NOTE: NULL atanmadığında takdirde build rastgele bir değer atıyor ve crashe sebep oluyor.
        newRoom->rid = -1;
        //Room type for unique interactions
        newRoom->type = type;
        return newRoom;

}

void connectRoom(const Map *map, Room *room) {
        //North
        if (room->rid + ROOM_SIDE < ROOM_NUMBER-1) {
                room->north = map->rooms[room->rid + ROOM_SIDE];
        }
        //South
        if (room->rid - ROOM_SIDE >= 0) {
                room->south = map->rooms[room->rid - ROOM_SIDE];
        }
        //East
        if ((room->rid)% ROOM_SIDE < ROOM_SIDE) {
                room->east = map->rooms[room->rid + 1];
        }
        //West
        if ((room->rid)% ROOM_SIDE > 0) {
                room->west = map->rooms[room->rid - 1];
        }

}

RoomType* getRoomType(Room* room) {
        return room->type;
}


void displayRoom(const Room *room) {
        //printf("Rid: %d\n", room->rid);
        switch (*room->type) {
                case ARMORY:
                        printf( "A rusty armory. You can smell dense gunpowder.\n");
                        break;
                case LOOT:
                        printf( "Seems like a special place, you can see useful stuff around.\n");
                        break;
                case HALL:
                        printf( "A long hallway, makes you wonder how massive of a labyrinth you are inside.\n");
                        break;
                case TESLA:
                        printf( "Strange hallway with bunch of coils planted. Coils flash short period sparks.\n");
                        break;
                case AIRLOCK:
                        printf( "This claustrophobic room makes you feel overwhelmed.\n");
                        break;
                case WARHEAD:
                        printf( "Extremely solid and protected room with a glowing keycard scanner present in the middle.\n");
                        break;
                case SHOP:
                        printf( "Looks like a cafeteria. There is a automat by the wall that seems to give items.\n");
                        break;
                case GENERIC:
                        printf( "Normal room, similar to other ones you've seen all the way.\n");
                        break;
                default:
                        printf( "Nothing interesting.\n");
        }
        if (room->creature != NULL) {
                if (*room->creature->health > 0) {
                        printf("There is a creature staring at you.\n");
                }
                else printf("A soulless body laying down in the middle.\n");
        }
        if (room->item != NULL) {
                printf("You spot something that might be useful for you.\n");
        }
}

void interactRoom(Room *room) {
}
