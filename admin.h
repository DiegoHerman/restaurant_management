#ifndef ADMIN_H
#define ADMIN_H
 typedef struct customer{
    int customerId;
    char name[50];
    float totalamount;
    struct customer *next;
}customer;

typedef struct{
    customer *front;
    customer *rear;
}customerqueue;

struct fooditem {
    int foodID;
    char name[50];
    float price;
    int quantity;
    struct fooditem *next;
};


void addfooditem(struct fooditem **head,int foodID,char name[],float price, int quantity);
void deletefooditem(struct fooditem **head,int foodID);
void editfooditem(struct fooditem **head,int foodID);
void searchfooditem(struct fooditem *head,int foodID);
void displayitems(struct fooditem *head);

void enqueue(customerqueue *queue,int customerId,char name[],float totalamount);
void loadqueuefromfile(customerqueue *queue,const char *filename);
void dequeue(customerqueue *queue);
void displayqueue(customerqueue *queue);

#endif