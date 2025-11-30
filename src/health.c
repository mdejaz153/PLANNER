#include <stdio.h>
#include <time.h>
#include "health.h"

void addHealth() {
    FILE *fp = fopen("health.txt", "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    int steps, calories;

    printf("Enter steps walked: ");
    scanf("%d", &steps);
    
    printf("Enter calories consumed: ");
    scanf("%d", &calories);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    int day = tm->tm_mday;
    int month = tm->tm_mon + 1;
    int year = tm->tm_year + 1900;

    fprintf(fp, "%d %d %d %d %d\n", steps, calories, day, month, year);
    fclose(fp);

    printf("Health entry added successfully!\n");
}

void viewHealth() {
    FILE *fp = fopen("health.txt", "r");
    if (!fp) {
        printf("No health data found.\n");
        return;
    }

    int steps, calories, day, month, year;

    printf("\n--- Health Log ---\n");

    while (fscanf(fp, "%d %d %d %d %d", &steps, &calories, &day, &month, &year) != EOF) {
        printf("Steps: %d | Calories: %d | Date: %d-%d-%d\n",
               steps, calories, day, month, year);
    }

    fclose(fp);
}

void dailySummary() {
    FILE *fp = fopen("health.txt", "r");
    if (!fp) {
        printf("No health data available.\n");
        return;
    }

    int steps, calories, day, month, year;
    int totalSteps = 0, totalCalories = 0;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    int cday = tm->tm_mday;
    int cmonth = tm->tm_mon + 1;
    int cyear = tm->tm_year + 1900;

    while (fscanf(fp, "%d %d %d %d %d",
                  &steps, &calories, &day, &month, &year) != EOF) {

        if (day == cday && month == cmonth && year == cyear) {
            totalSteps += steps;
            totalCalories += calories;
        }
    }

    fclose(fp);

    printf("\n--- Today's Summary ---\n");
    printf("Total Steps: %d\n", totalSteps);
    printf("Total Calories: %d\n", totalCalories);
}

void healthMenu() {
    int ch;

    do {
        printf("\n--- Health Tracker ---\n");
        printf("1. Add Health Entry\n");
        printf("2. View Health Log\n");
        printf("3. Today's Summary\n");
        printf("4. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addHealth(); break;
            case 2: viewHealth(); break;
            case 3: dailySummary(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }

    } while (ch != 4);
}
