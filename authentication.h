#ifndef AUTH_H  
#define AUTH_H    

typedef struct{
    char username[30];
    char password[30];  
} user;

user users[] ={
    {"admin","admin123"},
    {"user","user123"}
};
int login();       // Function declaration
#endif        