#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Student
{
    int id;
    char name[50];   // Restored string buffer size
    char course[30]; // Restored string buffer size
    int totalClasses;
    int attendedClasses;
};

struct Student students[MAX];
int count = 0;

// Function Prototypes
void addStudent();
void markAttendance();
void displayStudents();
void calculateAttendance();
void saveToFile();

int main()
{
    int choice;

    do
    {
        printf("\n====================================");
        printf("\n STUDENT ATTENDANCE TRACKING SYSTEM");
        printf("\n====================================");
        printf("\n1. Add Student");
        printf("\n2. Mark Attendance");
        printf("\n3. Display Records");
        printf("\n4. Calculate Attendance");
        printf("\n5. Save Records");
        printf("\n6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                markAttendance();
                break;

            case 3:
                displayStudents();
                break;

            case 4:
                calculateAttendance();
                break;

            case 5:
                saveToFile();
                break;

            case 6:
                printf("\nExiting Program...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 6);

    return 0;
}

// Add Student
void addStudent()
{
    if (count >= MAX) {
        printf("\nSystem Full! Cannot add more students.\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &students[count].id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", students[count].name);

    printf("Enter Course: ");
    scanf(" %[^\n]", students[count].course);

    students[count].totalClasses = 0;
    students[count].attendedClasses = 0;

    count++;

    printf("\nStudent Added Successfully!\n");
}

// Mark Attendance
void markAttendance()
{
    int id, present, i;
    int found = 0;

    printf("\nEnter Student ID: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++)
    {
        if(students[i].id == id)
        {
            found = 1;
            students[i].totalClasses++;

            printf("Present? (1 = Yes, 0 = No): ");
            scanf("%d", &present);

            if(present == 1)
            {
                students[i].attendedClasses++;
                printf("\nAttendance marked: Present\n");
            }
            else
            {
                printf("\nAttendance marked: Absent\n");
            }
            break;
        }
    }

    if (!found)
    {
        printf("\nStudent with ID %d not found!\n", id);
    }
}

// Display Records
void displayStudents()
{
    if (count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n--------------------------------------------------------------");
    printf("\n%-5s %-20s %-15s %-8s %-8s", "ID", "Name", "Course", "Total", "Attended");
    printf("\n--------------------------------------------------------------");
    for (int i = 0; i < count; i++)
    {
        printf("\n%-5d %-20s %-15s %-8d %-8d", 
               students[i].id, 
               students[i].name, 
               students[i].course, 
               students[i].totalClasses, 
               students[i].attendedClasses);
    }
    printf("\n--------------------------------------------------------------\n");
}

// Calculate Attendance Percentage
void calculateAttendance()
{
    if (count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n--- Attendance Summary ---");
    for (int i = 0; i < count; i++)
    {
        float percentage = 0.0;
        if (students[i].totalClasses > 0)
        {
            percentage = ((float)students[i].attendedClasses / students[i].totalClasses) * 100;
        }
        printf("\nID: %d | Name: %-15s | Percentage: %.2f%%", 
               students[i].id, students[i].name, percentage);
    }
    printf("\n--------------------------\n");
}

// Save Records to File
void saveToFile()
{
    FILE *file = fopen("attendance.txt", "w");
    if (file == NULL)
    {
        printf("\nError opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%s,%d,%d\n", 
                students[i].id, 
                students[i].name, 
                students[i].course, 
                students[i].totalClasses, 
                students[i].attendedClasses);
    }

    fclose(file);
    printf("\nRecords saved successfully to 'attendance.txt'!\n");
} 