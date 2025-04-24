#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"//includes order header files

static OrderNode *front = NULL, *rear = NULL;//this is the implementation of a linked list


void displayMenu(MenuItem menu[], int size) //Displays all available menu items with their IDs and prices.
{
    printf("\nAvailable Items:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - $%.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

void push(StackNode **top, OrderItem item) 
{
    StackNode *newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = *top;
    *top = newNode;
}

int pop(StackNode **top, OrderItem *item) 
{
    if (!*top) return 0;
    StackNode *temp = *top;
    *item = temp->item;
    *top = temp->next;
    free(temp);
    return 1;
}

void enqueueOrder(OrderItem items[], int count) {
    OrderNode *newOrder = malloc(sizeof(OrderNode));
    memcpy(newOrder->items, items, sizeof(OrderItem) * count);
    newOrder->itemCount = count;
    newOrder->next = NULL;

    if (rear == NULL) {
        front = rear = newOrder;
    } else {
        rear->next = newOrder;
        rear = newOrder;
    }

    printf(" Order placed successfully into the queue!\n");
}

void displayOrderQueue() {
    if (!front) {
        printf(" No orders in queue.\n");
        return;
    }

    printf("\nCurrent Order Queue:\n");
    OrderNode *curr = front;
    int orderNum = 1;
    while (curr) {
        printf("Order %d:\n", orderNum++);
        for (int i = 0; i < curr->itemCount; i++) {
            printf("  Item ID: %d, Quantity: %d\n", curr->items[i].itemID, curr->items[i].quantity);
        }
        curr = curr->next;
    }
}

void startOrder(MenuItem menu[], int menuSize) {
    OrderItem items[10];
    int count = 0;
    int choice, quantity;
    StackNode *undoStack = NULL;

    printf("\n Start your order (0 to finish, -1 to undo last item):\n");

    while (1) {
        displayMenu(menu, menuSize);
        printf("Enter item number: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }

        if (choice == 0) break;

        if (choice == -1) {
            OrderItem undone;
            if (pop(&undoStack, &undone)) {
                count--;
                printf(" Undid item %d x%d\n", undone.itemID, undone.quantity);
            } else {
                printf("Nothing to undo.\n");
            }
            continue;
        }

        if (choice < 1 || choice > menuSize) {
            printf("Invalid item.\n");
            continue;
        }

        printf("Enter quantity: ");
        if (scanf("%d", &quantity) != 1 || quantity <= 0) {
            while (getchar() != '\n');
            printf("Invalid quantity.\n");
            continue;
        }

        items[count].itemID = choice;
        items[count].quantity = quantity;
        push(&undoStack, items[count]);
        count++;

        if (count >= 10) {
            printf("Maximum of 10 items reached.\n");
            break;
        }
    }

    if (count > 0) {
        displayCart(items, count, menu, menuSize);
        printf("Total: $%.2f\n", calculateTotal(items, count, menu, menuSize));
        enqueueOrder(items, count);
    }
}

void displayCart(OrderItem orders[], int count, MenuItem menu[], int menuSize) {
    printf("\n Order Summary:\n");
    for (int i = 0; i < count; i++) {
        int id = orders[i].itemID - 1;
        printf("%s (x%d) - $%.2f\n", menu[id].name, orders[i].quantity, menu[id].price * orders[i].quantity);
    }
}

float calculateTotal(OrderItem orders[], int count, MenuItem menu[], int menuSize) {
    float total = 0;
    for (int i = 0; i < count; i++) {
        int id = orders[i].itemID - 1;
        total += menu[id].price * orders[i].quantity;
    }
    return total;
}
