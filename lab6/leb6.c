#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ContentType;

struct TreeNode {
    ContentType data;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
    
};

struct TreeNode* create_node(struct TreeNode* tree,int i,ContentType content) {
    tree[i].data = content;
    tree[i].height = 1;
    tree[i].right = NULL;
    tree[i].left = NULL;
   
    return &tree[i];

}
int tree_size(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int sizeleft = 0;
    if (root->left != NULL) {
        sizeleft = root->left->height;
    }
    else {
        sizeleft = 0;
    }
    int sizeright = 0;
    if (root->right != NULL) {
        sizeright = root->right->height;
    }
    else {
        sizeright = 0;
    }
    if (sizeleft > sizeright) {
        root->height = sizeleft + 1;
    }
    else {
        root->height = sizeright + 1;
    }
    root->height = (sizeleft > sizeright) ? sizeleft + 1 : sizeright + 1;
    return root->height;
}
struct TreeNode* rotate_left(struct TreeNode* root) {
    struct TreeNode* right_child = root->right;

    root->right = right_child->left;
    right_child->left = root;

    tree_size(root);
    tree_size(right_child);
    return right_child;
}

struct TreeNode* rotate_right(struct TreeNode* root) {
    struct TreeNode* left_child = root->left;

    root->left = left_child->right;

    left_child->right = root;


    tree_size(root);
    tree_size(left_child);
    return left_child;
}

int balance_factor(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int sizeleft = 0;
    if (root->left != NULL) {
        sizeleft = root->left->height;
    }
    else {
        sizeleft = 0;
    }
    int sizeright = 0;
    if (root->right != NULL) {
        sizeright = root->right->height;
    }
    else {
        sizeright = 0;
    }
    return sizeleft - sizeright;
}


struct TreeNode* insert_node(struct TreeNode* tree, int i, struct TreeNode* root, ContentType content) {
    if (root == NULL) {
        return create_node(tree,i,content);
    }
    else if (content >= root->data) {
        root->right = insert_node(tree,i,root->right, content);
    }
    else {
        root->left = insert_node(tree, i, root->left, content);
    }
    tree_size(root);
    int balance = balance_factor(root);
    if (balance > 1 && content < root->left->data) {
        return rotate_right(root);
    }
    if (balance < -1 && content >= root->right->data) {
        return rotate_left(root);
    }
    if (balance > 1 && content >= root->left->data) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && content < root->right->data) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

int main() {
    //printf("%d", sizeof(struct TreeNode));
    int N;
    if (scanf("%d", &N) != 1) {
        return 0;
    }
    if (N == 0) {
        printf("%d", 0);
        return 0;
    }
    struct TreeNode* tree = (struct TreeNode*)malloc(N * sizeof(struct TreeNode));
    struct TreeNode* root = NULL;
    int a = 0;
    int  num;
    if (scanf("%d", &num) != 1) {
        free(tree);
    }
    insert_node(tree, a, root, num);
    a++;
        root = &tree[0];
    for (int i = 1; i < N; i++) {
        if (scanf("%d", &num) != 1) {
            free(tree);
            return 0;
        }
        root = insert_node(tree, a, root, num);
        a++;
    }
    if (root == NULL) {
        free(tree);
        printf("0\n");
        return 0;
    }
        printf("%d\n", root->height);
    
   
    free(tree);
    return 0;
}