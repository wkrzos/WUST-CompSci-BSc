#pragma once
#include "Evaluator.h"
#include "Individual.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int populationSize, double crossProbability, double mutationProbability, CLFLnetEvaluator* evaluator);

	void runIteration();
	void runIterations(unsigned long n, void(*callback)(double));

	Individual& getBestIndividual();

private:
	Individual bestIndividual;
	double scaling = 1.5; // modification
	std::vector<Individual*> population;
	double crossProbability;
	double mutationProbability;
	CLFLnetEvaluator* evaluator;

	void generateRandomPopulation(int populationSize);
	void evaluatePopulation();

	double* cumulativeFitness();

	Individual* getParentCandidate();
	Individual* getParentCandidateRoulette(double* fitnesses);

};

