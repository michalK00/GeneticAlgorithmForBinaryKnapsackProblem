#pragma once
#include "Individual.h"
#include "Mutation.h"
#include "Cross.h"
#include "Population.h"


class GeneticAlgorithm {
public:
	GeneticAlgorithm(int populationSize, KnapsackProblem& problem, double mutationProbability, double crossProbability);
	GeneticAlgorithm(Population& population, KnapsackProblem& problem, double mutationProbability, double crossProbability);
	


	void runAlgorithm(KnapsackProblem& problem);
	std::pair<std::vector<bool>, double> getSolution();

	double getMutationProbability() const;
	double getCrossProbability() const;
	const Mutation& getMutation() const;
	const Cross& getCross() const;
private:
	void checkIfNewPopulationGotBetterIfNotAddOldBestAndBoostMutProbIfYesUpdateBestSolution();
	void validateInputParameters(int populationSize, double mutationProbability, double crossProbability) const;
	void validatePopulation(Population& population, KnapsackProblem& problem);

	static const int NUMBER_OF_ITERATIONS = 1000;
	//nie wiem czemu nie ale double nie moze zostac zainicjalizowany w obrebie klasy bez constexpr
	static constexpr double MUTATION_BOOSTER = 0.1;
	double mutationProbability;
	double crossProbability;

	Population population;
	std::pair<std::vector<bool>, double> lastBestSolution;

	KnapsackProblem problem;
	Mutation mutation;
	Cross cross;
};