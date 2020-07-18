#include <iostream>
#include <queue>

using namespace std;

typedef struct node
{
	node* l; // node의 l
	int key; // node의 key
	node* r; // node의 r
}node;

void bfs(node*);
node* treeSearch(node*, int);
void treeInsert(node*, int);
void treeDel(node*, int);

int main(void)
{
	char command; // 명령을 입력받는 변수
	int key; // key값을 입력받는 변수

	// Tree initialization
	node* t, * head;
	head = (struct node*)malloc(sizeof * head);
	head->l = NULL;
	head->r = NULL;
	head->key = 0;

	// 기본 출력 부분
	cout << "Commands:\n" << "\t+key : Insert(or update) element\n";
	cout << "\t?key : Retrieve element\n";
	cout << "\t-key : Remove element\n";
	cout << "\tQ    : Quit the test program\n" << endl;
	cout << "Empty tree;\n" << endl;

	while(1)
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

			treeInsert(head, key);
			cout << "Insert : key = " << key << endl;
			// bfs방법으로 트리를 탐색하여 트리를 적절하게 출력해주는 함수
			bfs(head);
		}
		else if (command == '?')
		{
			// ? 명령어로 찾을 키 값이 어디에 있고 자식 노드들에는 어떤 값이 있는지 확인하는 조건문

			// treeSearch()함수는 찾은 노드의 헤더를 반환
			t = treeSearch(head, key);

			if (t == NULL) // 만약 반환된 treeSearch()함수의 값이 NULL이면 값을 찾지 못했음을 의미함
				cout << "트리에 " << key << "값이 존재하지 않는다." << endl;
			else if (t->l != NULL && key == t->l->key)
			{
				// 반환된 값의 왼쪽 자식이 NULL이 아니고 그 노드의
				// key값이 찾으려는 값과 같다면 실행되는 조건문

				cout << "Retrieved : key = " << t->l->key << endl;

				cout << "left child is ";
				if (t->l->l != NULL) // 찾은 값의 왼쪽 자식 노드를 탐색
					cout << t->l->l->key << endl;
				else
					cout << "none" << endl;

				cout << "right child is ";
				if (t->l->r != NULL) // 찾은 값의 오른쪽 자식 노드를 탐색
					cout << t->l->r->key << endl;
				else
					cout << "none" << endl;
			}
			else if (t->r != NULL && key == t->r->key)
			{
				// 반환된 값의 오른쪽 자식이 NULL이 아니고 그 노드의
				// key값이 찾으려는 값과 같다면 실행되는 조건문

				cout << "Retrieved : key = " << t->r->key << endl;

				cout << "left child is ";
				if (t->r->l != NULL) // 찾은 값의 왼쪽 자식 노드를 탐색
					cout << t->r->l->key << endl;
				else
					cout << "none" << endl;

				cout << "right child is ";
				if (t->r->r != NULL) // 찾은 값의 오른쪽 자식 노드를 탐색
					cout << t->r->r->key << endl;
				else
					cout << "none" << endl;
			}
			else
			{
				// 반환된 값의 key값이 찾으려는 키 값과 같다면 실행되는 조건문
				// 즉 트리에는 하나의 노드밖에 없는 경우를 의미함

				cout << "Retrieved : key = " << t->key << endl;

				cout << "left child is ";
				if (t->l != NULL) // 찾은 값의 왼쪽 자식 노드를 탐색
					cout << t->l->key << endl;
				else
					cout << "none" << endl;

				cout << "right child is ";
				if (t->r != NULL) // 찾은 값의 오른쪽 자식 노드를 탐색
					cout << t->r->key << endl;
				else
					cout << "none" << endl;
			}

			// 이진트리를 알맞게 출력해주는 함수
			bfs(head);
		}
		else if (command == '-')
		{
			// 명령어가 - 즉 이진트리에 있는 값을 빼는 경우 실행되는 조건문

			treeDel(head, key);

			bfs(head);
		}
	}


	return 0;
}

