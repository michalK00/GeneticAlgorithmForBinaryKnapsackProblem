#include "KnapsackProblem.h"
#include <fstream> 
#include "Exceptions.h"

std::vector<std::pair<double, double> >& KnapsackProblem::getItems() {
	return items;
}
double KnapsackProblem::getKnapsackSize() const {
	return knapsackSize; 
}
KnapsackProblem::KnapsackProblem(const std::string& itemsFilePath) {
	loadProblemFromFile(itemsFilePath);
}
KnapsackProblem::KnapsackProblem(const double knapsackSize, const std::vector<std::pair<double, double> > items) 
	: knapsackSize(knapsackSize), 
	numberOfItems(items.size()), 
	items(items) 
{
	validatePassedParameters(knapsackSize, items);
}

double KnapsackProblem::calculateSolutionValue(const std::vector<bool>& genotype) const {
	double weight = 0;
	double value = 0;
	for (int index = 0; index < genotype.size(); index++) {
		if (genotype[index]) {
			value += items[index].first;
			weight += items[index].second;
		}
	}
	if (weight > knapsackSize) {
		return 0;
	}
	else {
		return value;
	}
}
void KnapsackProblem::loadProblemFromFile(const std::string& itemsFilePath) {
	std::ifstream file(itemsFilePath);
	if (!file.is_open()) {
		throw FileNotOpenedException(itemsFilePath);
	}
	int pairNumber = 1;
	int redNumberOfItems;
	double redKnapsackSize;
	
	file >> redNumberOfItems >> redKnapsackSize;
	if (file.fail() || redKnapsackSize <= 0 || redNumberOfItems <= 0) {
		throw FileReadingException(pairNumber);
	}
	pairNumber++;
	items.reserve(numberOfItems);
	numberOfItems = redNumberOfItems;
	knapsackSize = redKnapsackSize;

	double value, weight;

	while (numberOfItems != items.size() && !file.eof()) {
		file >> value >> weight;
		if (file.fail() || value <= 0 || weight <= 0) {
			throw FileReadingException(pairNumber);
		}
		items.push_back(std::make_pair(value, weight));
		pairNumber++;
	}

	if (!file.eof() || numberOfItems != items.size()) {
		throw NumberOfItemsDifferentThanNumberOfLinesInFileException(numberOfItems);
	}
	
}

void KnapsackProblem::validatePassedParameters(const double knapsackSize, const std::vector<std::pair<double, double> >& items) {
	if (knapsackSize <= 0 ) {
		throw IllegalSizeException(knapsackSize, KNAPSACK_SIZE_INFO);
	}
	if (items.size() == 0) {
		throw IllegalSizeException(items.size(), ITEM_SIZE_INFO);
	}
	for (int i = 0; i < items.size(); i++) {
		if (items[i].first <= 0) {
			throw IllegalItemParametersException(items[i].first);
		}
		if (items[i].second <= 0) {
			throw IllegalItemParametersException(items[i].second);
		}
	}

}
