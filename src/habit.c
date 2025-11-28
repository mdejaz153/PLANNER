#include <stdio.h>
#include <string.h>
#include "habit.h"

void addHabit() {
    FILE *fp = fopen("habits.txt", "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    char habit[50];
    printf("Enter habit name: ");
    scanf("%s", habit);

    fprintf(fp, "%s 0\n", habit);   // 0 = not completed
    fclose(fp);

    printf("Habit added successfully!\n");
}

void viewHabits() {
    FILE *fp = fopen("habits.txt", "r");
    if (!fp) {
        printf("No habits found.\n");
        return;
    }

    char habit[50];
    int completed;

    printf("\n--- Habit List ---\n");

    while (fscanf(fp, "%s %d", habit, &completed) != EOF) {
        printf("%s - %s\n", habit, completed ? "Completed" : "Pending");
    }

    fclose(fp);
}

void markCompleted() {
    FILE *fp = fopen("habits.txt", "r");
    if (!fp) {
        printf("No habits found.\n");
        return;
    }

    char habits[100][50];
    int completed[100];
    int count = 0;

    // Read all habits
    while (fscanf(fp, "%s %d", habits[count], &completed[count]) != EOF) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("No habits available.\n");
        return;
    }

    // Show habits
    printf("\n--- Select Habit to Mark Completed ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s (%s)\n", i + 1, habits[i], completed[i] ? "Completed" : "Pending");
    }

    int choice;
    printf("Enter number: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > count) {
        printf("Invalid choice.\n");
        return;
    }

    completed[choice - 1] = 1; // mark completed

    // Rewrite file
    fp = fopen("habits.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d\n", habits[i], completed[i]);
    }
    fclose(fp);

    printf("Habit marked as completed!\n");
}

void habitMenu() {
    int ch;

    do {
        printf("\n--- Habit Tracker ---\n");
        printf("1. Add Habit\n");
        printf("2. Mark Habit Completed\n");
        printf("3. View All Habits\n");
        printf("4. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: addHabit(); break;
            case 2: markCompleted(); break;
            case 3: viewHabits(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 4);
}
