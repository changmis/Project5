#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

// ���� Ž�� Ʈ�� ��� ����
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// ���� Ž�� Ʈ�� ���� �Լ�
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ���� Ž�� Ʈ�� ���� �Լ� (���)
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// ���� Ž�� Ʈ�� �˻� �Լ� (�ݺ�)
Node* search(Node* root, int key, int* visitCount) {
    while (root != NULL) {
        (*visitCount)++;
        if (key == root->key) {
            return root;
        }
        else if (key < root->key) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return NULL;
}

// ���� Ž�� Ʈ���� ���� ���� ��� ã��
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// ���� Ž�� Ʈ�� ���� �Լ� (���)
Node* deleteNode(Node* root, int key, int* visitCount) {
    if (root == NULL) {
        return root;
    }

    (*visitCount)++;
    if (key < root->key) {
        root->left = deleteNode(root->left, key, visitCount);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key, visitCount);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key, visitCount);
    }

    return root;
}

// ���� ��ȸ �Լ� (���)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// �޴� ��� �Լ�
void printMenu() {
    printf("s: �˻�\n");
    printf("i: ��� �߰�\n");
    printf("d: ��� ����\n");
    printf("t: ���� ��ȸ\n");
    printf("I: ��� �߰�(�ݺ�)\n");
    printf("D: ��� ����(�ݺ�)\n");
    printf("c: ����\n");
}

int main() {
    Node* root = NULL;
    char input[MAX_INPUT_LENGTH];
    char choice;
    int visitCount = 0;

    root = insert(root, 60);
    root = insert(root, 41);
    root = insert(root, 74);
    root = insert(root, 16);
    root = insert(root, 53);
    root = insert(root, 65);
    root = insert(root, 25);
    root = insert(root, 46);
    root = insert(root, 55);
    root = insert(root, 63);
    root = insert(root, 70);
    root = insert(root, 42);
    root = insert(root, 62);
    root = insert(root, 64);


    do {
        printMenu();
        printf("�޴� �Է�: ");
        fgets(input, sizeof(input), stdin);
        sscanf_s(input, " %c", &choice, sizeof(choice));

        switch (choice) {
        case 's':
            printf("�˻��� �� �Է�: ");
            int searchKey;
            fgets(input, sizeof(input), stdin);
            sscanf_s(input, "%d", &searchKey, sizeof(searchKey));
            visitCount = 0;
            Node* result = search(root, searchKey, &visitCount);
            if (result != NULL) {
                printf("�˻� ����: %d\n", result->key);
            }
            else {
                printf("�˻� ����\n");
            }
            printf("�湮�� ����� ��: %d\n", visitCount);
            break;

        case 'i':
            printf("�߰��� �� �Է�: ");
            int insertKey;
            fgets(input, sizeof(input), stdin);
            sscanf_s(input, "%d", &insertKey, sizeof(insertKey));
            root = insert(root, insertKey);
            visitCount = 0;
            inorderTraversal(root);
            printf("\n");
            break;

        case 'd':
            printf("������ �� �Է�: ");
            int deleteKey;
            fgets(input, sizeof(input), stdin);
            sscanf_s(input, "%d", &deleteKey, sizeof(deleteKey));
            visitCount = 0;
            root = deleteNode(root, deleteKey, &visitCount);
            inorderTraversal(root);
            printf("\n");
            break;

        case 't':
            inorderTraversal(root);
            printf("\n");
            break;

        case 'I':
            printf("�ݺ������� �߰��� �� �Է� (����: -1): ");
            while (1) {
                int key;
                fgets(input, sizeof(input), stdin);
                sscanf_s(input, "%d", &key, sizeof(key));
                if (key == -1) {
                    break;
                }
                root = insert(root, key);
                visitCount = 0;
                inorderTraversal(root);
                printf("\n");
            }
            break;

        case 'D':
            printf("�ݺ������� ������ �� �Է� (����: -1): ");
            while (1) {
                int key;
                fgets(input, sizeof(input), stdin);
                sscanf_s(input, "%d", &key, sizeof(key));
                if (key == -1) {
                    break;
                }
                visitCount = 0;
                root = deleteNode(root, key, &visitCount);
                inorderTraversal(root);
                printf("\n");
            }
            break;

        case 'c':
            // ����
            break;

        default:
            printf("�߸��� �޴� ����\n");
            break;
        }
    } while (choice != 'c');

    // �޸� ����
    free(root);

    return 0;
}


