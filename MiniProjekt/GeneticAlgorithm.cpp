#include "GeneticAlgorithm.h"
#include "Exceptions.h"



GeneticAlgorithm::GeneticAlgorithm(unsigned int populationSize, KnapsackProblem& problem, double mutationProbability, double crossProbability)
	: populationSize(populationSize),
	mutationProbability(mutationProbability),
	crossProbability(crossProbability),
	mutation(mutationProbability),
	cross(crossProbability),
	population(populationSize, problem.getItems().size()),
	problem(problem)
{
	validateInputParameters(mutationProbability, crossProbability);
}
GeneticAlgorithm::GeneticAlgorithm(Population& population, KnapsackProblem& problem, double mutationProbability, double crossProbability)
	: populationSize(population.getPopulation().size()),
	mutationProbability(mutationProbability),
	crossProbability(crossProbability),
	mutation(mutationProbability),
	cross(crossProbability),
	population(population),
	problem(problem)
{
	validateInputParameters(mutationProbability, crossProbability);
}
void GeneticAlgorithm::validateInputParameters(double mutationProbability, double crossProbability) const{

	if (mutationProbability > 1 || mutationProbability < 0) {
		throw IllegalProbabilityException(mutationProbability);
	}
	if (crossProbability > 1 || crossProbability < 0) {
		throw IllegalProbabilityException(crossProbability);
	}

}
void GeneticAlgorithm::runAlgorithm(KnapsackProblem& problem) {
	
	for (int iteration = 0; iteration < NUMBER_OF_ITERATIONS; iteration++) {
		population.rateAllIndividuals(problem);

		if (findBestResultFromCurrentPopulation().getFitness() < lastBestIndividual.getFitness()) {
			population.swapIndividualAtIndex(population.findWorstIndividualIndex(), lastBestIndividual);
		}
		else {
			setLastBestIndividualToTheOneFromCurrentPopulation();
			mutation.setMutationProbability(std::min(1.0, mutationProbability + MUTATION_BOOSTER));			
		}
		population = std::move(population.executeCrossing(cross));
		population.executeMutating(mutation);
		mutation.setMutationProbability(mutationProbability);
	}
	population.rateAllIndividuals(problem);
	setLastBestIndividualToTheOneFromCurrentPopulation();
}
std::pair<std::vector<bool>, double> GeneticAlgorithm::getSolution()
{
	return std::make_pair(lastBestIndividual.getGenotype(), lastBestIndividual.getFitness());
}
Individual GeneticAlgorithm::findBestResultFromCurrentPopulation() const
{
	int index = population.findBestIndividualIndex();
	Individual bestResult{ (population.getPopulation())[index] };
	return bestResult;
}



double GeneticAlgorithm::getMutationProbability() const {
	return mutationProbability;
}
double GeneticAlgorithm::getCrossProbability() const {
	return crossProbability;
}
unsigned int GeneticAlgorithm::getPopulationSize() const {
	return populationSize;
}
void GeneticAlgorithm::setLastBestIndividualToTheOneFromCurrentPopulation()
{
	lastBestIndividual = findBestResultFromCurrentPopulation();
}

const Mutation& GeneticAlgorithm::getMutation() const {
	return mutation;
}
const Cross& GeneticAlgorithm::getCross() const {
	return cross;
}