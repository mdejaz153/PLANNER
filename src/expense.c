// Expense Module - Handles adding, viewing, and summarizing expenses

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "expense.h"

// Adds a new expense entry to expenses.txt
void addExpense() {
    FILE *fp = fopen("expenses.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    char item[50];
    float amount;

    printf("Enter expense name: ");
    scanf("%s", item);
    printf("Enter amount: ");
    scanf("%f", &amount);

    // Get current month & year from system
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    int month = tm_info->tm_mon + 1;
    int year = tm_info->tm_year + 1900;

    // Store expense entry
    fprintf(fp, "%s %.2f %d %d\n", item, amount, month, year);
    fclose(fp);

    printf("Expense added successfully!\n");
}

// Displays all saved expenses
void viewExpenses() {
    FILE *fp = fopen("expenses.txt", "r");
    if (!fp) {
        printf("No expenses found!\n");
        return;
    }

    char item[50];
    float amount;
    int month, year;

    printf("\n--- All Expenses ---\n");

    while (fscanf(fp, "%s %f %d %d", item, &amount, &month, &year) != EOF) {
        printf("%s - ₹%.2f (Month: %d, Year: %d)\n", item, amount, month, year);
    }

    fclose(fp);
}

// Shows total expense for current month
void monthlySummary() {
    FILE *fp = fopen("expenses.txt", "r");
    if (!fp) {
        printf("No data found!\n");
        return;
    }

    float total = 0;
    char item[50];
    float amount;
    int month, year;

    // Get system month & year
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    int currentMonth = tm_info->tm_mon + 1;
    int currentYear = tm_info->tm_year + 1900;

    // Sum all expenses of current month
    while (fscanf(fp, "%s %f %d %d", item, &amount, &month, &year) != EOF) {
        if (month == currentMonth && year == currentYear) {
            total += amount;
        }
    }

    fclose(fp);

    printf("\n--- Monthly Summary (%d/%d) ---\n", currentMonth, currentYear);
    printf("Total expenses: ₹%.2f\n", total);
}

// Expense menu controller
void expenseMenu() {
    int choice;

    do {
        printf("\n--- Expense Tracker ---\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Monthly Summary\n");
        printf("4. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: monthlySummary(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);
}
