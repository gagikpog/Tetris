rm app.pro
clear
g++ -o app.pro main.cpp Game.cpp Block.cpp lib/GluiColor.cpp lib/GluiText.cpp lib/Glui_UF.cpp -lGL -lGLU -lglut -g