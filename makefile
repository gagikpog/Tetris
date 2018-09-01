CC=g++
FLAG=-c
DEBUG=-g
F_OPENGL=-lGL -lGLU -lglut
F_OPENAL=-lopenal -lalut

all: bin bin/GluiColor.o bin/GluiText.o bin/ConfigINI.o bin/Glui_UF.o  bin/main.o bin/Game.o bin/Block.o bin/CRC_code.o bin/Sound.o bin/Label.o
	$(CC) -o app.pro bin/GluiColor.o bin/GluiText.o bin/ConfigINI.o bin/Glui_UF.o bin/main.o bin/Game.o bin/Block.o bin/CRC_code.o bin/Sound.o bin/Label.o $(F_OPENGL) $(F_OPENAL)

allDebog: addDebugFlag bin bin/GluiColor.o bin/GluiText.o bin/ConfigINI.o bin/Glui_UF.o  bin/main.o bin/Game.o bin/Block.o bin/CRC_code.o bin/Sound.o bin/Label.o
	$(CC) -o app.pro bin/GluiColor.o bin/GluiText.o bin/ConfigINI.o bin/Glui_UF.o bin/main.o bin/Game.o bin/Block.o bin/CRC_code.o bin/Sound.o bin/Label.o $(F_OPENGL) $(F_OPENAL) -g

#project 
bin/main.o:
	$(CC) $(FLAG) main.cpp -o bin/main.o

bin/Game.o:
	$(CC) $(FLAG) Game.cpp -o bin/Game.o 

bin/Block.o:
	$(CC) $(FLAG) Block.cpp -o bin/Block.o

#lib source
bin/GluiColor.o:
	$(CC) $(FLAG) lib/GluiColor.cpp -o bin/GluiColor.o

bin/GluiText.o:
	$(CC) $(FLAG) lib/GluiText.cpp -o bin/GluiText.o

bin/ConfigINI.o:
	$(CC) $(FLAG) lib/ConfigINI.cpp -o bin/ConfigINI.o

bin/Glui_UF.o:
	$(CC) $(FLAG) lib/Glui_UF.cpp -o bin/Glui_UF.o

bin/CRC_code.o:
	$(CC) $(FLAG) lib/CRC_code.cpp -o bin/CRC_code.o

bin/Sound.o:
	$(CC) $(FLAG) Sound.cpp -o bin/Sound.o

bin/Label.o:
	$(CC) $(FLAG) Label.cpp -o bin/Label.o

clear:
	find . -name '*.o' -delete
	clear

bin: | /bin
	@echo "Create new directory /bin"
	mkdir bin

addDebugFlag:
	$(eval FLAG += $(DEBUG))