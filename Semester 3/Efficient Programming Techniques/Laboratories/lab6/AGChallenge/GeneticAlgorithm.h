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
	void initPopulation(int populationSize);
	Individual* getParentCandidate();
	Individual* getParentCandidateRoulette(double* fitnesses);

	double* cumulativeFitness();

	void evaluatePopulation();


	Individual bestIndividual;
	std::vector<Individual*> population;
	double crossProbability;
	double mutationProbability;
	CLFLnetEvaluator* evaluator;
};

