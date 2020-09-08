#include <chrono>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <vector>
using namespace std;

/* 
WorkingSzie values: 1000, 2000, 3000, 5000, 7500, 10000, 20000, 50000, 75000, 100000, 200000. 
These values were chosen to observe whether the relationship is linear or exponential. The first few
values are linear; then, the scale grows to observe the time for large sizes.
*/

class IntegerArray
{
public:
	IntegerArray()
	{
	}

	IntegerArray(std::initializer_list<int> init)
		: values_(init)
	{
	}

	IntegerArray(std::vector<int>&& v)
		: values_(std::move(v))
	{
	}

	std::vector<int>::const_iterator begin() const
	{
		return values_.begin();
	}

	std::vector<int>::const_iterator end() const
	{
		return values_.end();
	}

	IntegerArray& operator << (int n)
	{
		values_.push_back(n);
		return *this;
	}

	size_t size() const
	{
		return values_.size();
	}
	/**
	* Insert value `v` at position `pos` within the array.
	*/
	std::vector<int>::iterator insert(int v, size_t pos) {

	}

private:
	std::vector<int> values_;
};

std::ostream& operator << (std::ostream&, const IntegerArray&);


// How many elements shall we store in our array?
constexpr size_t WorkingSize = 1000;


int main(int, char*[])
{	
	// Create an empty IntegerArray
	IntegerArray array;

	// Initialize random number generator
	srand(static_cast<unsigned int>(time(nullptr)));

	// Add random elements to the array
	for (size_t i = 0; i < WorkingSize; i++)
	{
		unsigned long r = static_cast<unsigned long>(rand());
		array << (r % WorkingSize);
	}

	//
	// Find an arbitrary number:
	//
	bool foundIt = false;
	int index = 0;

	auto start = std::chrono::high_resolution_clock::now();
	for (int value : array)
	{
		if (value == 42)
		{
			foundIt = true;
			break;
		}

		index++;
	}
	auto end = std::chrono::high_resolution_clock::now();

	if (foundIt)
	{
		cout << "found the value 42 at index " << index;
	}
	else
	{
		cout << "42 is not in the IntegerArray array";
	}

	cout << " (took " << (end - start).count() << " µs)\n";

	//
	// Find the largest number:
	//
	start = std::chrono::high_resolution_clock::now();
	int largest = 0;
	for (auto i = array.begin(); i != array.end(); i++)
	{
		if (*i > largest)
		{
			largest = *i;
		}
	}
	end = std::chrono::high_resolution_clock::now();

	cout << "the largest value is: " << largest
	     << " (took " << (end - start).count() << " µs)\n";

	return 0;
}


std::ostream& operator << (std::ostream& o, const IntegerArray& a)
{
	o << "[";
	for (int i : a)
	{
		o << " " << i;
	}
	o << " ]\n";

	return o;
}