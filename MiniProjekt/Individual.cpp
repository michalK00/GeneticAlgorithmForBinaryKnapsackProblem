#include "Individual.h"
#include <random>
#include <iostream>

Individual::Individual() 
	: gen{ std::random_device{}() } 
{
	fitness = -1;
}

Individual::Individual(int genotypeSize)
	: gen{ std::random_device{}() } 
{
	std::uniform_int_distribution<> distrib(0, 1);
	genotype.reserve(genotypeSize);
	for (int index = 0; index < genotypeSize; index++) {
		genotype.push_back(distrib(gen));
	}
	fitness = -1;
}
Individual::Individual(const std::vector<bool>& genotype) 
	: genotype(genotype), 
	gen{std::random_device{}()} 
{
	//nie wiem czy to ma sens
	fitness = -1;
}

Individual::Individual(const std::vector<bool>& genotype, double fitness) 
	: genotype(genotype),
	fitness(fitness),
	gen{ std::random_device{}() }
{}

double Individual::calculateFitness(const KnapsackProblem& problem) {
	fitness = problem.calculateSolutionValue(genotype);
	return fitness;
}

void Individual::mutate(Mutation& mutation) {

	mutation.mutateOverEntireGenotype(genotype);
	
}

std::vector<Individual> Individual::cross(Cross& cross, Individual& secondParent) {

	std::vector<Individual> result{ cross.onePointCross(*this, secondParent.getGenotype()) };
	return  result;
}

const std::vector<bool>& Individual::getGenotype() const {
	return genotype;
}

const double Individual::getFitness() const
{
	return fitness;
}
