#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

typedef struct {
    Node *root;
    Node *nil;
} Tree;

void InorderTreeWalk(Node *x) {
    if (x != NULL) {
        InorderTreeWalk(x->left);
        printf("%d -> ", x->key);
        InorderTreeWalk(x->right);
    }
}

void PreorderTreeWalk(Node *x) {
    if (x != NULL) {
        printf("%d -> ", x->key);
        PreorderTreeWalk(x->left);
        PreorderTreeWalk(x->right);
    }
}

void PostorderTreeWalk(Node *x) {
    if (x != NULL) {
        PostorderTreeWalk(x->left);
        PostorderTreeWalk(x->right);
        printf("%d -> ", x->key);
    }
}

Node *TreeSearch(Tree *t, int key) {
    Node *p = t->root;
    while (p != NULL) {
        if (key < p->key) {
            p = p->left;
        } else if (key > p->key) {
            p = p->right;
        } else {
            return p;
        }
    }
    printf("\n 찾는 키가 없습니다.");
    return p;
}

Node *treeMinimum(Node *x) {
    Node *y;
    while (x != NULL) {
        printf("현재는 %d 입니다.\n", x->key);
        y = x;
        x = x->left;
    }
    return y;
}

Node *treeMaximum(Node *x) {
    Node *y;
    while (x != NULL) {
        y = x;
        x = x->right;
    }
    return y;
}

Node *treeSuccessor(Node *x) {
    if (x->right != NULL) {
        return treeMinimum(x->right);
    }
    Node *y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

Node *treePredecessor(Node *x) {
    if (x->left != NULL) {
        return treeMaximum(x->left);
    }
    Node *y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

Node *treeInsert(Tree *t, int key) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    Node *x = t->root;
    Node *y = t->nil;

    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    while (x != NULL) {
        y = x;
        if (key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    newNode->parent = y;
    if (y == t->nil) {
        t->root = newNode;
    } else if (newNode->key < y->key) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }
    return newNode;
}

void transplant(Tree *t, Node *u, Node *v) {
    if (u->parent == t->nil) {
        t->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != t->nil) {
        v->parent = u->parent;
    }
}

void treeDelete(Tree *t, Node *z) {
    if (z == NULL) {
        return;
    }
    if (z->left == t->nil) {
        transplant(t, z, z->right);
    } else if (z->right == t->nil) {
        transplant(t, z, z->left);
    } else {
        Node *y = treeMinimum(z->right);
        if (y->parent != z) {
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}


int main() {
    //트리 생성
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    //루트 노드 삽입
    Node *root = treeInsert(tree, 1);
    // 노드 삽입
    Node *a1 = treeInsert(tree, 5);
    Node *a2 = treeInsert(tree, 3);
    Node *a3 = treeInsert(tree, 9);
    Node *a4 = treeInsert(tree, 2);
    // 순회 출력
    printf("\n");
    printf("중위순회 : ");
    InorderTreeWalk(root);
    printf("\n");
    printf("전위순회 : ");
    PreorderTreeWalk(root);
    printf("\n");
    printf("후위순회 : ");
    PostorderTreeWalk(root);

    // 직전 원소 출력.
    printf("\n%d의 직전원소 : ", a3->key);// 직전 원소 출력
    Node *answer = treePredecessor(a3);
    if (answer == NULL) {
        printf("없습니다.\n");
    } else {
        printf("%d ", answer->key);
    }
    //직후 원소 출력.
    printf("\n%d의 직후원소 : ", a2->key);// 직후 원소 출력
    answer = treeSuccessor(a2);
    if (answer == NULL) {
        printf("없습니다.\n");
    } else {
        printf("%d ", answer->key);
    }
    //삭제
    treeDelete(tree, a2);// a2(key=3) 삭제
    //다시 순회
    printf("\n");
    printf("중위순회 : ");
    InorderTreeWalk(root);
    printf("\n");
    printf("전위순회 : ");
    PreorderTreeWalk(root);
    printf("\n");
    printf("후위순회 : ");
    PostorderTreeWalk(root);


    return 0;
}
