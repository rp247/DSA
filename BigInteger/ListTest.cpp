/*
 * Ruchit Patel
 * rpatel18
 * pa6
 */

#include <iostream>
#include <string>

#include "List.h"

using namespace std;

int main() {

	// List()
	List L1, L2, L3, L4, L5;

	// insertAfter, moveNext
	L1.insertAfter(1); L1.moveNext();
	L1.insertAfter(2); L1.moveNext();
	L1.insertAfter(3); L1.moveNext();
	L1.insertAfter(4); L1.moveNext();
	L1.insertAfter(5); L1.moveNext();

	// to_string(), operator<<
	cout << "L1: " << L1 << endl;				// [1, 2, 3, 4, 5]

	// length()
	cout << "L1 length: " << L1.length() << endl;		// 5
	cout << endl;

	// insertBefore, movePrev
	L2.insertBefore(-1); L2.movePrev();
	L2.insertBefore(-2); L2.movePrev();
	L2.insertBefore(-3); L2.movePrev();
	L2.insertBefore(-4); L2.movePrev();
	L2.insertBefore(-5); L2.movePrev();
	
	// to_string(), operator<<
	cout << "L2: " << L2 << endl;				// [-5, -4, -3, -2, -1]

	// length()
	cout << "L2 length: " << L2.length() << endl;		// 5
	cout << endl;

	// copy List(), operator=
	L3 = L2;
	
	// equals()
	cout << "L3 == L2? " << L3.equals(L2) << endl;		// 1 (true)

	// front()
	cout << "L3 front: " << L3.front() << endl;		// -5

	// moveBack()
	L3.moveBack();

	// back()
	cout << "L3 back: " << L3.back() << endl;		// -1

	// movePrev()
	L3.movePrev();

	// position()
	cout << "L3 position: " << L3.position() << endl;	// 4

	// equals()
	L4 = L3;
	
	// setAfter()
	L4.moveBack(); L4.movePrev();
	L4.setAfter(0);
	
	// equals(), == operator
	cout << endl;
	cout << "L4 == L3? " << (L3 == L4) << endl;		// 0 (false)

	// insertAfter()
	L4.insertAfter(1);
	
	// setBefore()
	L4.setBefore(2);
	
	// to_string(), operator<<
	cout << "L4: " << L4 << endl;				// [-5, -4, -3, 2, 1, 0]

	// length()
	cout << "L4 length: " << L4.length() << endl;		// 6
	
	// position()
	cout << "L4 position: " << L4.position() << endl;	// 4
	
	// peekNext()
	cout << "L4 peekNext: " << L4.peekNext() << endl;	// 1

	// peekPrev()
	L4.moveFront(); L4.moveNext();
	cout << "L4 peekPrev: " << L4.peekPrev() << endl;	// -5
	
	// position()
	cout << "L4 position: " << L4.position() << endl;	// 1
	cout << "L4: " << L4 << endl;				// [-5, -4, -3, 2, 1, 0]

	// eraseAfter()
	L4.eraseAfter();					// remove -4

	L4.moveFront();
	L4.eraseAfter();					// remove -5

	L4.moveBack(); L4.movePrev();
	L4.eraseAfter();					// remove 0

	cout << "L4: " << L4 << endl;				// [-3, 2, 1]

	// position()
	cout << "L4 position: " << L4.position() << endl;	// 3
	
	// eraseBefore
	L4.eraseBefore();
	L4.eraseBefore();

	cout << "L4: " << L4 << endl;				// [-3]
	cout << "L4 position: " << L4.position() << endl;	// 1
	cout << endl;
	
	// clear()
	L5 = L4;
	cout << "L5: " << L5 << endl;				// [-3]
	L5.clear(); L4.clear();
	cout << "L5 == L4? " << (L5 == L4) << endl;		// 1 (true)
	cout << "L5: " << L5 << endl;				// []
	cout << endl;
	
	// concat()
	List L6 = L2.concat(L1);
	cout << "L6: " << L6 << endl;				// [-5,...-1,1,...,5]
	cout << "L6 length: " << L6.length() << endl;		// 10
	cout << "L6 position: " << L6.position() << endl;	// 0

	L6.moveFront(); L6.moveNext();				// pos = 1
	L6.setAfter(-5);					// [-5, -5, ...]

	L6.moveNext(); L6.moveNext(); L6.moveNext();		// -1 should be -5
	L6.setAfter(-5);					// [-5, -5, ...]

	L6.moveBack();
	L6.setBefore(-5);
	cout << "L6: " << L6 << endl;				
	
	// findNext()
	L6.moveFront();
	cout << "Next -5 at: " << L6.findNext(-5) << endl;	// 1
	cout << "Next -5 at: " << L6.findNext(-5) << endl;	// 2
	cout << "Next -5 at: " << L6.findNext(-5) << endl;	// 5
	cout << "Next -5 at: " << L6.findNext(-5) << endl;	// 10

	L6.moveFront();
	cout << "Next -99 at: " << L6.findNext(-99) << endl;	// -1
	cout << "L6 position: " << L6.position() << endl;	// 10

	// findPrev()
	L6.moveBack();
	cout << "Prev -5 at: " << L6.findPrev(-5) << endl;	// 9
	cout << "Prev -5 at: " << L6.findPrev(-5) << endl;	// 4
	cout << "Prev -5 at: " << L6.findPrev(-5) << endl;	// 1
	cout << "Prev -5 at: " << L6.findPrev(-5) << endl;	// 0

	L6.moveBack();
	cout << "Next -99 at: " << L6.findPrev(-99) << endl;	// -1
	cout << "L6 position: " << L6.position() << endl;	// 0

	// copy
	L6 = L2;
	cout << "L6: " << L6 << endl;
	cout << "L2: " << L2 << endl;
	cout << "L6 == L2? " << (L6 == L2) << endl;		// 1
	cout << endl;

	
	List L7;
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(2); L7.movePrev();
	L7.insertBefore(3); L7.movePrev();
	L7.insertBefore(4); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(2); L7.movePrev();
	L7.insertBefore(4); L7.movePrev();


	cout << "L7: " << L7 << endl;			// 4 2 1 4 | 3 2 1

	L7.moveFront(); 
	L7.moveNext(); L7.moveNext(); L7.moveNext(); L7.moveNext();

	// cleanup()
	L7.cleanup();
	cout << "L7: " << L7 << endl;				// 4 2 1 | 3
	cout << "L7 position: " << L7.position() << endl;	// 3
	cout << "L7 prev: " << L7.peekPrev() << endl;		// 1
	cout << "L7 next: " << L7.peekNext() << endl;		// 3

	L7.clear();
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.moveNext();

	cout << "L7: " << L7 << endl;				// 1 1 1 1 1 1 1 1
	L7.cleanup();
	cout << "L7: " << L7 << endl;				// 1 |
	cout << "L7 position: " << L7.position() << endl;	// 1
	cout << "L7 prev: " << L7.peekPrev() << endl;		// 1

	L7.clear();
	L7.cleanup();

	L7.insertBefore(3); L7.movePrev();
	L7.insertBefore(4); L7.movePrev();
	L7.insertBefore(2); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.insertBefore(3); L7.movePrev();
	L7.insertBefore(2); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.moveNext();
	L7.moveFront(); 
	L7.moveNext(); L7.moveNext(); L7.moveNext(); L7.moveNext();

	cout << "L7: " << L7 << endl;				// 1 2 3 1 | 2 4 3
	L7.cleanup();
	cout << "L7: " << L7 << endl;				// 1 2 3 | 4
	cout << "L7 position: " << L7.position() << endl;	// 3
	cout << "L7 prev: " << L7.peekPrev() << endl;		// 3
	cout << "L7 next: " << L7.peekNext() << endl;		// 4
	L7.clear();

	L7.insertBefore(7); L7.movePrev();
	L7.insertBefore(6); L7.movePrev();
	L7.insertBefore(5); L7.movePrev();
	L7.insertBefore(4); L7.movePrev();
	L7.insertBefore(3); L7.movePrev();
	L7.insertBefore(2); L7.movePrev();
	L7.insertBefore(1); L7.movePrev();
	L7.moveNext();
	L7.moveFront(); 
	L7.moveNext(); L7.moveNext(); L7.moveNext(); L7.moveNext();

	cout << "L7: " << L7 << endl;				// 1 2 3 4 | 5 6 7
	L7.cleanup();
	cout << "L7: " << L7 << endl;				// 1 2 3 4 | 5 6 7
	cout << "L7 position: " << L7.position() << endl;	// 4
	cout << "L7 prev: " << L7.peekPrev() << endl;		// 4
	cout << "L7 next: " << L7.peekNext() << endl;		// 5
	
	// ~List()

	return 0;
}
