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
	char command; // ����� �Է¹޴� ����
	int key; // key���� �Է¹޴� ����

	RBTree* rbtree;
	rbtree = (RBTree*)malloc(sizeof(RBTree));
	initTree(&rbtree);

	while (1)
	{
		// ����ڰ� Q�� q�� �Է��� �� ���� �ݺ��ϴ� �ݺ���
		// �������� ����Ʈ���� ���� ������ ����

		// ��ɾ�� Ű ���� �Է¹޴� �κ�
		// Q or q�� �Է����� ������ �ݺ����� ��������
		cout << "Command: ";
		cin >> command;
		if (command == 'Q' || command == 'q')
			break;
		cin >> key;

		if (command == '+')
		{
			// + ����� �Էµ� ��� ����Ǵ� ���ǹ�
			// ����Ʈ���� Ű ���� �ش�Ǵ� ���� �߰���

			RB_INSERT(&rbtree, createNode(key));
			cout << "Insert : key = " << key << endl;

			// bfs������� Ʈ���� Ž���Ͽ� Ʈ���� �����ϰ� ������ִ� �Լ�
			bfs(rbtree->root);
		}
	}


	return 0;
}



void initTree(RBTree** pRBTree)
{
	// Ʈ���� �ʱ�ȭ �ϴ� �Լ�

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
	// ���ο� ��带 �����ϴ� �Լ�

	Node* node = (Node*)malloc(sizeof(Node));

	node->color = RED; // ���ο� ���� ���� RED�� ������
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->p = NULL;

	return node;
}

void leftRotate(RBTree** T, Node* x)
{
	// ���� �������� �ε���Ʈ��Ű�� �Լ�

	Node* y = x->right; // y ����

	// y�� ���� ����Ʈ���� x�� ������ ���� Ʈ���� �ű�
	x->right = y->left;

	if (y->left != (*T)->nil)
	{
		y->left->p = x;
	}

	// x�� �θ� y�� �θ�� ����
	y->p = x->p;

	if (x->p == (*T)->nil)
	{
		// �� ��� x�� root�� ����̹Ƿ� y�� root�� ������

		(*T)->root = y;
	}
	else if (x == x->p->left)
	{
		// x�� �θ� x�� ���ʿ� �ΰ� �ִٸ� y�� ���ʿ� ����

		x->p->left = y;
	}
	else
	{
		// x�� �θ� x�� �����ʿ� �ΰ� �ִٸ� y�� �����ʿ� ����

		x->p->right = y;
	}

	y->left = x; // x�� y�� ���ʿ� ����
	x->p = y; // x�� �θ� y�� ������
}

void rightRotate(RBTree** T, Node* x)
{
	// ������ �������� �ε���Ʈ��Ű�� �Լ�
	// ���� leftRotate�� ��Ȯ�� �ݴ� �Լ�

	Node* y = x->left; // y ����

	// y�� ������ ����Ʈ���� x�� ���� ���� Ʈ���� �ű�
	x->left = y->right;

	if (y->right != (*T)->nil)
	{
		y->right->p = x;
	}

	// x�� �θ� y�� �θ�� ����
	y->p = x->p;

	if (x->p == (*T)->nil)
	{
		// �� ��� x�� root�� ����̹Ƿ� y�� root�� ������

		(*T)->root = y;
	}
	else if (x == x->p->left)
	{
		// x�� �θ� x�� ���ʿ� �ΰ� �ִٸ� y�� ���ʿ� ����

		x->p->left = y;
	}
	else
	{
		// x�� �θ� x�� �����ʿ� �ΰ� �ִٸ� y�� �����ʿ� ����

		x->p->right = y;
	}

	y->right = x; // x�� y�� �����ʿ� ����
	x->p = y; // x�� �θ� y�� ������
}

void RB_INSERT(RBTree** T, Node* z)
{
	Node* y = (*T)->nil;
	Node* x = (*T)->root;

	while (x != (*T)->nil)
	{
		// ������ġ ã�� �ݺ���

		y = x; // parent�� ����ϴ� �κ�
		if (z->key < x->key) // �����Ϸ��� ���� x���� ���� ���
			x = x->left; // ���� Ž��
		else // �����Ϸ��� ���� x���� ū ���
			x = x->right; // ������ Ž��
	}

	z->p = y; // z�� parent�� y�� �����ϴ� �κ�
	if (y == (*T)->nil)
	{
		// ù ��° ������ ��� ����Ǵ� ���ǹ�

		(*T)->root = z; // root���� z�� ����
	}
	else if (z->key < y->key)
	{
		// �����Ϸ��� ���� key���� parent�� key������ ���� ��� ����Ǵ� ���ǹ�

		y->left = z;
	}
	else
	{
		// �����Ϸ��� ���� key���� parent�� key������ ū ��� ����Ǵ� ���ǹ�

		y->right = z;
	}

	z->left = (*T)->nil; // ���� ���� �����Ƿ� ���� ��带 nill�� ����
	z->right = (*T)->nil;
	z->color = RED; // ���ԵǴ� ������ ó���� ���� RED�� ����

	RB_INSERT_FIXUP(T, z); // �����Ʈ�� Ư���� �����ϱ� ���� �Լ�
}

