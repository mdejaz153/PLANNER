// Study Module - Tracks subjects studied and hours spent

#include <stdio.h>
#include <time.h>
#include "study.h"

// Adds a study entry (subject + hours)
void addStudy() {
    FILE *fp = fopen("study.txt", "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    char subject[50];
    int hours;

    printf("Enter subject: ");
    scanf("%s", subject);

    printf("Enter hours studied: ");
    scanf("%d", &hours);

    // Get today's date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    int day = tm->tm_mday;
    int month = tm->tm_mon + 1;
    int year = tm->tm_year + 1900;

    // Save entry
    fprintf(fp, "%s %d %d %d %d\n", subject, hours, day, month, year);
    fclose(fp);

    printf("Study session added successfully!\n");
}

// Displays complete study log
void viewStudy() {
    FILE *fp = fopen("study.txt", "r");
    if (!fp) {
        printf("No study records found.\n");
        return;
    }

    char subject[50];
    int hours, day, month, year;

    printf("\n--- Study Log ---\n");

    while (fscanf(fp, "%s %d %d %d %d",
                  subject, &hours, &day, &month, &year) != EOF) {
        printf("Subject: %s | Hours: %d | Date: %d-%d-%d\n",
               subject, hours, day, month, year);
    }

    fclose(fp);
}

// Shows today's total study hours
void studySummary() {
    FILE *fp = fopen("study.txt", "r");
    if (!fp) {
        printf("No study data found.\n");
        return;
    }

    char subject[50];
    int hours, day, month, year;
    int totalHours = 0;

    // Get current date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    int cday = tm->tm_mday;
    int cmonth = tm->tm_mon + 1;
    int cyear = tm->tm_year + 1900;

    // Add today's hours
    while (fscanf(fp, "%s %d %d %d %d",
                  subject, &hours, &day, &month, &year) != EOF) {
        if (day == cday && month == cmonth && year == cyear) {
            totalHours += hours;
        }
    }

    fclose(fp);

    printf("\n--- Today's Study Summary ---\n");
    printf("Total Hours Studied: %d\n", totalHours);
}

// Study menu controller
void studyMenu() {
    int ch;

    do {
        printf("\n--- Study Tracker ---\n");
        printf("1. Add Study Session\n");
        printf("2. View Study Log\n");
        printf("3. Today's Study Summary\n");
        printf("4. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: addStudy(); break;
            case 2: viewStudy(); break;
            case 3: studySummary(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }

    } while(ch != 4);
}
