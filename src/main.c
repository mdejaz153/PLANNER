#include <stdio.h>
#include "expense.h"
#include "habit.h"
#include "health.h"
#include "study.h"
#include "reminder.h"

int main() {
    int choice;

    do {
        printf("\n===== PERSONAL LIFE MANAGEMENT SYSTEM =====\n");
        printf("1. Expense Tracker\n");
        printf("2. Habit Tracker\n");
        printf("3. Health Tracker\n");
        printf("4. Study Tracker\n");
        printf("5. Reminder System\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: expenseMenu(); break;
            case 2: habitMenu(); break;
            case 3: healthMenu(); break;
            case 4: studyMenu(); break;
            case 5: reminderMenu(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }

    } while(choice != 6);

    return 0;
}
