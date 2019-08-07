CXX=g++
CXXFLAGS=-std=c++14 -Wall -Werror=vla -MMD
OBJECTS=main.o floor.o chamber.o character.o dragon.o treasure.o potion.o merchant.o human.o dwarf.o orcs.o elf.o halfling.o player.o enemy.o object.o drow.o vampire.o troll.o goblin.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
clean:
	rm *.o *.d cc3k
.PHONY: clean
