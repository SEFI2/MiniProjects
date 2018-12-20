#include "Node.h"

Node::Node() {
  this->prev = NULL;
  this->next = NULL;
  this->word = "";
}

Node::Node(std::string word) {
  this->prev = NULL;
  this->next = NULL;
  this->word = word;
}

Node::Node(std::string word, Node * prev) {
  this->prev = prev;
  this->next = NULL;
  this->word = word;

  if (prev) {
    prev->next = this;
  }
}

std::string& Node::getWord() {
  return this->word;
}

Node* Node::getNext() const {
  return this->next;
}

Node* Node::getPrev() const {
  return this->prev;
}

void Node::setWord(std::string word) {
  this->word = word;
}

void Node::setNext(Node* next) {
  this->next = next;
}

void Node::setPrev(Node* prev) {
  this->prev = prev;
}
