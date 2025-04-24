#include <stdio.h>
#include <string.h>
#include "authentication.h"

int choice=0;//global var
typedef struct{
    char username[30];
    char password[30];  
} user;

user users[] ={
    {"admin","admin123"},
    {"user","user123"}
};

int login(){
    char username[30],password[30];
    printf("Enter Username  : ");
    scanf("%s",username);
    printf("Enter password: ");
    scanf("%s",password);


for (int i=0; i<sizeof(users)/sizeof(users); i++){
    if (strcmp(username, users[i].username)==0&&
        strcmp(password, users[i].password) ==0){
        printf("Login successfully!\n");
        choice=1;
        return 0;
        }
}
printf("Invalid credentials.\n");
return -1;//for failed login
}
