#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	int count;
	int height;
	struct node* left;
	struct node* right;
};

struct bst{
	struct node* root;
};

struct node* create_node(int data){
	struct node* newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->count = 1;
	newnode->height = 0;
	return newnode;
}

int Height(struct node* root){
	if(root == NULL)
		return 0;
	int left = 1 + Height(root->left);
	int right = 1 + Height(root->right);
	return left>right?left:right;	
}

int balance_factor(struct node* root){
	if(root == NULL){
		return 0;
	}
	return Height(root->left) - Height(root->right);
}

struct node* leftrotate(struct node* root){
	struct node* temp1 = root->right;
	struct node* temp2 = temp1->left;
	temp1->left = root;
	root->right = temp2;
	return temp1;
}

struct node* rightrotate(struct node* root){
	struct node* temp1 = root->left;
	struct node* temp2 = temp1->right;
	temp1->right = root;
	root->left = temp2;
	return temp1;
}

struct node* insert(struct node* root,int data){
	if(root == NULL){
		root = create_node(data);
		return root;
	}
	if(root->data < data){
		root->right = insert(root->right,data);
	}
	else{
		if(root->data == data){
			root->count += 1;
			return root;
		}
		root->left = insert(root->left,data);
	}
	int bf = balance_factor(root);
	if(bf > 1){
		int tbf = balance_factor(root->left);
		if(tbf < 0){
			root->left = leftrotate(root->left);
			root = rightrotate(root);
		}
		else{
			root = rightrotate(root);
		}
	}
	else if(bf < -1){
		int tbf = balance_factor(root->right);
		if(tbf > 0){
			root->right = rightrotate(root->right);
			root = leftrotate(root);
		}
		else{
			root = leftrotate(root);
		}
	}
	return root;

}

void inorder(struct node* root){
	if(root == NULL)
		return;	
	inorder(root->left);
	int count = root->count;
	for(int i=0;i<count;i++){
		printf("%d ",root->data);
	}	
	inorder(root->right);
}



int main(){
	struct bst *T;
	T = (struct bst*)malloc(sizeof(struct bst));
	T->root = NULL;
	int n,i,key;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&key);
		T->root = insert(T->root,key);
		//printf("The root val is %d\n",T->root->data);
	}
	inorder(T->root);
	printf("\n");
	return 0;
}
