#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int data;
	struct node* leftchild;
	struct node* rightchild;
};

struct tree{
	struct node* root;
};

struct node* create_node(int data){
	struct node* newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->leftchild = NULL;
	newnode->rightchild = NULL;
	newnode->data = data;
	return newnode;
}

void insert(struct tree *T,int data){
	//printf("here1\n");
	struct node* newnode = create_node(data);
	struct node* root = T->root;
	//printf("here1\n");
	if(root == NULL){
		//printf("here1\n");
		T->root = newnode;
		return;
	}
	//printf("here1\n");
	while(1){
		if(root->data > newnode->data){
			//printf("here1\n");
			if(root->leftchild == NULL){
				root->leftchild = newnode;
				return;
			}
			root = root->leftchild;
		}
		else{
			if(root->rightchild == NULL){
				root->rightchild = newnode;
				return;
			}
			//printf("here1\n");
			root = root->rightchild;
		}
	}
}

void print(struct node *root){
	if(root == NULL)
		return;
	print(root->leftchild);
	printf("%d ",root->data);
	print(root->rightchild);	
}

struct node* SEARCH(struct node** root,int data){         
          if((*root) == NULL)
                 return NULL;
          else if((*root)->data == data)
                 return *root;              
          else if((*root)->data < data)
                 SEARCH(&(*root)->rightchild,data);
          else if((*root)->data > data)
                 SEARCH(&(*root)->leftchild,data);                                                     
}

void func(struct node* root,int a,int b){
		if(SEARCH(&root,a) == NULL|| SEARCH(&root,b) == NULL)
			return;
		int temp;	
		if(a>b){
			temp = a;
			a = b;
			b = temp;
		}	
		struct node* var1 = SEARCH(&root,b);
		struct node* var2 = SEARCH(&root,a);
		if(SEARCH(&var2,b) != NULL){
			int greatest=0;
			struct node* temp1 = SEARCH(&root,a);
			struct node* temp2 = SEARCH(&root,b);		
			while(temp1 != temp2){
				if(temp1->data > temp2->data){
					if(greatest < temp1->data)
						greatest = temp1->data;
					temp1 = temp1->leftchild;	
					//printf("here2\n");
				}
				else{
					if(greatest < temp1->data)
						greatest = temp1->data;
					temp1 = temp1->rightchild;
					//printf("here3\n");	
				}
			}
			printf("%d\n",greatest);
				return;
			
		}
		if(SEARCH(&var1,a) != NULL){
			int greatest=0;
			struct node* temp1 = SEARCH(&root,b);
			struct node* temp2 = SEARCH(&root,a);		
			while(temp1 != temp2){
				if(temp1->data > temp2->data){
					if(greatest < temp1->data)
						greatest = temp1->data;
					temp1 = temp1->leftchild;	
				}
				else{
					if(greatest < temp1->data)
						greatest = temp1->data;
					temp1 = temp1->rightchild;	
				}
				printf("%d\n",greatest);
				return;
			}
			
		}
		while(SEARCH(&root->leftchild,a) == NULL || SEARCH(&root->rightchild,b) == NULL){
			if(SEARCH(&root->leftchild,a) != NULL && SEARCH(&root->leftchild,b) != NULL){
				root = root->leftchild;
			}
		}	
		int greatest = 0;
		struct node* itr = root;
		//printf("%d is the root\n",root->data);
		while(itr != SEARCH(&root,a)){
			if(itr->data > a){
				if(itr->data > greatest){
					greatest = itr->data;
				}
				itr = itr->leftchild;
			}
			else{
				if(itr->data > greatest){
					greatest = itr->data;
				}
				itr = itr->rightchild;
			}
		}
		itr = root;
		while(itr != SEARCH(&root,b)){
			if(itr->data > b){
				if(itr->data > greatest){
					greatest = itr->data;
				}
				itr = itr->leftchild;
			}
			else{
				if(itr->data > greatest){
					greatest = itr->data;
				}
				itr = itr->rightchild;
			}
		}
		printf("%d\n",greatest);
}


int main(){
	struct tree *T;
	T = (struct tree*)malloc(sizeof(struct tree));
	T->root = NULL;
	int data;
	char ch;
	/*struct node* sample = create_node(18);
	sample->rightchild = create_node(36);
	sample->leftchild = create_node(9);
	struct node* temp = sample->leftchild;
	temp->leftchild = create_node(6);
	temp->rightchild = create_node(12);
	temp = temp->leftchild;
	temp->leftchild = create_node(1);
	temp->rightchild = create_node(8);
	temp = sample->leftchild;
	temp = temp->rightchild;
	temp->leftchild = create_node(10);
	print(sample);
	printf("\n");
	int a,b;*/
	do{
		scanf("%d",&data);
		insert(T,data);	
		scanf("%c",&ch);
	}while(ch != '\n');
	int a,b;
	scanf("%d",&a);
	scanf("%d",&b);
	func(T->root,a,b);
	return 0;
}
