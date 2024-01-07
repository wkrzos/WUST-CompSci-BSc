#include "GeneticAlgorithm.h"
#include <iostream>
#include <random>

GeneticAlgorithm::GeneticAlgorithm(int populationSize, float crossProbability, float mutationProbability, IEvaluator* evaluator)
    : crossProbability(crossProbability),
    mutationProbability(mutationProbability),
    evaluator(evaluator) {
    initializePopulation(populationSize);
    bestIndividual = population.front();
}

void GeneticAlgorithm::runOneIteration() {
    std::vector<Individual> newPopulation;

    while (newPopulation.size() < population.size()) {
        std::pair<Individual, Individual> parents = selectParents();
        std::vector<Individual> children = crossParents(parents);

        newPopulation.insert(newPopulation.end(), children.begin(), children.end());
    }

    applyMutation(newPopulation);
    population = std::move(newPopulation);
}

void GeneticAlgorithm::runIterations(int numberOfIterations) {
    for (int i = 0; i < numberOfIterations; ++i) {
        runOneIteration();
        evaluatePopulation();
        std::cout << bestIndividual.getFitness() << std::endl;
    }
}

Individual GeneticAlgorithm::getBestCandidat() {
    return bestIndividual;
}

void GeneticAlgorithm::initializePopulation(int populationSize) {
    for (int i = 0; i < populationSize; ++i) {
        std::vector<int> genotype = generateGenotype();
        population.emplace_back(genotype, evaluator);
    }
}

void GeneticAlgorithm::evaluatePopulation() {
    bestIndividual = *std::max_element(population.begin(), population.end(),
        [](const Individual& a, const Individual& b) {
            return a.getFitness() < b.getFitness();
        });
}

std::vector<int> GeneticAlgorithm::generateGenotype() {
    std::vector<int> genotype;
    size_t genotypeSize = evaluator->iGetNumberOfBits();

    for (size_t j = 0; j < genotypeSize; ++j) {
        genotype.push_back(lRand(evaluator->iGetNumberOfValues(j)));
    }

    return genotype;
}

std::pair<Individual, Individual> GeneticAlgorithm::selectParents() {
    Individual firstParent = selectBetterIndividual();
    Individual secondParent = selectBetterIndividual();

    return { firstParent, secondParent };
}

Individual GeneticAlgorithm::selectBetterIndividual() {
    Individual firstCandidate = population.at(dRand() * population.size());
    Individual secondCandidate = population.at(dRand() * population.size());

    return firstCandidate.getFitness() > secondCandidate.getFitness() ? firstCandidate : secondCandidate;
}

std::vector<Individual> GeneticAlgorithm::crossParents(const std::pair<Individual, Individual>& parents) {
    if (dRand() < crossProbability) {
        return parents.first.cross(parents.second);
    }
    else {
        return { parents.first, parents.second };
    }
}

void GeneticAlgorithm::applyMutation(std::vector<Individual>& individuals) {
    for (Individual& individual : individuals) {
        individual.mutate(mutationProbability);
    }
}
