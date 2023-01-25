#pragma once
#include <random>

class Individual;


class Cross {
public:
	Cross(double crossProb);
	
	~Cross() = default;
	Cross(const Cross& other) = default;
	Cross(Cross&& other) = default;
	Cross& operator= (const Cross& other) = default;
	Cross& operator= (Cross&& other) noexcept = default;

	std::vector<Individual> onePointCross(const Individual& fstParentGenotype, const Individual& sndParentGenotype);
	
private:
	bool decideCrossing();
	int getBreakpoint(int upperBound);

	double crossProb;
	std::mt19937 gen;
};