/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

/*
[main문 설명]
command변수를 선언해 입력을 받고 switch-case문을 사용해 입력받은 문자에 대한 구문을 실행함
*/
int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf("[----- [Son Ji Yeon] [2020039104] -----]\n");	
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { //연결리스트의 헤드노드를 가리키는 포인터(h)와 새로운 노드에 저장될 값(key)을 매개변수로짐

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 동적할당
	node->key = key; //node의 key에 key 값 저장
	node->link = NULL; //node의 link를 NULL로 설정

	if (h->first == NULL) //리스트에 값이 존재하지 않으면
	{
		h->first = node; //헤드는 생성된 새로운 노드를 가리킴
		return 0;
	}

	/*리스트 검색할 구조체 포인터 n, trail 생성
	초기에 둘은 헤드와 같은 노드를 가리킴*/
	listNode* n = h->first;
	listNode* trail = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = node; //리스트의 첫번째 값을 node로 설정
				node->link = n; //node의 다음 값은 n
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n; //새로운 노드는 n을 가리킴
				trail->link = node; //n의 이전 노드는 새 노드를 가리킴
			}
			return 0;
		}

		trail = n; //trail에 n의 위치 대입
		n = n->link; //n은 다음 노드 위치로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; //마지막 노드가 새 노드를 가리킴
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {  //연결리스트의 헤드노드를 가리키는 포인터(h)와 새로운 노드에 저장될 값(key)을 매개변수로짐
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 동적할당
	node->key = key; //node의 값 key로 설정
	node->link = NULL; //node의 link NULL로 설정

	if (h->first == NULL) //리스트에 값이 존재하지 않으면
	{
		h->first = node; //헤드는 생성된 새로운 노드를 가리킴
		return 0;
	}

	/*리스트 검색할 구조체 포인터 n 생성하며, 헤드와 같은 노드를 가리키게 함*/
	listNode* n = h->first; //
	while(n->link != NULL) { //리스트 끝에 도달할 때까지 반복
		n = n->link; //다음 노드로 이동
	}
	n->link = node; //마지막 노드의 link 값을 새로운 노드로 설정
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { //연결리스트의 헤드노드를 가리키는 포인터(h)와 새로운 노드에 저장될 값(key)을 매개변수로짐

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 동적할당
	node->key = key; //새 노드에 key값 할당

	node->link = h->first; //새 노드의 link가 첫 번째 노드를 가리키는 값을 가리키게 함
	h->first = node; //헤드 노드가 가리키는 노드에 새로운 노드를 할당

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { //연결리스트의 헤드노드를 가리키는 포인터(h)와 새로운 노드에 저장될 값(key)을 매개변수로짐

	if (h->first == NULL) //리스트가 빈 경우
	{
		printf("nothing to delete.\n"); //메시지 출력
		return 0; //0 반환
	}

	//리스트에서 삭제할 노드를 찾기 위해 사용할 포인터 변수 n과 이전 노드를 가리키는 trail 변수 생성
	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) { //삭제할 토드를 찾았을 시
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //현재 노드(n)
				h->first = n->link; //헤드 노드를 삭제할 노드의 다음 노드로
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; //이전 노드와 삭제할 노드의 다음 노드를 연결
			}
			free(n); //동적할당 해제
			return 0;
		}

		//다음 노드 탐색을 위해 포인터를 이동
		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //만약 리스트에 값이면
	{
		printf("nothing to delete.\n"); //메시지 출력
		return 0; //0 반환
	}

	//리스트에서 삭제할 노드를 찾기 위해 사용할 포인터 변수 n과 이전 노드를 가리키는 trail 변수 생성
	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL; //노드 삭제 후 헤드 포인터에 NULL 할당
		free(n); //동적할당 해제
		return 0; //0 반환
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n); //동적할당 해제

	return 0; //0 반환
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //리스트에 값이 없다면
	{
		printf("nothing to delete.\n"); //메시지 출력
		return 0; //0 반환
	}
	listNode* n = h->first; //n에 첫 번째 노드를 가리키는 포인트 할당

	h->first = n->link; //헤드 포인터를 첫 번째 노드의 다음 노드로 변경
	free(n); //동적할당 해제

	return 0; //0 반환
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if(h->first == NULL) { //h의 다음 값이 비어있는 경우
		printf("nothing to invert...\n"); //메시지 력
		return 0; //0 반환
	}

	// 현재 노드(n), 전 노드(trail), 전전 노드(middle)를 저장할 포인터 변수 선언
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){ //리스트 끝까지
		// 이전 노드를 middle로 옮기고, 현재 노드를 middle로 옮김
		trail = middle;
		middle = n;
		n = n->link; //다음 노드로 이동
		middle->link = trail; //middle의 link를 이전 노드와 연결
	}

	h->first = middle; //첫번째 노드를 middle로 바꿈

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

