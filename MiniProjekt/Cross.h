#pragma once
#include <random>

class Individual;


class Cross {
public:
	Cross(double crossProb);
	//std::vector< std::vector<bool> > onePointCross(const std::vector<bool>& fstParentGenotype, const std::vector<bool>& sndParentGenotype);
	std::vector<Individual> onePointCross(const Individual& fstParentGenotype, const Individual& sndParentGenotype);
	
private:
	bool decideCrossing();
	int getBreakpoint(int upperBound);

	double crossProb;
	std::mt19937 gen;
};