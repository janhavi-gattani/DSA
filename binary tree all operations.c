#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

// Create new node
struct node* newNode(int val) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert into BST
struct node* insert(struct node* root, int val) {
    if (root == NULL)
        return newNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Inorder
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder
void preorder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder
void postorder(struct node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Mirror Image
void mirror(struct node* root) {
    if (root != NULL) {
        mirror(root->left);
        mirror(root->right);
        struct node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

// Get height
int height(struct node* root) {
    if (root == NULL)
        return 0;
    int l = height(root->left);
    int r = height(root->right);
    return (l > r ? l : r) + 1;
}

// Print nodes at level
void printLevel(struct node* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Level-wise display
void levelOrder(struct node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
    }
}

// Count leaf nodes
int countLeaves(struct node* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// Count total nodes
int countTotal(struct node* root) {
    if (root == NULL)
        return 0;
    return 1 + countTotal(root->left) + countTotal(root->right);
}

// Search
int search(struct node* root, int key) {
    if (root == NULL)
        return 0;
    if (key == root->data)
        return 1;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Find minimum value node
struct node* findMin(struct node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete node
struct node* delete(struct node* root, int key) {
    if (root == NULL)
        return NULL;
    if (key < root->data)
        root->left = delete(root->left, key);
    else if (key > root->data)
        root->right = delete(root->right, key);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

// Display tree structure
void display(struct node* root, int space) {
    if (root == NULL)
        return;

    space += 5;
    display(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    display(root->left, space);
}

// Main
int main() {
    struct node* root = NULL;
    int choice, val, key;

    while (1) {
        printf("\nMenu:\n1.Insert\n2.Inorder\n3.Preorder\n4.Postorder\n5.Mirror\n6.Level Order\n7.Count Leaves\n8.Total Nodes\n9.Search\n10.Delete\n11.Exit\n12.Display Tree\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                mirror(root);
                printf("Mirror image created.\n");
                break;
            case 6:
                printf("Level Order: ");
                levelOrder(root);
                printf("\n");
                break;
            case 7:
                printf("Leaf Nodes: %d\n", countLeaves(root));
                break;
            case 8:
                printf("Total Nodes: %d\n", countTotal(root));
                break;
            case 9:
                printf("Enter value to search: ");
                scanf("%d", &key);
                if (search(root, key))
                    printf("Found!\n");
                else
                    printf("Not Found.\n");
                break;
            case 10:
                printf("Enter value to delete: ");
                scanf("%d", &key);
                root = delete(root, key);
                printf("Deleted if present.\n");
                break;
            case 11:
                exit(0);
            case 12:
                printf("\nTree Structure:\n");
                display(root, 0);
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
