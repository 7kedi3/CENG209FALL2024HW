//23050111032

#ifndef ROOM_H
#define ROOM_H
#include <stdbool.h>

#include "Creature.h"
#define ROOM_DESC 500

struct Map;

typedef enum{
  ARMORY,
  LOOT,
  HALL,
  GENERIC,
  TESLA,
  AIRLOCK,
  WARHEAD,
  SHOP,
    ROOM_TYPE_COUNT

} RoomType;

typedef struct Room{
    RoomType* type;
    struct Room* north;
    struct Room* east;
    struct Room* south;
    struct Room* west;
    int rid; //Room id
    Creature* creature;
    Item* item;
} Room;

Room* generateRoom(int rid);
Room* createRoom(RoomType *type);
void connectRoom(const struct Map *map, Room *room);
RoomType* getRoomType(Room* room);
void displayRoom(const Room* room);
void interactRoom(Room* room);


#endif //ROOM_H
