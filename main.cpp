#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Constants
#define MAX_ORDERS 100
#define DELIVERY_TIME 5 // Delivery time for each car in months
// Structures
struct Date {
int day, month, year;
};
struct Car {
char color[20];
struct Date deliveryDate;
};
struct Order {
char customerID[11]; // 5 digits + 5 alphabets + '\0'
char name[50];
char dob[11]; // DD-MM-YYYY format
char model[20];
char variant[20];
struct Car car;
struct Date orderDate;
};
// Global variable to keep track of the front of the queue
int front = 0;
// Function prototypes
void generateCustomerID(char customerID[]);
void placeOrder(struct Order orders[], int *numOrders);
void checkOrderStatus(const struct Order orders[], int numOrders);
void cancelOrder(struct Order orders[], int *numOrders);
void displayMenu();
void processOrders(struct Order orders[], int *numOrders);
int main() {
struct Order orders[MAX_ORDERS];
int numOrders = 0;
int choice;
do {
displayMenu();
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
placeOrder(orders, &numOrders);
break;
case 2:
checkOrderStatus(orders, numOrders);
break;
case 3:
cancelOrder(orders, &numOrders);
break;
case 4:
printf("Exiting the program.\n");
break;
default:
printf("Invalid choice. Please enter a valid option.\n");
}
// Process orders after each action
processOrders(orders, &numOrders);
} while (choice != 4);
return 0;
}
void generateCustomerID(char customerID[]) {
// Code to generate a random customer ID
// This is a simplified version; you may need a more sophisticated approach
srand(time(NULL));
sprintf(customerID, "%05d", rand() % 100000); // 5-digit number
strcat(customerID, "-");
for (int i = 0; i < 5; ++i) {
char randomChar = 'A' + rand() % 26;
strncat(customerID, &randomChar, 1);
}
}
void placeOrder(struct Order orders[], int *numOrders) {
if (*numOrders < MAX_ORDERS) {
struct Order newOrder;
// Get customer details
printf("Enter customer name: ");
scanf("%s", newOrder.name);
printf("Enter customer date of birth (DD-MM-YYYY): ");
scanf("%s", newOrder.dob);
printf("Enter car model: ");
scanf("%s", newOrder.model);
printf("Enter car variant: ");
scanf("%s", newOrder.variant);
printf("Enter car color: ");
scanf("%s", newOrder.car.color);
// Generate customer ID
generateCustomerID(newOrder.customerID);
// Set order date
time_t t = time(NULL);
struct tm tm = *localtime(&t);
newOrder.orderDate.day = tm.tm_mday;
newOrder.orderDate.month = tm.tm_mon + 1;
newOrder.orderDate.year = tm.tm_year + 1900;
// Set delivery date
newOrder.car.deliveryDate.day = newOrder.orderDate.day;
newOrder.car.deliveryDate.month = newOrder.orderDate.month + (*numOrders) *
DELIVERY_TIME; // Delivery after (5 * numOrders) months
newOrder.car.deliveryDate.year = newOrder.orderDate.year;
// Add order to the list
orders[*numOrders] = newOrder;
(*numOrders)++;
printf("Order placed successfully. Customer ID: %s\n", newOrder.customerID);
} else {
printf("Order limit reached. Cannot place more orders.\n");
}
}
void checkOrderStatus(const struct Order orders[], int numOrders) {
char searchID[11];
printf("Enter customer ID to check order status: ");
scanf("%s", searchID);
for (int i = 0; i < numOrders; ++i) {
if (strcmp(orders[i].customerID, searchID) == 0) {
printf("Order Details:\n");
printf("Customer ID: %s\n", orders[i].customerID);
printf("Name: %s\n", orders[i].name);
printf("DOB: %s\n", orders[i].dob);
printf("Car Model: %s\n", orders[i].model);
printf("Car Variant: %s\n", orders[i].variant);
printf("Car Color: %s\n", orders[i].car.color);
printf("Order Date: %02d-%02d-%04d\n", orders[i].orderDate.day, orders[i].orderDate.month,
orders[i].orderDate.year);
printf("Delivery Date: %02d-%02d-%04d\n", orders[i].car.deliveryDate.day,
orders[i].car.deliveryDate.month, orders[i].car.deliveryDate.year);
// Calculate time left for delivery
time_t t = time(NULL);
struct tm tm = *localtime(&t);
int daysLeft = (orders[i].car.deliveryDate.year - 1900 - tm.tm_year) * 365 +
(orders[i].car.deliveryDate.month - 1 - tm.tm_mon) * 30 +
(orders[i].car.deliveryDate.day - tm.tm_mday);
printf("Time left for delivery: %d days\n", daysLeft);
return;
}
}
printf("Customer ID not found. Please check the ID and try again.\n");
}
void cancelOrder(struct Order orders[], int *numOrders) {
char cancelID[11];
printf("Enter customer ID to cancel the order: ");
scanf("%s", cancelID);
for (int i = 0; i < *numOrders; ++i) {
if (strcmp(orders[i].customerID, cancelID) == 0) {
// Mark the order as canceled
orders[i].customerID[0] = '\0';
printf("Order canceled successfully.\n");
return;
}
}
printf("Customer ID not found. Please check the ID and try again.\n");
}
void displayMenu() {
printf("\nVehicleHub Order Management System\n");
printf("1. Place Order\n");
printf("2. Check Order Status\n");
printf("3. Cancel Order\n");
printf("4. Exit\n");
}
void processOrders(struct Order orders[], int *numOrders) {
// Code to simulate the progress of orders
// In this simplified version, we only increment the delivery date by DELIVERY_TIME months for
//each order
for (int i = front; i < *numOrders; ++i) {
if (orders[i].customerID[0] != '\0') {
orders[i].car.deliveryDate.month += DELIVERY_TIME;
}
}
}