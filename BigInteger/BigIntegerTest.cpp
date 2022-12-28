/*
 * Ruchit Patel
 * rpatel18
 * pa6
 */

#include "BigInteger.h"

using namespace std;

int main() {
	// constructor tests
	BigInteger B1; cout << "B1: " << B1 << endl;
	BigInteger B2("+1234567890123456789123"); cout << "B2: " << B2 << endl;
	BigInteger B3("+123456789"); cout << "B3: " << B3 << endl;
	BigInteger B4("-123"); cout << "B4: " << B4 << endl;
	BigInteger B5("0001"); cout << "B5: " << B5 << endl;
	//BigInteger B6("+"); cout << "B6: " << B6 << endl;
	BigInteger B7("1234000567891"); cout << "B7: " << B7 << endl;			// how to print it though???
	BigInteger B8("0123456789"); cout << "B8: " << B8 << endl;			// how to print it though???
	BigInteger B10("000000000123456789"); cout << "B10: " << B10 << endl;
	BigInteger B11("+000000000123456789"); cout << "B11: " << B11 << endl;
	BigInteger B12("-1000000000123456789"); cout << "B12: " << B12 << endl;
	//BigInteger Ber("100000000*123456789"); cout << "Ber: " << Ber << endl;

	// copy constructor
	BigInteger B13 = B3; cout << "B13: " << B13 << endl;

	BigInteger B14("-123456789000000000"); cout << "B14: " << B14 << endl;
	BigInteger B15("-000000000123456789"); cout << "B15: " << B15 << endl;
	cout << endl;

	// compare (0 = same, 1 = greater, -1 = less)
	cout << "B2.compare(B3) : " << B2.compare(B3) << endl;			// 1
	cout << "B13.compare(B3) : " << B13.compare(B3) << endl;		// 0
	cout << "B13.compare(B3) : " << B13.compare(B3) << endl;		// 0

	cout << "B14.compare(B15) : " << B14.compare(B15) << endl;		// -1

	BigInteger B16("-0000000001");
	BigInteger B17("-1");
	cout << "B17.compare(B16) : " << B17.compare(B16) << endl;		// 0

	BigInteger B18("0000000009");
	BigInteger B19("97");
	cout << "B18.compare(B19) : " << B18.compare(B19) << endl;		// -1
	cout << endl;

	// BigInteger B20("0000000000");

	// make zero
	B5.makeZero(); cout << "B5: " << B5 << endl;

	// negate
	B18.negate(); cout << "B18: " << B18 << endl;
	cout << "B18 sign : " << B18.sign() << endl;		// -1
	B1.negate(); cout << "B1: " << B1 << endl;
	cout << "B1 sign : " << B1.sign() << endl;		// 0
	B14.negate(); cout << "B14: " << B14 << endl;
	cout << "B14 sign : " << B14.sign() << endl;		// 1
	cout << endl;

	// operator testing
	
	// << already tested with print
	
	// ==
	cout << "B13 == B3? " << (B13 == B3) << endl;				// true 1
	cout << endl;
	
	// <
	cout << "B14 < B15? " << (B14 < B15) << endl;				// false 0
	cout << "B2 < B12? " << (B2 < B12) << endl;				// false 0
	cout << "B1 < B12? " << (B2 < B12) << endl;				// false 0
	cout << "B4 < B5? " << (B4 < B5) << endl;				// true 1
	cout << "B1 < B1? " << (B1 < B1) << endl;				// false 0
	cout << endl;
	
	// <=
	cout << "B8 <= B10? " << (B8 <= B10) << endl;				// true 1
	cout << "B15 <= B14? " << (B15 <= B14) << endl;				// true 1
	cout << "B3 <= B3? " << (B3 <= B3) << endl;				// true 1
	cout << endl;
	
	// >
	cout << "B14 > B15? " << (B14 > B15) << endl;				// true 1
	cout << "B2 > B12? " << (B2 > B12) << endl;				// true 1
	cout << "B1 > B12? " << (B2 > B12) << endl;				// true 1
	cout << "B4 > B5? " << (B4 > B5) << endl;				// false 0
	cout << "B1 > B1? " << (B1 > B1) << endl;				// false 0
	cout << endl;
	
	
	// >=
	cout << "B8 >= B10? " << (B8 >= B10) << endl;				// true 1
	cout << "B15 >= B14? " << (B15 >= B14) << endl;				// false 0
	cout << "B3 >= B3? " << (B3 >= B3) << endl;				// true1
	cout << endl;
	
	BigInteger B20("123456789123456789");
	BigInteger B22 = B20;
	BigInteger B21("999999999999999999");

	// add
	cout << "B20 + B21 = " << (B20 + B21) << endl;			// 1123456789 123456788
	B20 += B21; // +=
	cout << "B20 (+=B21) = " << B20 << endl;
	cout << "B20 + B1(0): = " << (B1 + B20) << endl;
	cout << "B1(0) + B1(0): = " << (B1 + B1) << endl;
	cout << endl;

	// sub
	B20 -= B21;
	cout << "B20 (-=B21) = " << B20 << endl;
	cout << "B20 == B22?  " << (B20 == B22) << endl;			// true 1
	cout << "B20 - B1(0): = " << (B20 - B1) << endl;
	cout << "B1(0) - B20: = " << (B1 - B20) << endl;
	cout << "B1(0) - B1(0): = " << (B1 - B1) << endl;
	cout << "B20: " << B20 << endl;
	cout << "B21: " << B21 << endl;
	cout << "B20 - B21 =  " << (B20 - B21) << endl;			// -123456789 123456790

	BigInteger B99("1234");
	BigInteger B98("999999");
	cout << "1234 - 999999 = " << B99-B98 << endl;			// -998765

	BigInteger B97("-20");
	BigInteger B96("-1");
	cout << "-20 - -1 = " << B97-B96 << endl;			// -19
	B96.negate(); BigInteger B95("2");
	cout << "1-2 = " << B96 - B95 << endl;				// -1
	cout << endl;

	// mult, TEST WITH BASE 100, POWER 2
	BigInteger B26("1212");
	BigInteger B27("1348");
	cout << "B26*B27 = " << (B26 * B27) << endl;			// 1663776

	BigInteger B28("111212");
	BigInteger B29("1348");
	cout << "B28*B29 = " << (B29 * B28) << endl;			// 149913776
	B28.negate();
	cout << "-B28*B29 = " << (B28 * B29) << endl;			// -149913776
	cout << "B29 * 0 = " << (B29 * B1) << endl;
	BigInteger Bn1("-1");
	cout << "B28*-1 = " << (B28 *= Bn1) << endl;			// 111212
	cout << "B28*B29*Bn1 = " << (B28*Bn1*B29) << endl;
	cout << "B28 squared = " << B28 * B28 << endl;			// 12368108944
	cout << "B29 squared = " << B29 * B29 << endl;			// 1817104

	BigInteger B81("1");
	BigInteger B82("2");
	BigInteger B83("3");
	BigInteger B84("4");
	BigInteger B85("5");
	cout << "5 fact = " << B81 * B82 * B83 * B84 * B85 << endl;
	
	// destructor

}
