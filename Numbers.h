#ifndef _WIND_NUMBERS_H_
#define _WIND_NUMBERS_H_

#include <list>
#include <math.h>
#include "Containers.h"

namespace wind
{

class Numbers
{
private:
	typedef std::pair<int, int> NumPair;

	static void PrintPermutations (std::list<wind::Array<int>*> * src)
	{
		for (std::list<wind::Array<int>*>::iterator it = src->begin(); it != src->end(); it++)
		{
			wind::Array<int> * A = *it;
			for (int i = 0; i < A->size(); i++)
			{
				std::cout << (*A)[i].value() << ",";
			}
			std::cout << std::endl;
		}
	}

	/*
	 * GenNextPermutation () - "Worker" function for GetPermutations(). This is used to implement
	 * the Steinhaus-Johnson-Trotter algorithm.
	 */
	static std::list<wind::Array<int>*> * GenNextPermutation (std::list<wind::Array<int>*> * src)
	{
		int new_size = src->front()->size() + 1;
		std::list<wind::Array<int>*> * gen = new std::list<wind::Array<int>*> ();
		int sign = -1;
		int c = new_size - 1;

		// For each permutation from
		// the list of permutations, src
		// ...
		for (std::list<wind::Array<int>*>::iterator it = src->begin(); it != src->end(); it++)
		{
			wind::Array<int> * A = *it;

			// Construct a new permutation for
			// where we have a new number
			// specified by 'new_size - 1'
			// this number is the 'mover'
			//
			//  012  		Notice how 2 moves from right to left
			//  021       	then left to right
			//  201
			//  210
			//  120
			//  102
			//
			while (c >= 0 && c < new_size)
			{
				wind::Array<int> * G = new wind::Array<int> (new_size);
				(*G)[c] = new_size - 1;
				for (int i = 0; i < A->size(); i++)
				{
					if (i >= c)
					{
						(*G)[i + 1] = (*A)[i].value();
					}
					else
					{
						(*G)[i] = (*A)[i].value();
					}
				}
				gen->push_back(G);
				c += sign;					// Move the mover
			}
			sign = (sign == -1 ? 1 : -1);	// Switch the mover direction
			c += sign;
		}
		PrintPermutations(gen);
		return gen;
	}

public:
	static std::list<int> * GetPrimesTo (int n)
	{
		std::list<int> * primes = new std::list<int> ();
		// A loop over all of the numbers up to the desired number.
		// Each loop will check to see if it is a prime, by checking
		// to see if it is divisible by a list of primes up to
		// that has been accumulated thus far, but we will only 
		// check up to prime <= sqrt(n). If the number is prime, it will
		// be added to the list of primes.

		// Add 2,3 to primes if n is large enough.
		// Get these cases out of the way so that we do not have
		// to test for them for every iteration of the following 
		//major loop.
		if (n > 1) primes->push_back(2);
		if (n > 2) primes->push_back(3);

		// For the rest of the numbers (odd numbers)...
		for (int i = 5; i <= n; i += 2)
		{
			// See if they are divisible by numbers in our list of
			// primes, only up to sqrt(n) - don't check past sqrt(n)
			// because doing so is a repetition of effort.
			double sqrt_i = sqrt(i);
			bool is_prime = true;
			//std::cout << "get_primes_to: check " << i << " for factors up to " << (sqrt_i + 1) << std::endl;
			for (std::list<int>::iterator p = primes->begin(); p != primes->end() && *p < (sqrt_i + 1); ++p)
			{
				//std::cout << "get_primes_to: " << i << " % " << *p << std::endl;
				if (i % *p == 0)
				{
					is_prime = false;
					break;
				}
			}

			// If it is prime, let us add it to the list of primes.
			// Let us also add it to the list of consecutive (odd)
			// primes if it was consecutive.
			if (is_prime)
			{
				// Now, add it..
				primes->push_back(i);
			}
		}

		// Add it at the end. All numbers are divisible by 1,
		// this will mess up the previous calculations.
		primes->push_front(1);
		return primes;
	}

	/*
	 * GetPermutations (int size) - Gets all permutations of integers 0, 1, ... n using
	 * to Steinhaus-Johnson-Trotter algorithm. Uses the accompanying private function:
	 * GenNextPermutation ();
	 */
	std::list<wind::Array<int>*> * GetPermutations (int size)
	{
		std::list<wind::Array<int>*> * permutations = new std::list<wind::Array<int>*> ();
		wind::Array<int> * p = new wind::Array<int> (1);
		(*p)[0] = 0;
		permutations->push_back(p);

		while (permutations->front()->size() < size)
		{
			// Builds up the list of permutations iteratively
			// starting with a single element array
			//	0
			// Then
			//	01 - 1 moves
			//	10
			// Then
			//  012   210 - 2 moves
			//  021   120
			//  201   102
			// ...
			permutations = GenNextPermutation(permutations);
		}
		return permutations;
	}

	static unsigned int Factorial (unsigned int n)
	{
	    unsigned int ret = 1;
	    for(unsigned int i = 1; i <= n; ++i)
	        ret *= i;
	    return ret;
	}
};

}
#endif
