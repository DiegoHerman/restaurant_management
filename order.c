#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "order.h"
void FoodOrderMenu();
void PlaceOrder();
void PaymentReceipt();
void getCurrentDate(char *date);
void displayOrderHistory(int customerIndex);
void clearInputBuffer();//ensures that unwanted characters don’t interfere with future input operations, making your program more reliable when handling user input.
int findCustomerbyId(int id);

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

Customer customers[100];
int customerCount = 0;
int adminLoggedIn = 0;
int nextCustomerId = 1001; 

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
void FoodOrderMenu() {
    printf("\n=== FOOD MENU ===\n");
    printf("%-5s %-40s %-10s\n", "ID", "ITEM NAME", "PRICE (KSH)");
    printf("------------------------------------------------\n");
    for (int i = 0; i < 12; i++) {
        printf("%-5d %-40s %-10d\n", menu[i].foodID, menu[i].foodName, menu[i].price);
    }
}
void clearInputBuffer() {
    while (getchar() != '\n');
}
void getCurrentDate(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}
int findCustomerbyId(int id) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].customerId == id) {
            return i;
        }
    }
    return -1;
}
void saveCustomersToFile() {
    FILE *file = fopen("customers.dat", "wb");
    if (file == NULL) {
        printf("Error saving customer data!\n");
        return;
    }
    fwrite(&customerCount, sizeof(int), 1, file);
    fwrite(&nextCustomerId, sizeof(int), 1, file);
    fwrite(customers, sizeof(Customer), customerCount, file);
    fclose(file);
}
void PlaceOrder() {
    if (customerCount == 0) {
        printf("\n No customers available. Please contact admin.\n");
        return;
    }

    int customerId;
    printf("\nEnter your Customer ID: ");
    if (scanf("%d", &customerId) != 1) {
        printf("Invalid customer ID.\n");
        clearInputBuffer();
        return;
    }
    
    int customerIndex = findCustomerbyId(customerId);
    if (customerIndex == -1) {
        printf("Customer not found!\n");
        return;
    }

    printf("\nWelcome, %s!\n", customers[customerIndex].name);
    FoodOrderMenu();
    
    int orderMore = 1;
    while (orderMore) {
        int foodId, quantity;
        printf("\nEnter Food ID to order (0 to finish): ");
        if (scanf("%d", &foodId) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        
        if (foodId == 0) {
            orderMore = 0;
            continue;
        }

        int foodIndex = -1;
        for (int i = 0; i < 12; i++) {
            if (menu[i].foodID == foodId) {
                foodIndex = i;
                break;
            }
        }

        if (foodIndex == -1) {
            printf("Invalid Food ID! Please try again.\n");
            continue;
        }

        printf("Enter quantity for %s: ", menu[foodIndex].foodName);
        if (scanf("%d", &quantity) != 1 || quantity <= 0) {
            printf("Invalid quantity! Must be a positive number.\n");
            clearInputBuffer();
            continue;
        }

        // Add to customer's orders
        int orderPos = customers[customerIndex].orderCount;
        if (orderPos >= 20) {
            printf("Maximum order items reached!\n");
            break;
        }
        
        customers[customerIndex].orders[orderPos] = menu[foodIndex];
        customers[customerIndex].orders[orderPos].quantity = quantity;
        customers[customerIndex].totalAmount += menu[foodIndex].price * quantity;
        customers[customerIndex].orderCount++;
        
        printf("Added %d x %s (KSH %d each)\n", 
              quantity, 
              menu[foodIndex].foodName, 
              menu[foodIndex].price);
    }
    printf("\nOrder placed successfully!\n");
    printf("Total amount: KSH %.2f\n", customers[customerIndex].totalAmount);
    saveCustomersToFile();
}
void displayOrderHistory(int customerIndex) {
    printf("\n=== ORDER HISTORY FOR %s ===\n", customers[customerIndex].name);
    if (customers[customerIndex].orderCount == 0) {
        printf("No orders found.\n");
        return;
    }
    
    printf("%-5s %-40s %-10s %-10s %-10s\n", 
          "ID", "ITEM", "PRICE", "QTY", "TOTAL");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < customers[customerIndex].orderCount; i++) {
        FoodOrderItem item = customers[customerIndex].orders[i];
        printf("%-5d %-40s %-10d %-10d %-10.2f\n", 
              item.foodID, 
              item.foodName, 
              item.price, 
              item.quantity, 
              item.price * item.quantity);
    }
    
    printf("\nGRAND TOTAL: KSH %.2f\n", customers[customerIndex].totalAmount);
}

void PaymentReceipt() {
    if (customerCount == 0) {
        printf("\nNo customers available. Please contact admin.\n");
        return;
    }

    int customerId;
    printf("\nEnter your Customer ID: ");
    if (scanf("%d", &customerId) != 1) {
        printf("Invalid customer ID.\n");
        clearInputBuffer();
        return;
    }

    int customerIndex = findCustomerbyId(customerId);
    if (customerIndex == -1) {
        printf("Customer not found!\n");
        return;
    }

    if (customers[customerIndex].orderCount == 0) {
        printf("No orders found for this customer.\n");
        return;
    }

    // Display receipt on screen
    printf("\n=== PAYMENT BILL ===\n");
    printf("Customer ID: %d\n", customers[customerIndex].customerId);
    printf("Customer Name: %s\n", customers[customerIndex].name);
    printf("----------------------------------------\n");
    
    displayOrderHistory(customerIndex);
    
    // Save receipt to file
    char fileName[50];
    sprintf(fileName, "receipt_%d.txt", customers[customerIndex].customerId);
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error saving receipt to file.\n");
        return;
    }

    fprintf(file, "=== PAYMENT BILL ===\n");
    fprintf(file, "Customer ID: %d\n", customers[customerIndex].customerId);
    fprintf(file, "Customer Name: %s\n", customers[customerIndex].name);
    fprintf(file, "----------------------------------------\n");
    
    for (int i = 0; i < customers[customerIndex].orderCount; i++) {
        FoodOrderItem item = customers[customerIndex].orders[i];
        fprintf(file, "%-5d %-40s %-10d %-10d %-10.2f\n", 
               item.foodID, 
               item.foodName, 
               item.price, 
               item.quantity, 
               item.price * item.quantity);
    }
    
    fprintf(file, "\nGRAND TOTAL: KSH %.2f\n", customers[customerIndex].totalAmount);
    fclose(file);
    
    printf("\nReceipt saved to %s\n", fileName);
}
int main() {
    int choice;
    FILE *file = fopen("customers.dat", "rb");
    if (file != NULL) {
        fread(&customerCount, sizeof(int), 1, file);
        fread(&nextCustomerId, sizeof(int), 1, file);
        fread(customers, sizeof(Customer), customerCount, file);
        fclose(file);
    }
    do {
        printf("\n=== RESTAURANT MANAGEMENT SYSTEM ===\n");
        printf("1. Place Order\n");
        printf("2. View Order History\n");
        printf("3. Generate Bill\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        switch(choice) {
            case 1:
                PlaceOrder();
                break;
            case 2:
                {
                    int customerId;
                    printf("Enter Customer ID: ");
                    scanf("%d", &customerId);
                    clearInputBuffer();
                    int index = findCustomerbyId(customerId);
                    if (index != -1) {
                        displayOrderHistory(index);
                    } else {
                        printf("Customer not found!\n");
                    }
                }
                break;
            case 3:
                PaymentReceipt();
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
    
    return 0;
}