#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "order.h"

// Function prototypes
void FoodOrderMenu();
void PlaceOrder();
void PaymentReceipt();
void AdminLogin();
void getCurrentDate(char *date);
void displayOrderHistory(int customerIndex);
void clearInputBuffer();
int findCustomerbyId(int Id);

Customer customers[100];
int customerCount = 0;
int adminLoggedIn = 0; // iss like a switch that turns gives special access


int findCustomerbyId(int Id) {
    for(int i=0;i<customerCount;i++) {
        if(customers[i].customerId==Id){
            return i;
        }
    }
    return -1;
}
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



void clearInputBuffer()
{
    while (getchar() != '\n')
        ;
}
void saveCustomersToFile() {
    FILE *file = fopen("customers.dat", "wb");
    if (file == NULL) {
        printf("Error saving customer data!\n");
        return;
    }
    fwrite(&customerCount, sizeof(int), 1, file);
    fwrite(customers, sizeof(Customer), customerCount, file);
    fclose(file);
}
void getCurrentDate(char *date)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}



void FoodOrderMenu()
{
    printf("\n=== FOOD MENU ===\n");
    printf("%-5s %-40s %-10s\n", "ID", "ITEM NAME", "PRICE (KSH)");
    printf("------------------------------------------------\n");
    for (int i = 0; i < 12; i++)
    {
        printf("%-5d %-40s %-10d\n", menu[i].foodID, menu[i].foodName, menu[i].price);
    }
}


            void addnewcustomer() {
                if (customerCount >= 100)
                {
                    printf("Maximum customer capacity reached!\n");
                    return;
                }

                Customer newCustomer;
                newCustomer.customerId =rand()%1000+1;

                printf("\nEnter customer name: ");
                clearInputBuffer();
                fgets(newCustomer.name, 50, stdin);
                newCustomer.name[strcspn(newCustomer.name, "\n")] = '\0';

                newCustomer.orderCount = 0;
                newCustomer.totalAmount = 0;
                getCurrentDate(newCustomer.OrderDate);

                customers[customerCount++] = newCustomer;

                printf("Customer added successfully with ID: %d\n", newCustomer.customerId);
                
            }
            
            void placetheorder() {
                printf("\n=== CUSTOMER LIST ===\n");
                printf("%-8s %-20s %-15s\n", "ID", "NAME", "REGISTER DATE");
                printf("----------------------------------------\n");
                for (int i = 0; i < customerCount; i++)
                {
                    printf("%-8d %-20s %-15s\n",
                           customers[i].customerId,
                           customers[i].name,
                           customers[i].OrderDate);
                }
                return;
            }
            
        void ViewOrderHistory() {
          int custId;
          printf("Enter Customer ID to view orders: ");
          if (scanf("%d", &custId) != 1) {
             printf("Invalid customer ID.\n");
             clearInputBuffer();
             return;
    }
    
    int customerIndex = findCustomerbyId(custId);
    if (customerIndex != -1) {
        displayOrderHistory(customerIndex);
    } else {
        printf("Customer not found!\n");
    }
}    
            void logout() {
                adminLoggedIn = 0;
                printf("Logged out successfully.\n");
            }


void PlaceOrder()
{
    if (customerCount == 0)
    {
        printf("\nNo customers available. Please contact admin.\n");
        return;
    }

    int customerId;
    printf("\nEnter your Customer ID: ");
    if (scanf("%d", &customerId) != 1)
    {
        printf("Invalid customer ID.\n");
        clearInputBuffer();
        return;
    }

    int customerIndex = findCustomerbyId(customerId);
    if (customerIndex == -1)
    {
        printf("Customer not found!\n");
        return;
    }

    printf("\nWelcome, %s!\n", customers[customerIndex].name);
    FoodOrderMenu();

    int orderMore = 1;
    while (orderMore)
    {
        int foodId, quantity;
        printf("\nEnter Food ID to order (0 to finish): ");
        if (scanf("%d", &foodId) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        if (foodId == 0)
        {
            orderMore = 0;
            continue;
        }

        int foodIndex = -1;
        for (int i = 0; i < 12; i++)
        {
            if (menu[i].foodID == foodId)
            {
                foodIndex = i;
                break;
            }
        }
        if (foodIndex == -1)
        {
            printf("Invalid Food ID! Please try again.\n");
            continue;
        }

        printf("Enter quantity for %s: ", menu[foodIndex].foodName);
        if (scanf("%d", &quantity) != 1 || quantity <= 0)
        {
            printf("Invalid quantity! Must be a positive number.\n");
            clearInputBuffer();
            continue;
        }

        // Add to customer's orders
        int orderPos = customers[customerIndex].orderCount;
        if (orderPos >= 20)
        {
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
}

void displayOrderHistory(int customerIndex)
{
    printf("\n=== ORDER HISTORY FOR %s ===\n", customers[customerIndex].name);
    if (customers[customerIndex].orderCount == 0)
    {
        printf("No orders found.\n");
        return;
    }

    printf("%-5s %-40s %-10s %-10s %-10s\n",
           "ID", "ITEM", "PRICE", "QTY", "TOTAL");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < customers[customerIndex].orderCount; i++)
    {
        FoodOrderItem item = customers[customerIndex].orders[i];
        printf("%-5d %-40s %-10d %-10d %-10.2f\n",
               item.foodID,
               item.foodName,
               item.price,
               item.quantity,
               (float)(item.price * item.quantity));
    }

    printf("\nGRAND TOTAL: KSH %.2f\n", customers[customerIndex].totalAmount);
}

void PaymentReceipt()
{
    if (customerCount == 0)
    {
        printf("\nNo customers available. Please contact admin.\n");
        return;
    }

    int customerId;
    printf("\nEnter your Customer ID: ");
    if (scanf("%d", &customerId) != 1)
    {
        printf("Invalid customer ID.\n");
        clearInputBuffer();
        return;
    }

    int customerIndex = findCustomerbyId(customerId);
    if (customerIndex == -1)
    {
        printf("Customer not found!\n");
        return;
    }

    if (customers[customerIndex].orderCount == 0)
    {
        printf("No orders found for this customer.\n");
        return;
    }

    // Display receipt on screen
    printf("\n=== PAYMENT RECEIPT ===\n");
    printf("Customer ID: %d\n", customers[customerIndex].customerId);
    printf("Customer Name: %s\n", customers[customerIndex].name);
    printf("----------------------------------------\n");

    char fileName[50];
    sprintf(fileName, "receipt_%d.txt", customers[customerIndex].customerId);
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Error saving receipt to file.\n");
        return;
    }  
    for (int i = 0; i < customers[customerIndex].orderCount; i++)
    {
        fprintf(file, "%d,%s,%.2f\n",
                customers[customerIndex].customerId,
                customers[customerIndex].name,
                customers[customerIndex].totalAmount
        );
    }

    fclose(file);

    printf("\nReceipt saved to %s\n", fileName);
}
