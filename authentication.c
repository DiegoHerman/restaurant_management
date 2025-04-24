#include <stdio.h>
#include <string.h>
#include "authentication.h"

typedef struct{
    char username[30];
    char password[30];
    int  choose; //1 for admin and 0 for local user access
} user;

user users[] ={
    {"admin","admin123",1},
    {"user","user123",0}
}

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
        return users[i].choose;
        }
}
printf("Invalid credentials.\n");
return -1;//for failed login
}
 int main(){
    int access;
    do{
        access=login();
    } while (access==-1);//continue looping  to the login pert if login failed
    
     if (access== 1){
        printf("Welcome Admin!\n");//this grants access to the admin
     }else {
        printf("Welcome User!\n");//this grants access to the user

    }
 
 return 0;   
}
    
    


 