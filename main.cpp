#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "..\headers\sortFunctors.h"

//Initializes the IDPool so that every sort functor has its own unique ID.
unsigned int sortFunc<int>::idPool = 0;

//Main illustrates how everything works together -- kinda like an integration
//test. This isn't a completed application! MTB.
int main()
{
	//Populate a vector with some numbers.
	std::vector<int> sortme;
	sortme.push_back(5);
	sortme.push_back(4);
	sortme.push_back(3);
	sortme.push_back(2);
	sortme.push_back(1);

	//Populate a linked list of sort functors! For now, we just repeat
	//Bubblesort twice.
	std::list<sortFunc<int>*> sortList;
	sortList.push_back(new bubbleSort<int>("Bubblesort"));
	sortList.push_back(new bubbleSort<int>("Bubblesort"));

	//Print the unsorted vector
	for (unsigned int i = 0; i < sortme.size(); i++)
		std::cout << sortme[i] << std::endl;

	//Sort the vector
	std::list<sortFunc<int>*>::iterator it;
	for (it = sortList.begin(); it != sortList.end(); ++it) {
		(*(*it))(sortme);	// <== I agree, it looks weird. Can you see what's going on
							// with the dereference operators? *it "dereferences" the
							// iterator to get the pointer to the sortFunc. Then, the
							// outer * [i.e. the (*(*it))] follows THAT pointer to get to
							// the sortFunc object. I readily grant this is spaghetti code!
							// Can you make it better? MTB.

		std::cout << "Results of running functor " << (*it)->getID()
			<< ":" << (*it)->getName() << "." << std::endl;
		//Print the sorted vector
		for (unsigned int i = 0; i < sortme.size(); i++)
			std::cout << sortme[i] << std::endl;
	}

	//Now, how long did our first Bubblesort take?
	std::cout << (*(sortList.begin()))->LRT() << " microseconds elapsed." << std::endl;

	//Clean up our mess!
	for (it = sortList.begin(); it != sortList.end(); ++it)
		delete (*it);

	return 0;
}