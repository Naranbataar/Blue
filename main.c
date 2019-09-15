#include <stdio.h> /* stderr, fprintf */
#include <stdlib.h> /* strtoll */
#include <string.h> /* strlen */
#include <getopt.h> /* getopt */

#include "blue.h"

static int
usage(void){
    fprintf(stderr, "Usage: blue CHECKSUM FILESIZE\n");
    fprintf(stderr, "Searches for file(s) by md5 checksum and size\n");
    return 1;
}

int
main(int argc, char *argv[])
{
    int ret = 0;

    if (argc != 3 || strlen(argv[1]) != 32)
    {
        ret = usage();    
    }
    else
    { 
        char *endptr;
        long long size = strtoll(argv[2], &endptr, 10);
        if (size == 0 || *endptr != '\0' )
        {
            ret = usage();
        }
        else
        {
            SIGNATURE sign;
            sign.hash = argv[1];
            sign.size = size;
            BlueSearch(sign, "./");
        }
    }
    return ret;
}
