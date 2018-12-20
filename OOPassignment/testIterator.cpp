#include <iostream>
#include <string>
#include <assert.h>
#include "Iterator.h"
#include "Node.h"


using namespace std;

void add_to_root(Node* &n, string new_word) {
  if (n == NULL) {
    n = new Node(new_word);
    n->setNext(n);
    n->setPrev(n);
    return;
  }

  Node* x = n->getPrev();

  Node* new_node = new Node(new_word);
  //x->setNext(new_node);
  new_node->setPrev(x);
  new_node->setNext(x->getNext());
  x->getNext()->setPrev(new_node);
  x->setNext(new_node);
}

void show_node(Node* n) {
  if (n == NULL) {
    cout << "Node is NULL\n";
    return;
  }
  if (n == n->getNext()) {
    cout << n->getWord() << "\n";
    return;
  }

  Node* x = n;
  while (x->getNext() != n) {
    cout << x->getWord() << "\n";
    x = x->getNext();
  }
  cout << x->getWord() << "\n";
}

int main(int argc, char const *argv[]) {
  Node *root = NULL;
  add_to_root(root, "I"); // 0
  Iterator u(root);
  assert((u + 1) == u);

  add_to_root(root, "am"); // 1
  // show_node(u.getCurr());
  assert((u + 1) != u);

  Iterator f(root);
  assert((f += 1) == f);
  assert(*f == "am");

  add_to_root(root, "writing"); // 2
  add_to_root(root, "this"); // 4
  add_to_root(root, "right"); // 5
  add_to_root(root, "now"); // 6

  // show_node(root);

  Iterator it(root);
  it ++;
  assert(*it == "am");

//  ++ it;
  assert (*(++it) == "writing");
  it -= 2;
  assert (*it == "I");
  assert (*(it - 1) == "now");
  it += 3;
  assert(*it == "this");
  it +=  3;
  assert(*it == "I");
  it -= 2;
  assert(*it == "right");
  -- it;
  assert(*it == "this");
  it --;
  assert(*it == "writing");
  assert (*(it + 3) == "now");
  Iterator another (root);
  assert(another != it);
  another -= 1;
  assert(another == (it + 3));
 //show_node(f.getCurr());

  return 0;
}
