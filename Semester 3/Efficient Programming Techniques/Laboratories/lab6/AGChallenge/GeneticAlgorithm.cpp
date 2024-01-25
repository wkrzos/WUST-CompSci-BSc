#include "GeneticAlgorithm.h"
#include "MyMath.h"
GeneticAlgorithm::GeneticAlgorithm(int populationSize, double crossProbability, double mutationProbability, CLFLnetEvaluator * evaluator) :
	crossProbability(crossProbability),
	mutationProbability(mutationProbability),
	evaluator(evaluator)
{
	bestIndividual = Individual();
	initPopulation(populationSize);
}

Individual* GeneticAlgorithm::getParentCandidate()
{
	Individual *individual1 = population[lRand(population.size())];
	Individual *individual2 = population[lRand(population.size())];
	if (individual1->getFitness() > individual2->getFitness()) {
		return individual1;
	}
	else {
		return individual2;
	}

}

Individual * GeneticAlgorithm::getParentCandidateRoulette(double* fitnesses)
{
	double selection = dRand() * fitnesses[population.size() - 1];

	int l = 0;
	int r = population.size() - 1;

	while (l <= r) {
		int m = (l + r) / 2;
		if (fitnesses[m] == selection) {
			l = m;
			r = m;
		}
		else if (fitnesses[m] < selection) {
			l = m + 1;
		}
		else {
			r = m - 1;	
		}

	}

#define DEBUG

#ifdef DEBUG
	std::cout << "poszukiwanie rodzica\n";
	std::cout << "tablica: ";
	for (int i = 0; i < population.size(); i++) {
		std::cout << fitnesses[i] << " ";
	}
	std::cout << "\n" << "poszukiwana wartosc: " << selection << "\n";
	std::cout << "znaleeziony indeks:" << l << "\n";
#endif

	return population[l];
}

double * GeneticAlgorithm::cumulativeFitness()
{
	double* fitnesses = new double[population.size()];

	fitnesses[0] = population[0]->getFitness();
	for (int i = 1; i < population.size(); i++) {
		fitnesses[i] = fitnesses[i - 1] + population[i]->getFitness();
	}


	return fitnesses;
}




void GeneticAlgorithm::evaluatePopulation()
{
	Individual *currBest = &bestIndividual;
	for (int i = 1; i < population.size(); i++) {
		if (currBest->getFitness() < population[i]->getFitness()) {
			currBest = population[i];
		}

	}
	bestIndividual = *currBest;
}

void GeneticAlgorithm::runIteration()
{
	std::vector<Individual*> newPopulation;
	newPopulation.reserve(population.size());

	// filling the population
	while (newPopulation.size() < population.size()) {
		double* fitnesses = cumulativeFitness();
		Individual* individual1 = getParentCandidateRoulette(fitnesses);
		Individual* individual2 = getParentCandidateRoulette(fitnesses);

		delete fitnesses;

		//Individual* individual1 = getParentCandidate();
		//Individual* individual2 = getParentCandidate();

		// crossing
		if (dRand() < crossProbability) {
			std::vector<Individual*> children = individual1->cross(individual2);
			newPopulation.push_back(children[0]);
			newPopulation.push_back(children[1]);

		}
		else {
			newPopulation.push_back(new Individual(*individual1));
			newPopulation.push_back(new Individual(*individual2));
		}

	}

	// mutation

	for (int i = 0; i < newPopulation.size(); i++) {
		newPopulation[i]->mutate(mutationProbability);
	}

	for (int i = 0; i < population.size(); i++) {
		delete population[i];
	}


	population = std::move(newPopulation);

	evaluatePopulation();

}

void GeneticAlgorithm::runIterations(unsigned long n, void(*callback)(double))
{
	for (unsigned long i = 0; i < n; i++) {
		runIteration();
		callback(bestIndividual.getFitness());
	}
}

Individual & GeneticAlgorithm::getBestIndividual()
{
	return bestIndividual;
}



void GeneticAlgorithm::initPopulation(int populationSize)
{
	int genotypeSize = evaluator->iGetNumberOfBits();
	for (int i = 0; i < populationSize; i++) {
		std::vector<int> genotype;

		for (int j = 0; j < genotypeSize; j++) {
			genotype.push_back(lRand(evaluator->iGetNumberOfValues(j)));
		}
		Individual* individual = new Individual(genotype, evaluator);

		population.push_back(individual);
	}
	evaluatePopulation();

}

