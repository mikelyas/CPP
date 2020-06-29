# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

CXX = g++ #compiler to use
CXXFLAGS = -w -g -std=c++14 -Wall -pedantic -pedantic-errors -Wno-long-long -O0 -ggdb

.PHONY = all clean compile run doc

LINKERFLAG = -lm

OBJECT_NAME = lyashmik

ALL_OBJECTS = src/main.o src/Game.o src/usefullFunctions.o src/Map/Map.o src/Map/Places/Place.o src/Map/Places/Village.o src/Map/Places/Arena.o src/Map/Places/Characters/Character.o src/Map/Places/Characters/GoodCharacter.o src/Map/Places/Characters/Warrior.o src/Map/Places/Characters/Hero.o src/Map/Places/Characters/Items/Item.o src/Map/Places/Characters/Items/Storage.o src/Map/Places/Characters/Items/Weapon.o src/Map/Places/Characters/Items/Armour.o src/Map/Places/Characters/Items/Healer.o

all: clean compile run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Object files
src/main.o: src/main.cpp src/Game.h
src/Game.o: src/Game.cpp src/Map/Map.h src/Map/Places/Characters/Hero.h

src/usefullFunctions.o: src/usefullFunctions.cpp

src/Map/Map.o: src/Map/Map.cpp src/usefullFunctions.h src/Constants.h src/Map/Places/Place.h src/Map/Places/Village.h src/Map/Places/Arena.h

src/Map/Places/Place.o: src/Map/Places/Place.cpp src/usefullFunctions.h src/Constants.h src/Map/Places/Characters/Character.h src/Map/Places/Characters/GoodCharacter.h src/Map/Places/Characters/Warrior.h src/Map/Places/Characters/Hero.h

src/Map/Places/Village.o: src/Map/Places/Village.cpp src/Map/Places/Place.h

src/Map/Places/Arena.o: src/Map/Places/Arena.cpp src/Map/Places/Place.h

src/Map/Places/Characters/GoodCharacter.o: src/Map/Places/Characters/GoodCharacter.cpp src/Map/Places/Characters/Character.h src/Map/Places/Characters/Items/Weapon.h src/Map/Places/Characters/Items/Armour.h src/Map/Places/Characters/Items/Healer.h src/Map/Places/Characters/Items/Storage.h

src/Map/Places/Characters/Character.o: src/Map/Places/Characters/Character.cpp src/usefullFunctions.h src/Constants.h

src/Map/Places/Characters/Warrior.o: src/Map/Places/Characters/Warrior.cpp src/Map/Places/Characters/Character.h

src/Map/Places/Characters/Hero.o: src/Map/Places/Characters/Hero.cpp src/Map/Places/Characters/GoodCharacter.h src/Map/Places/Characters/Warrior.h

src/Map/Places/Characters/Items/Item.o: src/Map/Places/Characters/Items/Item.cpp src/usefullFunctions.h src/Constants.h

src/Map/Places/Characters/Items/Armour.o: src/Map/Places/Characters/Items/Armour.cpp src/Map/Places/Characters/Items/Item.h

src/Map/Places/Characters/Items/Healer.o: src/Map/Places/Characters/Items/Healer.cpp src/Map/Places/Characters/Items/Item.h

src/Map/Places/Characters/Items/Weapon.o: src/Map/Places/Characters/Items/Weapon.cpp src/Map/Places/Characters/Items/Item.h

src/Map/Places/Characters/Items/Storage.o: src/Map/Places/Characters/Items/Storage.cpp src/Map/Places/Characters/Items/Armour.h src/Map/Places/Characters/Items/Healer.h src/Map/Places/Characters/Items/Weapon.h


compile: $(ALL_OBJECTS)
	$(CXX) $^ -o $(OBJECT_NAME) $(LINKERFLAG)
	
run: $(OBJECT_NAME)
	./$< -g

clean:
	@echo "Cleaning up..."
	rm -rvf lyashmik src/*.o src/Map/*.o src/Map/Places/*.o src/Map/Places/Characters/*.o src/Map/Places/Characters/Items/*.o

doc:
	doxygen src/Doxyfile
	mv doc/html/* doc/
	rm -rvf doc/html
	rm -rvf doc/latex
