#include<stdio.h>
#include<stdlib.h>
#define MAXI 200
#include "header.h"
int main(){
    init();
    readMap();
    //myprint();
    findPath();
    storePath();
    return 0;
}