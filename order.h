#ifndef ORDER_H
#define ORDER_H

typedef struct {
    int id;
    char name[50];
    float price;
} MenuItem;

typedef struct {
    int itemID;
    int quantity;
} OrderItem;

// Stack for recent additions
typedef struct StackNode {
    OrderItem item;
    struct StackNode *next;
} StackNode;

// Queue for submitted orders
typedef struct OrderNode {
    OrderItem items[10]; // Up to 10 items per order
    int itemCount;
    struct OrderNode *next;
} OrderNode;

void startOrder(MenuItem menu[], int menuSize);
void displayMenu(MenuItem menu[], int size);
void displayOrderQueue();
void enqueueOrder(OrderItem items[], int count);
void push(StackNode **top, OrderItem item);
int pop(StackNode **top, OrderItem *item);
float calculateTotal(OrderItem orders[], int count, MenuItem menu[], int size);
void displayCart(OrderItem orders[], int count, MenuItem menu[], int size);

#endif
