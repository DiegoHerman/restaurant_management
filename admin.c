#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "menu.h"

struct addnodequeue {
    int data;
    struct addnodequeue *next;
};

struct fooditem {
    int foodID;
    char name[50];
    float price;
    int quantity;
    struct fooditem *next;
};

struct fooditem *head=NULL;

struct fooditem *createfooditem(int foodID,char name[],float price, int quantity) {
    struct fooditem* newnode=(struct foodname *)malloc(sizeof(struct fooditem));
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
    struct fooditem *temp=*head;
    if(temp==NULL) {
        return;
    }
    while(temp->next!=NULL) {
        temp=temp->next;
    }
    temp->next=newnode;
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
        printf("|--------|----------------------|------------|-----------|\n");
    }
   } else {
    printf("No food items availablen\n");
    return;
   }
   while(head!=NULL) {
     printf("| %-8d | %-20s | %-10.2f | %-9d |\n",head->foodID,head->name,head->price,head->quantity);
    head=head->next;
   }
   printf("|----------|----------------------|------------|-----------|\n");
}

