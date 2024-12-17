# SITE-02 ADVENTURE GAME

## CENG209 FALL 2024 Homework
**Date:** 12/17/2024

---

### Game Overview
SITE-02 is a 16x16 facility with rooms, each containing random encounters like creatures and loot. The game is inspired by one of the favorite games, Secret Laboratory, featuring a variety of creatures, weapons, and a rich adventure theme.

### Core Mechanics & Gameplay
- **Starting Point:** The player begins in the first room with a pistol (COM-03) in the inventory.
- **Room Types:** Rooms are categorized into types such as armory, tesla, airlock, etc. Each type has a different chance of including items or creatures:
  - **Armory:** Guaranteed to contain ammo.
  - **Tesla:** Higher chance of having a creature.
  - **Airlock** Guaranteed to have creature.
  - **Shop** Higher chance of having loot.
  - **Warhead** Game can be ended with Keycard-4 or Keycard-5.
  - **Hall** and **Generic** normal rooms.
- **Inventory Management:** The player can manage their inventory, loot items from the current room, or loot a defeated creature's body.
- **Engaging Creatures:** When encountering a creature:
  - A turn-based battle begins with the player always going first.
  - The player must be equipped with a weapon to deal damage.
  - Armor can be worn to reduce damage taken.
  - Potions can be used to increase the player's strength and damage.
  - The goal is to damage and reduce the creature’s health to zero.
- **Looting:** After defeating a creature, the player can loot its body. If there is loot present in the room, it can be picked up as well.
- **Item Quantities:** All items have quantities that represent different attributes:
  - Weapons have damage quantities (e.g., Weapon-20 deals 20 damage).
  - Ammo is needed to use weapons.
  - Health have healing quantitites (e.g., Medkit-20 heals by 20.)
  - Armor have damage reductant quantities
  - Keycard is a special game item that can be used to lead to neutral ending.
  - Potion have strength quantities (e.g., Potion-10 makes player stronger by 10.)
- **Game End Conditions:** The game ends if the player is defeated or if they activate the warhead.
  - **Warhead Room:** Can be interacted with if the player possesses a keycard with access level greater than 3 (quantity > 3).
  - Activating the warhead vaporizes the facility, including the player and all creatures within. Which is neutral ending.

### Saving & Loading Progress
- **Save Progress:** Current game progress can be saved when starting a new game. This includes the facility's room stats, creature stats if present, player stats, and inventory items.
  - *save savefile.dat*
- **Load Save:** A saved game can be loaded from the main menu by specifying the save file path.
  - *load savefile.dat*

---

## Credits
- **Developer:** Fatih Erdoğdu
- **Course:** CENG209 - Fall 2024

---

## Instructions
**Compile and Run:**
   Compile the files using CMake, CMakeList is included in the source files.
