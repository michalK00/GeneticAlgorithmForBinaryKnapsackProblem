#include "Cross.h"

#include "Individual.h"

Cross::Cross(double crossProb)
	: crossProb(crossProb),
	gen{ std::random_device{}() }
{}


int Cross::getBreakpoint(int upperBound)  {

	std::uniform_int_distribution<> distrib(1, upperBound);
	return distrib(gen);
}

std::vector<Individual> Cross::onePointCross(const Individual& fstParent, const Individual& sndParent) {

	std::vector<Individual> crossResult;
	crossResult.reserve(2);

	if (decideCrossing()) {
		std::vector<bool> fstChildGenotype;
		std::vector<bool> sndChildGenotype;
		fstChildGenotype.reserve(fstParent.getGenotype().size());
		sndChildGenotype.reserve(sndParent.getGenotype().size());

		int breakPoint = getBreakpoint(fstParent.getGenotype().size() - 2);

		for (int index = 0; index < breakPoint; index++) {
			fstChildGenotype.push_back(fstParent.getGenotype()[index]);
			sndChildGenotype.push_back(sndParent.getGenotype()[index]);
		}
		for (int index = breakPoint; index < fstParent.getGenotype().size(); index++) {
			fstChildGenotype.push_back(sndParent.getGenotype()[index]);
			sndChildGenotype.push_back(fstParent.getGenotype()[index]);
		}

		crossResult.emplace_back(fstChildGenotype);
		crossResult.emplace_back(sndChildGenotype);
	}
	else {
		crossResult.push_back(fstParent);
		crossResult.push_back(sndParent);
	}
	return crossResult;
}

bool Cross::decideCrossing() {
	std::uniform_real_distribution<> distrib(0, 1);
	if (distrib(gen) < crossProb) return true;
	else return false;
}