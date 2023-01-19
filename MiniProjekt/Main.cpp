#include "GeneticAlgorithm.h"
#include "KnapsackProblem.h"
#include "Cross.h"
#include "Mutation.h"
#include "Exceptions.h"


void printSolution(const std::pair<std::vector<bool>, double>& solution);
int main() {
	//pozniej przeniesc do .h
	const int populationSize = 45;
	const double mutationProb = 0.15;
	const double crossProb = 0.6;
	const double knapsackSize = 269;
	std::vector< std::pair<double, double> > items;
	items.push_back(std::make_pair(55, 95));
	items.push_back(std::make_pair(10, 4));
	items.push_back(std::make_pair(47, 60));
	items.push_back(std::make_pair(5, 32));
	items.push_back(std::make_pair(4, 23));
	items.push_back(std::make_pair(50, 72));
	items.push_back(std::make_pair(8, 80));
	items.push_back(std::make_pair(61, 62));
	items.push_back(std::make_pair(85, 65));
	items.push_back(std::make_pair(87, 46));
	try
	{
		//Population population(10, 5);

		KnapsackProblem problem("test2.txt");

		//KnapsackProblem problem(knapsackSize, items);

		GeneticAlgorithm algorithm(populationSize, problem, mutationProb, crossProb);

		//GeneticAlgorithm algorithm(population, problem, mutationProb, crossProb);

		algorithm.runAlgorithm(problem);

		//dodac klase runner albo metode printSolution
		std::pair<std::vector<bool>, double> solution = algorithm.getSolution();
		printSolution(solution);
	}
	catch (const FileNotOpenedException& e)
	{
		std::cout << e.what() << "\n";
	}
	catch (const FileReadingException& e)
	{
		std::cout << e.what() << "\n";
	}
	catch (const NumberOfItemsDifferentThanNumberOfLinesInFileException& e)
	{
		std::cout << e.what() << "\n";
	}
	catch (const IllegalItemNumberException& e) {
		std::cout << e.what() << "\n";
	}
	catch (const IllegalParameterValueException& e) {
		std::cout << e.what() << "\n";
	}
	catch (...)
	{
		std::cout << UNKNOWN_ERROR << "\n";
	}
	

	return 0;
}

void printSolution(const std::pair<std::vector<bool>, double>& solution) {
	std::cout << solution.second << "\n";
	for (int i = 0; i < solution.first.size(); i++) {
		std::cout << solution.first[i];
	}
	std::cout << std::endl;
}