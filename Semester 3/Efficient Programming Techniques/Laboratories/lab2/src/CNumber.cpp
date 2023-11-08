#include <iostream>
#include <sstream>
#include "CNumber.h"

using namespace std;

void CNumber::operator=(const int iValue) {
	// Calculate the length required for the new number
	int temp = iValue < 0 ? -iValue : iValue;
	i_length = 0;
	while (temp > 0) {
		temp /= 10;
		i_length++;
	}

	// Check if the current dynamic array needs to be resized
	if (i_length > NUMBER_DEFAULT_LENGTH) {
		delete[] pi_number;
		pi_number = new int[i_length];
	}

	// Reset pi_number to store the new number
	temp = iValue < 0 ? -iValue : iValue;
	bool isNegative = iValue < 0;

	for (int i = i_length - 1; i >= 0; i--) {
		if (temp == 0) {
			// Fill any remaining digits with zeros
			pi_number[i] = 0;
		}
		else {
			pi_number[i] = temp % 10;
			temp /= 10;
		}
	}

	if (isNegative) {
		// If the original value was negative, set the most significant digit to a negative sign (-)
		pi_number[0] = -pi_number[0];
	}
}

/* This code won't work as expected. 
When you write pi_number = pcOther.pi_number, you are just copying the pointer to the pi_number array from pcOther to the current object. 
This means both objects will end up pointing to the same dynamic array in memory, and if one object modifies the array, it will affect the other object as well. 
This can lead to unintended consequences.

void CNumber::operator=(const CNumber& pcOther) {
	pi_number = pcOther.pi_number;
	i_length = pcOther.i_length;
}
*/

void CNumber::operator=(const CNumber& pcOther) {
	// Check for self-assignment
	if (this == &pcOther) {
		return;
	}

	// Allocate a new array for the current object
	if (i_length != pcOther.i_length) {
		delete[] pi_number;
		pi_number = new int[pcOther.i_length];
		i_length = pcOther.i_length;
	}

	// Copy the values from the other object's array
	for (int i = 0; i < i_length; i++) {
		pi_number[i] = pcOther.pi_number[i];
	}
}

CNumber CNumber::operator+(const CNumber& pcNewVal) {
	// Allocate a new array for the result
	CNumber result;
	result.i_length = std::max(i_length, pcNewVal.i_length) + 1;
	result.pi_number = new int[result.i_length];

	// Perform the addition
	int carry = 0;
	int i = i_length - 1;
	int j = pcNewVal.i_length - 1;
	int k = result.i_length - 1;

	while (i >= 0 || j >= 0 || carry > 0) {
		int digit1 = i >= 0 ? pi_number[i] : 0;
		int digit2 = j >= 0 ? pcNewVal.pi_number[j] : 0;
		int sum = digit1 + digit2 + carry;

		result.pi_number[k] = sum % 10;
		carry = sum / 10;

		i--;
		j--;
		k--;
	}

	// Adjust the result's length if the most significant digit is zero
	if (result.pi_number[0] == 0) {
		result.i_length--;
		delete[] result.pi_number;
		result.pi_number = new int[result.i_length];

		for (int i = 0; i < result.i_length; i++) {
			result.pi_number[i] = result.pi_number[i + 1];
		}
	}

	return result;
}


CNumber CNumber::operator-(const CNumber& pcNewVal) {
	// Determine the larger operand
	bool isThisLarger = i_length > pcNewVal.i_length;
	int largerLength = isThisLarger ? i_length : pcNewVal.i_length;

	// Allocate a new array for the result
	CNumber result;
	result.i_length = largerLength + 1;
	result.pi_number = new int[result.i_length];

	// Perform the subtraction
	int borrow = 0;
	int i = isThisLarger ? i_length - 1 : pcNewVal.i_length - 1;
	int j = isThisLarger ? pcNewVal.i_length - 1 : i_length - 1;
	int k = result.i_length - 1;

	while (i >= 0 || j >= 0 || borrow > 0) {
		int digit1 = isThisLarger ? pi_number[i] : 0;
		int digit2 = isThisLarger ? 0 : pcNewVal.pi_number[j];
		int diff = digit1 - digit2 - borrow;

		if (diff < 0) {
			diff += 10;
			borrow = 1;
		} else {
			borrow = 0;
		}

		result.pi_number[k] = diff;

		i--;
		j--;
		k--;
	}

	// Adjust the result's length if the most significant digit is zero
	if (result.pi_number[0] == 0) {
		result.i_length--;
		delete[] result.pi_number;
		result.pi_number = new int[result.i_length];

		for (int i = 0; i < result.i_length; i++) {
			result.pi_number[i] = result.pi_number[i + 1];
		}
	}

	return result;
}

