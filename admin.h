#ifndef ADMIN_H
#define ADMIN_H

struct fooditem {
    char name[20];
    float price;
    int quantity;

};


void addfooditem();
void editfooditem();
void deletefooditem();
void displayitems();

#endif