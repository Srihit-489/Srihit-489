#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct hash{
	struct node **arr;
	int size;
};

struct node{
	char *ch;
	struct node *next;
};

struct node* create_node(char *str){
	struct node* new;
	new = (struct node*)malloc(sizeof(struct node));
	new->next = NULL;
	new->ch = (char*)malloc(sizeof(char)*30);
	strcpy(new->ch,str);
	return new;
}

int power(int base,int exp){
	int pro = 1;
	int temp = exp;
	while(temp>0){
		pro = pro*base;
		temp--;
	}
	return pro;
}

int val(char ch){
	int value = ch - 97;
	return power(2,value);
}

int spv(char* str){
	int i=0;
	int sum=0;
	for(i=0;i<strlen(str);i++){
		for(int z=i+1;z<strlen(str);z++){
			if(str[i] == str[z]){
				sum = sum - val(str[i]);
				break;
			}
		}
		sum = sum + val(str[i]);
	}
	return sum;
}

void insert(struct hash *T,char *str){
	struct node *newnode = create_node(str);
	int sp_val = spv(str);
	char temp[50];
	int key = sp_val % 255;
	if(T->arr[key] == NULL){
		T->arr[key] = newnode;
		return;
	}
	else{
		struct node *root = T->arr[key];
		if(strcmp(newnode->ch,root->ch) < 0){
			newnode->next = root;
			T->arr[key] = newnode;
			return;
		}
		while(root->next && strcmp(root->ch,newnode->ch) < 0){
			root = root->next;
		}
		newnode->next = root->next;
		root->next = newnode;
		return;
	}
}

void print(struct hash *T){
	int i;
	for(i=0;i<255;i++){
		if(T->arr[i] == NULL){
			continue;
		}
		else{
			struct node* root = T->arr[i];
			while(root){
				printf("%s ",root->ch);
				root = root->next;
			}
			printf("\n");
		}
	}
}

int main(){
	struct hash *T;
	int n;
	T = (struct hash*)malloc(sizeof(struct hash));
	T->size = 255;
	scanf("%d",&n);
	T->arr = (struct node**)malloc(sizeof(struct node*)*T->size);
	int i;
	char temp[40];
	for(i=0;i<n;i++){
		scanf("%s",temp);
		insert(T,temp);
	}
	print(T);
}