CNumber CNumber::operator*(const CNumber& pcNewVal) {
	// Determine the length of the product
	int productLength = i_length + pcNewVal.i_length;

	// Create a temporary array to store the partial products
	int* tempArray = new int[productLength];

	// Initialize the temporary array with zeros
	for (int i = 0; i < productLength; i++) {
		tempArray[i] = 0;
	}

	// Calculate the partial products
	for (int i = 0; i < i_length; i++) {
		for (int j = 0; j < pcNewVal.i_length; j++) {
			int partialProduct = pi_number[i] * pcNewVal.pi_number[j];
			int carry = 0;

			for (int k = i + j; k < productLength; k++) {
				int digitSum = tempArray[k] + partialProduct + carry;
				tempArray[k] = digitSum % 10;
				carry = digitSum / 10;
			}
		}
	}

	// Create the result object
	CNumber result;
	result.i_length = productLength;
	result.pi_number = new int[result.i_length];

	// Copy the partial products to the result object
	for (int i = 0; i < productLength; i++) {
		result.pi_number[i] = tempArray[i];
	}

	// Adjust the result's length if the most significant digit is zero
	if (result.pi_number[0] == 0) {
		result.i_length--;
		delete[] result.pi_number;
		result.pi_number = new int[result.i_length];

		for (int i = 0; i < result.i_length; i++) {
			result.pi_number[i] = result.pi_number[i + 1];
		}
	}

	// Delete the temporary array
	delete[] tempArray;

	return result;
}


CNumber CNumber::operator/(const CNumber& pcNewVal) {
	// Check for divisor zero
	if (pcNewVal.i_length == 0) {
		std::cerr << "Error: Division by zero is undefined." << std::endl;
		return result;
	}

	// Normalize the divisor
	while (pcNewVal.pi_number[0] == 0) {
		if (pcNewVal.i_length == 1) {
			std::cerr << "Error: Division by zero is undefined." << std::endl;
			return result;
		}

		// Shift the digits of the divisor to the left
		for (int i = 1; i < pcNewVal.i_length; i++) {
			pcNewVal.pi_number[i - 1] = pcNewVal.pi_number[i];
		}

		pcNewVal.i_length--;
	}

	// Initialize the result
	CNumber result;
	result.i_length = i_length;
	result.pi_number = new int[result.i_length];

	// Perform the division algorithm
	int quotient = 0;
	int remainder = 0;

	for (int i = i_length - 1; i >= 0; i--) {
		int digit = pi_number[i];
		int tempQuotient = digit * 10 + remainder;

		if (tempQuotient >= pcNewVal.pi_number[0]) {
			quotient = tempQuotient / pcNewVal.pi_number[0];
			remainder = tempQuotient % pcNewVal.pi_number[0];
		}
		else {
			quotient = 0;
			remainder = tempQuotient;
		}

		result.pi_number[i] = quotient;
	}

	// Adjust the result's length
	if (result.pi_number[0] == 0) {
		result.i_length--;
		delete[] result.pi_number;
		result.pi_number = new int[result.i_length];

		for (int i = 0; i < result.i_length; i++) {
			result.pi_number[i] = result.pi_number[i + 1];
		}
	}

	// Handle special cases
	if (pcNewVal.i_length > i_length) {
		for (int i = 0; i < result.i_length; i++) {
			result.pi_number[i] = 0;
		}
	}

	return result;
}


/*
* 
*	TRYING KARATSUBA algorithm
* 
CNumber CNumber::operator/(const CNumber& pcNewVal) {
	// Check for divisor zero
	if (pcNewVal.i_length == 0) {
		std::cerr << "Error: Division by zero is undefined." << std::endl;
		return result;
	}

	// Normalize the divisor
	while (pcNewVal.pi_number[0] == 0) {
		if (pcNewVal.i_length == 1) {
			std::cerr << "Error: Division by zero is undefined." << std::endl;
			return result;
		}

		// Shift the digits of the divisor to the left
		for (int i = 1; i < pcNewVal.i_length; i++) {
			pcNewVal.pi_number[i - 1] = pcNewVal.pi_number[i];
		}

		pcNewVal.i_length--;
	}

	// Check if the dividend is smaller than the divisor
	if (i_length < pcNewVal.i_length) {
		// Handle special cases
		CNumber result;
		result.i_length = 1;
		result.pi_number = new int[result.i_length];
		result.pi_number[0] = 0;

		return result;
	}

	// Determine the maximum length for intermediate results
	int maxLength = std::max(i_length, pcNewVal.i_length);

	// Perform division using Karatsuba algorithm
	CNumber quotient;
	quotient.i_length = maxLength;
	quotient.pi_number = new int[quotient.i_length];

	karatsubaDivide(pi_number, i_length, pcNewVal.pi_number, pcNewVal.i_length, quotient.pi_number);

	// Adjust the quotient's length if necessary
	if (quotient.pi_number[0] == 0) {
		quotient.i_length--;
		delete[] quotient.pi_number;
		quotient.pi_number = new int[quotient.i_length];

		for (int i = 0; i < quotient.i_length; i++) {
			quotient.pi_number[i] = quotient.pi_number[i + 1];
		}
	}

	return quotient;
} */


std::string CNumber::sToStr() {
	std::ostringstream oss;

	for (int i = 0; i < i_length; i++) {
		oss << pi_number[i];
	}

	return oss.str();
}

void CNumber::vPrint() {
	if (i_length == 0) {
		std::cerr << "Error: Cannot print value. Array length is zero." << std::endl;
		return;
	}

	std::cout << "CNumber Value: ";
	for (int i = 0; i < i_length; i++) {
		std::cout << pi_number[i];
	}
	std::cout << std::endl;
}

