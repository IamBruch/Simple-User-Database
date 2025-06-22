# simpleDatabase 

# Simple User Database

## Slovensky

Jednoduchý konzolový program v C++, ktorý umožňuje správu používateľov – pridávať, upravovať, vyhľadávať, mazať a zobrazovať všetkých používateľov v databáze uložených v súbore `users.txt`. Dáta sú spravované v triedach `User` a `Database`, ovláda sa prostredníctvom menu v termináli.

### Funkcionalita:
- Pridanie používateľa (login, heslo, poznámka, kľúč)
- Vyhľadanie používateľa podľa kľúča
- Úprava poznámky používateľa
- Vymazanie používateľa
- Zobrazenie všetkých používateľov
- Vymazanie celej databázy

### Ako spustiť:
1. Vyžaduje CMake a C++20 kompilátor (napr. g++).
2. Skopíruj projekt (alebo stiahni ZIP).
3. V adresári `code` spusti:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ./simpleDatabase
   ```
4. Vytvorí sa súbor `users.txt`, kde sú dáta uložené.

### Súbory:
- `main.cpp` – hlavný vstup programu a cyklus menu
- `classes.h/.cpp` – triedy pre používateľa, databázu a rozhranie
- `users.txt` – súbor s uloženými používateľmi

---

## English

Simple C++ console application for managing a user database – add, edit, search, delete, and list users stored in `users.txt`. Data is handled with `User` and `Database` classes, and menu navigation is via terminal.

### Features:
- Add user (login, password, note, key)
- Search for user by key
- Edit user note
- Delete user
- List all users
- Clear database

### How to build & run:
1. Requires CMake and C++20 compiler (e.g., g++).
2. Clone the repo or download zip.
3. In the `code` directory, run:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ./simpleDatabase
   ```
4. Users are stored in `users.txt` file.

### Files:
- `main.cpp` – entry point, menu loop
- `classes.h/.cpp` – user/database/interface classes
- `users.txt` – storage for users

---

Projekt je vhodný ako ukážka práce s triedami, súbormi a jednoduchým UI v C++.
