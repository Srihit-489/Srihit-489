#include<stdio.h>
#include<stdlib.h>


struct node{
	struct node *left,*right,*p;
	int data;
};

struct tree{
	struct node* root;
};

struct node* create_node(int data){
      struct node* newnode;
      newnode = (struct node*)malloc(sizeof(struct node));
      newnode->data = data;
      newnode->left = NULL;
      newnode->right = NULL;
      newnode->p = NULL;
      return newnode;
}

/*void INSERT(struct tree *tree,struct node* newnode){
     struct node* y = NULL;
     struct node* x = tree->root;
     while(x){
         y = x;
         if(newnode->data < x->data)
                 x = x->left;
         else
                 x = x->right;        
     }  
     newnode->p = y;
     if(y == NULL)
            tree->root = newnode;
     else if(newnode->data < y->data)
             y->left = newnode;
     else
             y->right = newnode;                              
}*/


struct node* inserting_arr(int arr[],int start,int last){
	if(start > last){
		return NULL;
	}
	int mid = (start + last)/2;
	struct node* root = create_node(arr[mid]);
	struct node* lc = inserting_arr(arr,start,mid-1);
	struct node* rc = inserting_arr(arr,mid+1,last);
	//printf("the value of root is %d\n",root->data);
	if(lc != NULL){
		lc->p = root;
	}
	if(rc != NULL){
		rc->p = root;
	}
	root->left = lc;
	root->right = rc;
	return root;
}

/*void print(struct node* root){
	if(root == NULL)
		return;
	print(root->left);
	printf("%d ",root->data);
	print(root->right);
}*/

void print(struct node* root){
	printf("(");
	printf(" ");
	if(root != NULL){
		printf("%d",root->data);
		printf(" ");
		print(root->left);
		printf(" ");
		print(root->right);
		printf(" ");
	}
	printf(")");

}

int depth(struct node* root){
	if(root == NULL){
		return 0;
	}
	int l = depth(root->left);
	int r = depth(root->right);
	if(l > r){
		return l + 1;
	}
	else if(l < r){
		return r + 1;
	}
	else{
		return l+1;
	}
}

void level_sums(struct node* root,int sum[]){
	if(root == NULL){
		return;
	}
	int root_depth = depth(root);
	sum[root_depth] = sum[root_depth] + root->data;
	//printf("the sum of sum[root_depth] is %d\n",sum[root_depth]);
	level_sums(root->left,sum);
	level_sums(root->right,sum);
}



int main(){
	struct tree* T;
	T = (struct tree*)malloc(sizeof(struct tree));
	int n;
	scanf("%d",&n);
	int arr[n];
	//arr = (int*)malloc(sizeof(int));
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	//printf("it is ok\n");
	T->root = inserting_arr(arr,0,n-1);
	print(T->root);
	int d = depth(T->root);
	int sum[d];
	for(int i=0;i<=d;i++){
		sum[i] = 0;
	}
	level_sums(T->root,sum);
	for(int j=0;j<d;j++){
		printf("%d ",sum[d-j]);
	}
	printf("\n");
	//printf("the depth is %d\n",d);
	return 0;
}
