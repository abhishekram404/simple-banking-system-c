#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct to represent a customer
struct customer {
    int id;
    char name[50];
    double balance;
};

// Struct to represent a transaction
struct transaction {
    int from_id;
    int to_id;
    double amount;
};

// Global variables
struct customer customers[100];
int num_customers = 0;
struct transaction transactions[1000];
int num_transactions = 0;

// Function to read customer data from file
void read_customer_data() {
    FILE *f = fopen("customers.txt", "r");
    if (f == NULL) {
        printf("Error: could not read customer data from file\n");
        exit(1);
    }

    fscanf(f, "%d\n", &num_customers);
    for (int i = 0; i < num_customers; i++) {
        fscanf(f, "%d,%[^,],%lf\n", &customers[i].id, customers[i].name, &customers[i].balance);
    }

    fclose(f);
}

// Function to write customer data to file
void write_customer_data() {
    FILE *f = fopen("customers.txt", "w");
    if (f == NULL) {
        printf("Error: could not write customer data to file\n");
        exit(1);
    }

    fprintf(f, "%d\n", num_customers);
    for (int i = 0; i < num_customers; i++) {
        fprintf(f, "%d,%s,%.2lf\n", customers[i].id, customers[i].name, customers[i].balance);
    }

    fclose(f);
}

// Function to read transaction data from file
void read_transaction_data() {
    FILE *f = fopen("transactions.txt", "r");
    if (f == NULL) {
        printf("Error: could not read transaction data from file\n");
        exit(1);
    }

    fscanf(f, "%d\n", &num_transactions);
    for (int i = 0; i < num_transactions; i++) {
        fscanf(f, "%d,%d,%lf\n", &transactions[i].from_id, &transactions[i].to_id, &transactions[i].amount);
    }

    fclose(f);
}

// Function to write transaction data to file
void write_transaction_data() {
    FILE *f = fopen("transactions.txt", "w");
    if (f == NULL) {
        printf("Error: could not write transaction data to file\n");
        exit(1);
    }

    fprintf(f, "%d\n", num_transactions);
    for (int i = 0; i < num_transactions; i++) {
        fprintf(f, "%d,%d,%.2lf\n", transactions[i].from_id, transactions[i].to_id, transactions[i].amount);
    }

    fclose(f);
}

// Function to generate a new customer ID
int generate_customer_id() {
    int max_id = 0;
    for (int i = 0; i < num_customers; i++) {
        if (customers[i].id > max_id) {
            max_id = customers[i].id;
        }
    }
    return max_id + 1;
}

// Function to register a new customer
void register_customer() {
    // Get customer name and balance
    char name[50];
    double balance;
    printf("Enter customer name: ");
    scanf("%s", name);
    printf("Enter initial balance: ");
    scanf("%lf", &balance);

    // Generate new customer ID
int id = generate_customer_id();

// Add new customer to array
customers[num_customers].id = id;
strcpy(customers[num_customers].name, name);
customers[num_customers].balance = balance;

// Increment number of customers
num_customers++;

// Write customer data to file
write_customer_data();

printf("Customer registered successfully\n");

}

// Function to display all customers
void display_customers() {
printf("Customers:\n");
for (int i = 0; i < num_customers; i++) {
printf("%d,%s,%.2lf\n", customers[i].id, customers[i].name, customers[i].balance);
}
}

// Function to find a customer by ID
int find_customer(int id) {
for (int i = 0; i < num_customers; i++) {
if (customers[i].id == id) {
return i;
}
}
return -1;
}

// Function to perform a transaction between two customers
void perform_transaction() {
// Get IDs of customers involved in transaction
int from_id, to_id;
printf("Enter ID of customer making the transfer: ");
scanf("%d", &from_id);
printf("Enter ID of customer receiving the transfer: ");
scanf("%d", &to_id);
// Find customers by ID
int from_index = find_customer(from_id);
int to_index = find_customer(to_id);
if (from_index == -1 || to_index == -1) {
    printf("Error: could not find customers with the specified IDs\n");
    return;
}

// Get amount of transfer
double amount;
printf("Enter amount to transfer: ");
scanf("%lf", &amount);

// Check if customer has sufficient funds
if (customers[from_index].balance < amount) {
    printf("Error: customer does not have sufficient funds for transfer\n");
    return;
}

// Update customer balances
customers[from_index].balance -= amount;
customers[to_index].balance += amount;

// Add new transaction to array
transactions[num_transactions].from_id = from_id;
transactions[num_transactions].to_id = to_id;
transactions[num_transactions].amount = amount;

// Increment number of transactions
num_transactions++;

// Write customer and transaction data to file
write_customer_data();
write_transaction_data();

printf("Transaction completed successfully\n");
}

// Function to modify a customer's name or balance
void modify_customer() {
// Get customer ID
int id;
printf("Enter ID of customer to modify: ");
scanf("%d", &id);
// Find customer by ID
int index = find_customer(id);
if (index == -1) {
    printf("Error: could not find customer with the specified ID\n");
    return;
}

// Get new name and balance
char name[50];
double balance;
printf("Enter new name (press enter to skip): ");
scanf("%s", name);
printf("Enter new balance (press 0 to skip): ");
scanf("%lf", &balance);

// Modify customer data
if (strcmp(name, "") != 0) {
    strcpy(customers[index].name, name);
}
if (balance != 0) {
    customers[index].balance = balance;
}

// Write customer data to file
write_customer_data();

printf("Customer modified successfully\n");
}

// Function to delete a customer and all associated transactions
void delete_customer() {
// Get customer ID
int id;
printf("Enter ID of customer to delete: ");
scanf("%d", &id);

// Find customer by ID
int index = find_customer(id);
if (index == -1) {
    printf("Error: could not find customer with the specified ID\n");
    return;
}

// Delete customer and associated transactions
for (int i = index; i < num_customers - 1; i++) {
    customers[i] = customers[i + 1];
}
num_customers--;
delete_transactions(id);

// Write customer and transaction data to file
write_customer_data();
write_transaction_data();

printf("Customer deleted successfully\n");
}

// Function to delete all transactions involving a given customer
void delete_transactions(int id) {
for (int i = 0; i < num_transactions; i++) {
if (transactions[i].from_id == id || transactions[i].to_id == id) {
for (int j = i; j < num_transactions - 1; j++) {
transactions[j] = transactions[j + 1];
}
num_transactions--;
i--;
}
}
}

// Main function
int main() {
// Load data from file
read_customer_data();
read_transaction_data();
// Login
int attempts = 0;
while (1) {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Login successful\n");
        break;
    } else {
        attempts++;
        if (attempts == 3) {
            printf("Too many login attempts, exiting\n");
            return 0;
        } else {
            printf("Invalid username or password, please try again\n");
        }
    }
}

// Menu loop
while (1) {
    printf("\n1. Register new customer\n");
    printf("2. Display all customers\n");
    printf("3. Perform transaction between customers\n");
    printf("4. Modify customer information\n");
    printf("5. Delete customer\n");
    printf("6. Exit\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            register_customer();
            break;
        case 2:
            display_customers();
            break;
        case 3:
            perform_transaction();
            break;
        case 4:
            modify_customer();
            break;
        case 5:
            delete_customer();
            break;
        case 6:
            return 0;
        default:
            printf("Invalid choice\n");
    }
}
}