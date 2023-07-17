#include <stdio.h>
#include <stdlib.h>
extern char alarm;
    void old_man(int x,int*p)
    {
       static char loop = 0;

       if((alarm == 0)&&((x == 0)||(*p == 0))&&(loop == 0)){
    printf("__________________________________|_____________\n");
    printf("                                  |             \n");
    printf("YOU ESCAPED FROM ROOM_1           |\n");
    printf("                                  |\n");
    printf("NOW YOU ARE IN                    |   CORRIDOR\n");
    printf("__________________________________|_____________\n");
    printf("                                  |              \n");
    printf("HELLO SON I AM THE OLD MAN        |\n");
    printf("GIVE ME 200 LE PLEASE             |   ");
    scanf("%d",&x);
    *p = x;
    printf("WAIT HERE I WILL OPEN THE DOOR    |   \n");
    loop++;
    return;}

       if((alarm == 0)&&((x != 200)||(*p != 200))&&(loop == 1)){
    printf("HELLO SON I AM THE OLD MAN        |\n");
    printf("GIVE ME 200 LE PLEASE             |   ");
    scanf("%d",&x);
    alarm = 1;
    printf("ALARM                             |\n");}

       if((alarm == 0)&&((x == 200)||(*p == 200))&&(loop == 1)){
    printf("OKAY SON I OPENED THE DOOR        |\n");}
    }
