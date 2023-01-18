#include "Population.h"

Population::Population() 
	: populationSize{ 0 },
	gen{ std::random_device{}() }
{}

Population::Population(unsigned int passedPopulationSize, unsigned int numberOfItems)
	: populationSize(passedPopulationSize),
	gen{ std::random_device{}() }
{
	if (populationSize > 0) {
		generatePopulation(numberOfItems);
	}
	
}

Population::Population(std::vector<Individual>& population)
	: population(population),
	populationSize(population.size()),
	gen{ std::random_device{}() }
{}

void Population::generatePopulation(const unsigned int numberOfItems)
{
	population.reserve(populationSize);

	for (int i = 0; i < populationSize; i++) {
		population.emplace_back(numberOfItems);
	}
}

std::pair<Individual, Individual> Population::findParentsForCrossing()
{
	std::pair<Individual, Individual> parents(getBestOfTwoRandomIndividuals(), getBestOfTwoRandomIndividuals());	
	return parents;
}

Individual& Population::getBestOfTwoRandomIndividuals() 
{
	std::uniform_int_distribution<> distrib1(0, populationSize - 1);
	std::uniform_int_distribution<> distrib2(1, populationSize - 1);

	int index1 = distrib1(gen);
	int index2 = (index1 + distrib2(gen)) % populationSize;

	if (population[index1].getFitness() > population[index2].getFitness()) {
		return population[index1];
	}
	return population[index2];
}


void Population::rateAllIndividuals(const KnapsackProblem& knapsackProblem) {
	for (Individual& individual : population) {
		individual.calculateFitness(knapsackProblem);
	}
}

Population Population::executeCrossing(Cross& cross)
{
	Population newPopulation;
	while (newPopulation.population.size() < population.size()) {
		std::pair<Individual, Individual> parents(findParentsForCrossing());

		std::vector<Individual> children(parents.first.cross(cross, parents.second));
		//czy obliczac dla ostatnich dwoch dzieci fitness i wybrac lepsze?
		if (newPopulation.populationSize == populationSize - 1) {
			newPopulation.population.emplace_back(std::move(children[0]));
			newPopulation.populationSize++;
		}
		else {
			newPopulation.population.emplace_back(std::move(children[0]));
			newPopulation.population.emplace_back(std::move(children[1]));
			newPopulation.populationSize += 2;
		}
	}
	return newPopulation;
}

void Population::executeMutating(Mutation& mutate)
{
	for (Individual& individual : population) {
		individual.mutate(mutate);
	}
}

const std::vector<Individual>& Population::getPopulation() const
{
	return population;
}

unsigned int Population::findWorstIndividualIndex() const
{
	int worstFittnes = population[findBestIndividualIndex()].getFitness();
	int index = -1;
	for (int i = 0; i < populationSize; i++) {
		if (population[i].getFitness() < worstFittnes) {
			worstFittnes = population[i].getFitness();
			index = i;
		}
	}
	return index;
}

unsigned int Population::findBestIndividualIndex() const
{
	int bestIndex = -1;
	int index = -1;
	for (int i = 0; i < populationSize; i++) {
		if (population[i].getFitness() > bestIndex) {
			bestIndex = population[i].getFitness();
			index = i;
		}
	}
	return index;
}

void Population::swapIndividualAtIndex(const int index, const Individual& individualToInsert)
{
	population[index] = individualToInsert;
}
