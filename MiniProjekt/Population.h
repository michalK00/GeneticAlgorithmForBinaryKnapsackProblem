#pragma once
#include "KnapsackProblem.h"
#include "Individual.h"
#include <iostream>

class Population {
public:
	Population();
	Population(unsigned int passedPopulationSize, unsigned int numberOfItems);
	Population(std::vector<Individual>& population);

	~Population() = default;
	Population(const Population& other) = default;
	Population(Population&& other) = default;
	Population& operator= (const Population& other) = default;
	Population& operator= (Population&& other) noexcept = default;
	
	void rateAllIndividuals(const KnapsackProblem& knapsackProblem);
	Population executeCrossing(Cross& cross);
	void executeMutating(Mutation& mutate);
	
	const unsigned int getPopulationSize() const;
	const unsigned int getNumberOfItemsFromIndividualAt(unsigned int index) const;

	unsigned int findWorstIndividualIndex(double bestFitness) const;
	std::pair<std::vector<bool>, double> findBestSolution() const;

	void injectGenotypeAndFitnessToIndividualAt(const int index, const std::pair<std::vector<bool>, double>& solutionToInject);
private:
	void generatePopulation(unsigned int numberOfItems);
	std::pair<Individual, Individual> findParentsForCrossing();
	Individual& getBestOfTwoRandomIndividuals();

	std::vector<Individual> population;
	unsigned int populationSize;
	std::mt19937 gen;
};