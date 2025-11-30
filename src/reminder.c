// Reminder Module - Stores reminder title, date, and time

#include <stdio.h>
#include <string.h>
#include "reminder.h"

// Adds a reminder
void addReminder() {
    FILE *fp = fopen("reminders.txt", "a");
    if (!fp) {
        printf("Error opening reminders file.\n");
        return;
    }

    char title[100];
    char date[20];
    char time[20];

    printf("Enter reminder title: ");
    scanf(" %[^\n]s", title);

    printf("Enter date (DD-MM-YYYY): ");
    scanf("%s", date);

    printf("Enter time (HH:MM): ");
    scanf("%s", time);

    // Store reminder in file
    fprintf(fp, "%s | %s | %s\n", title, date, time);
    fclose(fp);

    printf("Reminder added successfully!\n");
}

// Displays all reminders
void viewReminders() {
    FILE *fp = fopen("reminders.txt", "r");
    if (!fp) {
        printf("No reminders found.\n");
        return;
    }

    char line[200];

    printf("\n--- Reminder List ---\n");

    // Print each reminder line
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

// Reminder menu controller
void reminderMenu() {
    int ch;

    do {
        printf("\n--- Reminder System ---\n");
        printf("1. Add Reminder\n");
        printf("2. View All Reminders\n");
        printf("3. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addReminder(); break;
            case 2: viewReminders(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 3);
}
