#ifndef _WIND_NUMBERS_H_
#define _WIND_NUMBERS_H_

#include <cstring>
#include <iostream>
#include <list>
#include <math.h>
#include <sys/time.h>
#include "Containers.h"

namespace wind
{

class Numbers
{
private:
	typedef std::pair<int, int> NumPair;

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

	static unsigned int Factorial (unsigned int n)
	{
	    unsigned int ret = 1;
	    for(unsigned int i = 1; i <= n; ++i)
	        ret *= i;
	    return ret;
	}
};

/*
 * Permutations () - Gets all permutations of integers 0, 1, ... n using
 * to Steinhaus-Johnson-Trotter algorithm. Uses the accompanying private function:
 * GenNextPermutation ();
 */
class Permutations 
{
private:
    void Move (int n, int direction)
    {
        int pos_old = NtoP[n];
        NtoP[n] += direction;
        int pos_new = NtoP[n];
        int m = PtoN[pos_new];
        PtoN[pos_new] = n;
        NtoP[m] = pos_old;
        PtoN[pos_old] = m;
    }
    void Print (int * arr)
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << arr[i];
        }
        std::cout << std::endl;
    }
    
    void FillGap (int n)
    {
        if (n == 0) return;
        if ((counter[n]+1) % (n+1) == 0)
        {
            direction[n] = !direction[n];
            FillGap (n - 1); 
        }
        else
        {
            Move (n, (direction[n] == 0 ? -1 : 1));
        }
        counter[n]++;
    }
    
    unsigned int Factorial (unsigned int n)
    {
        unsigned int ret = 1;
        for(unsigned int i = 1; i <= n; ++i)
            ret *= i;
        return ret;
    }
    
    int size;
    int result_size;

    int * PtoN; 		// PtoI[position] = number
    int * NtoP; 		// ItoP[number] = position
    int * counter;      // progress counter for each number
    int * direction;    // 0 is left, 1 is right
    int ** result;
public:
    Permutations (int size_)
    {
        size = size_;
        result_size = Factorial (size);

        PtoN = (int*) malloc (sizeof(int) * size);
        NtoP = (int*) malloc (sizeof(int) * size);
        counter = (int*) malloc (sizeof(int) * size);
        direction = (int*) malloc (sizeof(int) * size);
        result = (int**) malloc (sizeof(int*) * result_size);

        for (int i = 0; i < size; i++)
        {
            PtoN[i] = i;
            NtoP[i] = i;
        }
        memset (counter, 0, sizeof(counter));
        memset (direction, 0, sizeof(direction));

        for (int i = 0; i < result_size; i++)
        {
        	result[i] = (int*) malloc (sizeof(int) * size);
        }
    }
    ~Permutations ()
    {
        delete PtoN;
        delete NtoP;
        delete counter;
        delete direction;
    }
    int ** Get ()
    {
    	int i = 0;
        for (; i < (result_size-1); i++)
        {
        	memcpy (result[i], PtoN, sizeof(int) * size);
            FillGap(size-1);
        }
        memcpy (result[i], PtoN, sizeof(int) * size);
        return result;
    }
};

class Timer
{
private:

	/*
	 * 	Return 1 if the result is negative
	 */
	int CalcDiff ()
	{
		long int diff_ = (stop.tv_usec + 1000000 * stop.tv_sec) - (start.tv_usec + 1000000 * start.tv_sec);
		diff.tv_sec = diff_ / 1000000;
		diff.tv_usec = diff_ % 1000000;
		return (diff_ < 0);
	}
	struct timeval start, stop, diff;
public:
	Timer ()
	{

	}
	void Start ()
	{
		gettimeofday(&start, NULL);
	}
	void Stop ()
	{
		gettimeofday(&stop, NULL);
		CalcDiff();
	}


	long int GetDurationSeconds ()
	{
		return diff.tv_sec;
	}

	long int GetDurationMicroseconds ()
	{
		return diff.tv_usec;
	}
};

}
#endif
