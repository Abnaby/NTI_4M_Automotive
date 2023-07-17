#include <stdio.h>
#include <stdlib.h>


int oldMan_Money;
extern int alarm ;
extern address_1 ;
extern int address_of_old_man_money ;
// Gard 1
extern int x_address;

//Gard 2
extern char num ;

// Garden
extern int y;

escape_access_control()
{


}

escape_old_man()
{

    old_man(200,&oldMan_Money);
    int *ptr = (int*)address_of_old_man_money ;
    *ptr = oldMan_Money ;
    address_1 =  &oldMan_Money;

}
escape_gard_1()
{
    int *ptr = x_address ;
    *ptr = 100 ;

}
escape_gard_2()
{

    num = 'A' ;

}
escape_tunnel_size()
{
    y = sizeof(short);
}
