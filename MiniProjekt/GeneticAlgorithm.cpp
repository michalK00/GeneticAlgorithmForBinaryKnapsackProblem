#include "GeneticAlgorithm.h"
#include "Exceptions.h"



GeneticAlgorithm::GeneticAlgorithm(int populationSize, KnapsackProblem& problem, double mutationProbability, double crossProbability)
	: 	mutationProbability(mutationProbability),
	crossProbability(crossProbability),
	mutation(mutationProbability),
	cross(crossProbability),
	problem(problem)
{
	validateInputParameters(populationSize, mutationProbability, crossProbability);
	population = Population(populationSize, problem.getItems().size());
}
GeneticAlgorithm::GeneticAlgorithm(Population& population, KnapsackProblem& problem, double mutationProbability, double crossProbability)
	: 	mutationProbability(mutationProbability),
	crossProbability(crossProbability),
	mutation(mutationProbability),
	cross(crossProbability),
	problem(problem)
{
	validateInputParameters(population.getPopulationSize(), mutationProbability, crossProbability);
	validatePopulation(population, problem);
	population = Population(population);
}
void GeneticAlgorithm::validateInputParameters(int populationSize, double mutationProbability, double crossProbability) const{

	if (populationSize <= 0) {
		throw IllegalPopulationSizeException(populationSize);
	}
	if (mutationProbability > 1 || mutationProbability < 0) {
		throw IllegalProbabilityException(mutationProbability);
	}
	if (crossProbability > 1 || crossProbability < 0) {
		throw IllegalProbabilityException(crossProbability);
	}

}
void GeneticAlgorithm::validatePopulation(Population& population, KnapsackProblem& problem)
{
	for (int i = 0; i < population.getPopulationSize(); i++) {
		int actualSize = population.getNumberOfItemsFromIndividualAt(i);
		int expectedSizeproblem = problem.getItems().size();
		if (actualSize != expectedSizeproblem) {
			throw IllegalItemNumberException(i + 1, expectedSizeproblem, actualSize);
		}
	}
}
void GeneticAlgorithm::runAlgorithm(KnapsackProblem& problem) {
	
	for (int iteration = 0; iteration < NUMBER_OF_ITERATIONS; iteration++) {
		population.rateAllIndividuals(problem);
		checkIfNewPopulationGotBetterIfNotAddOldBestAndBoostMutProbIfYesUpdateBestSolution();
		population = std::move(population.executeCrossing(cross));
		population.executeMutating(mutation);
		//nie wiem czy odwolywac sie do tego przez populacje czy przez mutation
		mutation.setMutationProbability(mutationProbability);
	}
	population.rateAllIndividuals(problem);
	lastBestSolution = std::move(population.findBestSolution());
}
std::pair<std::vector<bool>, double> GeneticAlgorithm::getSolution()
{
	return lastBestSolution;
}
void GeneticAlgorithm::checkIfNewPopulationGotBetterIfNotAddOldBestAndBoostMutProbIfYesUpdateBestSolution() {
	std::pair<std::vector<bool>, double> bestSolutionFromCurrentPopulation(std::move(population.findBestSolution()));
	if (bestSolutionFromCurrentPopulation.second < lastBestSolution.second) {
		population.injectGenotypeAndFitnessToIndividualAt(population.findWorstIndividualIndex(bestSolutionFromCurrentPopulation.second), lastBestSolution);
		mutation.setMutationProbability(std::min(1.0, mutationProbability + mutationProbability * MUTATION_BOOSTER));
	}
	else {
		lastBestSolution = std::move(bestSolutionFromCurrentPopulation);
	}
}



double GeneticAlgorithm::getMutationProbability() const {
	return mutationProbability;
}
double GeneticAlgorithm::getCrossProbability() const {
	return crossProbability;
}
const Mutation& GeneticAlgorithm::getMutation() const {
	return mutation;
}
const Cross& GeneticAlgorithm::getCross() const {
	return cross;
}