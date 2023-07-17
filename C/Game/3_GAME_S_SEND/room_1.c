#include <stdio.h>
#include <stdlib.h>
extern int pin_number;
extern char alarm;

void access_control()
{
    int x = 0;
    printf("\n________________________________________________\n");
    printf("                                  |             \n");
    printf("YOU ARE IN                        |   ROOM_1\n");
    printf("__________________________________|_____________\n");
    printf("                                  |             \n");
    printf("ENTER PIN CODE IN ACCESS CONTROL  |   ");
    scanf("%d",&x);
    if(x == 5664)
    printf("ACCESS ALLOWED                    |\n");
    else{
    alarm = 1;
    printf("\nALARM\n");}
}
