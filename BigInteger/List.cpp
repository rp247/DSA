/*
 * Ruchit Patel
 * rpatel18
 * pa6
 */

#include<iostream>
#include<string>

#include "List.h"

#define DUMMY_VAL -1

// Class Constructors & Destructors

// Node constructor
List::Node::Node(ListElement x) {
	data = x;
	next = prev = nullptr;
}

// Creates new List in the empty state.
List::List() {
	frontDummy = new Node(DUMMY_VAL);
	backDummy = new Node(DUMMY_VAL);

	frontDummy->prev = nullptr; frontDummy->next = backDummy;
	backDummy->prev = frontDummy; backDummy->next = nullptr;

	beforeCursor = frontDummy;
	afterCursor = backDummy;		// frontDummy | backDummy : emptyList

	pos_cursor = 0;
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
	// an empty list

	frontDummy = new Node(DUMMY_VAL);
	backDummy = new Node(DUMMY_VAL);

	frontDummy->prev = nullptr; frontDummy->next = backDummy;
	backDummy->prev = frontDummy; backDummy->next = nullptr;

	beforeCursor = frontDummy;
	afterCursor = backDummy;		// frontDummy | backDummy : emptyList

	pos_cursor = 0;
	num_elements = 0;

	Node *N = L.frontDummy->next;
	int len = L.num_elements;

	while (len > 0) {
		insertAfter(N->data);	// keep appending elements of L to this till end
		moveNext();
		N = N->next;
		len--;
	}

	// do we need to cpy position of cursor, before and afterCursors?
	// copy curosr position, before and afterCursor
	pos_cursor = L.pos_cursor;
	N = frontDummy;
	for (int i = 0; i < pos_cursor; i++) {
		N = N->next;
	}
	beforeCursor = N;
	afterCursor = N->next;

}

