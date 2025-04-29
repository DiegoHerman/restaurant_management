#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void clearInputBuffer();

// Data structures
typedef struct
{
    int foodID;
    char foodName[120];
    int price;
    int quantity;
} FoodOrderItem;

typedef struct
{
    int customerId;
    char name[50];
    FoodOrderItem orders[20];
    int orderCount;
    float totalAmount;
    char OrderDate[11];
} Customer;



/// THE FOOD MENU INVOLVED
FoodOrderItem menu[12] = {
    {101, "Swahili Pilau with Chicken Curry", 250, 0},
    {102, "Chapati with Beef Stew", 150, 0},
    {103, "Pasta with Beef Stew", 120, 0},
    {104, "Chapati with Beans", 100, 0},
    {105, "Ugali with Fish Stew", 150, 0},
    {106, "Ugali with Beef Stew", 150, 0},
    {107, "Ugali with Chicken Stew", 200, 0},
    {108, "Ugali with Vegetable Stew", 100, 0},
    {109, "Rice with Beans Stew", 100, 0},
    {110, "Rice with Beef Stew", 150, 0},
    {111, "Rice with Chicken Stew", 200, 0},
    {112, "Rice with Vegetable Stew", 100, 0}};

int main(void)
{
    int platformChoice;

    while (1)
    {
        printf("\n=== HOTEL MANAGEMENT SYSTEM ===\n");
        printf("1. View Food Menu\n");
        printf("2. Place Order\n");
        printf("3. Print Bill/Receipt\n");
        printf("4. Admin Login\n");
        printf("5. Exit\n");
        printf("Please select an option: ");

        if (scanf("%d", &platformChoice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (platformChoice)
        {
        case 1:
            FoodOrderMenu();
            break;
        case 2:
            PlaceOrder();
            break;
        case 3:
            PaymentReceipt();
            break;
        case 4:
            AdminLogin();
            break;
        case 5:
            printf("Exiting the program...\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
    return 0;
}

void clearInputBuffer()
{
    while (getchar() != '\n')
        ;
}





