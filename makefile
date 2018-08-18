CC=g++

all: bin app
allDebog: bin appDebog

app: bin/GluiColor.o bin/GluiText.o bin/ConfigINI.o bin/Glui_UF.o  bin/main.o bin/Game.o bin/Block.o 
	$(CC) -o app.pro bin/GluiColor.o bin/GluiText.o bin/ConfigINI.o bin/Glui_UF.o bin/main.o bin/Game.o bin/Block.o -lGL -lGLU -lglut

appDebog: bin/GluiColor.o bin/GluiText.o bin/ConfigINI.o bin/Glui_UF.o  bin/main.o bin/Game.o bin/Block.o 
	$(CC) -o app.pro bin/GluiColor.o bin/GluiText.o bin/ConfigINI.o bin/Glui_UF.o bin/main.o bin/Game.o bin/Block.o -lGL -lGLU -lglut -g

#project 
bin/main.o:
	$(CC) -c main.cpp -o bin/main.o

bin/Game.o:
	$(CC) -c Game.cpp -o bin/Game.o 

bin/Block.o:
	$(CC) -c Block.cpp -o bin/Block.o

#lib source
bin/GluiColor.o:
	$(CC) -c lib/GluiColor.cpp -o bin/GluiColor.o

bin/GluiText.o:
	$(CC) -c lib/GluiText.cpp -o bin/GluiText.o

bin/ConfigINI.o:
	$(CC) -c lib/ConfigINI.cpp -o bin/ConfigINI.o

bin/Glui_UF.o:
	$(CC) -c lib/Glui_UF.cpp -o bin/Glui_UF.o

clear:
	rm bin/*.o
	clear

bin: | /bin
	@echo "Create new directory /bin"
	mkdir bin