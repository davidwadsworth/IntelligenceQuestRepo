#pragma once

/*
 * unruly : unorganized array
 * addition adds the element to end of list unless its full in which case it does nothing
 * remove displaces the last element with the position of remove
 * clear brings the array back to its starting point
 */

template <typename T, std::size_t Sz>
struct unruly
{
	T buffer[Sz];
	unsigned size = 0;
	
	void push_back(T col) // emplaces T to the end of the unruly and increments size, if full then nothing is added
	{
		if (size > Sz - 1) return;
		buffer[size++] = col;
	}
	
	void remove(unsigned ele) // replaces the element with the element at the end
	{
		buffer[ele] = buffer[--size];
	} 
	void clear() { size = 0; }

	T& operator[](unsigned i)
	{
		return buffer[i];
	}

	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin() { 
		return &buffer[0]; 
	}
	const_iterator begin() const { return &buffer[0]; }
	iterator end() { return &buffer[size - 1]; }
	const_iterator end() const { return &buffer[size - 1]; }

};


