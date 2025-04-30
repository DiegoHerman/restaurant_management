void AdminLogin()
{
    char username[20], password[20];
    printf("\n=== ADMIN LOGIN ===\n");
    printf("Username: ");
    if (scanf("%19s", username) != 1)
    {
        printf("Error reading username.\n");
        clearInputBuffer();
        return;
    }
    printf("Password: ");
    if (scanf("%19s", password) != 1)
    {
        printf("Error reading password.\n");
        clearInputBuffer();
        return;
    }

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
    {
        adminLoggedIn = 1;
        printf("\nLogin successful!\n");

        int adminChoice;
        do
        {
            printf("\n=== ADMIN MENU ===\n");
            printf("1. Add New Customer\n");
            printf("2. View All Customers\n");
            printf("3. View Customer Orders\n");
            printf("4. Logout\n");
            printf("Select option: ");

            if (scanf("%d", &adminChoice) != 1)
            {
                printf("Invalid input. Please enter a number.\n");
                clearInputBuffer();
                continue;
            }

            switch (adminChoice)
            {
            case 1:
            {
                if (customerCount >= 100)
                {
                    printf("Maximum customer capacity reached!\n");
                    break;
                }

                Customer newCustomer; // Declare the newCustomer variable
                newCustomer.customerId = nextCustomerId;
                nextCustomerId++;

                printf("\nEnter customer name: ");
                clearInputBuffer();
                fgets(newCustomer.name, 50, stdin);
                newCustomer.name[strcspn(newCustomer.name, "\n")] = '\0';

                newCustomer.orderCount = 0;
                newCustomer.totalAmount = 0;
                getCurrentDate(newCustomer.OrderDate);

                customers[customerCount++] = newCustomer;

                printf("Customer added successfully with ID: %d\n", newCustomer.customerId);
                break;
            }
            case 2:
            {
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
                break;
            }
            case 3:
            {
                int custId;
                printf("Enter Customer ID to view orders: ");
                if (scanf("%d", &custId) != 1)
                {
                    printf("Invalid customer ID.\n");
                    clearInputBuffer();
                    break;
                }
                int index = findCustomerbyId(custId);
                if (index != -1)
                {
                    displayOrderHistory(index);
                }
                else
                {
                    printf("Customer not found!\n");
                }
                break;
            }
            case 4:
                adminLoggedIn = 0;
                printf("Logged out successfully.\n");
                break;
            default:
                printf("Invalid choice.\n");
            }
        } while (adminChoice != 4);
    }
    else
    {
        printf("Invalid credentials!\n");
    }
}
