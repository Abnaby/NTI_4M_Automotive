#include <stdio.h>
#include <stdlib.h>
#include "corridor.h"
#include "escape.h"
#include "garden.h"
#include "room_1.h"
#include "tunnel.h"

char alarm = 0;
int address_of_old_man_money = 0;
int address_1 = &address_1;
int main()
{

    int old_man_money = 0;
    address_of_old_man_money = &old_man_money;
    escape_access_control();
    access_control();
    escape_old_man();
    old_man(old_man_money,address_1);
    old_man(old_man_money,address_1);
    gard_1();
    gard_2();
    tunnel_size();
    return 0;
}
