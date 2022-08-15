set -e
gcc -g  -c sticksouls.c -o ./lib/sticksouls.o 
gcc -o sticksouls lib/sticksouls.o -s -Wall  -lraylib -lm -lpthread -ldl -lrt -lX11  
./sticksouls