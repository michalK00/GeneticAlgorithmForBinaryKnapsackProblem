#pragma once
#include <random>
#include <vector>

class Mutation {
public:
	Mutation(double mutationProb);

	~Mutation() = default;
	Mutation(const Mutation& other) = default;
	Mutation(Mutation&& other) = default;
	Mutation& operator= (const Mutation& other) = default;
	Mutation& operator= (Mutation&& other) noexcept = default;

	void mutateOverEntireGenotype(std::vector<bool>& genotype);
	void setMutationProbability(double mutationProbability);
private:
	void flipGene(int index, std::vector<bool>& genotype) const;

	double mutationProb;
	std::mt19937 gen;

};

