/*
 * Ruchit Patel
 * rpatel18
 * pa6
 */

#include<iostream>
#include<string>
#include <stdexcept>
#include <cstdlib>
#include <math.h>

#include "BigInteger.h"

long base = 1000000000;
int power = 9;

// Class Constructors & Destructors 

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
	signum = 0;
	digits = List();
}

static bool valid_str(std::string s) { 
	for (int i = 0; i < s.length(); i++) {
		// non-numeric value
		if (s[i] < 48 || s[i] > 57) return false;
	}
	return true;
}

// removes preceding zeroes in a string
// ex: "0000000123001" -> "123001"
static void remove_prez(std::string &s) {
	int i = 0; 
	while (s[i] == '0' && i < s.length()) {
		i++;
	}
	s.erase(0, i);
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
	if (s.empty()) throw std::invalid_argument("BigInteger: Constructor: empty string");

	// change signs
	signum = 1;
	if (s[0] == '+') {
		s.erase(0, 1);
	}
	else if (s[0] == '-') {
		signum = -1;
		s.erase(0, 1);
	}

	// cant have "+" or "-"
	if (s.empty()) throw std::invalid_argument("BigInteger: Constructor: empty string");

	// remove preceding zeroes
	remove_prez(s);
	
	// cant have "+000000" or "-000000", can have "0000000" ???? 
	if (s.empty()) throw std::invalid_argument("BigInteger: Constructor: empty string");

	long slen = s.length();
	long total_subs;	// num of substring that need to be converted to long

	if ((slen % power) == 0) total_subs = slen/power;
	else total_subs = slen/power + 1;
	
	std::string s_sub;			// to store temporary substrings

	long pos = slen;			// substring from
	size_t len = power;			// substring to
	for (int i = 1; i <= total_subs; i++) {
		pos -= power;

		if (pos < 0) {
			len = pos + power;
			pos = 0;
		}

		// get substrings with atmost power characters
		s_sub = s.substr((size_t) pos, len);
		if (!(valid_str(s_sub))) throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		// add to list
		digits.moveFront();
		digits.insertBefore(strtol(s_sub.c_str(), NULL, 10));
		//std::cout << digits << std::endl;
	}
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
	signum = N.signum;
	digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()

// Access functions

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
	List A = this->digits;		// this is constant
	List B = N.digits;		// N's constant

	// 3 signs, 4 cases, A=this, B=N
	int A_sign = signum, B_sign = N.signum;	
	int A_len = A.length();
	int B_len = B.length();

	// A is negative, B is zero or positive -> A < B
	if (A_sign == -1 && B_sign >= 0) {
		return -1;
	}
	
	// A is positive, B is zero or negative -> A > B
	else if (A_sign == 1 && B_sign <= 0) {
		return 1;
	}

	else if (A_sign <= 0 && B_sign > 0) return -1;

	else if (A_sign >= 0 && B_sign < 0) return 1;

	// both negative
	else if (A_sign == -1 && B_sign == -1) {
		if (A_len > B_len) return -1;		// greater length means lower (negative num)
		else if (A_len < B_len) return 1;	// less length means higher

		// same length, compare item by item
		else {

			A.moveFront(); B.moveFront();
			int i = 0;	

			ListElement A_peeked, B_peeked;
			int ret = 0;

			while (i < A_len) {
				A_peeked = A.moveNext();	
				B_peeked = B.moveNext();	

				// elem bigger, means num smaller
				if (A_peeked > B_peeked) {
					ret = -1;
					break;
				}

				// elem smaller, means num bigger
				else if (A_peeked < B_peeked) {
					ret = 1;
					break;
				}

				// else keep comparing

				i++;
			}	

			return ret;
		}
	}
	
	// both positive
	else if (A_sign == 1 && B_sign == 1) {
		if (A_len > B_len) return 1;		// greater length means higher (positive num)
		else if (A_len < B_len) return -1;	// less length means lower

		// same length, compare item by item
		else {

			A.moveFront(); B.moveFront();
			int i = 0;	

			ListElement A_peeked, B_peeked;
			int ret = 0;

			while (i < A_len) {
				A_peeked = A.moveNext();	
				B_peeked = B.moveNext();	

				// elem bigger, means num bigger
				if (A_peeked > B_peeked) {
					ret = 1;
					break;
				}

				// elem smaller, means num smaller
				else if (A_peeked < B_peeked) {
					ret = -1;
					break;
				}

				// else keep comparing

				i++;
			}	

			return ret;
		}
	}

	// both equal or both zero
	return 0;
}

