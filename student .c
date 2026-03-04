#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int roll;
    char name[50];
    float marks;
};

struct Student students[MAX_STUDENTS];
int count = 0;

// Function Prototypes
int searchStudent(int roll);
void clearInputBuffer();

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addStudent() {
    if (count >= MAX_STUDENTS) {
        printf("Error: Storage full! Cannot add more students.\n");
        return;
    }

    int roll;
    printf("\n-----------------------------------------\n");
    printf("            ADD NEW STUDENT              \n");
    printf("-----------------------------------------\n");
    
    printf("Enter Roll Number: ");
    scanf("%d", &roll);

    if (searchStudent(roll) != -1) {
        printf("Error: Roll Number %d already exists!\n", roll);
        return;
    }

    students[count].roll = roll;
    clearInputBuffer(); 

    printf("Enter Name: ");
    fgets(students[count].name, 50, stdin);
    students[count].name[strcspn(students[count].name, "\n")] = 0;

    printf("Enter Marks: ");
    scanf("%f", &students[count].marks);

    count++;
    printf(">> Student added successfully!\n");
}

void displayStudents() {
    if (count == 0) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n==============================================\n");
    printf("              ALL STUDENT RECORDS             \n");
    printf("==============================================\n");
    printf("%-10s %-25s %-10s\n", "ROLL NO", "NAME", "MARKS");
    printf("----------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d %-25s %-10.2f\n",
               students[i].roll,
               students[i].name,
               students[i].marks);
    }
    printf("==============================================\n");
}

int searchStudent(int roll) {
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            return i;
        }
    }
    return -1;
}

void updateStudent() {
    printf("\n-----------------------------------------\n");
    printf("             UPDATE STUDENT              \n");
    printf("-----------------------------------------\n");
    
    printf("Enter Roll Number to update: ");
    int roll;
    scanf("%d", &roll);

    int index = searchStudent(roll);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("\n[Current] Name: %s, Marks: %.2f\n",
           students[index].name,
           students[index].marks);

    clearInputBuffer();

    printf("Enter new Name: ");
    fgets(students[index].name, 50, stdin);
    students[index].name[strcspn(students[index].name, "\n")] = 0;

    printf("Enter new Marks: ");
    scanf("%f", &students[index].marks);

    printf(">> Record updated successfully!\n");
}

void deleteStudent() {
    printf("\n-----------------------------------------\n");
    printf("             DELETE STUDENT              \n");
    printf("-----------------------------------------\n");
    
    printf("Enter Roll Number to delete: ");
    int roll;
    scanf("%d", &roll);

    int index = searchStudent(roll);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;

    printf(">> Record deleted successfully!\n");
}

int main() {
    int choice;

    printf("\n==============================================\n");
    printf("       STUDENT RECORD MANAGEMENT SYSTEM       \n");
    printf("==============================================\n");

    do {
        printf("\n1. Add Student\n");
        printf("2. Display All Records\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("----------------------------------------------\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: addStudent();       break;
            case 2: displayStudents();  break;
            case 3: {
                printf("\n-----------------------------------------\n");
                printf("             SEARCH STUDENT              \n");
                printf("-----------------------------------------\n");
                printf("Enter Roll Number to search: ");
                int roll;
                scanf("%d", &roll);
                int idx = searchStudent(roll);
                
                if (idx != -1) {
                    printf("\n>> Record Found:\n");
                    printf("-----------------------------------------\n");
                    printf("Roll Number : %d\n", students[idx].roll);
                    printf("Name        : %s\n", students[idx].name);
                    printf("Marks       : %.2f\n", students[idx].marks);
                    printf("-----------------------------------------\n");
                } else {
                    printf(">> Student with Roll Number %d not found!\n", roll);
                }
                break;
            }
            case 4: updateStudent();    break;
            case 5: deleteStudent();    break;
            case 6: printf("\nExiting system... Thank you!\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}