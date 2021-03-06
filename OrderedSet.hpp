// Title: Lab 14 OrderedSet class and implementation
// Author: Zack Pace
// Description: This file is used to create the class OrderedSet, as well as defining
// member functions for the created class.

#ifndef ORDEREDSET_HPP
#define ORDEREDSET_HPP

#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

enum dtype { FORWARD, BACKWARD };

template <class ST> class OrderedSet;
template <class ST> ostream & operator <<
        (ostream & outs, const OrderedSet<ST> & L);

template <class ST>
class OrderedSet
{
   private:
      struct LNode
      {
         LNode ();
         ST data;
         LNode * next;
         LNode * prev;
      };

   public:
     class Exception
     {
     public:
       Exception ();
       Exception (string msg);
       Exception (int idx);

       string Message () const;

     private:
       string message;
     };

       class Iterator
       {
       public:
               Iterator ();
               Iterator (LNode * NP);
	 // ST & operator * () const;
	       const ST operator * ()const;
	       Iterator operator ++ ();
               Iterator operator ++ (int);
               Iterator operator -- ();
               Iterator operator -- (int);
               bool operator == (const Iterator & other) const;
               bool operator != (const Iterator & other) const;

       private:
               LNode * current;
       };

       OrderedSet ();
      OrderedSet (const OrderedSet & other);
      ~OrderedSet ();
      OrderedSet & operator = (const OrderedSet & other);
      bool operator == (const OrderedSet & other);
      ST  operator [] (const int & index) const;
      int Size () const;
      void SetDirection (dtype dir);
      dtype GetDirection () const;
      friend ostream & operator << <>
              (ostream & outs, const OrderedSet<ST> & L);
      void Forward (void function (const ST & param));
      void Backward (void function (const ST & param));
      void Clear ();
      bool IsEmpty () const;
      bool IsIn (const ST & value);
      bool Insert ( const ST & value);
      bool Delete (const ST & value);
      OrderedSet operator + (const OrderedSet & other);
      OrderedSet operator * (const OrderedSet & other);

    Iterator begin () const;
    Iterator rbegin () const;
    Iterator end () const;
    Iterator rend () const;
private:

  bool InsertFirst (const ST & value);
  bool InsertLast (const ST & value);
  bool DeleteFirst ();
  bool DeleteLast ();
      LNode * first;
      LNode * last;
      int size;
      dtype direction;
};

template <class ST>
OrderedSet<ST>::Iterator::Iterator()
{
  current = NULL; //sets defualt values to value current before its assigned.
}

template <class ST>
OrderedSet<ST>::Iterator::Iterator(LNode * NP)
{
  current = NP; //constructor of Iterator assigns LNode * to current
}

template <class ST>
const ST  OrderedSet<ST>::Iterator::operator * () const
//this function is the dereferencing operator, it returns the data which a pointer is pointing to.
{
  if (current == NULL) //checks for a case which an error would return
    throw (Exception("Cannot dereference a NULL pointer")); //statement will print to cerr if conditional is true
  return current->data;
}

