#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "admin.h"

struct fooditem *head=NULL;

struct fooditem *createfooditem(int foodID,char name[],float price, int quantity) {
    struct fooditem* newnode=(struct fooditem *)malloc(sizeof(struct fooditem));
    if(newnode!=NULL) {
        newnode->foodID=foodID;
    strcpy(newnode->name,name);
    newnode->price=price;
    newnode->quantity=quantity;
    newnode->next=NULL;
}
return newnode;
}

void addfooditem(struct fooditem **head,int foodID,char name[],float price, int quantity) {
    struct fooditem* newnode=createfooditem(foodID,name,price,quantity);
    if(*head==NULL) {
        *head=newnode;
        return;
    }
    struct fooditem *temp=*head;
    while(temp->next!=NULL) {
        temp=temp->next;
    }
    temp->next=newnode;
    printf("Food item added!\n");
}

void deletefooditem(struct fooditem **head,int foodID) {
    struct fooditem *current=*head;
    struct fooditem *prev=NULL;

    while(current!=NULL&&current->foodID!=foodID) {
        prev=current;
        current=current->next;
    }
    if(current==NULL) {
        return;
    }
    if(prev!=NULL) {
        prev->next=current->next;
        printf("Food item deleted successfully!\n");
    }else {
        *head=current->next;
          printf("Food item deleted successfully!\n");
    }
    printf("Food item not found!\n");
    free(current);
}

void editfooditem(struct fooditem **head,int foodID) {
    struct fooditem *temp=*head;
    while (temp!=NULL) {
        if(temp->foodID==foodID) {
            printf("Input the new name of %s\n",temp->name);
            scanf("%[^\n]",temp->name);
            printf("Input new price %f\n");
            scanf("%f",&temp->price);
            printf("Input new quantity %d\n");
            scanf("%d",&temp->quantity);
            return;
        }
    temp=temp->next;
    }
    printf("Food item is not avaliable in FoodID\n");
    
}
void searchfooditem(struct fooditem *head,int foodID) {
        while(head!=NULL) {
            if (head->foodID==foodID) {
                printf("%s is avaliable at foodID %d\n",head->name,head->foodID);
                return;
            }
            head=head->next;
        }
    printf("Food item not found!\n");
    }


void displayitems(struct fooditem *head) {
   if(head!=NULL) {
     {
        printf("|----------|----------------------|------------|-----------|\n");
        printf("| %-8s | %-20s | %-10s | %-9s |\n", "FoodID", "Name", "Price (ksh)", "Quantity");
        printf("|----------|----------------------|------------|-----------|\n");
    }
   } else {
    printf("No food items available\n");
    return;
   }
   while(head!=NULL) {
     printf("| %-8d | %-20s | %-10.2f | %-9d |\n",head->foodID,head->name,head->price,head->quantity);
    head=head->next;
   }
   printf("|----------|----------------------|------------|-----------|\n");
}

void enqueue(customerqueue *queue,int customerId,char name[],float totalamount) {
    struct customer *newnode=(struct customer*)malloc(sizeof(struct customer));
    if(newnode!=NULL) {
    newnode->customerId=customerId;
    strcpy(newnode->name,name);
    newnode->totalamount=totalamount;
    newnode->next=NULL;
    }
    if(queue->front==NULL) {
        queue->front=queue->rear=newnode;
    }
    if(queue->rear!=NULL) {
        queue->rear->next=newnode;
        queue->rear=newnode;
    } 
}

void loadqueuefromfile(customerqueue *queue,const char *filename) {
    FILE *file=fopen(filename,"r");
        if(file==NULL) {
            printf("File does not exist!\n");
            return;
        }
    char inbuf[300];
    while(fgets(inbuf,sizeof(inbuf),file)) {
        char name[50];
        int customerId;
        float totalamount;

        if (sscanf(inbuf,"%d,%[^,],%f",&customerId,name,&totalamount)==3) {
            enqueue(queue,customerId,name,totalamount);
        }
    }
   fclose(file); 
}

void dequeue(customerqueue *queue) {
    if(queue->front==NULL) {
        printf("No order in the queue!\n");
        return;
    }
    customer *temp=queue->front;
    printf("\n=============================================================\n");
    printf("Processing CustomerId: %d - Customer: %s - Totalamount: %.2f\n", temp->customerId,temp->name,temp->totalamount);
    fflush(stdout);

    for (int i = 0; i < 25; ++i)
    {
        printf(".");
        fflush(stdout);
        Sleep(50);
    }

    printf("\n");
    printf("Processed CustomerId: %d -Customer: %s -Totalamount: %.2f\n", temp->customerId, temp->name, temp->totalamount);
    queue->front=queue->front->next;
    free(temp);
}

void displayqueue(customerqueue *queue) {
    if (queue->front != NULL)
    {
        printf("===============================================================================================\n");
        printf("| %-5s | %-20s | %-30s | %-20s |\n", "S.No.", "Customer ID", "Customer Name", "Total Amount");
        printf("==============================================================================================\n");

        customer* current = queue->front;
        int serialNumber = 1;
        while (current != NULL)
        {
            printf("| %-5d | %-20d | %-30s | KSh%-20.2f |\n", serialNumber,current->customerId, current->name, current->totalamount);
            current = current->next;
            serialNumber++;
        }

        printf("===============================================================================================\n");
    }
    else
    {
        printf("===================================================================================================\n");
        printf(" No Order queue\n");
        printf("===================================================================================================\n");
    }
}


