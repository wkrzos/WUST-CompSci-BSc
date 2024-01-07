#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include <string>

class IEvaluator; // Forward declaration of IEvaluator

class Individual {
public:
    // Constructors
    Individual(std::vector<int> genotype, IEvaluator* evaluator);
    Individual();

    // Public methods
    double getFitness();
    void mutate(float probability);
    std::vector<Individual> cross(Individual& other);
    Individual& operator=(const Individual& other);
    std::string toString() const;

private:
    // Member variables
    std::vector<int> genotype;
    IEvaluator* evaluator;
    double fitness;

    // Private helper methods
    std::vector<int> createChildGenotype(const Individual& parent, int crossoverPoint);
};

#endif // INDIVIDUAL_H
