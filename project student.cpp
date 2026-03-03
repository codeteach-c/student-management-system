#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    char course[50];
};

// Function prototypes
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while(1) {
        printf("\n=== Student Management System ===\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Add a new student
void addStudent() {
    struct Student s;
    FILE *fptr = fopen("students.dat", "ab");
    if(fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Course: ");
    scanf(" %[^\n]s", s.course);

    fwrite(&s, sizeof(s), 1, fptr);
    fclose(fptr);
    printf("Student added successfully!\n");
}

// View all students
void viewStudents() {
    struct Student s;
    FILE *fptr = fopen("students.dat", "rb");
    if(fptr == NULL) {
        printf("No students found!\n");
        return;
    }

    printf("\n--- Student List ---\n");
    while(fread(&s, sizeof(s), 1, fptr)) {
        printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\n\n", s.id, s.name, s.age, s.course);
    }
    fclose(fptr);
}

// Search student by ID
void searchStudent() {
    int id;
    struct Student s;
    FILE *fptr = fopen("students.dat", "rb");
    if(fptr == NULL) {
        printf("No students found!\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    int found = 0;
    while(fread(&s, sizeof(s), 1, fptr)) {
        if(s.id == id) {
            printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\n", s.id, s.name, s.age, s.course);
            found = 1;
            break;
        }
    }
    if(!found) printf("Student not found!\n");

    fclose(fptr);
}

// Update student
void updateStudent() {
    int id;
    struct Student s;
    FILE *fptr = fopen("students.dat", "rb+");
    if(fptr == NULL) {
        printf("No students found!\n");
        return;
    }

    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    int found = 0;
    while(fread(&s, sizeof(s), 1, fptr)) {
        if(s.id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]s", s.name);
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Course: ");
            scanf(" %[^\n]s", s.course);

            fseek(fptr, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fptr);
            printf("Student updated successfully!\n");
            found = 1;
            break;
        }
    }
    if(!found) printf("Student not found!\n");

    fclose(fptr);
}

// Delete student
void deleteStudent() {
    int id;
    struct Student s;
    FILE *fptr = fopen("students.dat", "rb");
    if(fptr == NULL) {
        printf("No students found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if(temp == NULL) {
        printf("Error creating temp file!\n");
        fclose(fptr);
        return;
    }

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    while(fread(&s, sizeof(s), 1, fptr)) {
        if(s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found) printf("Student deleted successfully!\n");
    else printf("Student not found!\n");
}