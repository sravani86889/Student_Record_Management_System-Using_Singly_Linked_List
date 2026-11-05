#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int id;
    char name[30];
    int marks;
    struct student *next;
};

void display(struct student *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while(head != NULL)
    {
        printf("%d:%s:%d -> ", head->id, head->name, head->marks);
        head = head->next;
    }

    printf("NULL\n");
}

void insert_beg(struct student **head, int id, char *name, int marks)
{
    struct student *newstudent;
    newstudent = malloc(sizeof(struct student));

    if(newstudent == NULL)
        return;

    newstudent->id = id;
    strcpy(newstudent->name, name);
    newstudent->marks = marks;
    newstudent->next = *head;

    *head = newstudent;
}

void insert_end(struct student **head, int id, char *name, int marks)
{
    struct student *newstudent;
    newstudent = malloc(sizeof(struct student));

    if(newstudent == NULL)
        return;

    newstudent->id = id;
    strcpy(newstudent->name, name);
    newstudent->marks = marks;
    newstudent->next = NULL;

    if(*head == NULL)
    {
        *head = newstudent;
        return;
    }

    struct student *temp = *head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newstudent;
}

int studentcount(struct student *head)
{
    int count = 0;

    while(head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

void insert_pos(struct student **head, int pos, int id, char *name, int marks)
{
    if(pos < 1)
    {
        printf("Invalid position\n");
        return;
    }

    if(pos == 1)
    {
        insert_beg(head, id, name, marks);
        return;
    }

    struct student *temp = *head;

    for(int i = 1; i < pos-1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    struct student *newstudent = malloc(sizeof(struct student));

    if(newstudent == NULL)
        return;

    newstudent->id = id;
    strcpy(newstudent->name, name);
    newstudent->marks = marks;
    newstudent->next = temp->next;
    temp->next = newstudent;
}

void delete(struct student **head, int pos)
{
    if(*head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if(pos < 1)
    {
        printf("Invalid position\n");
        return;
    }

    struct student *temp = *head;

    if(pos == 1)
    {
        *head = temp->next;
        free(temp);
        printf("Student deleted successfully\n");
        return;
    }

    for(int i = 1; i < pos-1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if(temp == NULL || temp->next == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    struct student *del = temp->next;
    temp->next = del->next;
    free(del);

    printf("Student deleted successfully\n");
}

void update(struct student *head, int id)
{
    while(head != NULL)
    {
        if(head->id == id)
        {
            printf("Enter new name: ");
            scanf("%s", head->name);

            printf("Enter new marks: ");
            scanf("%d", &head->marks);

            printf("Student updated successfully\n");
            return;
        }

        head = head->next;
    }

    printf("Student ID not found\n");
}

void reverse(struct student **head)
{
    struct student *cur = *head;
    struct student *prev = NULL;
    struct student *Next = NULL;

    while(cur != NULL)
    {
        Next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = Next;
    }

    *head = prev;

    printf("List reversed successfully\n");
}

int main()
{
    struct student *head = NULL;
    int choice, id, marks, pos;
    char name[30];

    while(1)
    {
        printf("\n----- STUDENT LINKED LIST -----\n");
        printf("1.Insert Beginning\n");
        printf("2.Insert Position\n");
        printf("3.Insert End\n");
        printf("4.Delete\n");
        printf("5.Display\n");
        printf("6.Student Count\n");
        printf("7.Update\n");
        printf("8.Reverse\n");
        printf("9.Exit\n");

        printf("Enter the choice: ");

        if(scanf("%d", &choice) != 1)
            break;

        switch(choice)
        {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);

                printf("Enter name: ");
                scanf("%29s", name);

                printf("Enter marks: ");
                scanf("%d", &marks);

                insert_beg(&head, id, name, marks);
                break;

            case 2:
                printf("Enter ID: ");
                scanf("%d", &id);

                printf("Enter name: ");
                scanf("%29s", name);

                printf("Enter marks: ");
                scanf("%d", &marks);

                printf("Enter position: ");
                scanf("%d", &pos);

                insert_pos(&head, pos, id, name, marks);
                break;

            case 3:
                printf("Enter ID: ");
                scanf("%d", &id);

                printf("Enter name: ");
                scanf("%29s", name);

                printf("Enter marks: ");
                scanf("%d", &marks);

                insert_end(&head, id, name, marks);
                break;

            case 4:
                printf("Enter position to delete: ");
                scanf("%d", &pos);

                delete(&head, pos);
                break;

            case 5:
                display(head);
                break;

            case 6:
                printf("Student count = %d\n", studentcount(head));
                break;

            case 7:
                printf("Enter student ID to update: ");
                scanf("%d", &id);

                update(head, id);
                break;

            case 8:
                reverse(&head);
                break;

            case 9:
                while(head != NULL)
                {
                    struct student *temp = head;
                    head = head->next;
                    free(temp);
                }

                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
