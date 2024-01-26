#include "GeneticAlgorithm.h"
#include "MyMath.h"
#include <iostream>
#include <iomanip>

// modification: add a new field, double scaling, scaling in [0, inf[, that increases the population on each iteration

GeneticAlgorithm::GeneticAlgorithm(int populationSize, double crossProbability, double mutationProbability, CLFLnetEvaluator* evaluator)
    : crossProbability(crossProbability), mutationProbability(mutationProbability), evaluator(evaluator)
{
    bestIndividual = Individual();
    generateRandomPopulation(populationSize);
}

void GeneticAlgorithm::runIterations(unsigned long n, void (*callback)(double))
{
    for (unsigned long i = 0; i < n; i++) {
        runIteration();
        callback(bestIndividual.getFitness());
    }
}

void GeneticAlgorithm::runIteration()
{
    int currentPopulationSize = population.size();
    int newPopulationSize = static_cast<int>(currentPopulationSize * scaling); // Modification increase by any percent by adding * scaling, where scaling is the factor

    std::vector<Individual*> newPopulation;
    newPopulation.reserve(newPopulationSize);

    while (newPopulation.size() < newPopulationSize) {
        double* fitnesses = cumulativeFitness();
        Individual* individual1 = getParentCandidateRoulette(fitnesses);
        Individual* individual2 = getParentCandidateRoulette(fitnesses);
        delete[] fitnesses;

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

    for (int i = 0; i < newPopulation.size(); i++) {
        newPopulation[i]->mutate(mutationProbability);
    }

    for (auto& ind : population) {
        delete ind;
    }

    population = std::move(newPopulation);

    evaluatePopulation();
}

void GeneticAlgorithm::generateRandomPopulation(int populationSize)
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

void GeneticAlgorithm::evaluatePopulation()
{
    Individual* currBest = &bestIndividual;
    for (int i = 1; i < population.size(); i++) {
        if (currBest->getFitness() < population[i]->getFitness()) {
            currBest = population[i];
        }
    }
    bestIndividual = *currBest;
}

Individual* GeneticAlgorithm::getParentCandidateRoulette(double* fitnesses)
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
    
    std::cout << "===== Parent Selection Debug Info =====\n";
    std::cout << "Population Size: " << population.size() << "\n";
    std::cout << "Cumulative Fitness Values:\n";
    for (int i = 0; i < population.size(); i++) {
        std::cout << "Index " << i << ": " << std::scientific << std::setprecision(6) << fitnesses[i] << "\n";
    }
    std::cout << "Random Selection Value: " << std::scientific << std::setprecision(6) << selection << "\n";
    std::cout << "Initial Range: 0 - " << (population.size() - 1) << "\n";
    std::cout << "Final Selection Range: " << l << " - " << r << "\n";
    std::cout << "Selected Index: " << l << "\n";
    std::cout << "========================================\n";

    return population[l];
}

double* GeneticAlgorithm::cumulativeFitness()
{
    double* fitnesses = new double[population.size()];
    fitnesses[0] = population[0]->getFitness();

    for (int i = 1; i < population.size(); i++) {
        fitnesses[i] = fitnesses[i - 1] + population[i]->getFitness();
    }

    return fitnesses;
}

Individual& GeneticAlgorithm::getBestIndividual()
{
    return bestIndividual;
}

Individual* GeneticAlgorithm::getParentCandidate()
{
    Individual* individual1 = population[lRand(population.size())];
    Individual* individual2 = population[lRand(population.size())];
    return (individual1->getFitness() > individual2->getFitness()) ? individual1 : individual2;
}

/*
    std::cout << "===== Parent Selection Debug Info =====\n";
    std::cout << "Population Size: " << population.size() << "\n";
    std::cout << "Cumulative Fitness Values:\n";
    for (int i = 0; i < population.size(); i++) {
        std::cout << "Index " << i << ": " << std::scientific << std::setprecision(6) << fitnesses[i] << "\n";
    }
    std::cout << "Random Selection Value: " << std::scientific << std::setprecision(6) << selection << "\n";
    std::cout << "Initial Range: 0 - " << (population.size() - 1) << "\n";
    std::cout << "Final Selection Range: " << l << " - " << r << "\n";
    std::cout << "Selected Index: " << l << "\n";
    std::cout << "========================================\n";
*/