void bfs(node* head)
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
	if (head->r == NULL)
		return;

	// queue<>를 사용하여 이진트리의 node들을 bfs탐색함
	queue<node *> q;
	q.push(head->r); // queue에 첫 노드를 입력함

	while (!q.empty())
	{
		// 큐에 값이 있을경우 계속 반복
		// 큐에 값이 있으면 아직 방문하지 않은 노드가 존재하는 것이기 때문
		i++; // 언제 트리의 높이를 높여서 출력해야하는지 알려주는 변수

		node* x = q.front(); // queue의 제일 처음 값을 반환
		q.pop(); // queue의 제일 처음 값을 반환

		if (x->l != NULL)
		{
			// pop된 노드의 왼쪽 자식 노드가 NULL이 아닌지 확인하는 조건문

			count++; // 부모의 자식 수를 1 올려줌(높이관여 변수)
			count2++; // 부모의 자식 수를 1 올려줌(<, \ 관여 변수)

			q.push(x->l); // bfs이므로 찾은 자식을 queue에 입력
		}
		if (x->r != NULL)
		{
			// pop된 노드의 오른쪽 자식 노드가 NULL이 아닌지 확인하는 조건문

			count++;
			count2++;

			q.push(x->r);
		}

		cout << x->key;
		if (count2 == 2)
		{
			// count2가 2라는 의미는 부모 노드가 자식 노드를 두 개 가지고 있다는 의미
			// 그러므로 <(자식이 두 개)를 출력함

			cout << "< ";
		}
		else if(count2 == 1)
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


node* treeSearch(node* head, int xkey)
{
	// xkey값을 찾아 부모의 값을 출력하는 함수
	// 어떠한 값도 찾지 못하면 NULL을 출력

	node* t;
	node* p;
	t = head->r;
	p = t;

	while (t != NULL)
	{
		if (xkey == t->key)
		{
			// 키 찾으면 실행되는 조건문

			return p;
		}

		p = t; // 부모의 값을 출력하므로 p=t를 해줌
		
		if (xkey < t->key)
		{
			// 더 작으면 노드의 왼쪽을 찾음

			t = t->l;
		}
		else if (xkey > t->key)
		{
			// 더 작으면 노드의 오른쪽을 찾음

			t = t->r;
		}
	}
	return NULL;
}

void treeInsert(node* head, int xkey)
{
	// xkey값을 이진트리에 삽입시키는 함수

	node* p, * t;
	p = head;
	t = p->r; // head의 오른쪽부터 찾음

	while (t != NULL)
	{
		// t가 NULL이 되기 전까지 반복하는 반복문

		p = t; // 부모 노드에 대한 정보

		if (xkey == t->key) // 동일한 키가 존재하면 삽입하지 않고 복귀
			return;
		else if (xkey < t->key)
		{
			// 키 값이 노드의 키 값보다 작으면 노드의 왼쪽으로 탐색

			t = t->l;
		}
		else
		{
			// 키 값이 노드의 키 값보다 작으면 노드의 오른쪽으로 탐색

			t = t->r;
		}
	}
	t = (node*)malloc(sizeof * t); // 삽입할 노드를 동적으로 생성
	t->key = xkey;
	t->l = NULL;
	t->r = NULL;

	if (xkey < p->key)
	{
		// 부모 노드의 키 값과 비교 후 작으면 왼쪽에 삽입

		p->l = t;
	}
	else
	{
		// 부모 노드의 키 값과 비교 후 크면 오른쪽에 삽입

		p->r = t;
	}
}

void treeDel(node* head, int xkey)
{
	// 트리에서 해당되는 키 값을 삭제하는 함수

	node* p, * c, * t, * x, *temp;
	p = head;
	x = head->r;
	
	temp = treeSearch(p, xkey); // 삭제할 키의 부모노드를 탐색
	if (temp == NULL) // NULL이면 키를 찾지 못했음을 의미
		return;
	else if (temp->l != NULL && xkey == temp->l->key)
	{
		// 부모노드의 왼쪽 자식이 NULL이 아니고 키 값이 같다면
		// 적절한 값을 찾았음을 의미하는 조건문

		p = temp;
		x = temp->l;
		t = x;
	}
	else if (temp->r != NULL && xkey == temp->r->key)
	{
		// 부모노드의 오른쪽 자식이 NULL이 아니고 키 값이 같다면
		// 적절한 값을 찾았음을 의미하는 조건문

		p = temp;
		x = temp->r;
		t = x;
	}
	else
	{
		// 부모노드가 곧 head인 조건문
		// 적절한 값이 트리의 첫 번째 노드임을 의미

		x = temp;
		t = x;
	}

	if (t->r == NULL)
	{
		// 오른쪽 자식이 없는 경우

		x = t->l;
	}
	else if (t->r->l == NULL)
	{
		// 오른쪽 자식의 왼쪽 자식이 없는 경우

		x = t->r;
		x->l = t->l;
	}
	else
	{
		// 위 두 조건 이외의 모든 경우

		c = x->r;
		while (c->l->l != NULL)
			c = c->l; // 오른쪽 부분나무에서 제일 작은 키 값을 찾음

		x = c->l;
		c->l = x->r;
		x->l = t->l;
		x->r = t->r;
	}

	free(t); // 노드 삭제

	if (xkey < p->key)
	{
		// x의 부모노드가 xkey보다 작으면 새로운 자식 노드를 부모의
		// 왼쪽에 저장

		p->l = x;
	}
	else
	{
		// x의 부모노드가 xkey보다 크면 새로운 자식 노드를 부모의
		// 오른쪽에 저장

		p->r = x;
	}
}