#include <iostream>
#include <malloc.h>
using namespace std;
typedef struct AVL{
    int data;
    int height;
    AVL *Lchild;
    AVL *Rchild;
    AVL *parent;
    AVL(){data=0;height=0;Lchild=NULL;Rchild=NULL;parent=NULL;}
}AVL;
AVL* Insert(int x,AVL* root);
int GetDepth(AVL *root);
AVL* IsBalance(int x,AVL *root);
AVL* Adjust(int x,AVL *root);
AVL* Search(int x,AVL *root);
AVL* Delete_balance(int x,AVL *root);
void LL(AVL *A,AVL *B,AVL *C,AVL *D,AVL *E);
void LR(AVL *A,AVL *B,AVL *C,AVL *D,AVL *E,AVL *F,AVL *G);
void RR(AVL *A,AVL *B,AVL *C,AVL *D,AVL *E);
void RL(AVL *A,AVL *B,AVL *C,AVL *D,AVL *E,AVL *F,AVL *G);
void print(AVL *root){
    AVL *p=root;
    if(p!=NULL){
        if(p->Lchild!=NULL)
            print(p->Lchild);
        if(p->Rchild!=NULL)
            print(p->Rchild);
        cout<<"  "<<p->data<<endl;
    }
}
int main()
{
    AVL *root = 0;
   /* root=Insert(3,root);
    root=Insert(5,root);
    root=Insert(2,root);
    root=Delete_balance(3,root);
    root=Insert(20,root);
    root=Insert(10,root);
    root=Delete_balance(5,root);*/
    root=Insert(25,root);
    root=Insert(27,root);
    root=Insert(30,root);
    //cout<<Search(3,root);
    //root=Delete_balance(3,root);
    //root=Insert(20,root);
    //cout<<"search : "<<Search(2,root)<<endl;
    //root=Insert(10,root);
    //root=Delete_balance(5,root);
    root=Insert(12,root);
    root=Insert(11,root);
    root=Insert(18,root);
    root=Insert(14,root);
    root=Insert(20,root);
    root=Insert(15,root);
    root=Insert(22,root);
    root=Delete_balance(11,root);
    root=Delete_balance(12,root);
    //root=Delete_balance(25,root);
    /*root=Insert(3,root);
    root=Delete_balance(15,root);
    root=Delete_balance(23,root);
    root=Delete_balance(25,root);
    root=Delete_balance(1,root);
    root=Delete_balance(30,root);
    root=Delete_balance(50,root);
    root=Delete_balance(40,root);
    root=Delete_balance(3,root);
    cout<<Search(4,root)<<endl;*/
    print(root);
    root=Delete_balance(15,root);
    cout<<"*****************************************";
    print(root);
    cout<<"root : "<<root->data<<endl;
    //cout<<"root : "<<root->Rchild->Lchild->Rchild->data<<endl;

    cout<<"root->Lchild : "<<root->Lchild->data<<endl;
    cout<<"root->Rchild : "<<root->Rchild->data<<endl;
   // cout<<"root->Rchild->Lchild : "<<root->Rchild->Lchild->data<<endl;
    return 0;
}
void LL(AVL *A,AVL *B,AVL *C,AVL *D,AVL *E){
    B->Rchild=A;
    B->Lchild=D;
    A->Lchild=E;
    A->Rchild=C;

    A->parent=B;
    D->parent=B;
    if(E!=NULL)
        E->parent=A;
    if(C!=NULL)
        C->parent=A;

}
void LR(AVL *A,AVL *B,AVL *C,AVL *D,AVL *E,AVL *F,AVL *G){
    E->Lchild=B;
    E->Rchild=A;
    B->Lchild=D;
    B->Rchild=F;
    A->Lchild=G;
    A->Rchild=C;

    A->parent=E;
    B->parent=E;
    if(D!=NULL)
        D->parent=B;
    if(F!=NULL)
        F->parent=B;
    if(C!=NULL)
        C->parent=A;
    if(G!=NULL)
        G->parent=A;

}
void RR(AVL *A,AVL *B,AVL *C,AVL *D,AVL *E){
    C->Lchild=A;
    C->Rchild=E;
    A->Lchild=B;
    A->Rchild=D;

    A->parent=C;
    E->parent=C;
    if(B!=NULL)
        B->parent=A;
    if(D!=NULL)
        D->parent=A;
}
void RL(AVL *A,AVL *B,AVL *C,AVL *D,AVL *E,AVL *F,AVL *G){
    D->Lchild=A;
    D->Rchild=C;
    A->Lchild=B;
    A->Rchild=F;
    C->Lchild=G;
    C->Rchild=E;

    A->parent=D;
    C->parent=D;
    if(B!=NULL)
        B->parent=A;
    if(G!=NULL)
        G->parent=C;
    if(E!=NULL)
        E->parent=C;
    if(F!=NULL)
        F->parent=A;
}
AVL* Insert(int x,AVL* root){
    AVL *p,*FRONT,*head;
    AVL *A,*B,*C,*D,*E,*F,*G;
    head=root;
    p = new AVL;
    p->data=x;
    if(root==0){root=p;}
    else{
        while(head!=0){
            if(x>head->data){
                FRONT=head;
                head=head->Rchild;
                if(head!=0)
                    head->parent=FRONT;
            }
            else{
                FRONT=head;
                head=head->Lchild;
                if(head!=0)
                    head->parent=FRONT;
            }
        }
        if(FRONT->data>x){
            FRONT->Lchild=p;
            p->parent=FRONT;
        }
        else{
            FRONT->Rchild=p;
            p->parent=FRONT;
        }
        }

    root = Adjust(x,root);

    return root;
}
AVL* Adjust(int x,AVL *root){
    AVL *A,*B,*C,*D,*E,*F,*G;
    AVL *Front;
    A=IsBalance(x,root);
    if(A!=NULL)
        Front=A->parent;
    else
        return root;
    if(A->height==2){
        B=A->Lchild;
        B->height=GetDepth(B->Lchild)-GetDepth(B->Rchild);
        if(B->height==1||B->height==0){
            D=B->Lchild;
            E=B->Rchild;
            C=A->Rchild;
            if(Front!=NULL){
                if(Front->Lchild->data==A->data)
                    Front->Lchild=B;
                else
                    Front->Rchild=B;
                B->parent=Front;
            }
            else{
                root=B;
                B->parent=NULL;
            }
            LL(A,B,C,D,E);
        }
        if(B->height==-1){
            D=B->Lchild;
            E=B->Rchild;
            C=A->Rchild;
            F=E->Lchild;
            G=E->Rchild;
            if(Front!=NULL){
                if(Front->Lchild->data==A->data)
                    Front->Lchild=E;
                else{
                    Front->Rchild=E;
                    E->parent=NULL;
                }

                E->parent=Front;
            }
            else{
                root=E;
                E->parent=NULL;
            }

            LR(A,B,C,D,E,F,G);
        }

    }
    else if(A->height==-2){
        C=A->Rchild;
        C->height=GetDepth(C->Lchild)-GetDepth(C->Rchild);
        if(C->height==-1){
            B=A->Lchild;
            D=C->Lchild;
            E=C->Rchild;
            if(Front!=NULL){
                if(Front->Lchild->data==A->data)
                    Front->Lchild=C;
                else
                    Front->Rchild=C;

                C->parent=Front;
            }
            else{
                root=C;
                C->parent=NULL;
            }

            RR(A,B,C,D,E);
        }
        if(C->height==1&&C->height==0){
            B=A->Lchild;
            D=C->Lchild;
            E=C->Rchild;
            F=D->Lchild;
            G=D->Rchild;
            if(Front!=NULL){
                if(Front->Lchild->data==A->data)
                    Front->Lchild=D;
                else
                    Front->Rchild=D;

                D->parent=Front;
            }
            else{
                root=D;
                D->parent=NULL;
            }

            RL(A,B,C,D,E,F,G);
        }
    }
    return root;
}
AVL* Delete_balance(int x,AVL *root){
    AVL *p=NULL,*FRONT=NULL,*tmp=NULL,*right_left=NULL;
    p=Search(x,root);
    int exchange;
    if(p==0){
        cout<<"NONE"<<endl;
    }
    else{
        if((p->Lchild==0) && (p->Rchild!=0)){
            if(p==root){
                root=p->Rchild;
                root->parent=NULL;
                tmp=root;
            }
            else{
                tmp=p->parent;
                if( (p->data) < (p->parent->data))
                    p->parent->Lchild=p->Rchild;
                else
                    p->parent->Rchild=p->Rchild;
                p->Rchild->parent=tmp;
                free(p);
            }
        }
        else if((p->Lchild!=0) && (p->Rchild==0)){
                if(p==root){
                    root=p->Lchild;
                    root->parent=NULL;
                    tmp=root;
                }
                else{
                    tmp=p->parent;
                    if( (p->data) < (p->parent->data))
                        p->parent->Lchild=p->Lchild;
                    else
                        p->parent->Rchild=p->Lchild;
                    p->Lchild->parent=tmp;
                    free(p);
                }
        }
        else if((p->Lchild==0) && (p->Rchild==0)){
            tmp=p->parent;
            if(tmp->data < p->data)
                tmp->Rchild=NULL;
            else
                tmp->Lchild=NULL;
            free(p);
        }
        else{
            right_left=p->Rchild;
            while(right_left->Lchild!=NULL){

                right_left=right_left->Lchild;
            }
            exchange=p->data;
            p->data=right_left->data;
            right_left->data=exchange;
            if(right_left->Rchild!=NULL){
                if(right_left==root->Rchild){
                    root->Rchild=right_left->Rchild;
                    right_left->parent=root;
                }
                else{
                    right_left->parent->Lchild=right_left->Rchild;
                    right_left->Rchild->parent=right_left->parent;
                }
            }
            else{
                if(right_left==root->Rchild)
                    root->Rchild=NULL;
                else
                    right_left->parent->Lchild=NULL;
            }
            tmp=right_left->parent;
            free(right_left);
        }
    }
    root = Adjust(tmp->data,root);
    return root;
}
AVL* Search(int x,AVL *root){
    AVL *p;
    p=root;
    while(p!=0){
        if(x>p->data)
            p=p->Rchild;
        else if(x<p->data)
            p=p->Lchild;
        else
            return p;
    }
    return 0;
}
AVL* IsBalance(int x,AVL *root){
    AVL *p;
    AVL* A=0;
    int flag;
    p=root;
    while(p!=0){
        if(GetDepth(p->Lchild)-GetDepth(p->Rchild)==2){
                A=p;
                A->height=2;
        }
        if(GetDepth(p->Lchild)-GetDepth(p->Rchild)==-2){
                A=p;
                A->height=-2;
        }
        if(x==p->data)
            break;
        if(x>p->data){
            p=p->Rchild;
        }
        if(x<p->data){
            p=p->Lchild;
        }
    }
    return A;
}
int GetDepth(AVL *root){
    if(root==0)
        return 0;

    else if(root->Lchild==0&&root->Rchild==0)
        return 1;

    else if(root->Lchild==0)
        return GetDepth(root->Rchild)+1;

    else if(root->Rchild==0)
        return GetDepth(root->Lchild)+1;

    else
        return GetDepth(root->Lchild) > GetDepth(root->Rchild)
                        ? GetDepth(root->Lchild)+1 : GetDepth(root->Rchild)+1;
}
