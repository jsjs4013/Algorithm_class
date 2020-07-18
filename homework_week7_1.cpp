#include <iostream>
#include <queue>

using namespace std;

typedef enum
{
	RED,
	BLACK
}Color;

typedef struct node
{
	struct node* p;
	struct node* left;
	struct node* right;
	int key;
	Color color;
}Node;

typedef struct rbtree
{
	Node* root;
	Node* nil;
}RBTree;


void initTree(RBTree**);
Node* createNode(int key);
void leftRotate(RBTree**, Node*);
void rightRotate(RBTree**, Node*);
void RB_INSERT(RBTree**, Node*);
void RB_INSERT_FIXUP(RBTree**, Node*);
void bfs(Node*);


int main(void)
{
	char command; // 명령을 입력받는 변수
	int key; // key값을 입력받는 변수

	RBTree* rbtree;
	rbtree = (RBTree*)malloc(sizeof(RBTree));
	initTree(&rbtree);

	while (1)
	{
		// 사용자가 Q나 q를 입력할 때 까지 반복하는 반복문
		// 여러가지 이진트리에 대한 연산을 수행

		// 명령어와 키 값을 입력받는 부분
		// Q or q가 입력으로 들어오면 반복문을 빠져나감
		cout << "Command: ";
		cin >> command;
		if (command == 'Q' || command == 'q')
			break;
		cin >> key;

		if (command == '+')
		{
			// + 명령이 입력될 경우 실행되는 조건문
			// 이진트리에 키 값에 해당되는 값을 추가함

			RB_INSERT(&rbtree, createNode(key));
			cout << "Insert : key = " << key << endl;

			// bfs방법으로 트리를 탐색하여 트리를 적절하게 출력해주는 함수
			bfs(rbtree->root);
		}
	}


	return 0;
}



void initTree(RBTree** pRBTree)
{
	// 트리를 초기화 하는 함수

	(*pRBTree)->nil = (Node*)malloc(sizeof(Node));
	(*pRBTree)->root = (*pRBTree)->nil;

	(*pRBTree)->nil->p = NULL;
	(*pRBTree)->nil->left = NULL;
	(*pRBTree)->nil->right = NULL;
	(*pRBTree)->nil->key = INT_MAX;
	(*pRBTree)->nil->color = BLACK;
}

Node* createNode(int key)
{
	// 새로운 노드를 생성하는 함수

	Node* node = (Node*)malloc(sizeof(Node));

	node->color = RED; // 새로운 노드는 색이 RED로 생성됨
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->p = NULL;

	return node;
}

void leftRotate(RBTree** T, Node* x)
{
	// 왼쪽 방향으로 로데이트시키는 함수

	Node* y = x->right; // y 설정

	// y의 왼쪽 서브트리를 x의 오른쪽 서브 트리로 옮김
	x->right = y->left;

	if (y->left != (*T)->nil)
	{
		y->left->p = x;
	}

	// x의 부모를 y의 부모로 연결
	y->p = x->p;

	if (x->p == (*T)->nil)
	{
		// 이 경우 x가 root인 경우이므로 y을 root로 선언함

		(*T)->root = y;
	}
	else if (x == x->p->left)
	{
		// x의 부모가 x를 왼쪽에 두고 있다면 y도 왼쪽에 삽입

		x->p->left = y;
	}
	else
	{
		// x의 부모가 x를 오른쪽에 두고 있다면 y도 오른쪽에 삽입

		x->p->right = y;
	}

	y->left = x; // x를 y의 왼쪽에 놓음
	x->p = y; // x의 부모를 y로 선언함
}

void rightRotate(RBTree** T, Node* x)
{
	// 오른쪽 방향으로 로데이트시키는 함수
	// 위의 leftRotate와 정확히 반대 함수

	Node* y = x->left; // y 설정

	// y의 오른쪽 서브트리를 x의 왼쪽 서브 트리로 옮김
	x->left = y->right;

	if (y->right != (*T)->nil)
	{
		y->right->p = x;
	}

	// x의 부모를 y의 부모로 연결
	y->p = x->p;

	if (x->p == (*T)->nil)
	{
		// 이 경우 x가 root인 경우이므로 y을 root로 선언함

		(*T)->root = y;
	}
	else if (x == x->p->left)
	{
		// x의 부모가 x를 왼쪽에 두고 있다면 y도 왼쪽에 삽입

		x->p->left = y;
	}
	else
	{
		// x의 부모가 x를 오른쪽에 두고 있다면 y도 오른쪽에 삽입

		x->p->right = y;
	}

	y->right = x; // x를 y의 오른쪽에 놓음
	x->p = y; // x의 부모를 y로 선언함
}

void RB_INSERT(RBTree** T, Node* z)
{
	Node* y = (*T)->nil;
	Node* x = (*T)->root;

	while (x != (*T)->nil)
	{
		// 삽입위치 찾는 반복문

		y = x; // parent를 기억하는 부분
		if (z->key < x->key) // 삽입하려는 값이 x보다 작은 경우
			x = x->left; // 왼쪽 탐색
		else // 삽입하려는 값이 x보다 큰 경우
			x = x->right; // 오른쪽 탐색
	}

	z->p = y; // z의 parent를 y로 선언하는 부분
	if (y == (*T)->nil)
	{
		// 첫 번째 삽입인 경우 실행되는 조건문

		(*T)->root = z; // root노드로 z가 선택
	}
	else if (z->key < y->key)
	{
		// 삽입하려는 값의 key값이 parent의 key값보다 작은 경우 실행되는 조건문

		y->left = z;
	}
	else
	{
		// 삽입하려는 값의 key값이 parent의 key값보다 큰 경우 실행되는 조건문

		y->right = z;
	}

	z->left = (*T)->nil; // 제일 끝에 들어오므로 다음 노드를 nill로 지정
	z->right = (*T)->nil;
	z->color = RED; // 삽입되는 노드들은 처음에 색을 RED로 지정

	RB_INSERT_FIXUP(T, z); // 레드블랙트리 특성을 복구하기 위한 함수
}

