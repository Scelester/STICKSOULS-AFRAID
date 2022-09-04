#include <stdio.h>
#include <string.h>
#include <stdlib.h>





int * x(int x){
    static int one[2] = {9,91};
    for (size_t i = 0; i < sizeof(one); i++)
    {
        one[i] = one[i] * x;
    }
    
    return one;
}

int main(int argc, char **argv){
    
    float x = 2 - 1.1;

    printf("%f\n", x);
    
    return 0;
}