#include <stdio.h>
#include "order.h"  // Include the order header file to access the functions

int main() {


    int inventorySize = sizeof(inventory) / sizeof(inventory[0])
    printf("Initial Inventory:\n");
    displayInventory(inventory, inventorySize);

    // Simulate ordering process
    printf("\nBuyer placing order...\n");
    startOrder(inventory, inventorySize);  // Assuming startOrder is defined in order.c

    // Display inventory after order
    printf("\nUpdated Inventory after order:\n");
    displayInventory(inventory, inventorySize);

    return 0;
}