void RB_INSERT_FIXUP(RBTree** T, Node* z)
{
	// 레드블랙트리 특성을 복구하기 위한 함수

	while (z->p->color == RED)
	{
		// z의 parent 노드의 색이 RED 일 경우 반복하는 반복문

		if (z->p == z->p->p->left)
		{
			// z의 parent가 z의 grandParent의 왼쪽 자식일 때

			Node* y = z->p->p->right; // y는 z의 uncle 노드

			if (y->color == RED)
			{
				// z의 uncle 노드가 RED 일 때
				// Case 1

				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				// parent 노드와 uncle 노드의 색이 다를 경우 실행되는 조건문
				// Case 2 & Case 3

				if (z == z->p->right)
				{
					// Case 2

					z = z->p;
					leftRotate(T, z);
				}

				// Case 3
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightRotate(T, z->p->p);
			}
		}
		else
		{
			// z의 parent가 z의 grandParent의 오른쪽 자식일 때 실행되는 조건문
			// 위 if()와 정확히 반대임

			Node* y = z->p->p->left; // y는 z의 uncle 노드

			if (y->color == RED)
			{
				// z의 uncle 노드가 RED 일 때
				// Case1과 닮았지만 else문 안에 있으므로 다른 Case 4 라고 하자

				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				// parent 노드와 uncle 노드의 색이 다를 경우 실행되는 조건문
				// z의 uncle 노드가 BLACK 일 때 실행되는 조건문
				// Case 2 & Case 3 이랑 비슷하지만 다르므로 Case 5 & Case 6 라고 하자

				if (z == z->p->left)
				{
					// Case 5

					z = z->p;
					rightRotate(T, z);
				}

				// Case 6
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftRotate(T, z->p->p);
			}
		}
	}
	(*T)->root->color = BLACK; // z가 루트일 때 색을 black으로 만드는 부분
}

void bfs(Node* head)
{
	// 트리를 적절히 알아볼 수 있게 출력해야하므로 bfs방식을
	// 사용하여 트리를 모두 탐색하고 출력하는 함수

	int visit[100];
	int i = 0;
	int j = 1;
	int count = 0; // 트리 출력 시 높이가 언제 높아져야하는지 알려주는 변수
	int count2 = 0; // 트리 출력 시 <(자식이 두 개)인지 \(자식이 하나)인지 자식이 없는지를 알려주는 변수

	cout << endl;

	// head가 존재하지 않다면 트리가 비어있는 것이므로 함수를 종료함
	if (head == NULL || head->key == INT_MAX)
		return;

	// queue<>를 사용하여 이진트리의 node들을 bfs탐색함
	queue<node*> q;
	q.push(head); // queue에 첫 노드를 입력함

	while (!q.empty())
	{
		// 큐에 값이 있을경우 계속 반복
		// 큐에 값이 있으면 아직 방문하지 않은 노드가 존재하는 것이기 때문
		i++; // 언제 트리의 높이를 높여서 출력해야하는지 알려주는 변수

		node* x = q.front(); // queue의 제일 처음 값을 반환
		q.pop(); // queue의 제일 처음 값을 반환

		if (x->left->key != INT_MAX)
		{
			// pop된 노드의 왼쪽 자식 노드의 key가 INT_MAX이 아닌지 확인하는 조건문

			count++; // 부모의 자식 수를 1 올려줌(높이관여 변수)
			count2++; // 부모의 자식 수를 1 올려줌(<, \ 관여 변수)

			q.push(x->left); // bfs이므로 찾은 자식을 queue에 입력
		}
		if (x->right->key != INT_MAX)
		{
			// pop된 노드의 오른쪽 자식 노드의 key가 INT_MAX이 아닌지 확인하는 조건문

			count++;
			count2++;

			q.push(x->right);
		}

		cout << x->key;
		if (count2 == 2)
		{
			// count2가 2라는 의미는 부모 노드가 자식 노드를 두 개 가지고 있다는 의미
			// 그러므로 <(자식이 두 개)를 출력함

			cout << "< ";
		}
		else if (count2 == 1)
		{
			// count2가 1이라는 의미는 부모 노드가 자식 노드를 한 개 가지고 있다는 의미
			// 그러므로 \(자식이 하나)를 출력함

			cout << "\\ ";
		}
		else
		{
			// count2가 0이라는 의미로 부모 노드가 자식 노드를 0개 가지고 있다는 의미

			cout << "  ";
		}
		count2 = 0; // 새로운 노드에 대해서 다시 자식노드 수를 계산 해야하므로 0으로 초기화

		if (i == j)
		{
			// i와 j의 값이 같아지면 트리의 높이 출력 표현이 1증가함

			j = count; // 부모노드의 자식 노드 수를 의미하므로 언제 트리의 출력 높이가 증가 되는지 알 수 있음
			count = 0;
			i = 0;
			cout << endl; // 트리의 출력 높이를 증가함
		}
	}

	cout << endl;
}