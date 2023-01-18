#pragma once
#include <random>
#include <vector>

class Mutation {
public:
	Mutation(double mutationProb);

	void mutateOverEntireGenotype(std::vector<bool>& genotype);
	//void singleMutation(std::vector<bool> genotype) const;
	void setMutationProbability(double mutationProbability);
private:
	void flipGene(int index, std::vector<bool>& genotype) const;

	double mutationProb;
	std::mt19937 gen;

};

