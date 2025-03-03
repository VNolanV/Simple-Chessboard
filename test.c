#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
char list[16];
} testlist;

int main( int argc, char **argv )
{

    testlist * test = malloc (sizeof(testlist));

    test->list[4] = a;

    for(int i = 0; i < 16; i++){
        printf("%c",test->list[i]);
    }

    return 0;
}