// Manipulation procedures 

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
	signum = 0;
	digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
	signum *= -1;		// 1 to -1, -1 to 1, 0 to 0
}


// BigInteger Arithmetic operations

// main_add()
// algortirhm for adding two big ints, return A+B
static List main_add(const List& A, const List& B) {
	List R;

	List A_digs = A;
	List B_digs = B;

	// start adding from the end
	A_digs.moveBack(); B_digs.moveBack();
	int carry = 0; ListElement sum = 0;

	// add both till both exist, after jsut add whichevers left, just like pa4
	while (A_digs.position() > 0 && B_digs.position() > 0) {
		sum = (A_digs.peekPrev() + B_digs.peekPrev() + carry);

		// normalize
		if (sum >= base && (A_digs.position() != 1 || B_digs.position() != 1)) {
			carry = 1;	// carry over
			R.insertBefore(sum-base);
			R.movePrev();
		}

		// already normalized
		else {
			carry = 0;
			R.insertBefore(sum);
			R.movePrev();
		}

		A_digs.movePrev(); B_digs.movePrev();
	}

	// only A left
	while (A_digs.position() > 0) {
		// we need carry in loop because if we have 999999999 999999999, we will 
		// always have carry even if just A is left, it could overflow
		sum = (A_digs.peekPrev() + carry);

		// normalize
		if (sum >= base && A_digs.position() != 1) {
			carry = 1;	// carry over
			R.insertBefore(sum-base);
			R.movePrev();
		}

		// already normalized
		else {
			carry = 0;
			R.insertBefore(sum);
			R.movePrev();
		}
		A_digs.movePrev();
	}
	
	// only B left
	while (B_digs.position() > 0) {
		sum = (B_digs.peekPrev() + carry);

		// normalize
		if (sum >= base && B_digs.position() != 1) {
			carry = 1;	// carry over
			R.insertBefore(sum-base);
			R.movePrev();
		}

		// already normalized
		else {
			carry = 0;
			R.insertBefore(sum);
			R.movePrev();
		}

		B_digs.movePrev();
	}

	return R;
}

