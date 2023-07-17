#include <stdio.h>
#include <stdlib.h>
#include "escape.h"

extern int alarm;
int x_address;
char num = 0;
void gard_1(void)
{
    const int x = 215;
    x_address = &x;
    int z = 0;
    escape_gard_1();
    if(alarm == 0){
    printf("__________________________________|_____________\n");
    printf("                                  |             \n");
    printf("YOU ESCAPED FROM CORRIDOR         |\n");
    printf("                                  |\n");
    printf("NOW YOU ARE IN                    |   GARDEN\n");
    printf("__________________________________|_____________\n");
    printf("                                  |             \n");
    printf("I AM GARD_1 WHAT IS YOUR NUMBER   |   ");
    }
    if(alarm == 0){
    scanf("%d",&z);

    if(z!=x){
    alarm = 1;
    printf("\nALARM\n");}
    }
}
void gard_2(void)
{
    if(alarm == 0){
    printf("__________________________________|_____________\n");
    printf("                                  |             \n");
    printf("NOW YOU ARE IN                    |   GARDEN\n");
    printf("__________________________________|_____________\n");
    printf("                                  |             \n");
    printf("I AM GARD_2 WHAT IS YOUR NUMBER   |     ");

    escape_gard_2();

    if(num != 65){
    alarm = 1;
    printf("\nALARM\n");}
    }
}
