#include "Population.h"

Population::Population() 
	: populationSize{ 0 },
	gen{ std::random_device{}() }
{}

Population::Population(unsigned int passedPopulationSize, unsigned int numberOfItems)
	: populationSize(passedPopulationSize),
	gen{ std::random_device{}() }
{
	generatePopulation(numberOfItems);	
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

const unsigned int Population::getPopulationSize() const
{
	return populationSize;
}

const unsigned int Population::getNumberOfItemsFromIndividualAt(unsigned int index) const
{
	return population[index].getGenotype().size();
}

unsigned int Population::findWorstIndividualIndex(double bestFitness) const
{
	double worstFitness = bestFitness;
	int index = -1;
	for (int i = 0; i < populationSize; i++) {
		if (population[i].getFitness() < worstFitness) {
			worstFitness = population[i].getFitness();
			index = i;
		}
	}
	return index;
}

std::pair<std::vector<bool>, double> Population::findBestSolution() const
{
	double bestFitness = -1;
	int index = -1;
	for (int i = 0; i < populationSize; i++) {
		if (population[i].getFitness() > bestFitness) {
			bestFitness = population[i].getFitness();
			index = i;
		}
	}
	return std::make_pair(population[index].getGenotype(), bestFitness);
}

void Population::injectGenotypeAndFitnessToIndividualAt(const int index, const std::pair<std::vector<bool>, double>& solutionToInject)
{
	population[index] = std::move(Individual(solutionToInject.first, solutionToInject.second));
}
