#include <stdio.h>
#include <stdlib.h>

struct Node {
  int Data;
	char Init;
  struct Node* Next;
};

struct Node* create(const int data, struct Node* next) {
  struct Node* p = (struct Node*)malloc(sizeof(struct Node));
  p->Data = data;
	p->Init = (char) (data + 65);
  p->Next = next;
  return p;
}

int main(int argc, char** argv) {
  struct Node *n = NULL;
  for (int i = 0; i < argc; i++) {
    n = create(i, n);
  }
  while (n) {
    printf("%d\n", n->Data);
		printf("%c\n", n->Init);
    n = n->Next;
  }
  return 0;
}
