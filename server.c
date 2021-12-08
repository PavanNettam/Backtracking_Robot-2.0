#include<stdio.h>
#include<stdlib.h>
#define MAXI 200
#include "header.h"
void init(){//to initialize graph
    for(int i=0;i<MAXI;i++){
        g[i] = NULL;
    }
}
void readMap(){
    FILE* rf = fopen("input.txt","r");
    if(rf==NULL){
        printf("ERROR in opening file\n");
        return;
    }
    fscanf(rf,"%d", &sx);
    fscanf(rf,"%d", &sy);
    fscanf(rf,"%d", &dx);
    fscanf(rf,"%d", &dy);
    int entity,k = 1;
    /*
    Look behind technique is used to construct the graph here where
    first we go to the vertex and then join the vertex to the prev vertex
    */
    for(int i=0;i<=dy;i++){
        for(int j=0;j<=dx;j++){
            fscanf(rf,"%d", &entity);
            Node* temp = (Node*)malloc(sizeof(Node));
            Node* temp2 = (Node*)malloc(sizeof(Node));
            temp2 = temp;
            temp->x = j;
            temp->y = i;
            temp->vid = k;
            temp->next = NULL;
            if(i == 0 && j== 0 ){
                continue;
            }else if(i == 0){
                if(entity == 0){
                    temp->next = g[k-1];
                    g[k-1] = temp;
                }
            }else if(j == 0){
                if(entity == 0){
                    temp->next = g[(k)-(dx+1)];
                    g[(k)-(dx+1)] = temp;
                }
            }else{
                if(entity == 0){
                    temp->next = g[k-1];
                    g[k-1] = temp;
                    temp2->next = g[k-dx-1];
                    g[k-dx-1] = temp2;
                }
            }
            k++;
        }
    }
    fclose(rf);
}
void myprint(){ // This is just a reference function to check weather the graph is constructed properly
    for(int i=0;i<MAXI;i++){
        if(g[i] != NULL){
            printf("(%d,%d) ",g[i]->x,g[i]->y);
            if(g[i]->next != NULL){
                printf("(%d,%d) ",g[i]->next->x,g[i]->next->y);
            }
        }
        printf("\n");
    }
}
void initS(Stack* s){//to intiallise the stack 
    s->top = -1;
}
void push(Stack* s,Node* ele){
    if(s->top == MAXI-1){
        return;
    }else{
        s->top++;
        s->arr[s->top] = ele;
    }
}
Node* pop(Stack* s){
    if(s->top == -1){
        return NULL;
    }else{
        Node* ele = s->arr[s->top];
        s->top--;
        return ele;
    }
}
void setVisit(){//This function is used to set all the elements to visited!!
    for(int i=0;i<MAXI;i++){
        visit[i] = 1;
    }
}
void dfsPath(int v,int d)
{
	int i;
	Node *p;
	visit[v]=1;
	if(v == d){
        dontPop = 1;
        setVisit();
        return;
    }
	for(p=g[v];p!=NULL;p=p->next) 
	{
		i=p->vid;
		if(visit[i]==0){
            push(&dfsS,p);
		    dfsPath(i,d); 
        }
	}
    if(!dontPop)
        pop(&dfsS);
}
void resetVisit(){//This function resets visited
    for(int i=0;i<MAXI;i++){
        visit[i] = 0;
    }
}
void qinsert(int v)
{
    r++;
    q[r]=v;
    if(f==-1)
      f=0;
}

int qdelete()
{
    int w;
    w=q[f];
    if(f==r)
     f=r=-1;
    else
     f++;
    return w;
}
 
int qisempty()
{
    if(f==-1)
       return 1;
    return 0;
}

void bfsPath(int v,int d)
  {
	  int w;int j;
	  struct node *p;
	  visit[v]=1;
	  
	  qinsert(v);
	  
	  while(!qisempty())
	  {
		  w=qdelete();
		  if(w == d){
              return;
          }
		  for(p=g[w];p!=NULL;p=p->next)
		  {
			  j=p->vid;
			  if(visit[j]==0)
			  {
				   visit[j]=1;
                   axArr[j] = w;
				   qinsert(j);
			  }
		  }
	  }
  }   
void findPath(){
    initS(&dfsS);
    resetVisit();
    dfsPath(0,99);
    resetVisit();
    bfsPath(0,99);
    axArr[0] = axArr[1] = 0;
}
void storePath(){
    FILE* wf1 = fopen("outdfs.txt","w");
    FILE* wf2 = fopen("outbfs.txt","w");
    if(wf1 == NULL || wf2 == NULL){
        printf("ERROR in writing into the file\n");
        return;
    }
    //DFS Results
    for(int i=0;i<(dfsS.top);i++){
        fprintf(wf1,"(%d,%d) \n",dfsS.arr[i]->x,dfsS.arr[i]->y);
    }
    //BFS Results
    int i = 99;
    while(axArr[i] != 0){
        rev[n] = axArr[i];
        n++;
        i = axArr[i];
    }
    for(int i=n-1;i>=0;i--){
        fprintf(wf2,"(%d,%d)\n",rev[i]%(dx+1),rev[i]/(dx+1));
    }
    fclose(wf1);
    fclose(wf2);
}