// main_sub()
// algortirhm for subtracting two big ints, returns A-B
static List main_sub(const List& A, const List& B) {
	List R;

	List A_digs = A;
	List B_digs = B;

	// start adding from the end
	A_digs.moveBack(); B_digs.moveBack();
	int carry = 0; ListElement sum = 0;

	// add both till both exist, after jsut add whichevers left, just like pa4
	while (A_digs.position() > 0 && B_digs.position() > 0) {
		sum = (A_digs.peekPrev() - B_digs.peekPrev() + carry);

		// normalize
		if (sum < 0 && (A_digs.position() != 1 || B_digs.position() != 1))  {
			carry = -1;	// carry over
			R.insertBefore(sum+base);
			R.movePrev();
		}

		// already normalized
		else {
			carry = 0;
			R.insertBefore(abs(sum));
			R.movePrev();
		}

		A_digs.movePrev(); B_digs.movePrev();

	}

	// only A left
	while (A_digs.position() > 0) {
		// we need carry in loop because if we have 999999999 999999999, we will 
		// always have carry even if just A is left, it could overflow
		sum = (A_digs.peekPrev() + carry);

		// normalize
		if (sum < 0 && A_digs.position() != 1) {
			carry = -1;	// carry over
			R.insertBefore(sum+base);
			R.movePrev();
		}

		// already normalized
		else {
			carry = 0;
			R.insertBefore(abs(sum));
			R.movePrev();
		}

		A_digs.movePrev();
	}
	
	// only B left
	while (B_digs.position() > 0 && B_digs.position() != 1) {
		// we need carry in loop because if we have 999999999 999999999, we will 
		// always have carry even if just A is left, it could overflow
		sum = (B_digs.peekPrev() + carry);

		// normalize
		if (sum < 0) {
			carry = -1;	// carry over
			R.insertBefore(sum+base);
			R.movePrev();
		}

		// already normalized
		else {
			carry = 0;
			R.insertBefore(abs(sum));
			R.movePrev();
		}

		B_digs.movePrev();
	}

	return R;
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
	// this = A, N = B
	// 4 cases
	int A_sign = signum, B_sign = N.signum;
	BigInteger R;
	
	// -A+B == B-A
	if (A_sign < 0 && B_sign >= 0) {

		BigInteger A_copy = *this;
		A_copy.negate();

		// determine sign
		if (N > A_copy) {
			R.signum = 1; 
			R.digits = main_sub(N.digits, A_copy.digits);
		}
		else if (N < A_copy) {
			R.signum = -1;
			R.digits = main_sub(A_copy.digits, N.digits);
		}
		else {		// both equal, B-A would be zero
			R.signum == 0;
			R.digits.clear();
		}
	}	

	// -A-B = -(A+B)
	else if (A_sign < 0 && B_sign <= 0) {
		R.digits = main_add(this->digits, N.digits);
		R.signum = -1;		// negate the positive sign (pos+pos = +ve no.)
	}

	// A+(-B) = A-B
	else if (A_sign >= 0 && B_sign <= 0) {

		// determine sign
		if (*this > N) {
		       	R.signum = 1; 
			R.digits = main_sub(this->digits, N.digits);
		}
		else if (*this < N) {
			R.signum = -1;
			R.digits = main_sub(N.digits, this->digits);
		}
		else {		// both equal, B-A would be zero
			R.signum == 0;
			R.digits.clear();
		}
	}

	// A+B
	else if (A_sign >= 0 && B_sign >= 0) {
		R.digits = main_add(this->digits, N.digits);
		R.signum = 1;		// pos + 0 or pos = +ve no.
	}
	
	// both zero
	return R;

}


// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
	// this = A, N = B
	// 4 cases
	int A_sign = signum, B_sign = N.signum;
	BigInteger R;
	
	// -A-B == -(A+B)
	if (A_sign < 0 && B_sign >= 0) {
		R.digits = main_add(this->digits, N.digits);
		R.signum = -1;		// negate the positive sign (pos+pos = +ve no.)
	}	

	// -A--B = -A+B = B-A
	else if (A_sign < 0 && B_sign <= 0) {
		
		BigInteger A_copy = *this;
		A_copy.negate();

		// determine sign
		if (N > A_copy) {
			R.signum = 1; 
			R.digits = main_sub(N.digits, A_copy.digits);
		}
		else if (N < A_copy) {
			R.signum = -1;
			R.digits = main_sub(A_copy.digits, N.digits);
		}
		else {		// both equal, B-A would be zero
			R.signum == 0;
			R.digits.clear();
		}

	}

	// A-(-B) = A+B
	else if (A_sign > 0 && B_sign <= 0) {
		R.digits = main_add(this->digits, N.digits);
		R.signum = 1;			// two positive number always add to a +ve no.
	}

	// A-B
	else if (A_sign > 0 && B_sign >= 0) {

		// determine sign
		if (*this > N) {
		       	R.signum = 1; 
			R.digits = main_sub(this->digits, N.digits);
		}
		else if (*this < N) {
			R.signum = -1;
			R.digits = main_sub(N.digits, this->digits);
		}
		else {		// both equal, B-A would be zero
			R.signum == 0;
			R.digits.clear();
		}

	}
	
	else if (A_sign == 0) {
		R = N;
		R.negate();
	}

	// both zero
	return R;
}

