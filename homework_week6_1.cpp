#include <iostream>
#include <queue>

using namespace std;

typedef struct node
{
	node* l; // node�� l
	int key; // node�� key
	node* r; // node�� r
}node;

void bfs(node*);
node* treeSearch(node*, int);
void treeInsert(node*, int);
void treeDel(node*, int);

int main(void)
{
	char command; // ����� �Է¹޴� ����
	int key; // key���� �Է¹޴� ����

	// Tree initialization
	node* t, * head;
	head = (struct node*)malloc(sizeof * head);
	head->l = NULL;
	head->r = NULL;
	head->key = 0;

	// �⺻ ��� �κ�
	cout << "Commands:\n" << "\t+key : Insert(or update) element\n";
	cout << "\t?key : Retrieve element\n";
	cout << "\t-key : Remove element\n";
	cout << "\tQ    : Quit the test program\n" << endl;
	cout << "Empty tree;\n" << endl;

	while(1)
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

			treeInsert(head, key);
			cout << "Insert : key = " << key << endl;
			// bfs������� Ʈ���� Ž���Ͽ� Ʈ���� �����ϰ� ������ִ� �Լ�
			bfs(head);
		}
		else if (command == '?')
		{
			// ? ��ɾ�� ã�� Ű ���� ��� �ְ� �ڽ� ���鿡�� � ���� �ִ��� Ȯ���ϴ� ���ǹ�

			// treeSearch()�Լ��� ã�� ����� ����� ��ȯ
			t = treeSearch(head, key);

			if (t == NULL) // ���� ��ȯ�� treeSearch()�Լ��� ���� NULL�̸� ���� ã�� �������� �ǹ���
				cout << "Ʈ���� " << key << "���� �������� �ʴ´�." << endl;
			else if (t->l != NULL && key == t->l->key)
			{
				// ��ȯ�� ���� ���� �ڽ��� NULL�� �ƴϰ� �� �����
				// key���� ã������ ���� ���ٸ� ����Ǵ� ���ǹ�

				cout << "Retrieved : key = " << t->l->key << endl;

				cout << "left child is ";
				if (t->l->l != NULL) // ã�� ���� ���� �ڽ� ��带 Ž��
					cout << t->l->l->key << endl;
				else
					cout << "none" << endl;

				cout << "right child is ";
				if (t->l->r != NULL) // ã�� ���� ������ �ڽ� ��带 Ž��
					cout << t->l->r->key << endl;
				else
					cout << "none" << endl;
			}
			else if (t->r != NULL && key == t->r->key)
			{
				// ��ȯ�� ���� ������ �ڽ��� NULL�� �ƴϰ� �� �����
				// key���� ã������ ���� ���ٸ� ����Ǵ� ���ǹ�

				cout << "Retrieved : key = " << t->r->key << endl;

				cout << "left child is ";
				if (t->r->l != NULL) // ã�� ���� ���� �ڽ� ��带 Ž��
					cout << t->r->l->key << endl;
				else
					cout << "none" << endl;

				cout << "right child is ";
				if (t->r->r != NULL) // ã�� ���� ������ �ڽ� ��带 Ž��
					cout << t->r->r->key << endl;
				else
					cout << "none" << endl;
			}
			else
			{
				// ��ȯ�� ���� key���� ã������ Ű ���� ���ٸ� ����Ǵ� ���ǹ�
				// �� Ʈ������ �ϳ��� ���ۿ� ���� ��츦 �ǹ���

				cout << "Retrieved : key = " << t->key << endl;

				cout << "left child is ";
				if (t->l != NULL) // ã�� ���� ���� �ڽ� ��带 Ž��
					cout << t->l->key << endl;
				else
					cout << "none" << endl;

				cout << "right child is ";
				if (t->r != NULL) // ã�� ���� ������ �ڽ� ��带 Ž��
					cout << t->r->key << endl;
				else
					cout << "none" << endl;
			}

			// ����Ʈ���� �˸°� ������ִ� �Լ�
			bfs(head);
		}
		else if (command == '-')
		{
			// ��ɾ - �� ����Ʈ���� �ִ� ���� ���� ��� ����Ǵ� ���ǹ�

			treeDel(head, key);

			bfs(head);
		}
	}


	return 0;
}

