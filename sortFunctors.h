/***************************************
* A library of sort functions written as
* functor objects that can later be embedded,
* say in a linked list, for use in an automated
* sort race!
* Author: Matthew Bell
* Last updated: 10/17/2020
****************************************/

#include <string>
#include <vector>
#include <chrono>

#ifndef SORTFUNC_H
#define SORTFUNC_H

//sortFunc is a polymorphic base class
template <typename T>
class sortFunc {
private:
	int idNum; //For holding the actual id
	std::string name; // For giving a name to this sort procedure
protected:
	double lastRunTime; // For holding the amount of time it took the last time it ran in microseconds
public:
	static unsigned int idPool; // For assigning an ID to each sort class
	sortFunc(std::string name = "None assigned") :
		idNum(++idPool),
		name(name),
		lastRunTime(-1.0) {}
	//Default polymorphic function, purely virtual
	virtual void operator()(std::vector<T>& unsorted) = 0;

	int getID() const { return idNum; }
	std::string getName() const { return name; }

	//Now for a most interesting getter: this one returns the last run time in microseconds
	double LRT() {
		return lastRunTime;
	}
	
};

template <typename T>
class bubbleSort : public sortFunc<T> {
public:
	bubbleSort(std::string name = "None assigned") :
		sortFunc<T>(name) {}
	void operator()(std::vector<T>& unsorted);
};

#endif

template<typename T>
inline void bubbleSort<T>::operator()(std::vector<T>& unsorted)
{
	// First, setup to track how long it takes
	auto start = std::chrono::high_resolution_clock::now();
	bool swapped = true;
	int last = unsorted.size();
	while (swapped) {
		swapped = false;
		for (int i = 0; i < last - 1; i++) {
			if (unsorted[i] > unsorted[i + 1]) {
				T temp = unsorted[i];
				unsorted[i] = unsorted[i + 1];
				unsorted[i + 1] = temp;
				swapped = true;
			}
		}
		last--;
	}
	auto end = std::chrono::high_resolution_clock::now();
	this->lastRunTime = (std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count();
}
