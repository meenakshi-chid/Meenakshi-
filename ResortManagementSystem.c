#include <stdio.h>
#include <string.h>
#define Room 10
typedef struct {
    int roomNo;
    char name[50];
    char phone[11];
    int members;
    int days;
    float bill;
    int age;
} customer;
customer customers[Room];
int validnumber(char phone[]) {
    if (strlen(phone) != 10) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return 0;
        }
    }
    return 1;
}
void availableRooms() {
    customer c;
    FILE *fp;
    int room, found;
    int occupied[Room] = {0};
    fp = fopen("Datas.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d %s %d %s %d %d %f", &c.roomNo, c.name, &c.age, c.phone, &c.members, &c.days, &c.bill) == 7) {
            if (c.roomNo >= 101 && c.roomNo <= 110) 
                occupied[c.roomNo - 101] = 1;
        }
        fclose(fp);
    }
    printf("\n===== AVAILABLE ROOMS =====\n");
    for (room = 101; room <= 110; room++) {
        if (!occupied[room - 101]) {
            printf("Room %d\n", room);
        }
    }
}
void checkIn()
{
    customer c,temp;
    FILE *fp;
    fp = fopen("Datas.txt", "a+");
    if(fp == NULL)
    {
        printf("File not found.\n");
        return;
    }
    printf("Enter Room Number: ");
    scanf("%d", &c.roomNo);
    rewind(fp);
    while(fscanf(fp, "%d %s %d %s %d %d %f", &temp.roomNo, temp.name, &temp.age, temp.phone, &temp.members,&temp.days, &temp.bill) == 7)
    {
        if(temp.roomNo == c.roomNo)
        {
            printf("Room %d is already occupied!\n", c.roomNo);
            fclose(fp);
            return;
        }
    }
    printf("Enter Name: ");
    scanf(" %49[^\n]", c.name);
    printf("Enter Age: ");
    scanf("%d", &c.age);
    printf("Enter Phone: ");
    scanf("%10s", c.phone);
    if(!validnumber(c.phone))
    {
        printf("Invalid Number!\n");
        fclose(fp);
        return;
    }
    printf("Enter Members: ");
    scanf("%d", &c.members);
    printf("Enter Days: ");
    scanf("%d", &c.days);
    c.bill = c.days * 2500;
    fprintf(fp, "%d %s %d %s %d %d %.2f\n", c.roomNo, c.name, c.age, c.phone, c.members, c.days, c.bill);
    fclose(fp);
    printf("Customer Checked In Successfully.\n");
}
void displayDetails() {
    customer c;
    FILE *fp ;
    fp=fopen("Datas.txt", "r");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }
    printf("\n===== Customer Details =====\n");
    while (fscanf(fp, "%d %s %d %s %d %d %f", &c.roomNo, c.name, &c.age, c.phone, &c.members, &c.days, &c.bill) == 7) {
        printf("\nRoom No : %d\n", c.roomNo);
        printf("Name    : %s\n", c.name);
        printf("Age     : %d\n", c.age);
        printf("Phone   : %s\n", c.phone);
        printf("Members : %d\n", c.members);
        printf("Days    : %d\n", c.days);
        printf("Bill    : %.2f\n", c.bill);
    }
    fclose(fp);
}
void searchCustomer() {
    customer c;
    FILE *fp;
    fp= fopen("Datas.txt", "r");
    int room, found = 0;
    if (fp == NULL) {
        printf("File Not Found!\n");
        return;
    }
    printf("Enter Room Number to Search: ");
    scanf("%d", &room);
    while (fscanf(fp, "%d %s %d %s %d %d %f", &c.roomNo, c.name, &c.age, c.phone, &c.members, &c.days, &c.bill) == 7) {
        if (c.roomNo == room) {
            found = 1;
            printf("\n===== Customer Details =====\n");
            printf("Room No : %d\n", c.roomNo);
            printf("Name    : %s\n", c.name);
            printf("Age     : %d\n", c.age);
            printf("Phone   : %s\n", c.phone);
            printf("Members : %d\n", c.members);
            printf("Days    : %d\n", c.days);
            printf("Bill    : %.2f\n", c.bill);
            break;
        }
    }
    if (!found)
        printf("Customer Not Found!\n");
    fclose(fp);
}
void updateCustomer() {
    customer c;
    FILE *fp ;
    fp= fopen("Datas.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");
    int room, found = 0;
    if (fp == NULL) {
        printf("File Not Found!\n");
        return;
    }
    printf("Enter Room Number to Update: ");
    scanf("%d", &room);
    while (fscanf(fp, "%d %s %d %s %d %d %f", &c.roomNo, c.name, &c.age, c.phone, &c.members, &c.days, &c.bill) == 7) {
        if (c.roomNo == room) {
            found = 1;
            printf("Enter New Name: ");
            scanf(" %[^\n]", c.name);
            printf("Enter New Age: ");
            scanf("%d", &c.age);
            printf("Enter New Phone: ");
            scanf("%s", c.phone);
            printf("Enter New Members: ");
            scanf("%d", &c.members);
            printf("Enter New Days: ");
            scanf("%d", &c.days);
            c.bill = c.days * 2500;
        }
        fprintf(temp, "%d %s %d %s %d %d %.2f\n", c.roomNo, c.name, c.age, c.phone, c.members, c.days, c.bill);
    }
    fclose(fp);
    fclose(temp);
    remove("Datas.txt");
    rename("Temp.txt", "Datas.txt");
    if (found)
        printf("Customer Updated Successfully.\n");
    else
        printf("Customer Not Found.\n");
}
void checkOut() {
    customer c;
    FILE *fp;
    fp = fopen("Datas.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");
    int room, found = 0;
    if (fp == NULL) {
        printf("File Not Found!\n");
        return;
    }
    printf("Enter Room Number to Check Out: ");
    scanf("%d", &room);
    while (fscanf(fp, "%d %s %d %s %d %d %f", &c.roomNo, c.name, &c.age, c.phone, &c.members, &c.days, &c.bill) == 7) {
        if (c.roomNo == room) {
            found = 1;
            printf("Customer Checked Out Successfully.\n");
        } else {
            fprintf(temp, "%d %s %d %s %d %d %.2f\n", c.roomNo, c.name, c.age, c.phone, c.members, c.days, c.bill);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("Datas.txt");
    rename("Temp.txt", "Datas.txt");
    if (!found)
        printf("Customer Not Found!\n");
}
int main() {
    int choice;
    do {
        printf("\n========== HOTEL MANAGEMENT SYSTEM ==========\n");
        printf("1. Check In\n");
        printf("2. Display Details\n");
        printf("3. Search Customer\n");
        printf("4. Update Customer\n");
        printf("5. Check Out\n");
        printf("6. Available Rooms\n");
        printf("7. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) 
            checkIn();
        else if (choice == 2)
            displayDetails();
        else if (choice == 3)
            searchCustomer();
        else if (choice == 4)
            updateCustomer();
        else if (choice == 5)
            checkOut();
        else if (choice == 6)
            availableRooms();
        else if (choice == 7)
            printf("Thank You!\n");
        else 
            printf("Invalid Choice!\n");
    } while (choice != 7);
    return 0;
}
