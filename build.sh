set -e
g++ -g  -c sticksouls.cpp -o ./lib/sticksouls.o 
g++ -o sticksouls lib/sticksouls.o -s -Wall  -lraylib -lm -lpthread -ldl -lrt -lX11  
./sticksouls 