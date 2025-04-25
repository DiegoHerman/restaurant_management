s#ifndef ORDER_H
#define ORDER_H


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

void FoodOrderMenu();
void PlaceOrder();
void PaymentReceipt();
void AdminLogin();
void getCurrentDate(char *date);
void displayOrderHistory(int customerIndex);
void clearInputBuffer();
int findCustomerbyId();
void addnewcustomer();
void placeorder();
void vieworderhistory();
void logout();
#endif
