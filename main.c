#include <stdio.h>
#include "order.h"  // Include the order header file to access the functions

int main() {
    // Example inventory for testing
    InventoryItem inventory[] = {
        {1, "Pizza", 9.99, 10},
        {2, "Burger", 5.99, 20},
        {3, "Pasta", 7.99, 15}
    };

    int inventorySize = sizeof(inventory) / sizeof(inventory[0]);

    // Display inventory before order
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