void RB_INSERT_FIXUP(RBTree** T, Node* z)
{
	// �����Ʈ�� Ư���� �����ϱ� ���� �Լ�

	while (z->p->color == RED)
	{
		// z�� parent ����� ���� RED �� ��� �ݺ��ϴ� �ݺ���

		if (z->p == z->p->p->left)
		{
			// z�� parent�� z�� grandParent�� ���� �ڽ��� ��

			Node* y = z->p->p->right; // y�� z�� uncle ���

			if (y->color == RED)
			{
				// z�� uncle ��尡 RED �� ��
				// Case 1

				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				// parent ���� uncle ����� ���� �ٸ� ��� ����Ǵ� ���ǹ�
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
			// z�� parent�� z�� grandParent�� ������ �ڽ��� �� ����Ǵ� ���ǹ�
			// �� if()�� ��Ȯ�� �ݴ���

			Node* y = z->p->p->left; // y�� z�� uncle ���

			if (y->color == RED)
			{
				// z�� uncle ��尡 RED �� ��
				// Case1�� ������� else�� �ȿ� �����Ƿ� �ٸ� Case 4 ��� ����

				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				// parent ���� uncle ����� ���� �ٸ� ��� ����Ǵ� ���ǹ�
				// z�� uncle ��尡 BLACK �� �� ����Ǵ� ���ǹ�
				// Case 2 & Case 3 �̶� ��������� �ٸ��Ƿ� Case 5 & Case 6 ��� ����

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
	(*T)->root->color = BLACK; // z�� ��Ʈ�� �� ���� black���� ����� �κ�
}

void bfs(Node* head)
{
	// Ʈ���� ������ �˾ƺ� �� �ְ� ����ؾ��ϹǷ� bfs�����
	// ����Ͽ� Ʈ���� ��� Ž���ϰ� ����ϴ� �Լ�

	int visit[100];
	int i = 0;
	int j = 1;
	int count = 0; // Ʈ�� ��� �� ���̰� ���� ���������ϴ��� �˷��ִ� ����
	int count2 = 0; // Ʈ�� ��� �� <(�ڽ��� �� ��)���� \(�ڽ��� �ϳ�)���� �ڽ��� �������� �˷��ִ� ����

	cout << endl;

	// head�� �������� �ʴٸ� Ʈ���� ����ִ� ���̹Ƿ� �Լ��� ������
	if (head == NULL || head->key == INT_MAX)
		return;

	// queue<>�� ����Ͽ� ����Ʈ���� node���� bfsŽ����
	queue<node*> q;
	q.push(head); // queue�� ù ��带 �Է���

	while (!q.empty())
	{
		// ť�� ���� ������� ��� �ݺ�
		// ť�� ���� ������ ���� �湮���� ���� ��尡 �����ϴ� ���̱� ����
		i++; // ���� Ʈ���� ���̸� ������ ����ؾ��ϴ��� �˷��ִ� ����

		node* x = q.front(); // queue�� ���� ó�� ���� ��ȯ
		q.pop(); // queue�� ���� ó�� ���� ��ȯ

		if (x->left->key != INT_MAX)
		{
			// pop�� ����� ���� �ڽ� ����� key�� INT_MAX�� �ƴ��� Ȯ���ϴ� ���ǹ�

			count++; // �θ��� �ڽ� ���� 1 �÷���(���̰��� ����)
			count2++; // �θ��� �ڽ� ���� 1 �÷���(<, \ ���� ����)

			q.push(x->left); // bfs�̹Ƿ� ã�� �ڽ��� queue�� �Է�
		}
		if (x->right->key != INT_MAX)
		{
			// pop�� ����� ������ �ڽ� ����� key�� INT_MAX�� �ƴ��� Ȯ���ϴ� ���ǹ�

			count++;
			count2++;

			q.push(x->right);
		}

		cout << x->key;
		if (count2 == 2)
		{
			// count2�� 2��� �ǹ̴� �θ� ��尡 �ڽ� ��带 �� �� ������ �ִٴ� �ǹ�
			// �׷��Ƿ� <(�ڽ��� �� ��)�� �����

			cout << "< ";
		}
		else if (count2 == 1)
		{
			// count2�� 1�̶�� �ǹ̴� �θ� ��尡 �ڽ� ��带 �� �� ������ �ִٴ� �ǹ�
			// �׷��Ƿ� \(�ڽ��� �ϳ�)�� �����

			cout << "\\ ";
		}
		else
		{
			// count2�� 0�̶�� �ǹ̷� �θ� ��尡 �ڽ� ��带 0�� ������ �ִٴ� �ǹ�

			cout << "  ";
		}
		count2 = 0; // ���ο� ��忡 ���ؼ� �ٽ� �ڽĳ�� ���� ��� �ؾ��ϹǷ� 0���� �ʱ�ȭ

		if (i == j)
		{
			// i�� j�� ���� �������� Ʈ���� ���� ��� ǥ���� 1������

			j = count; // �θ����� �ڽ� ��� ���� �ǹ��ϹǷ� ���� Ʈ���� ��� ���̰� ���� �Ǵ��� �� �� ����
			count = 0;
			i = 0;
			cout << endl; // Ʈ���� ��� ���̸� ������
		}
	}

	cout << endl;
}