// Destructor
List::~List() {

	// free dll

	Node *curr = frontDummy->next;
	Node *temp;

	while (num_elements > 0) {
		temp = curr->next;
		delete curr;
		curr = temp;
		num_elements--;
	}

	// pos_cursor = 0;

	delete frontDummy;
	delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
	if (num_elements == 0) throw std::length_error("List: front(): empty List");
	return frontDummy->next->data;	// front data
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
	if (num_elements == 0) throw std::length_error("List: back(): empty List");
	return backDummy->prev->data;	// back data
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
	return pos_cursor;		// would never be undefined
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
	if (!(position() < num_elements)) throw std::length_error("List: peekNext(): next element is a guard node");
	return afterCursor->data;	// data of node after the cursor
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
	if (!(position() > 0)) throw std::length_error("List: peekPrev(): prev element is a guard node");
	return beforeCursor->data;	// data of node before the cursor
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
	// basically delete without deleting dummy nodes

	Node *curr = frontDummy->next;
	Node *temp;

	while (num_elements > 0) {
		temp = curr->next;
		delete curr;
		curr = temp;
		num_elements--;
	}

	// original state
	frontDummy->prev = nullptr; frontDummy->next = backDummy;
	backDummy->prev = frontDummy; backDummy->next = nullptr;

	beforeCursor = frontDummy;
	afterCursor = backDummy;		// frontDummy | backDummy : emptyList

	pos_cursor = 0;

	return;

}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
	pos_cursor = 0;

	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;			// frontDummy | (front or backDummy)

	return;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
	pos_cursor = num_elements;

	beforeCursor = backDummy->prev;
	afterCursor = backDummy;			// (frontDummy or front) | backDummy

	return;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
	if (!(position() < num_elements)) throw std::length_error("List: moveNext(): next element is a guard node");

	pos_cursor++;

	beforeCursor = afterCursor;			// before: | 1 2 3
	afterCursor = afterCursor->next;		// after : 1 | 2 3	

	return beforeCursor->data;			// passed over one
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
	if (!(position() > 0)) throw std::length_error("List: movePrev(): prev element is a guard node");

	pos_cursor--;

	afterCursor = beforeCursor;			// before: 1 2 3 |
	beforeCursor = afterCursor->prev;		// after : 1 2 | 3	

	return afterCursor->data;			// passed over one
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
	Node *N = new Node(x);

	if(N) {
		// attach N in between
		N->prev = beforeCursor;
		N->next = afterCursor;

		beforeCursor->next = N;
		afterCursor->prev = N;

		// update afterCursor
		afterCursor = N;	

		num_elements++;
	}

	return;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
	Node *N = new Node(x);

	if(N) {
		// attach N in between
		N->prev = beforeCursor;
		N->next = afterCursor;
		
		beforeCursor->next = N;
		afterCursor->prev = N;

		// update beforeCursor
		beforeCursor = N;	

		pos_cursor++;	// update position as well
		num_elements++;
	}

	return;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
	if (!(position() < num_elements)) throw std::length_error("List: setAfter(): next element is a guard node");

	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
	if (!(position() > 0)) throw std::length_error("List: setBefore(): prev element is a guard node");

	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
	if (!(position() < num_elements)) throw std::length_error("List: eraseAfter(): next element is a guard node");

	Node *N = afterCursor;

	// update dll connection
	beforeCursor->next = afterCursor->next;
	afterCursor->next->prev = beforeCursor;

	afterCursor = beforeCursor->next;

	num_elements--;

	delete N;			
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
	if (!(position() > 0)) throw std::length_error("List: eraseBefore(): prev element is a guard node");

	Node *N = beforeCursor;

	// update dll connection
	N->prev->next = N->next;
	afterCursor->prev = beforeCursor->prev;

	// no change in afterCursor
	beforeCursor = N->prev;		

	pos_cursor--;			// update cursor position
	num_elements--;

	delete N;			
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
	Node *N = afterCursor;

	int found = 0;

	// go till last element
	while (pos_cursor < num_elements) {

		// found element
		if (N->data == x) {
			found = 1;
			break;
		}

		N = N->next;
		pos_cursor++;
	}

	// if found
	if (found == 1) {
		pos_cursor++;		// put it after the found element

		// update cursor position
		beforeCursor = N;
		afterCursor = N->next;

		return pos_cursor;
	}

	// not found
	else {
		// update cursor position
		beforeCursor = backDummy->prev;
		afterCursor = backDummy;

		// pos_cursor already equals length()

		return -1;
	}
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
	Node *N = beforeCursor;

	int found = 0;

	// go till last element
	while (pos_cursor > 0) {

		// found element
		if (N->data == x) {
			found = 1;
			break;
		}

		N = N->prev;
		pos_cursor--;
	}

	// if found
	if (found == 1) {
		pos_cursor--;		// put it before the found element

		// update cursor position
		afterCursor = N;
		beforeCursor = N->prev;

		return pos_cursor;
	}

	// not found
	else {
		// update cursor position
		beforeCursor = frontDummy;
		afterCursor = frontDummy->next;

		// pos_cursor already equals 0

		return -1;
	}
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {


	Node *N1, *N2, *N;			// temp nodes
	int pos1 = 1, pos2;				// to track if to lessen pos_cursor or not

	// pick one element, search the whole list
	// no change in pos_cursor, first apparence retained
	for (N1 = frontDummy->next; N1 != backDummy; N1 = N1->next) {

		N2 = N1->next;
		pos2 = pos1 + 1;

		while (N2 != backDummy) {

			// found
			if (N2->data == N1->data) {
				
				// update dll connection
				N2->prev->next = N2->next;
				N2->next->prev = N2->prev;

				// take care of before and afterCursor
				if (N2 == beforeCursor) {
					beforeCursor = N2->prev;
					pos_cursor--;
				}		

				else if (N2 == afterCursor) {
					afterCursor = N2->next;
				}

				else if (pos2 < pos_cursor) pos_cursor--;	// removed elem before cursor

				num_elements--;
				pos2--;

				// delete that node, continue searching
				N = N2;
				N2 = N2->next;
				delete N;
			}

			// continue searching
			else {
				N2 = N2->next;
				pos2++;
			}

		}

		pos1++;
	}

	return;
}


// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
	List temp;
	temp.moveFront();

	Node *N = this->frontDummy->next;

	// append this to temp
	while (N != this->backDummy) {
		temp.insertAfter(N->data);
		temp.moveNext();
		N = N->next;
	}

	// append L to temp
	N = L.frontDummy->next;
	while (N != L.backDummy) {
		temp.insertAfter(N->data);
		temp.moveNext();
		N = N->next;
	}

	// update values
	temp.pos_cursor = 0;
	temp.beforeCursor = temp.frontDummy;
	temp.afterCursor = temp.frontDummy->next;

	return temp;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
	Node *N;
	std::string s = "[";

	for (N = frontDummy->next; N != backDummy; N = N->next) {
		s += std::to_string(N->data) + ", ";
	}

	s += "]";

	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
	Node *N, *M;
	bool eq = false;

	// idea from Queue example on website
	eq = ( this->num_elements == R.num_elements );

	N = this->frontDummy->next;
	M = R.frontDummy->next;

	while (eq && N != this->backDummy) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}

	return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
	if (this != &L) {
		List temp = L;	// make a copy

		// still no clue why
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	}

	return *this;
}

