/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("------------[      [Won Jong Min] [2019038014]      ]-----------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr)		//현재 노드가 NULL이 아니라면
	{
		inorderTraversal(ptr->left);	//맨 왼쪽으로 먼저 가서 출력
		printf(" [%d] ", ptr->key);		//끝에서 한칸 씩 올라가며 출력
		inorderTraversal(ptr->right);	//한칸 올라갈때마다 오른쪽 노드에 있다면 출력
	}
	
}

void preorderTraversal(Node* ptr)
{
	if (ptr)		//현재 노드가 NULL이 아니라면
	{
		printf(" [%d] ", ptr->key);		//노드를 출력하며
		preorderTraversal(ptr->left);	//맨 왼쪽으로 이동
		preorderTraversal(ptr->right);	//왼쪽 노드가 없을 때 오른쪽 노드가 있다면 출력
	}
	
}

void postorderTraversal(Node* ptr)
{
	if (ptr)		//현재 노드가 NULL이 아니라면
	{
		postorderTraversal(ptr->left);		//맨 왼쪽으로 먼저 이동
		postorderTraversal(ptr->right);		//왼쪽노드가 없다면 오른쪽 노드로 이동
		printf(" [%d] ", ptr->key);			//오른쪽 노드도 없다면 출력
	}
}


int insert(Node* head, int key)
{
	if (head == NULL)		//헤드가 없다면
	{
		printf("initialize first!\n");
		return -1;		//초기화 부터 하라고 출력
	}

	Node *node = (Node*)malloc(sizeof(Node));	//노드 생성
	node->key = key;	//값 입력
	node->left = NULL;	//좌우 링크를 NULL로 설정
	node->right = NULL;
	
	if (head->left == NULL)		//노드가 하나도 없다면
	{
		head->left = node;		//노드를 헤드와 연결
		return 1;
	}
	
	Node *p = head->left;		//이동용 노드
	Node *n = NULL;				//값 확인용 노드	,현재 노드의 부모노드

	while (p != NULL)			//노드가 비어있을 떄까지
	{
		if(p->key == key)		//현재노드가 입력받은 값과 같다면
		{
			printf("This key is already in here\n");
			return 1;			//이진탐색트리는 똑같은 값은 하나이므로 값이 있다고 출력
		}
		
		n = p;		//현재노드를 부모노드로 설정 후

		if (p->key < key)	//입력받은 값이 크다면
		{
			p = p->right;	//우측으로 이동
		}
		else				//아니라면
		{	
			p = p->left;	//좌측으로 이동
		}
	}						//전부 비교 후 현재노드가 NULL이라면
	
	if (n->key < key)		//부모노드의 값과 입력받은 값을 비교 후
	{
		n->right = node;	//크다면 우측노드로 연결
	}
	else
	{
		n->left = node;		//작다면 좌측노드로 연결
	}
	

	return 1;

}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL || head->left == NULL)
	{		//헤드가 없거나 노드가 없다면
		printf("No Nodes!\n");		//노드가 없다고 출력
		return -1;
	}

	Node *node = head->left;	//현재노드
	Node *prenode = head;		//현재 노드의 부모노드

	while (node != NULL)		//현재 노드가 비어있을때까지
	{
		if (node->key == key)	//현재노드의 값이 입력받은 값과 같다면
		{
			if (node->left != NULL && node->right != NULL)
			{			//노드의 좌우가 비어있지 않다면
				printf("This node is not a leaf!\n");	//현재노드가 리프노드가 아니라고 출력
			}
			else		//현재노드의 좌우가 비어있다면
			{
				if (prenode == head)	//현재노드의 부모노드가 헤드일 경우
				{
					head->left = NULL;	//헤드에 NULL을 연결 후
				}

				if (prenode->left == node)	//현재노드의 부모노드 기준으로
				{
					prenode->left = NULL;	//좌측에 있다면 좌측을 NULL로 연결 후
				}
				else
				{
					prenode->right = NULL;	//우측에 있다면 우측을 NULL로 연결 후
				}

				free(node);		//현재노드 초기화
			}
			
			return 1;
		}
		
		prenode = node;			//현재노드를 부모노드로 설정 후

		if (node->key < key)	//입력받은 값이 현재노드의 값보다
		{
			node = node->right;	//크다면 우측노드로 이동
		}
		else
		{
			node = node->left;	//작다면 좌측노드로 이동
		}		
	}
	
	printf("No node in Nodes!\n");		//비교를 전부 하고 같은 값이 없다면

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr == NULL)	//현재노드(헤드에 연결된 노드)가 비어있다면
	{
		printf("No Nodes!\n");	//노드가 없다고 출력
		return NULL;			//NULL 반환
	}
	
	if (ptr->key == key)		//현재 노드의 값과 입력받은 값과 같다면
	{
		return ptr;				//현재노드 반환
	}
	
	if (ptr->key < key)			//현재노드의 값과 입력받은 값과 비교해서
	{
		searchRecursive(ptr->right, key);	//입력받은 값이 크다면 우측노드로 이동
	}
	else
	{
		searchRecursive(ptr->left, key);	//입력받은 값이 작다면 좌측노드로 이동
	}
	
}

Node* searchIterative(Node* head, int key)
{
	Node *node = head->left;		//현재노드
	while (node != NULL)			//현재노드가 비어있을 때까지 반복
	{
		if (node->key == key)		//현재값과 입력받은 값이 같다면
		{
			return node;			//현재노드 반환
		}
		
		if (node->key < key)		//현재값과 입력받은값을 비교해서
		{
			node = node->right;		//입력받은 값이 크다면 우측노드로 이동
		}
		else
		{
			node = node->left;		//입력받은 값이 작다면 좌측노드로 이동
		}
		
	}

	return NULL;				//그 외에 경우 입력받은 값을 찾을 수 없다면 NULL 반환
	
}


void freeNode(Node* ptr)
{
	if(ptr) {		//현재노드가 안비었을때
		freeNode(ptr->left);		//좌측으로 가서 반복
		freeNode(ptr->right);		//우측으로 가서 반복
		free(ptr);					//현재노드 메모리 반환
	}
}

int freeBST(Node* head)
{

	if(head->left == NULL)	//헤드에 연결된 노드가 없다면
	{
		free(head);			//헤드의 메모리 반환
		return 1;
	}

	Node* p = head->left;	//헤드의 다음노드를 임시노드로 설정 후

	freeNode(p);			//헤드에 연결된 모든 노드의 메모리 반환

	free(head);				//헤드의 메모리 반환
	return 1;
}
