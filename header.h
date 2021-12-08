#include<stdio.h>
#include<stdlib.h>
#define MAXI 200
typedef struct node{
    int vid;
    int x;
    int y;
    struct node* next;
}Node;
typedef struct stack{
    Node* arr[MAXI];
    int top;
}Stack;

Node* g[MAXI];
int visit[MAXI];
int sx,sy,dx,dy;
Stack dfsS;
int axArr[MAXI];
int dontPop;
int q[MAXI];
int f,r;

int rev[MAXI];
int n;

void init();
void readMap();
void myprint();
void initS(Stack* s);
void push(Stack* s,Node* ele);
Node* pop(Stack* s);
void setVisit();
void dfsPath(int v,int d);
void resetVisit();
void qinsert(int v);
int qdelete();
int qisempty();
void bfsPath(int v,int d);
void findPath();
void storePath();