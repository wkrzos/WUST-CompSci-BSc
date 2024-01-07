#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "Individual.h"
#include <vector>
#include <utility> // For std::pair

class IEvaluator; // Forward declaration of IEvaluator

class GeneticAlgorithm {
public:
    // Constructor
    GeneticAlgorithm(int populationSize, float crossProbability, float mutationProbability, IEvaluator* evaluator);

    // Public methods
    void runOneIteration();
    void runIterations(int numberOfIterations);
    Individual getBestCandidat();

private:
    // Member variables
    std::vector<Individual> population;
    Individual bestIndividual;
    float crossProbability;
    float mutationProbability;
    IEvaluator* evaluator;

    // Private helper methods
    void initializePopulation(int populationSize);
    void evaluatePopulation();
    std::vector<int> generateGenotype();
    std::pair<Individual, Individual> selectParents();
    Individual selectBetterIndividual();
    std::vector<Individual> crossParents(const std::pair<Individual, Individual>& parents);
    void applyMutation(std::vector<Individual>& individuals);
};

#endif // GENETICALGORITHM_H