template  <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator++()
//post incrementor for iterator
{
  if (current->next == NULL) //checks for error case
    throw (Exception("Cannot increment a NULL iterator"));

  current = current->next;//does what function normally does
  return *this;
    
  /*  catch (const char * message)
    {
      cerr << message << endl;
      exit(1);
      
    }
*/
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++ (int)
// pre - incrementor for iterator
{
  if (current->next == NULL) //check for error case
    throw (Exception("Cannot increment a NULL iterator"));
  Iterator temp = *this; // current is saved to variable
  current = current->next; // current is incremented 
  return temp; // old value is returned

}

template  <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator--()
// post decrementor for iterator
{
  if (current->prev == NULL)//checks for error case
    throw (Exception("Cannot decrement a NULL iterator"));
  current = current->prev; //iterator is decremented
  return *this; // return statement
}


template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator -- (int)
// pre decrementor for iterator
{
  if (current->prev == NULL) // checks fo an error case
    throw (Exception("Cannot decrement a NULL iterator"));
  Iterator temp = *this; //current is saved into temp
  current = current->prev; //current is decremented
  return temp; // temp is returned
  }

template <class ST>
bool OrderedSet<ST>::Iterator::operator==(const Iterator & other) const
// equality operator for the iterator
{
  return current == other.current; //returns true if they are equal
}



template <class ST>
OrderedSet<ST>::Exception::Exception ()
// this is the basecase type implementation of Exception(), it doesnt have to do anything
// because nothing is passed to the function
{  
}

template <class ST>
OrderedSet<ST>::Exception::Exception (string msg)
// if Exception() is used and a string is being thrown
{
  message = msg; //assignment of member variable of Exception
}

template <class ST>
OrderedSet<ST>::Exception::Exception (int idx)
// if Exception() is used and a integer is thrown
{
  stringstream ss (stringstream::in | stringstream::out); //use of stringstream to print out at end
  ss << "Subscript [" << idx << "] out of range"; //creates input for stringstream to be outted later
  getline(ss, message); //makes a line so message can put to cerr

}

template <class ST>
string OrderedSet<ST>::Exception::Message() const
// this function is called as a getter function
{
  return message; //return data
}

template <class ST>
ST  OrderedSet<ST>::operator [] (const int & index) const
// this operator searches throught the OrderedSet to the chronological space <index>
// error cases are also checked for.  
{
  if (index < 0)//check for error case
    throw (Exception(index)); // calls exception and the statement used for index operator
  if (index >= size)// check for error case
    throw (Exception(index)); // calls exception and the statement used for index operator
  typename OrderedSet<ST>::LNode * n = first; //starts from beginning 
  for (int i = 0; i < index; i++) //there will be as many iterations as index
    n = n->next; //traverse to the next LNode
  return n->data;//return data
  
}

template <class ST>
bool OrderedSet<ST>::Iterator::operator!=(const Iterator &other) const
//function will return true if the two items being compared are not equal.
{
    return current != other.current;
}


template <class ST>
OrderedSet<ST>::LNode::LNode ()
// This function will give default values to an instance of LNode.
{
    next = NULL;
    prev = NULL;
}

      
template <class ST>
OrderedSet<ST>::OrderedSet ()
// This function will set default values to a linked list.
{
    size = 0;
    first = NULL;
    last = NULL;
    direction = FORWARD;
}

template <class ST>
OrderedSet<ST>::OrderedSet (const OrderedSet & other)
// This function will create an new instance of OrderedSet, after using another OrderedSet passed as
// a parameter to input it's data into the new instance of OrderedSet.  
{
  first = last = NULL; //initializes first and last
  size = 0; //initializes size
  for (LNode * n = other.first; n != NULL; n = n->next) //iterates for every LNode inside other
  {
    InsertLast(n->data); // inputs data from other into this via InsertLast()
  }
  direction = other.direction; // intitalizes direction from other
}

template <class ST>
OrderedSet<ST>::~OrderedSet ()
{ // This function will delete an instance of LList and all of the LNodes assigned
  while(first)// The value of first is false when the first * doesnt exist, thrfr empty OrderedSet
    {
      DeleteFirst(); //DeleteFirst takes off one LNode from front
    }
}

template <class ST>
OrderedSet<ST> OrderedSet<ST>::operator + (const OrderedSet<ST> & other)
// This operator adds two OrderedSets together, Insert() is used because if data is 
// a duplicate it is not added to the list, returning an OrderedSet containing the union of the
// two OrderedSets, (this and other)
{
  OrderedSet<ST> US; //creates a empty OrderedSet to hold union of both sets

  LNode * t = first; //creates pointer for this.first
  LNode * o = other.first; //creates pointer other.first

  while (t != last) // goes until last LNode in this
    {
      US.Insert(t->data);  //trys to insert the data at t into US
      t = t->next; // goes to next LNode
    }
  US.Insert(last->data); // trys to insert last peice of data in this

  while (o != other.last) // goes until last LNode in other
    {
      US.Insert(o->data); // trys to insert the data at o into US
      o = o->next; // goes to next LNode
    }

  if (US.IsIn(other.last->data)) //is true if data other.last is already in set
    return US; // return complete union of set
  
  US.Insert(other.last->data);  //trys to insert other.last->data into US 

  return US; // returns complete union of set
}

template <class ST>
OrderedSet<ST> OrderedSet<ST>::operator * (const OrderedSet<ST> & other)
// This operator will find the intersection of two sets, a new OrderedSet will be made
// to contain the intersection. This set will then be returned.
{
  OrderedSet<ST> IS; // new OrderedSet made for intersectin of sets
  LNode * n = other.first; // create pointer to start at first LNode in other
  while (n != other.last) // goes until n is at last LNode
    {
      if (IsIn(n->data)) // checks if data at n is already a value in this 
	IS.Insert(n->data); // inserts data inside both into OrderedSet IS
      
      n = n->next; //traverses to next LNode
    }
  if (IsIn(other.last->data)) //checks if data at other.last
    IS.Insert(other.last->data);

  return IS; //return intersection set
  
}


template <class ST>
OrderedSet<ST> & OrderedSet<ST>::operator = (const OrderedSet<ST> & other)
{ // This function will assign one value of one OrderedSet, other to this
  if (this == &other)//checks to see if the sets are equivelent 
    return * this; //if the sets are already the same this can be returned as is

  while (first) //keeps iterating until first == NULL
    DeleteFirst(); //deletes every value in set

  for (LNode * n = other.first; n != NULL; n = n->next) //iterates through all nodes of other
    InsertLast(n->data); //inserts data sequentially into set, other is already in order

  direction = other.direction; //assign the direction of this to be the same as other
  
  return * this; //returns the this OrderedSet 
}

template <class ST>
bool OrderedSet<ST>::operator == (const OrderedSet & other)
// This function will check to see if this and other are the same set
{
  if ( size != other.size) // if the sizes are not the same the two sets cannot be equal
  {
    return false;
  }
  
  LNode * np1 = first; //sets pointer to this.first 
  LNode * np2 = other.first; // sets pointer to other.first

  while (np1 != NULL) // iterates this.size times 
    {
      if (np1->data != np2->data) // checks to see if the two pointers' data are not equal
	return false; 
      
      np1 = np1->next;//increments np1
      np2 = np2->next;//increments np2
    }

  return true;
}

template <class ST>
int OrderedSet<ST>::Size () const
{ // This function will return the size of the OrderedSet.
  return size;
}

template <class ST>
void OrderedSet<ST>::SetDirection(dtype dir)
// This function will set the direction of the OrderedSet
{
  direction = dir;
}

template <class ST>
dtype OrderedSet<ST>::GetDirection () const
// This function returns the direction of this
{
  return direction;
}

template <class ST>
ostream & operator << (ostream & outs, const OrderedSet<ST> & L)
// This function will traverse the list
// output the data values, each followed by a space
// return outs.
{

  outs << '{';  // brace is needed for format for all cases
  if (L.first == NULL) //checks if OrderedSet L is size 0
    {
      outs << '}'; // closing brace for formatting
      return outs; // returns outs
    }

  if (L.direction == FORWARD) 
  {//print the list from the beginning to end
    outs << L.first->data; // prints first peice of data, bc it must exist to get here
    typename OrderedSet<ST>::LNode * n; // creates an LNode pointer
    for (n = L.first->next; n != NULL; n = n->next) // for loop traverses through OrderedSet L
      outs << ',' << n->data; // adds comma then data 

    outs << '}'; // closing brace for formatting
  }
  else// L.direction == BACKWARD
  {
    outs << L.last->data; //prints last peice of data
    typename OrderedSet<ST>::LNode * p; //creates LNode pointer
    for (p = L.last->prev; p != NULL; p = p->prev) // iterates through OrderedSet L backwards
      outs << ',' << p->data; //add comma then data
    outs << '}'; // closing brace for formatting
  }
  return outs; // return information inside outs
}

template <class ST>
bool OrderedSet<ST>::InsertFirst (const ST & value)
{ // This function will insert an LNode in the the front of the LL.
  LNode * nnp =  new LNode; //allocate space for new node
  if (nnp == NULL)//return false if space cannot be allocated for the node
  {
      return false;
  }  

  if (size != 0) //if size is not 0 then assign pointer to first->prev
    first->prev = nnp;

  if (size == 0) //cases if size is 0, nnp will be the only LNode
  {
    first = nnp; //first * is assigned to nnp
    last = nnp; //last * is assigned to nnp
    nnp->next = NULL; //next should be NULL to prevent problems
  }
  
  nnp->data = value; //set the data of the new node to the input value
  if (size != 0)
    nnp->next = first; // set the next of the new node to the current first

  nnp->prev = NULL; // nothing should always be previous of LNode nnp

  
  first = nnp; //set first to  nnp as last step

  size ++; // increment size
  return true;
}

template <class ST>
bool OrderedSet<ST>::InsertLast (const ST & value)
{ // This function will insert an LNode into the back of the LL.
  if (size == 0)
  {
    return InsertFirst(value); //InsertFirst is used because InsertLast cant deal with size 0 OS
  }
  LNode * n = new LNode; //create new LNode
  if (n == NULL)// if memory cannot be stored 
    return false; // return false

  //setting pointers in new LNode
  n->data = value;//set data in new LNode
  n->next = NULL; //Nothing should come after LNode n
  n->prev = last; //n is now after the last

  //reassigning pointers already existing in OrderedSet
  last->next = n; // reassign last->next to n
  last = n; // reassing last to n

  size++; // increment size
  return true;
}

template <class ST>
bool OrderedSet<ST>::DeleteFirst ()
{ // This function will delete the first LNode in the OrderedSet, reassign pointers, decrement size,
  // will return true if the deletion was successful.
  if (first == NULL) //if the OrderedSet has no LNodes none can be deleted
  {
    return false; // return false
  }
  LNode * temp = first; //create LNode pointer = to first

  if (size == 1) // cases handeled if size is only 1
    {
      //reassigns default values to OrderedSet instance
      delete temp; 
      first = NULL;
      last = NULL;
      size--;
      return true;
    }
  
  first = temp->next;//reassigns value of first to the second LNode in the Set
  first->prev = NULL; //sets prev of new first to NULL
  
  delete temp; //deletes temp, originally the first LNode
  size--; //decrement size

  return true;
}

template <class ST>
bool OrderedSet<ST>::DeleteLast ()
{ // This function will delete the last LNode of the LinkedList.
  if (size == 0)//returning false if size is zero
  {
    return false;
  }
  
  if(size == 1) //conditional to use DeleteFirst function for size of 1 LNodes.
  {
    return DeleteFirst();
  }
  

  LNode * n = last; //creates an LNode pointer to last
  n = n->prev; // sets n to one before the last LNode
  n->next = NULL; // the next of n now NULL
  delete last; //delete LNode being pointed to by last
  last = n; // reassign last to n
  size--;//makes size smaller by 1
  return true;
}
template <class ST>
bool OrderedSet<ST>::IsEmpty () const
// this function checks to see if the set is empty, if this is empty then true is returned.
{
  if (size == 0) // if size is 0 then the list must be empty
    return true;
  return false;
}


template <class ST>
bool OrderedSet<ST>::IsIn (const ST & value)
// this function checks to see if a value is stored in this
{
  if (size == 0) //no data can be stored if size is zero
    return false; //return false
  LNode * n = first; //create LNode pointer to first of this
  for (int i = 0; i < size; i++) //iterates through the this 
  {
    if (n->data == value)  // checks to see if value is equal to n->data
      return true; //returns true because value is in set
    if ((i + 1) == size) // checks if the loop needs to be broken
      break;
    n = n->next; //moves to the next LNode
  }
  return false;
}


template <class ST>
void OrderedSet<ST>::Clear ()
// this function will delete every LNode in the set of this
{
  while (DeleteLast ());
}

template <class ST>
bool OrderedSet<ST>::Delete (const ST & value)
// this function deletes the LNode in the set which has the same data as the parameter value.
{  
  
  if (!IsIn(value)) //if value is not in set it cannot be deleted
    return false;

  if (value == first->data) // checks instance to use DeleteFirst()
    return DeleteFirst();

  if (value == last->data) // checks instance to use DeleteLast()
    return DeleteLast();

  // value must one of the non first or last nodes->data after this point

  LNode * n = first;// creates pointer at first
  while (n->data != value) //keeps iterating through loop until value == n->data
    n = n->next; //traverses through Set

  //n is now pointing to the node to be deleted

  LNode * left, * right = n; //creates two new LNode *s

  
  left = n->prev; //assigns pointer left
  right = n->next; //assigns pointer right

  left->next = right; //reassigns next pointer of left to skip n
  right->prev = left; //reassigns prev pointer of right to skip n
  
  size--; //decrement size
  return true;

}

template <class ST>
bool OrderedSet<ST>::Insert (const ST & value)
//this function will insert a new LNode with data in order with rest of this. the parameter value is
//the data to be in the new LNode
{
  if (IsIn(value)) //if value already exists as data in set it cannot be added
    return false;
  
  if(size == 0) // if size is 0 utilize the InsertFirst function
    return InsertFirst(value);
  
  if (value < first->data) // if value is smaller than smallest value use insertfirst
    return InsertFirst(value);

  if (value > last->data) // if value is bigger then largest value in set use insertlast
    return InsertLast(value);

  //now only values = # inbetween first and last, no duplicates

  LNode * nnp = new LNode; //new LNode is created
  if (nnp == NULL) //if memory cannot be allocated then return false
    return false;

  nnp->data = value; //assigns value to new LNode
  LNode * left, * right = first; //creates left and right pointers
  while (right->data < value) // loop keeps iterating until right is on the right of where the data should go
    right = right->next; //traverses Set
  left = right->prev; // assigns left pointer

  //reassignments of prev/next *s to include new LNode, nnp into set
  nnp->prev = left; 
  left->next = nnp;
  nnp->next = right;
  right->prev = nnp;

  size++;//increment size

  return true;
}




void PrintValue (const  int & value)
{
  cout << "The value in the list is " << value << endl;
}

template <class ST>
void OrderedSet<ST>::Forward (void function (const ST & param))
//this function performs a function passed as a param to each LNode in a forward manner
{
  for (LNode * n = first; n; n = n->next) //iterates through each LNode
    function (n->data);//calls function passed as param with n->data as the parameter

}

template <class ST>
void OrderedSet<ST>::Backward (void function (const ST & param)) {
//this function performs a function passed as a param to each LNode in a backward manner
  for (LNode *n = last; n; n = n->prev)//iterates through each LNode
    function(n->data);//calls function passed as param with n->data as the parameter

}

//implementations for the Iterator functions; begin, rbegin, end, rend.
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::begin() const
//this function returns an iterator at the first location in the OrderedSet
{
  Iterator temp (first);
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rbegin() const
//this function return an iterator at the last location in the orderedSet
{
  Iterator temp (last);
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::end() const
//this function returns an iterator at the last locationin the orderedSet
{
  Iterator temp (last);
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rend() const
//this function returns an iterator at the first location in the OrderedSet
{
  Iterator temp (first);
  return temp;
}

#endif
