// CSE221 Assignment 1

#ifndef polynomial_h
#define polynomial_h

#include <typeinfo>
#include <iostream>
#include <math.h>

template <typename T>
class Term {
	T coef;
	int exp;
};

template <typename T>
class Polynomial
{
public:
	// Default constructor p(x) = 0
	Polynomial();

	// Copy constructor
	Polynomial(const Polynomial& source);

	// Destructor
	~Polynomial();

	// Assignment operator
	Polynomial& operator = (const Polynomial& source);

	// Sum of *this and source polynomials
	Polynomial operator+(const Polynomial& source);
	
	// Subtract of source polynomials from *this
	Polynomial operator-(const Polynomial& source);

	// Product of *this and source polynomials
	Polynomial operator*(const Polynomial& source);
	
	// Compute derivative of the current polynomial
	Polynomial Derivative();

	// Evaluate polynomial *this at x and return the result
	T Eval(T x);

	// Print polynomial
	void Print();

	// Create a new term. If the term exists, overwrite its coefficient.
	void CreateTerm(const T coef, const int exp);

private:
	Term<T> *termArray;
	int capacity, terms;
};

//
// Implementation
//

// Copy constructor
template <typename T>
Polynomial<T>::Polynomial(const Polynomial& source)
{
	
}	

template <typename T>
Polynomial<T>& Polynomial<T>::operator = (const Polynomial& source)
{
	
}

template <typename T>
Polynomial<T>::~Polynomial()
{
	
}

template <typename T>
void Polynomial<T>::Print()
{
	
}

// Sum of *this and source polynomials
template <typename T>
Polynomial<T> 
Polynomial<T>::operator+(const Polynomial& source)
{
	
}

template <typename T>
Polynomial<T> 
Polynomial<T>::operator-(const Polynomial& source)
{
	
}

template <typename T>
Polynomial<T> 
Polynomial<T>::operator*(const Polynomial& source)
{
	
}

template <typename T>
T Polynomial<T>::Eval(T x)
{
	
}

template <typename T>
void Polynomial<T>::CreateTerm(const T coef, const int exp)
{
	
}


#endif