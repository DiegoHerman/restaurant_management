#ifndef ORDER_H
#define ORDER_H


typedef struct FoodOrderItem {
    int foodID;
    char foodName[120];
    int price;
    int quantity;
} FoodOrderItem;


typedef struct Customer {
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
int findCustomerbyId(int Id);
void addnewcustomer();
void ViewOrderHistory();  
void logout();
#endif
