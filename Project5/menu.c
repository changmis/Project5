#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

// 이진 탐색 트리 노드 정의
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// 이진 탐색 트리 생성 함수
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 이진 탐색 트리 삽입 함수 (재귀)
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

// 이진 탐색 트리 검색 함수 (반복)
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

// 이진 탐색 트리의 가장 작은 노드 찾기
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// 이진 탐색 트리 삭제 함수 (재귀)
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

// 중위 순회 함수 (재귀)
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// 메뉴 출력 함수
void printMenu() {
    printf("s: 검색\n");
    printf("i: 노드 추가\n");
    printf("d: 노드 삭제\n");
    printf("t: 중위 순회\n");
    printf("I: 노드 추가(반복)\n");
    printf("D: 노드 삭제(반복)\n");
    printf("c: 종료\n");
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
        printf("메뉴 입력: ");
        fgets(input, sizeof(input), stdin);
        sscanf_s(input, " %c", &choice, sizeof(choice));

        switch (choice) {
        case 's':
            printf("검색할 값 입력: ");
            int searchKey;
            fgets(input, sizeof(input), stdin);
            sscanf_s(input, "%d", &searchKey, sizeof(searchKey));
            visitCount = 0;
            Node* result = search(root, searchKey, &visitCount);
            if (result != NULL) {
                printf("검색 성공: %d\n", result->key);
            }
            else {
                printf("검색 실패\n");
            }
            printf("방문한 노드의 수: %d\n", visitCount);
            break;

        case 'i':
            printf("추가할 값 입력: ");
            int insertKey;
            fgets(input, sizeof(input), stdin);
            sscanf_s(input, "%d", &insertKey, sizeof(insertKey));
            root = insert(root, insertKey);
            visitCount = 0;
            inorderTraversal(root);
            printf("\n");
            break;

        case 'd':
            printf("삭제할 값 입력: ");
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
            printf("반복적으로 추가할 값 입력 (종료: -1): ");
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
            printf("반복적으로 삭제할 값 입력 (종료: -1): ");
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
            // 종료
            break;

        default:
            printf("잘못된 메뉴 선택\n");
            break;
        }
    } while (choice != 'c');

    // 메모리 해제
    free(root);

    return 0;
}


