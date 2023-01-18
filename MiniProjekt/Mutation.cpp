#include "Mutation.h"
#include <random>
#include <vector>

Mutation::Mutation(double mutationProb) 
	: mutationProb(mutationProb), 
	gen{ std::random_device{}() } 
{}

void Mutation::mutateOverEntireGenotype(std::vector<bool>& genotype) {
	std::uniform_real_distribution<> distrib(0, 1);

	for (int index = 0; index < genotype.size(); index++) {
		if (distrib(gen) < mutationProb) {
			flipGene(index, genotype);
		}
	}
}

void Mutation::setMutationProbability(double mutationProbability)
{
	mutationProb = mutationProbability;
}


void Mutation::flipGene(int index, std::vector<bool>& genotype) const{
	if (genotype[index]) {
		genotype[index] = false;
	}
	else {
		genotype[index] = true;
	}
}