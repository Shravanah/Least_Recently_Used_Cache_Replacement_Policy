#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int usrdata;
int count;
char task;

struct Node {
    int data;
    struct Node *next;
};

struct Node *CreateNode(int data) {
    struct Node *newn = (struct Node *)malloc(sizeof(struct Node));
    newn->data = data;
    newn->next = NULL;
    return newn;
}

int get_data() {
    printf("Enter the data: ");
    scanf("%d", &usrdata);
    return usrdata;
}

void check_len(struct Node **head) {
    struct Node *temp = *head;
    count = 1;
    if (temp == NULL) {
        printf("0\n");
        return;
    }
    while (temp->next != NULL) {
        count += 1;
        temp = temp->next;
    }

    printf("%d\n", count);
    if (count >= 5) {
        printf("Cache is full, need replacement\n");
    } else {
        printf("You can add more blocks\n");
    }
}

void insert_at_beg(struct Node **head, int data) {
    struct Node *newn = CreateNode(data);
    if ((*head) == NULL) {
        *head = newn;
        return;
    }
    newn->next = *head;
    *head = newn;
    return;
}

void del_at_end(struct Node **head) {
    
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *temp = *head;

    
    if (temp->next == NULL) {
        free(temp);
        *head = NULL;  
        return;
    }

  
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

   
    struct Node *lastNode = temp->next;
    temp->next = NULL;  
    free(lastNode);  
}

void replacement(struct Node **head) {
    
    if (count != 5) {
        insert_at_beg(head, usrdata);
        return;
    } else {
        insert_at_beg(head, usrdata);
        del_at_end(head);
    }
}

void printll(struct Node**head) {
    struct Node *temp = *head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


void checkdata(struct Node **head) {
    struct Node *temp = *head;
    struct Node *temp1 = NULL;

    while (temp != NULL) {
        if (temp->data != usrdata) {
            temp1 = temp;
            temp = temp->next;
        } else {
            printf("Requested data is present in the cache\n");
            //insert_at_beg(head, usrdata);
            
            if (temp1 != NULL) {
                temp1->next = temp->next;
            } else {
                *head = temp->next;
            }
            free(temp);
            return;
        }
    }

   // printf("Replacement needed!\n");
    replacement(head);
}

void usertask(struct Node **head) {
    printf("Do you want to continue? yes/no\n");
    scanf(" %c", &task);  

    

    if (task == 'y') {
        check_len(head);
        get_data();  
        checkdata(head);
        printll(head);
        usertask(head);
        
    } else {
        printf("Exiting...\n");
        printll(head);
        return;
    }
}



int main() {
    struct Node *head = NULL;
    
    usertask(&head);
    
    
    return 0;
}
