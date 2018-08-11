rm app.pro
clear
g++ -o app.pro main.cpp Tetris.cpp GluiColor.cpp -lGL -lGLU -lglut
./app.pro