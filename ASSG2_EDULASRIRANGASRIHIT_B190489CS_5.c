#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{ 
    int data;
    struct node* left;
    struct node* right;
    struct node* p;
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

struct node* minimum(struct node *root){
       while(root->left != NULL)
              root = root->left;
       return root;       
}

struct node* maximum(struct node *root){
       while(root->right != NULL)
              root = root->right;
       return root;       
}

struct node* succesor(struct node **root){
     struct node *pi = *root;
     if(pi == NULL){
     	return NULL;
     }
     if(pi->right != NULL)
               return minimum(pi->right);
     struct node *q = pi->p;
     while(q != NULL && pi == q->right){
               pi = q;
               q = q->p;
     }
     return q;       
                      
}

struct node* predecessor(struct node **root){
     struct node *pi = *root;
     if(pi == NULL){
     	return NULL;
     }
     if(pi->left != NULL)
               return maximum(pi->left);
     struct node *q = pi->p;
     while(q != NULL && pi == q->left){
               pi = q;
               q = q->p;
     }
     return q;       
                      
}

void inorder(struct node* root){
          if(root == NULL)
                return;
          inorder(root->left);
          printf("%d ",root->data);
          inorder(root->right);      
}

int operand(char ch){
   
    return (ch >= '0' && ch <= '9');  
         
}

int create_num(char* string,int i){
	int num = 0;
	if(string[i] == '-'){
		i = i + 1;
		 while(operand(string[i])){
                      
          num = num*10 + (int)string[i]-'0';
                       
          i++;
    	  }
    return -num;
	}
    while(operand(string[i])){
                      
          num = num*10 + (int)string[i]-'0';
                       
          i++;
    }
    return num;
}

int noofdigits(int num){
	int data=abs(num),count=0;
	while(data != 0){
		count++;
		data = data/10;
	}
	return count;
}

int leveling(char *ch,int leveler){
	int level=0,count =0;
	for(int i=0;i<strlen(ch);i++){
		if(ch[i] == '('){
			level++;
		}
		else if(ch[i] == ')'){
			level--;
		}
		else if(leveler == level){
			if(count == 1){
			return i;
			}
			else{
				count = 1;
			}
		}
	}
}

int find_matching_index(char *s,int start,int end){
    int level=0;
    for (int i=start;i<end;i++){
        if (s[i]=='('){
            level++;
        }
        if (s[i]==')'){
            level--;
        }
        if (level==0){
            return i;
        }
    }
    return -1;
}

struct node* create_tree(char *ch,int pos){
	if(ch[pos] == '(' && ch[pos+1] == ')'){
		return NULL;
	}
	if(ch[pos] == '('){
		create_tree(ch,pos+1);
	}
	else if(ch[pos] == ')'){
		create_tree(ch,pos+1);
	}
	else{
		struct node* root;
		int var = create_num(ch,pos);
		root = create_node(var);
		if(var >= 0)
			pos = pos + noofdigits(var);
		else
			pos = pos + noofdigits(var) + 1;
		root->left = create_tree(ch,pos);
		if(root->left != NULL){
		(root->left)->p = root;
		}
		int temp = find_matching_index(ch,pos,strlen(ch));
		root->right = create_tree(ch,temp);
		if(root->right != NULL){
			(root->right)->p = root;
		}
		return root;
	}
	
}

struct node* SEARCH(struct node** root,int data){         
          if((*root) == NULL)
                 return NULL;
          else if((*root)->data == data)
                 return *root;              
          else if((*root)->data < data)
                 SEARCH(&(*root)->right,data);
          else if((*root)->data > data)
                 SEARCH(&(*root)->left,data);                                                     
}

struct node* Kthlargest(struct node* root,int k){
	struct node* largest = maximum(root);
	for(int i=0;i<k-1;i++){
		largest = predecessor(&largest);
	}
	return largest;
}

struct node* Kthsmallest(struct node* root,int k){
	struct node* smallest = minimum(root);
	for(int i=0;i<k-1;i++){
		smallest = succesor(&smallest);
	}
	return smallest;
}




int main(){
	struct tree *T;
	T = (struct tree*)malloc(sizeof(struct tree));
	T->root = NULL;
	char str[1000];
	scanf("%[^\n]s",str);
	//printf("%s",str);
	char ch[50];
	//scanf("%s",ch);
	int i=0,j=0;
	while(j != strlen(str)){
		if(str[j] == ' '){
			j++;
		}
		else{
			ch[i] = str[j];
			i++;
			j++;
		}
	}
	T->root = create_tree(ch,0);
	char choice;
	int key;
	while(1){
		scanf("%c",&choice);
		switch(choice){
			case 'r':
				scanf("%d",&key);
				struct node* varb = SEARCH(&T->root,key);
				if(varb){
					printf("%d\n",predecessor(&varb)->data);
				}
				else{
					printf("-1\n");
				}
				break;
			case 'u':
				scanf("%d",&key);
				struct node* var = SEARCH(&T->root,key);
				if(var){
					printf("%d\n",succesor(&var)->data);
				}
				else{
					printf("-1\n");
				}
				break;
			case 'i':
				inorder(T->root);
				printf("\n");
				break;
			case 'l':
			    scanf("%d",&key);
				struct node* temp = Kthlargest(T->root,key);
				if(temp){
					printf("%d\n",temp->data);
				}
				else{
					printf("-1\n");
				}
				break;
			case 's':
				scanf("%d",&key);
			    temp = Kthsmallest(T->root,key);
				if(temp){
					printf("%d\n",temp->data);
				}
				else{
					printf("-1\n");
				}
				break;
			case 'e':
				exit(1);		
						
		}
	}
	return 0;
}




