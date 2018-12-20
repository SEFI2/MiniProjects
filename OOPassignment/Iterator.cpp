#include "Iterator.h"

Iterator::Iterator(Node* currIn) {
    curr = currIn;
}

const std::string Iterator::operator*() const {
  return curr == NULL ? "" : curr->getWord();
}

Iterator& Iterator::operator++() {
  if (curr == NULL) {
    return *this;
  }
  curr = curr->getNext();
  return *this;
}

Iterator Iterator::operator++(int i) {
  if (curr == NULL) {
    return *this;
  }
  Iterator toRet(curr);
  curr = curr->getNext();
  return toRet;
}

Iterator Iterator::operator+(const int &num) {
  Iterator toRet(curr);
  for (int cnt = 0 ; cnt < num ; cnt ++){
    ++ toRet;
  }
  return toRet;
}

Iterator Iterator::operator+=(const int &num) {
  for (int cnt = 0 ; cnt < num ; cnt ++){
    if (curr == NULL) {
      // cout << "[operator +=] NULL\n";
      return *this;
    }
    curr = curr->getNext();
  }
  return *this;
}

Iterator& Iterator::operator--() {
  if (curr == NULL) {
    return *this;
  }
  curr = curr->getPrev();
  return *this;
}

Iterator Iterator::operator--(int i) {
  if (curr == NULL) {
    return *this;
  }
  Iterator toRet(curr);
  curr = curr->getPrev();
  return toRet;
}


// for iterator math
// for example it = it - 2;
Iterator Iterator::operator-(const int & num){
  Iterator toRet(curr);
  for (int cnt = 0 ; cnt < num ; cnt ++){
    toRet --;
  }
  return toRet;
}

// for iterator math
// for example it -= 2;
Iterator Iterator::operator-=(const int & num) {
  for (int cnt = 0 ; cnt < num ; cnt ++){
    if (curr == NULL) {
      // cout << "[operator +=] NULL\n";
      return *this;
    }
    curr = curr->getPrev();
  }
  return *this;
}

// equality operator
// is true if 2 iterators are pointing to the same node
bool Iterator::operator==(const Iterator &other) {
  return other.curr == curr;
}

// inequality operator
// is true if 2 iterators are pointing to different nodes
bool Iterator::operator!=(const Iterator &other) {
  return other.curr != curr;
}

// returns the node to which the iterator points
Node *& Iterator::getCurr() {
  return curr;
}