void bfs(node* head)
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
	if (head->r == NULL)
		return;

	// queue<>�� ����Ͽ� ����Ʈ���� node���� bfsŽ����
	queue<node *> q;
	q.push(head->r); // queue�� ù ��带 �Է���

	while (!q.empty())
	{
		// ť�� ���� ������� ��� �ݺ�
		// ť�� ���� ������ ���� �湮���� ���� ��尡 �����ϴ� ���̱� ����
		i++; // ���� Ʈ���� ���̸� ������ ����ؾ��ϴ��� �˷��ִ� ����

		node* x = q.front(); // queue�� ���� ó�� ���� ��ȯ
		q.pop(); // queue�� ���� ó�� ���� ��ȯ

		if (x->l != NULL)
		{
			// pop�� ����� ���� �ڽ� ��尡 NULL�� �ƴ��� Ȯ���ϴ� ���ǹ�

			count++; // �θ��� �ڽ� ���� 1 �÷���(���̰��� ����)
			count2++; // �θ��� �ڽ� ���� 1 �÷���(<, \ ���� ����)

			q.push(x->l); // bfs�̹Ƿ� ã�� �ڽ��� queue�� �Է�
		}
		if (x->r != NULL)
		{
			// pop�� ����� ������ �ڽ� ��尡 NULL�� �ƴ��� Ȯ���ϴ� ���ǹ�

			count++;
			count2++;

			q.push(x->r);
		}

		cout << x->key;
		if (count2 == 2)
		{
			// count2�� 2��� �ǹ̴� �θ� ��尡 �ڽ� ��带 �� �� ������ �ִٴ� �ǹ�
			// �׷��Ƿ� <(�ڽ��� �� ��)�� �����

			cout << "< ";
		}
		else if(count2 == 1)
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


node* treeSearch(node* head, int xkey)
{
	// xkey���� ã�� �θ��� ���� ����ϴ� �Լ�
	// ��� ���� ã�� ���ϸ� NULL�� ���

	node* t;
	node* p;
	t = head->r;
	p = t;

	while (t != NULL)
	{
		if (xkey == t->key)
		{
			// Ű ã���� ����Ǵ� ���ǹ�

			return p;
		}

		p = t; // �θ��� ���� ����ϹǷ� p=t�� ����
		
		if (xkey < t->key)
		{
			// �� ������ ����� ������ ã��

			t = t->l;
		}
		else if (xkey > t->key)
		{
			// �� ������ ����� �������� ã��

			t = t->r;
		}
	}
	return NULL;
}

void treeInsert(node* head, int xkey)
{
	// xkey���� ����Ʈ���� ���Խ�Ű�� �Լ�

	node* p, * t;
	p = head;
	t = p->r; // head�� �����ʺ��� ã��

	while (t != NULL)
	{
		// t�� NULL�� �Ǳ� ������ �ݺ��ϴ� �ݺ���

		p = t; // �θ� ��忡 ���� ����

		if (xkey == t->key) // ������ Ű�� �����ϸ� �������� �ʰ� ����
			return;
		else if (xkey < t->key)
		{
			// Ű ���� ����� Ű ������ ������ ����� �������� Ž��

			t = t->l;
		}
		else
		{
			// Ű ���� ����� Ű ������ ������ ����� ���������� Ž��

			t = t->r;
		}
	}
	t = (node*)malloc(sizeof * t); // ������ ��带 �������� ����
	t->key = xkey;
	t->l = NULL;
	t->r = NULL;

	if (xkey < p->key)
	{
		// �θ� ����� Ű ���� �� �� ������ ���ʿ� ����

		p->l = t;
	}
	else
	{
		// �θ� ����� Ű ���� �� �� ũ�� �����ʿ� ����

		p->r = t;
	}
}

void treeDel(node* head, int xkey)
{
	// Ʈ������ �ش�Ǵ� Ű ���� �����ϴ� �Լ�

	node* p, * c, * t, * x, *temp;
	p = head;
	x = head->r;
	
	temp = treeSearch(p, xkey); // ������ Ű�� �θ��带 Ž��
	if (temp == NULL) // NULL�̸� Ű�� ã�� �������� �ǹ�
		return;
	else if (temp->l != NULL && xkey == temp->l->key)
	{
		// �θ����� ���� �ڽ��� NULL�� �ƴϰ� Ű ���� ���ٸ�
		// ������ ���� ã������ �ǹ��ϴ� ���ǹ�

		p = temp;
		x = temp->l;
		t = x;
	}
	else if (temp->r != NULL && xkey == temp->r->key)
	{
		// �θ����� ������ �ڽ��� NULL�� �ƴϰ� Ű ���� ���ٸ�
		// ������ ���� ã������ �ǹ��ϴ� ���ǹ�

		p = temp;
		x = temp->r;
		t = x;
	}
	else
	{
		// �θ��尡 �� head�� ���ǹ�
		// ������ ���� Ʈ���� ù ��° ������� �ǹ�

		x = temp;
		t = x;
	}

	if (t->r == NULL)
	{
		// ������ �ڽ��� ���� ���

		x = t->l;
	}
	else if (t->r->l == NULL)
	{
		// ������ �ڽ��� ���� �ڽ��� ���� ���

		x = t->r;
		x->l = t->l;
	}
	else
	{
		// �� �� ���� �̿��� ��� ���

		c = x->r;
		while (c->l->l != NULL)
			c = c->l; // ������ �κг������� ���� ���� Ű ���� ã��

		x = c->l;
		c->l = x->r;
		x->l = t->l;
		x->r = t->r;
	}

	free(t); // ��� ����

	if (xkey < p->key)
	{
		// x�� �θ��尡 xkey���� ������ ���ο� �ڽ� ��带 �θ���
		// ���ʿ� ����

		p->l = x;
	}
	else
	{
		// x�� �θ��尡 xkey���� ũ�� ���ο� �ڽ� ��带 �θ���
		// �����ʿ� ����

		p->r = x;
	}
}