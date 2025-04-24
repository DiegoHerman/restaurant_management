s#ifndef ORDER_H
#define ORDER_H


typedef struct 
{
    int foodID;
    char foodName[120];
    int price;
    int quantity;

} FoodOrderItem;

typedef struct {
    int customerId;
    char name[50];
    FoodOrderItem orders[20];
    int orderCount;
    float totalAmount;
} Customer;

void FoodOrderMenu();
void PlaceOrder();
void PaymentReceipt();
void getCurrentDate(char *date);
void displayOrderHistory(int customerIndex);
void clearInputBuffer();
int findCustomerbyId(int id);


#endif