// main_mult()
// actual algorithm for mult, result = A*B
static List main_mult(const List &A, const List &B) {
	/*
	 * general algo
	 * take elements of shorter list, multiply with each ofbigger list
	 * take carry, add on next round, add results together
	 */


	List R;
	List A_digs = A;
	List B_digs = B;
	int req_elems = A_digs.length() + B_digs.length();

	// to add two lists and zeroes and carries together
	for (int i = 0; i < req_elems; i++) {
		R.insertAfter(0);
		R.moveNext();
	}

	ListElement res; int carry = 0;

	B_digs.moveBack();
	for (int i = 1; i <= B.length(); i++) {
		A_digs.moveBack();
		for (int j = 1; j <= A.length(); j++) {
			res = (A_digs.movePrev() * B_digs.peekPrev()) + carry + R.peekPrev();
			carry = res/base;	// quotient
			res %= base;		// remainder
			R.setBefore(res);	
			R.movePrev();
		}
		B_digs.movePrev();

		// if there is carry we need to change the first element
		if (carry != 0) {
			R.setBefore((ListElement) carry);
			carry = 0;
		}

		// get correct R position
		R.moveBack();
		for(int times = 0; times < i; times++) R.movePrev(); 
	}

	// remove preceding zeroes (no carry overs)
	R.moveFront();
	while (R.moveNext() == 0) {
		R.eraseBefore();
	}

	return R;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger R;

	// A*0 = 0 or B*0 = 0 or 0*0 = 0
	if (this->signum == 0 || N.signum == 0) return R;

	// -A*B = A*-B = -(A*B)
	else if ((this->signum == -1 && N.signum == 1) || (this->signum == 1 && N.signum == -1)) {
		if (this->digits.length() >= N.digits.length()) R.digits = main_mult(this->digits, N.digits);
		else R.digits = main_mult(N.digits, this->digits);
		R.signum = -1;
	}

	// -A*-B = A*B = A*B
	else if ((this->signum == -1 && N.signum == -1) || (this->signum == 1 && N.signum == 1)) {
		if (this->digits.length() >= N.digits.length()) R.digits = main_mult(this->digits, N.digits);
		else R.digits = main_mult(N.digits, this->digits);
		R.signum = 1;
	}

	return R;
}


// Other Functions

// helper function that adds n zeroes in a string
static void add_zeroes(std::string &s, int n) {
	for (int i = 1; i <= n; i++) {
		s += "0";
	}
}

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
	std::string s = "";
	if (signum == 0) {
		s = "0";
		return s;
	}

	List L = this->digits;
	ListElement res;
	int num_digits;			// to prepend zeroes

	L.moveFront();
	for (int i = 0; i < L.length(); i++) {
		res = L.moveNext();

		// 9 has 1 digit, 10 has 2 digits, 1003 has 3 digits and so on
		num_digits = (int) (floor(log10(res)) + 1); 

		// 9 becomes 000000009, 10 becomes 000000010, and so on
		if (res == 0) add_zeroes(s, power-1);		// -1 since we add res after
		else add_zeroes(s, power - num_digits);

		s += std::to_string(res);	// add result
	}

	remove_prez(s);	// remove preceding zeroes

	if (signum == -1) s.insert(0, "-");

	return s;
}


// Overriden Operators 

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
	return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
	return (A.compare(B) == 0);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
	return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
	int res = A.compare(B);
	return (res == -1 || res == 0);	
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
	return (A.compare(B) == 1);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
	int res = A.compare(B);
	return (res == 1 || res == 0);	
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
	return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
	A = A.add(B);
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
	return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
	A = A.sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
	return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
	A = A.mult(B);
	return A;
}

