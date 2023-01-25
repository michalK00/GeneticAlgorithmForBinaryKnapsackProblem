#include "GeneticAlgorithm.h"
#include "KnapsackProblem.h"
#include "Cross.h"
#include "Mutation.h"
#include "Exceptions.h"


void printSolution(const std::pair<std::vector<bool>, double>& solution);
std::pair<std::vector<bool>, double> run(const std::string& problemFilePath, const int populationSize, const double mutationProb, const double crossProb);
std::pair<std::vector<bool>, double> run(const std::string& problemFilePath, Population& population, const double mutationProb, const double crossProb);
std::pair<std::vector<bool>, double> run(const std::vector< std::pair<double, double> >& items, const double knapsackSize, Population& population, const double mutationProb, const double crossProb);
std::pair<std::vector<bool>, double> run(const std::vector< std::pair<double, double> >& items, const double knapsackSize, const int populationSize, const double mutationProb, const double crossProb);
int main() {
	const int populationSize = 60;
	const double mutationProb = 0.15;
	const double crossProb = 0.6;
	const double knapsackSize = 878;
	std::vector< std::pair<double, double> > items;
	items.push_back(std::make_pair(44, 92));
	items.push_back(std::make_pair(46, 4));
	items.push_back(std::make_pair(90, 43));
	items.push_back(std::make_pair(72, 83));
	items.push_back(std::make_pair(91, 84));
	items.push_back(std::make_pair(40, 68));
	items.push_back(std::make_pair(75, 92));
	items.push_back(std::make_pair(35, 82));
	items.push_back(std::make_pair(8, 6));
	items.push_back(std::make_pair(54, 44));
	items.push_back(std::make_pair(78, 32));
	items.push_back(std::make_pair(40, 18));
	items.push_back(std::make_pair(77, 56));
	items.push_back(std::make_pair(15, 83));
	items.push_back(std::make_pair(61, 25));
	items.push_back(std::make_pair(17, 96));
	items.push_back(std::make_pair(75, 70));
	items.push_back(std::make_pair(29, 48));
	items.push_back(std::make_pair(75, 14));
	items.push_back(std::make_pair(63, 58));
		
	Population population(60, 20);
	try
	{

		printSolution(run("test2.txt", 45, mutationProb, crossProb));
		printSolution(run("test2.txt", population, mutationProb, crossProb));
		printSolution(run(items, knapsackSize, population, mutationProb, crossProb));
		printSolution(run(items, knapsackSize, 45, mutationProb, crossProb));
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

std::pair<std::vector<bool>, double> run(const std::string& problemFilePath, const int populationSize, const double mutationProb, const double crossProb)
{
	KnapsackProblem problem(problemFilePath);
	GeneticAlgorithm algorithm(populationSize, problem, mutationProb, crossProb);
	algorithm.runAlgorithm();

	return algorithm.getSolution();
}

std::pair<std::vector<bool>, double> run(const std::string& problemFilePath, Population& population, const double mutationProb, const double crossProb)
{
	KnapsackProblem problem(problemFilePath);
	Population populationCopy(population);
	GeneticAlgorithm algorithm(populationCopy, problem, mutationProb, crossProb);
	algorithm.runAlgorithm();

	return algorithm.getSolution();
}

std::pair<std::vector<bool>, double> run(const std::vector<std::pair<double, double>>& items, const double knapsackSize, Population& population, const double mutationProb, const double crossProb)
{
	KnapsackProblem problem(knapsackSize, items);
	Population populationCopy(population);
	GeneticAlgorithm algorithm(populationCopy, problem, mutationProb, crossProb);
	algorithm.runAlgorithm();
	return algorithm.getSolution();
}

std::pair<std::vector<bool>, double> run(const std::vector<std::pair<double, double>>& items, const double knapsackSize, const int populationSize, const double mutationProb, const double crossProb)
{
	KnapsackProblem problem(knapsackSize, items);
	GeneticAlgorithm algorithm(populationSize, problem, mutationProb, crossProb);
	algorithm.runAlgorithm();

	return algorithm.getSolution();
}
