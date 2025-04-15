#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t lock;
int balance=200;
int temp;

void *depositamnt(void *arg) {
   int amount=*(int *)arg;
   free(arg);
   pthread_mutex_lock(&lock);
   balance+=amount;
   printf("Deposited: %d | New amount: %d\n",amount,balance);
   pthread_mutex_unlock(&lock);
   return NULL;
}

int main() {
   pthread_t thread[50];
   int amount[50];
   int count=0;
   pthread_mutex_init(&lock,NULL);

   while(count<50) {
         int *tempamnt=malloc(sizeof(int)*100);
         if(tempamnt==NULL) {
            printf("Invalid memory access\n");
            break;
         }

         printf("Enter amount %d deposit: ",count+1);
         fflush(stdout);
         if(scanf("%d",tempamnt)!=1) {
            printf("Non integer detected. Exiting prompt...\n");
            free(tempamnt);
            break;
         }
         
         if(*tempamnt==-1) {
            printf("integer(-1) detected. Exiting prompt...\n");
            free(tempamnt);
            break;
         }
         pthread_create(&thread[count],NULL,depositamnt,tempamnt);
          pthread_join(thread[count],NULL);
         count++;
   }
   

   printf("Final balance: %d\n",balance);
   pthread_mutex_destroy(&lock);
return 0;
}