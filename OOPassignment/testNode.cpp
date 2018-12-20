#include <iostream>
#include "Node.h"
#include <string>
#include <assert.h>

using namespace std;

int main(int argc, char const *argv[]) {
  Node *n = new Node ("curr");
  assert(n != NULL);
  n->setNext(new Node("next"));
  assert(n->getNext() != NULL);
  assert(n->getNext()->getPrev() == NULL);
  n->getNext()->setPrev(n);
  n->setPrev(n->getNext());
  n->getNext()->setNext(n);
  return 0;
}
