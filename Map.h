//23050111032

#ifndef MAP_H
#define MAP_H
#include "Room.h"
#include "Player.h"
#include <math.h>
#include <time.h>

#define ROOM_NUMBER 256 //16 x 16
#define ROOM_SIDE 16 //For simplicity in code

typedef struct Map{
    int seed;
    int roomCount;
    Room* rooms[ROOM_NUMBER];
    Player* player;




} Map;

Map* generateMap();
Map* createMap(int seed);
void destroyMap(Map* map);
void addRoom(Map* map, Room* room);
void removeRoom(Map* map, Room* room);
Room* getRoom(Map* map, int rid);
void printMap(Map* map);
void expandMap(Map* map);

void saveMap(const Map* map, const char *filename);
Map* loadMap(const char *filename);

void freeMap(Map* map);



#endif //MAP_H
