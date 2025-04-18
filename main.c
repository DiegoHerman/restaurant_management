 //Header files
#include <stdio.h>
#include <stdlib.h>

//Date and Time 
#include <time.h>

//String Manipulation
#include <string.h>
//Math
#include <math.h>
//File Handling
#include <fcntl.h>
//Console Input and Output
#include <conio.h> //In order for getch() to work


void FoodOrderMenu();
void CustomerOrder();
void PaymentReceipt();



int main (void){
    int platformChoice;

    //MAIN PLATFORM PAGE
    printf("Welcome to the Sansiro Coopa Hotel \n");
    printf("1. Food Order Menu \n");
    printf("2. Exit \n");

    printf("Please select an option: \n");
    scanf("%d", &platformChoice); 

    //Switch case to handle the platform choice made by the user
    switch (platformChoice){
        case 1:
            FoodOrderMenu();
            break;
      
        case 2:
            printf("Exiting the program...\n");
            exit(0);  // Exit the program via stdlib.h guys
            break;
        default:
            printf("Invalid  Platform choice. Please try again.\n");
            break;

    }

    return 0;

}


typedef struct 
{
    int foodID;
    char foodName[120];
    int price;

} FoodOrderItem;

 FoodOrderItem menu[12] = {
    {101, "Swahili Pilau with Chicken Curry", 250},
    {102, "Chapati with Beef Stew", 150},
    {103, "Pasta with Beef Stew", 120},
    {104, "Chapati with Beans", 100},
    {105, "Ugali with Fish Stew", 150},
    {106, "Ugali with Beef Stew", 150},
    {107, "Ugali with Chicken Stew", 200},
    {108, "Ugali with Vegetable Stew", 100},
    {109, "Rice with Beans Stew", 100},
    {110, "Rice with Beef Stew", 150},
    {111, "Rice with Chicken Stew", 200},
    {112, "Rice with Vegetable Stew", 100}
};

void FoodOrderMenu(){
    for (int i = 0; i < 12; i++)
    {
        printf("Food ID: %d, Food Name: %s, Price: %d\n",
                 menu[i].foodID,
                 menu[i].foodName,
                 menu[i].price);
    }
}

