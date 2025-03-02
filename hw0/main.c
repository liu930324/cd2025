#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode {
    char character;
    int count;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* createNode(char ch) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("記憶體分配失敗\n");
        exit(1);
    }
    newNode->character = ch;
    newNode->count = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* insertOrUpdate(TreeNode* root, char ch) {
    if (root == NULL) return createNode(ch);
    if (ch < root->character) {
        root->left = insertOrUpdate(root->left, ch);
    } else if (ch > root->character) {
        root->right = insertOrUpdate(root->right, ch);
    } else {
        root->count++;
    }
    return root;
}

void inorderPrint(TreeNode* root) {
    if (root == NULL) return;
    inorderPrint(root->left);
    if (root->character == '\n') {
        printf("'\\n' : %d 次\n", root->count);
    } else {
        printf("'%c' : %d 次\n", root->character, root->count);
    }
    inorderPrint(root->right);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    FILE* file;
    char filename[] = __FILE__;
    char ch;
    TreeNode* root = NULL;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("無法開啟自身檔案");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        root = insertOrUpdate(root, ch);
    }

    fclose(file);

    printf("字元統計結果 (排序後):\n");
    inorderPrint(root);

    freeTree(root);

    return 0;
}
