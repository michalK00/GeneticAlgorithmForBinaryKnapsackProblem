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
GeneticAlgorithm::GeneticAlgorithm(Population& passedPopulation, KnapsackProblem& problem, double mutationProbability, double crossProbability)
	: 	mutationProbability(mutationProbability),
	crossProbability(crossProbability),
	mutation(mutationProbability),
	cross(crossProbability),
	problem(problem)
{
	validateInputParameters(passedPopulation.getPopulationSize(), mutationProbability, crossProbability);
	validatePopulation(passedPopulation, problem);
	population = Population(passedPopulation);
}
void GeneticAlgorithm::validateInputParameters(int populationSize, double mutationProbability, double crossProbability) const{

	if (populationSize <= 0) {
		throw IllegalSizeException(populationSize, POP_SIZE_INFO);
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
void GeneticAlgorithm::runAlgorithm() {
	
	for (int iteration = 0; iteration < NUMBER_OF_ITERATIONS; iteration++) {
		population.rateAllIndividuals(problem);

		std::pair<std::vector<bool>, double> bestSolutionFromCurrentPopulation(std::move(population.findBestSolution()));
		if (bestSolutionFromCurrentPopulation.second < lastBestSolution.second) {
			double bestFitnessFromCurrentPopulation = population.findWorstIndividualIndex(bestSolutionFromCurrentPopulation.second);
			swapOldBestWithWorstFromNewPopulation(bestFitnessFromCurrentPopulation);
			boostMutProb();
		}
		else {
			lastBestSolution = std::move(bestSolutionFromCurrentPopulation);
		}
		population = std::move(population.executeCrossing(cross));
		population.executeMutating(mutation);

		mutation.setMutationProbability(mutationProbability);
	}
	population.rateAllIndividuals(problem);
	lastBestSolution = std::move(population.findBestSolution());
}
std::pair<std::vector<bool>, double> GeneticAlgorithm::getSolution()
{
	return lastBestSolution;
}
void GeneticAlgorithm::boostMutProb()
{
	mutation.setMutationProbability(std::min(1.0, mutationProbability + mutationProbability * MUTATION_BOOSTER));
}
void GeneticAlgorithm::swapOldBestWithWorstFromNewPopulation(double bestFitnessFromCurrentPopulation)
{
	population.injectGenotypeAndFitnessToIndividualAt(bestFitnessFromCurrentPopulation, lastBestSolution);
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