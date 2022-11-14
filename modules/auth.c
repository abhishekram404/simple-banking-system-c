#include <stdlib.h>
#include <stdio.h>


void login(){
    char email[100];
    char password[100];
    struct Customer customer;
    int found = 0;
    FILE *fp;
    char line[300];


    printf("=======Login=======\n");
    printf("===================\n");
    printf("\nEmail: ");
    scanf("%s", &email); // get email from user

    printf("\nPassword: ");
    scanf("%s", &password); // get password from user

    // open customers database file
    fp = fopen("customers.txt", "r");
    if(fp == NULL){
        printf("\nError opening file\n");
        exit(1);
    }

    // read each line from the file
    while(1){
        // if end of file is reached, break the loop
        if(feof(fp)){
            break;
        }

        // parse each line and store it in the customer struct
        sscanf(line, "%d %s %s %s %d %s %s %f %s", &customer.id, &customer.firstName, &customer.lastName, &customer.email, &customer.birthYear, &customer.address, &customer.phone, &customer.balance, &customer.password);
        
        // if email and password match, set found to 1 and break the loop
        if(strcmp(email, customer.email) == 0 && strcmp(password, customer.password) == 0){
            found = 1;
            break;
        }

        fgets(line, 300, fp);
    }

    // if found is 1, print success message
    if(found == 1){
        printf("\nLogin successful!\n");
    }else{
        // if found is 0, print error message
        printf("\nLogin failed!\n");
    }
    fclose(fp);
}