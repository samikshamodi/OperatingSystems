#include <stdio.h>
#include <inttypes.h>

void add (int64_t, int64_t);     // function in NASM assembly language

int main(int argc, char *argv[ ])
{
    int64_t a, b;

    printf("\nInput a, b: ");
    scanf("%ld %ld", &a, &b);
    add(a, b);
    return 0;
} 
