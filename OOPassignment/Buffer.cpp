#include "Buffer.h"
#include <iostream>

Buffer::Buffer() {

}

Buffer::Buffer(const Buffer &other) {
  copy(other);
}

Buffer::~Buffer() {

}


Buffer& Buffer::operator=(const Buffer & original) {
  copy(original);
  return *this;
}

Node * Buffer::getHead() {
  return head;
}

Node * Buffer::getTail() {
  return head == NULL ? NULL : head->getPrev();
}

std::string Buffer::getHeadElement() {
  return head == NULL ? "" : getHead()->getWord();
}

std::string Buffer::getTailElement() {
  return head == NULL ? "" : getTail()->getWord();
}

void Buffer::produceAtHead(const std::string str) {
    if (head == NULL) {
      head = new Node(str);
      head->setNext(head);
      head->setPrev(head);
    } else {
      Node *tail = getTail();
      Node* new_node = new Node(str);

      new_node->setPrev(tail);
      new_node->setNext(head);

      head->setPrev(new_node);
      tail->setNext(new_node);
      // one line difference
      head = new_node;
    }
    count ++;
}

void Buffer::produceAtTail(const std::string str) {
    if (head == NULL) {
      head = new Node(str);
      head->setNext(head);
      head->setPrev(head);
    } else {
      Node *tail = getTail();
      Node* new_node = new Node(str);

      new_node->setPrev(tail);
      new_node->setNext(head);

      head->setPrev(new_node);
      tail->setNext(new_node);
    }
    count ++;
}

Iterator Buffer::produceAtMiddle(Iterator pos, const std::string str) {
  Node* next = pos.getCurr();
  Node* prev = pos.getCurr()->getPrev();

  Node* new_node = new Node(str);

  new_node->setPrev(prev);
  new_node->setNext(next);

  next->setPrev(new_node);
  prev->setNext(new_node);
  if (head == pos.getCurr())
    head = new_node;
  count ++;
}


void Buffer::consumeAtHead() {
  if (head == NULL) {
    return;
  }
  if (head == head->getNext()) {
    delete head;
    head = NULL;
  } else {
    Node *tail = getTail();
    head->getNext()->setPrev(tail);
    head->getPrev()->setNext(head->getNext());
    Node *old_head = head;
    head = head->getNext();
    delete old_head;
    old_head = NULL;
  }
  count --;
}

void Buffer::consumeAtTail() {
  if (head == NULL) {
    return;
  }
  if (head == head->getNext()) {
    delete head;
    head = NULL;
  } else {
    // one line is changed from consumeAtHead
    Node *tail = getTail();
    head->setPrev(tail->getPrev());
    tail->getPrev()->setNext(head);
    delete tail;
  }
  count --;
}

void Buffer::consume(Iterator it) {
  Node* curr = it.getCurr();
  Node* prev = curr->getPrev();
  Node* next = curr->getNext();
  prev->setNext(next);
  next->setPrev(prev);
  if (head == curr) {
    head = next;
  }
  delete curr;
  curr = NULL;
  count --;
}

void Buffer::consume(Iterator s, Iterator t) {
  Iterator temp;
  while (s != t) {
    temp = s;
    consume(temp);
    s ++;
  }
}

unsigned Buffer::size() const {
  return count;
}

bool Buffer::isEmpty() {
  return count == 0;
}

std::string& Buffer::operator[](int i) const {
  if (i >= count) {
    throw "size is less than given index";
  }

  Node* pt = head;
  for (int j = 0 ; j < i ; ++j) {
    pt = pt->getNext();
  }
  return pt->getWord();
}

Iterator Buffer::getHeadItr() {
  Iterator it(getHead());
  return it;
}

Iterator Buffer::getTailItr() {
  Iterator it(getTail());
  return it;
}

Iterator Buffer::getNextItr(Iterator it) {
  return ++it;
}

Iterator Buffer::getPrevItr(Iterator it) {
  return --it;
}

void Buffer::print() {
  if (isEmpty()) {
    std::cout << "->\n\n";
    return;
  }
  if (this->size() == 1) {
    std::cout << (*this)[0] << "\n";
    return;
  }
  std::cout << (*this)[0];
  for (int i = 1 ; i < this->size() ; ++i) {
    std::cout << " -> " << (*this)[i];
  }
  std::cout << "\n\n";
}

void Buffer::copy(const Buffer & other) {
  clear();
  for (int i = 0 ; i < other.size() ; ++i) {
    produceAtTail(other[i]);
  }
}

void Buffer::clear() {
  count = 0;
  deleteBuffer(head);
}

void Buffer::deleteBuffer(Node * p) {
  if (p == NULL)return;
  Node* nx = p->getNext();
  delete p; p = NULL;
  deleteBuffer(nx);
}

bool findNode(Iterator first, Iterator last, std::string str) {
    if (*first == str)
      return true;
    while (first != last) {
      first ++;
      if (*first == str) return true;
    }
    return false;
}
