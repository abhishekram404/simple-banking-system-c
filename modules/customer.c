#include <stdio.h>
#include <stdlib.h>
#include "id.h"

int generateId();
void registerCustomer();


// customer struct
struct Customer{
    int id;
    char firstName[20];
    char lastName[20];
    char email[50];
    int birthYear;
    char address[100];
    char phone[20];
    float balance;
    char password[20];
};


void registerCustomer(){
    struct Customer customer;
    printf("Enter your first name: ");
    scanf("%s", &customer.firstName);
    printf("Enter your last name: ");
    scanf("%s", &customer.lastName);
    printf("Enter your email: ");
    scanf("%s", &customer.email);
    printf("Enter your birth year: ");
    scanf("%d", &customer.birthYear);
    printf("Enter your address: ");
    scanf("%s", &customer.address);
    printf("Enter your phone: ");
    scanf("%s", &customer.phone);
    printf("Create a strong password: ");
    scanf("%s", &customer.password);
    
    customer.id = generateId();
    customer.balance = 0;

    system("cls");
    printf("Your account has been created successfully!\n");

    printf("Your account details:\n");
    
    printf("ID: %d \n", customer.id);
    printf("First name: %s \n", customer.firstName);
    printf("Last name: %s \n", customer.lastName);
    printf("Email: %s \n", customer.email);
    printf("Birth year: %d \n", customer.birthYear);
    printf("Address: %s \n", customer.address);
    printf("Phone: %s \n", customer.phone);
    printf("Balance: %.2f \n", customer.balance);


    FILE *fptr;
    fptr = fopen("customers.dat", "a");
    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }
    fprintf(fptr, "%d %s %s %s %d %s %s %.2f %s \n", customer.id, customer.firstName, customer.lastName, customer.email, customer.birthYear, customer.address, customer.phone, customer.balance, customer.password);
    fclose(fptr);
}