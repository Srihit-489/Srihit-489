#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct hash{
	struct node **arr;
	int size;
};

struct node{
	char *ch;
	struct node* next;
};

struct node* create_node(char *ch){
	struct node* newnode;
	newnode->next = NULL;
	newnode->ch = (char*)malloc(sizeof(char)*30);
	strcpy(newnode->ch,ch);
	return newnode;
}

void print(struct hash *T){
	int n = T->size;
	int i;
	for(i=0;i<n;i++){
		if(T->arr[i] == NULL){
			printf("%d null",i);
		}
		else{
			printf("%d:",i);
			struct node* root = T->arr[i];
			printf("%s",root->ch);
			root = root->next;
			while(root != NULL){
				printf("-%s",root->ch);
				//printf("The root is %p\n",root);
				root = root->next;
				//printf("The root is %p\n",root);
			}
		
		}
		printf("\n");
	}
}


void insert(struct hash *T,char* str){
    int n = T->size;
	struct node *new;
	new =(struct node*)malloc(sizeof(struct node));
	new->next = NULL;
	new->ch = (char*)malloc(sizeof(char)*50);
	strcpy(new->ch,str);
	int key = (strlen(str)*strlen(str))%n;
	if(T->arr[key] == NULL){
		T->arr[key] = new;
		return;
	}
	struct node *p = T->arr[key];
	while(p->next){
		if(strcmp(new->ch,p->ch) == 0){
			free(new);
			return;
		}
		p = p->next;
	}
	p->next = new;
}

void initialize(struct node **arr,int n){
	for(int i=0;i<n;i++){
		arr[i] = NULL;
	}
}




int main(){
	struct hash *T;
	T = (struct hash*)malloc(sizeof(struct hash));
	scanf("%d",&T->size);
	//printf("\n");
	//char *test;
	//test = (char*)malloc(sizeof(char)*30);
	//scanf("%s",test);
	//printf("%ld\n",strlen(test));
	//struct node **T->arr;
	T->arr = (struct node**)malloc(sizeof(struct node*)*T->size);
	initialize(T->arr,T->size);
	//T->arr = (struct node*)malloc(n*sizeof(struct node));
	//initialize(T->arr,n);
	char input;
	char **temp;
	temp = (char**)malloc(T->size*sizeof(char*));
	int count=0;
	int string_count=0;
	char gar;
	scanf("%c",&gar);
	while(1){
		scanf("%c",&input);
		if(input == '\n'){    
			insert(T,temp[string_count]);
			break;
		}
		else if(input == ' '){	
			insert(T,temp[string_count]);
			string_count++;
			count = 0;
		}
		else{
			if(count == 0)
				temp[string_count] = malloc(sizeof(char)*30);
			temp[string_count][count] = input;
			count++;
		}
	}
	print(T);
	return 0;
}
