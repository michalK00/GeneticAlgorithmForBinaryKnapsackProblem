#pragma once
#include <iostream>
#include <vector>
#include "Exceptions.h"

class KnapsackProblem {
public:
	KnapsackProblem(const std::string& itemsFilePath);
	KnapsackProblem(const double knapsackSize,const std::vector<std::pair<double, double> > items);
	~KnapsackProblem() = default;

	double calculateSolutionValue(const std::vector<bool>& genotype) const;
	void loadProblemFromFile(const std::string& itemsFilePath);

	std::vector<std::pair<double, double> >& getItems();
	double getKnapsackSize() const;
private:
	void validatePassedParameters(const double knapsackSize, const std::vector<std::pair<double, double> >& items);

	unsigned int numberOfItems;
	double knapsackSize;
	std::vector<std::pair<double, double> > items;



};