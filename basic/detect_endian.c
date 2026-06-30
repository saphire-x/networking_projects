#include <stdio.h>
int main() {
    int x = 1;
    char *p = (char*)&x;
    

    if(*p == 1)
        printf("Little Endian");
    else
        printf("Big Endian");


}