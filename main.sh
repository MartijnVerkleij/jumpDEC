gpio mode 7 out
gpio mode 0 out

gpio write 7 0
gpio write 0 0
gcc main.c -lwiringpi -lSDL -lSDL_image -lpthread
./a.out
