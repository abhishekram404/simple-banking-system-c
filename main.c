#include <stdio.h>
#include <stdlib.h>
#include "modules/id.c"
#include "modules/customer.c"   
#include "modules/auth.c"
#include "modules/menu.c"
void main(){
    int choice;
    showMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            registerCustomer();
            break;
        case 2:
            login();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Invalid choice");
    }

printf("\nPress ENTER to exit");
char a;
scanf("%c", &a);

}
