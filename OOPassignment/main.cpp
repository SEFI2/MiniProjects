
#include <iostream>
#include "Buffer.h"
#include "Iterator.h"

using namespace std;

int main() {
  Buffer v1;
  Iterator it;

  v1.produceAtHead("Object");
  v1.produceAtHead("Is");
  v1.produceAtHead("This");
  v1.produceAtTail("Oriented");
  v1.produceAtTail("Programming");

  cout << "count = " << v1.size() << endl; // print "5"
  cout << "first string= " << v1.getHeadElement() << endl; // print "This"
  cout << "last string= " << v1.getTailElement() << endl;  // print "Programming"
  v1.print(); // This -> Is -> Object -> Oriented -> Programming

  v1.consumeAtHead();
  v1.consumeAtTail();
  v1.print(); // Is -> Object -> Oriented

  it = v1.getHeadItr();
  it = v1.getNextItr(it);
  v1.consume(it);
  v1.print(); // Is -> Oriented


  // insert in middle
  it = v1.getTailItr();
  it = v1.produceAtMiddle(it, "Object");
  v1.print(); // Is -> Object -> Oriented
  Buffer new_one(v1);


  // test find
  cout << findNode(v1.getHeadItr(), v1.getTailItr(), "hallo") << endl;

  // empty buffer
  v1.consumeAtHead();
  v1.consumeAtHead();
  v1.consumeAtHead();
  cout << "count = " << v1.size() << endl; // 0
  v1.print(); // ->
  // test isEmpty()
  if (v1.isEmpty())
    cout << "empty buffer" << endl;
  new_one.produceAtHead("jelovek");
  new_one.produceAtHead("kakoyto");
  new_one.produceAtHead("no one");
  new_one.produceAtHead("WIM");

  new_one.print();

  Iterator it1 = new_one.getHeadItr();
  it1 += 2;
  new_one.consume (it1);
  Iterator it2 = new_one.getTailItr();
  ++ it2;
  new_one.consume(it2);

  new_one.print();
  it2 = new_one.getTailItr();
  it2 ++;
  new_one.produceAtMiddle(it2, "jindi");
  new_one.print();


  return 0;
}
