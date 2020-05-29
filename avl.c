#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	struct node *left,*right;
	int data;
}node;
int height(node *root);
node *insert(node *r,node *new_node);
void display(node *root);
node *ll_maintain(node *root);
node *lr_maintain(node *root);
node *rr_maintain(node *root);
node *rl_maintain(node *root);
node* balance(node* root,node *parent);
int balance_factor(node *root);
int main()
{
	int option,ele,h;
	node *root=NULL,*new_node;;
	printf("1.Insertin\n2.Display\n3.Exit\n");
	do
	{
		printf("Enter the option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1:	printf("Enter the element : ");
				new_node=(node *)malloc(sizeof(node));
			       	scanf("%d",&new_node->data);
			       	new_node->left=NULL;
			       	new_node->right=NULL;
				root=insert(root,new_node);
				root=balance(root,NULL);
				display(root);
				printf("\nRoot=%d\n",root->data);
				h=height(root);
			       	printf("\n");
			      	printf("height=%d\n",h);
			       	break;
			case 2:	display(root);
				root=balance(root,NULL);	//uncomment to check the bf's of all the node
			       	printf("\n");
			       	break;
			case 3:	break;
			default:printf("Invalid Option\n");
				break;
		}
	}while(option!=3);
	return 0;
}
node *insert(node *r,node *new_node)
{
	node *parent=NULL,*root;
	root=r;
	if(r==NULL)
		return new_node;
	while(root!=NULL)
	{
		parent=root;
		if(new_node->data>root->data)
			root=root->right;
		else
			root=root->left;
	}
	if(new_node->data>parent->data)
		parent->right=new_node;
	else
		parent->left=new_node;
	return r;
}
int height(node *root)
{
	int p,q;
	if(root==NULL||(root->left==NULL && root->right==NULL))
		 return 0;
	else
	{
	 	p=height(root->left);
		q=height(root->right);
		if(p>q)
			return p+1;
		else
			return q+1;
	}
}
void display(node *root)
{
	if(root!=NULL)
	{
		display(root->left);
		printf("%d ",root->data);
		display(root->right);
	}
}
node* balance(node* root,node *parent)
{
	int bf,bf1;
	if(root==NULL)
		return root;
	balance(root->left,root);
	balance(root->right,root);
	bf=balance_factor(root);
	if(bf==-1 || bf==0 || bf==1)
	{
		printf("Root=%d  bf=%d\n",root->data,bf);
		return root;
	}
	else
	{
		if(bf==2)
		{
			bf1=balance_factor(root->left);
			if(bf1==1 || bf1==0)
				root=ll_maintain(root);
			else
				root=lr_maintain(root);
			if(parent!=NULL)
				parent->left=root;
		}
		else
		{
			bf1=balance_factor(root->right);
			if(bf1==-1 || bf==0)
				root=rr_maintain(root);
			else
				root=rl_maintain(root);
			if(parent!=NULL)
				parent->right=root;
		}
		printf("Root=%d  bf=%d\n",root->data,bf);
	}
	return root;
	
}
int balance_factor(node *root)
{
	int bf;
        if(root->left==NULL && root->right==NULL)
		bf=0;
	else if(root->left==NULL)
		bf=-(height(root->right)+1);
	else if(root->right==NULL)
	        bf=height(root->left)+1;
	else
		bf=height(root->left)-height(root->right);
	return bf;

}
node *ll_maintain(node *root)
{
	node *prev,*curr;
	prev=root;
	root=root->left;
	curr=root->right;
	root->right=prev;
	prev->left=NULL;
	if(curr!=NULL)
		root=insert(root,curr);
	return root;
}
node *lr_maintain(node *root)
{
	node *prev,*curr;
	prev=root->left;
	curr=root->left->right;
	curr->left=prev;
	root->left=curr;
	prev->right=NULL;
	root=ll_maintain(root);
	return root;
}
node *rr_maintain(node *root)
{
	node *prev,*curr;
	prev=root;
	root=root->right;
	curr=root->left;
	root->left=prev;
	prev->right=NULL;
	if(curr!=NULL)
		root=insert(root,curr);
	return root;
}
node *rl_maintain(node *root)
{
	node *prev,*curr;
	prev=root->right;
	curr=root->right->left;
	curr->right=prev;
	root->right=curr;
	prev->left=NULL;
	root=rr_maintain(root);
	return root;
}
