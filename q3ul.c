#include<stdio.h>
#include<stdlib.h>

struct node{
	struct node* left;
	struct node* right;
	int key;
	int cb;
};


struct node* create_node(int data){
	struct node* newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->key = data;
	newnode->cb = 0;
	return newnode;
}

int color(struct node* node){
	if(node == NULL)
		return 1;
	else
		return node->cb;		
}

struct node* leftrotate(struct node* x)
{
	struct node* y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

struct node* rightrotate(struct node* x)
{
	struct node* y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

struct node* insert(struct node* root,struct node* newnode){
	if(root == NULL)
		return newnode;
	else if(root->key > newnode->key){
		root->left = insert(root->left,newnode);
		if(color(root->left) == 0){
			if(color(root->left->left) == 0 || color(root->left->right) == 0){
			
				if(color(root->right) == 0){
					root->right->cb =  1;
					root->left->cb = 1;
					root->cb = 0;
				}
				else{
					if(color(root->left->left) == 0){
						struct node* y = rightrotate(root);
						y->right->cb = 0;
						y->cb = 1;
						return y;
					}
					else{
						root->left = leftrotate(root->left);
						struct node* y = rightrotate(root);
						y->right->cb = 0;
						y->cb = 1;
						return y;
					}
				}
			}
		}
		return root;
	}
	else{
		root->right = insert(root->right,newnode);
		if(color(root->right) == 0){
			if(color(root->right->left)== 0 || color(root->right->right) == 0){
				if(color(root->left) == 0){
					root->left->cb = 1;
					root->right->cb = 1;
					root->cb = 0;
				}
				else{
					if(color(root->right->right) == 0){
						struct node* y = leftrotate(root);
						y->left->cb = 0;
						y->cb = 1;
						return y;
					}
					else{
						root->right = rightrotate(root->right);
						struct node* y = leftrotate(root);
						y->left->cb = 0;
						y->cb = 1;
						return y;
					}		
				}
			
			}
				
		}
		return root;
	}	

}

struct node* rbinsert(struct node* r,struct node* x)
{
	r = insert(r,x);
	if(r->cb==0)
		r->cb = 1;
	return r;
}

struct node* print(struct node* A)
{
        if(A!=NULL)
        {
        	if(A->cb == 0)
                printf("( %d R ",A->key);
            else
            	printf("( %d B ",A->key);    
                print(A->left);
                print(A->right);
                printf(") ");
                return A;
        }
        else
        {
                printf("( ) ");
                return A;
        }
}



int main(){
	struct node* root=NULL;
	int i,key;
	while(scanf("%d",&key) == 1){
		root = rbinsert(root,create_node(key));
		print(root);
		printf("\n");
	}
	
	return 0;
}
