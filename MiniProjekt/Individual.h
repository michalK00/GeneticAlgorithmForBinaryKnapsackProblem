#pragma once
#include <iostream>
#include <random>
#include <vector>
#include "KnapsackProblem.h"
#include "Mutation.h"
#include "Cross.h"

class Individual {
public:
	Individual();
	Individual(int numberOfItems);
	Individual(const std::vector<bool>& genotype);
	Individual(const std::vector<bool>& genotype, double fitness);

	double calculateFitness(const KnapsackProblem& problem);
	void mutate(Mutation& mutation);
	std::vector<Individual> cross(Cross& cross, Individual& secondParent);
	const std::vector<bool>& getGenotype() const;
	const double getFitness() const;
private:
	std::vector<bool> genotype;
	double fitness;
	std::mt19937 gen;

};
