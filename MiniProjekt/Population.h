#pragma once
#include "KnapsackProblem.h"
#include "Individual.h"
#include <iostream>

class Population {
public:
	Population();
	Population(unsigned int passedPopulationSize, unsigned int numberOfItems);
	Population(std::vector<Individual>& population);

	
	void rateAllIndividuals(const KnapsackProblem& knapsackProblem);
	Population executeCrossing(Cross& cross);
	void executeMutating(Mutation& mutate);
	
	const std::vector<Individual>& getPopulation() const;

	unsigned int findWorstIndividualIndex() const;
	unsigned int findBestIndividualIndex() const;

	void swapIndividualAtIndex(const int index, const Individual& individualToInsert);
private:
	void generatePopulation(unsigned int numberOfItems);
	std::pair<Individual, Individual> findParentsForCrossing();
	Individual& getBestOfTwoRandomIndividuals();

	std::vector<Individual> population;
	unsigned int populationSize;
	std::mt19937 gen;
};