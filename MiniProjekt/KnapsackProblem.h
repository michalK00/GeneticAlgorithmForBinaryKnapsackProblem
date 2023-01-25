#pragma once
#include <iostream>
#include <vector>
#include "Exceptions.h"

class KnapsackProblem {
public:
	KnapsackProblem(const std::string& itemsFilePath);
	KnapsackProblem(const double knapsackSize,const std::vector<std::pair<double, double> > items);

	~KnapsackProblem() = default;
	KnapsackProblem(const KnapsackProblem& other) = default;
	KnapsackProblem(KnapsackProblem&& other) = default;
	KnapsackProblem& operator= (const KnapsackProblem& other) = default;
	KnapsackProblem& operator= (KnapsackProblem&& other) noexcept = default;

	double calculateSolutionValue(const std::vector<bool>& genotype) const;
	
	std::vector<std::pair<double, double> >& getItems();
	double getKnapsackSize() const;
private:
	void validatePassedParameters(const double knapsackSize, const std::vector<std::pair<double, double> >& items);
	void loadProblemFromFile(const std::string& itemsFilePath);

	unsigned int numberOfItems;
	double knapsackSize;
	std::vector<std::pair<double, double> > items;



};