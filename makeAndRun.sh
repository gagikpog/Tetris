rm app.pro
clear
g++ -o app.pro main.cpp Tetris.cpp lib/GluiColor.cpp lib/Glui_UF.cpp -lGL -lGLU -lglut
./app.pro