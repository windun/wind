#ifndef _WIND_CONTAINERS_H_
#define _WIND_CONTAINERS_H_

#include <cstdlib>
#include <cstring>

namespace wind 
{ 

template <class T> class Array
{
private:

	class ValueHandler
	{
	private:
		T * array;
		int index;
	public:
		ValueHandler ()
		{
			array = 0;
			index = 0;
		}

		void Set (T * array_, int index_)
		{
			array = array_;
			index = index_;
		}

		void operator= (T val)
		{
			array[index] = val;
		}

		T value ()
		{
			return array[index];
		}
	};

	void Extend (int index)
	{
		int size_ = (index > A_size ? index : A_size) * EXPANSION_RATIO;
		T * A_ = (T*) malloc (sizeof(T) * size_);
		for (int i = 0; i < A_size; i++)
		{
			A_[i] = A[i];
		}
		delete A;
		A = A_;
		A_size = size_;
	}

	void InitArray (int size_)
	{
		A = (T*) malloc (sizeof(T) * size_);
		memset (A, 0, size_);
	}

	ValueHandler handler;
	T * A;
	int A_size;
	float EXPANSION_RATIO;
	static const int DEFAULT_SIZE = 10;

public:
	Array ()
	{
			A_size = DEFAULT_SIZE;
			A = (T*) malloc (sizeof(T) * A_size);
			EXPANSION_RATIO = 1.5f;
			InitArray(A_size);
	}

	Array (int size_)
	{
			A_size = size_;
			A = (T*) malloc (sizeof(T) * A_size);
			EXPANSION_RATIO = 1.5f;
			InitArray(A_size);
	}

	~Array ()
	{
		delete A;
	}

	ValueHandler operator[] (int index)
	{
		if (index > (A_size-1)) Extend (index);
		handler.Set(A, index);
		return handler;
	}

	int size ()
	{
		return A_size;
	}

	void clear ()
	{
		delete A;
		A = (T*) malloc (sizeof(T) * A_size);
		InitArray(A_size);
	}
};

}
#endif
