#include <stdio.h>
#include <stdlib.h>

typedef struct Employee {
    int emp_id;
    char name[50];
    struct Employee *left, *right;
} Employee;

// Create new node
Employee* create(int id, char* name) {
    Employee* e = (Employee*)malloc(sizeof(Employee));
    e->emp_id = id;
    strcpy(e->name, name);
    e->left = e->right = NULL;
    return e;
}

// Insert into BST
Employee* insert(Employee* root, int id, char* name) {
    if (!root) return create(id, name);
    if (id < root->emp_id)
        root->left = insert(root->left, id, name);
    else if (id > root->emp_id)
        root->right = insert(root->right, id, name);
    return root;
}

// Search employee by id
Employee* search(Employee* root, int id) {
    while (root && root->emp_id != id) {
        if (id < root->emp_id) root = root->left;
        else root = root->right;
    }
    return root;
}

// Inorder traversal (sorted ascending)
void inorder(Employee* root) {
    if (!root) return;
    inorder(root->left);
    printf("ID: %d, Name: %s\n", root->emp_id, root->name);
    inorder(root->right);
}

int main() {
    Employee* root = NULL;
    int choice, id;
    char name[50];
    Employee* found;

    while (1) {
        printf("\n1.Insert 2.Search 3.Display Sorted 4.Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter emp-id and name: ");
                scanf("%d %s", &id, name);
                root = insert(root, id, name);
                break;
            case 2:
                printf("Enter emp-id to search: ");
                scanf("%d", &id);
                found = search(root, id);
                if (found)
                    printf("Found: ID=%d, Name=%s\n", found->emp_id, found->name);
                else
                    printf("Employee not found.\n");
                break;
            case 3:
                printf("Employees sorted by emp-id:\n");
                inorder(root);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
