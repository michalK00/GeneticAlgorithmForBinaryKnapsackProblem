#pragma once
#include "Individual.h"
#include "Mutation.h"
#include "Cross.h"
#include "Population.h"


class GeneticAlgorithm {
public:
	GeneticAlgorithm(unsigned int populationSize, KnapsackProblem& problem, double mutationProbability, double crossProbability);
	GeneticAlgorithm(Population& population, KnapsackProblem& problem, double mutationProbability, double crossProbability);
	


	void runAlgorithm(KnapsackProblem& problem);
	std::pair<std::vector<bool>, double> getSolution();

	double getMutationProbability() const;
	double getCrossProbability() const;
	const Mutation& getMutation() const;
	const Cross& getCross() const;
	unsigned int getPopulationSize() const;
private:
	Individual findBestResultFromCurrentPopulation() const;
	void validateInputParameters(double mutationProbability, double crossProbability) const;
	void setLastBestIndividualToTheOneFromCurrentPopulation();

	static const int NUMBER_OF_ITERATIONS = 1000;
	//nie wiem czemu nie ale double nie moze zostac zainicjalizowany w obrebie klasy bez constexpr
	static constexpr double MUTATION_BOOSTER = 0.1;
	double mutationProbability;
	double crossProbability;
	unsigned int populationSize;

	Population population;
	Individual lastBestIndividual;

	KnapsackProblem problem;

	Mutation mutation;
	Cross cross;
};