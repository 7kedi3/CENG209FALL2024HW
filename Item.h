//23050111032

#ifndef ITEM_H
#define ITEM_H

#define ITEM_NAME_LENGTH 50

typedef enum{
  WEAPON,
  AMMO,
  KEYCARD,
  HEALTH,
  ARMOR,
  STRENGTH,
   ITEM_TYPE_AMOUNT

} ItemType;

typedef struct Item{

  char name[ITEM_NAME_LENGTH];
  int quantity; //WEAPON = damage, AMMO = amount, KEYCARD = access, HEALTH = healing, ARMOR = shielding
  ItemType type;

} Item;

Item* generateItem();
Item* createItem(const char* name, int quantity, ItemType type);
void sellItem(Item* item);





#endif //ITEM_H
