#include "Individual.h"
#include <sstream>
#include <algorithm>

Individual::Individual(std::vector<int> genotype, IEvaluator* evaluator)
    : genotype(std::move(genotype)), evaluator(evaluator), fitness(0.0) {}

Individual::Individual() : fitness(0.0) {}

double Individual::getFitness() {
    if (fitness == 0.0 && evaluator) {
        fitness = evaluator->dEvaluate(&genotype);
    }
    return fitness;
}

void Individual::mutate(float probability) {
    for (int& gene : genotype) {
        if (dRand() < probability) {
            gene = lRand(evaluator->iGetNumberOfValues(&gene - &genotype[0]));
        }
    }
}

std::vector<Individual> Individual::cross(Individual& other) {
    int crossoverPoint = static_cast<int>(dRand() * genotype.size());
    std::vector<int> child1_genotype = createChildGenotype(other, crossoverPoint);
    std::vector<int> child2_genotype = other.createChildGenotype(*this, crossoverPoint);

    return { Individual(child1_genotype, evaluator), Individual(child2_genotype, evaluator) };
}

Individual& Individual::operator=(const Individual& other) {
    if (this != &other) {
        fitness = other.fitness;
        genotype = other.genotype;
        evaluator = other.evaluator;
    }
    return *this;
}

std::string Individual::toString() const {
    std::stringstream ss;
    for (size_t i = 0; i < genotype.size(); ++i) {
        if (i != 0) ss << ", ";
        ss << genotype[i];
    }
    return ss.str();
}

std::vector<int> Individual::createChildGenotype(const Individual& parent, int crossoverPoint) {
    std::vector<int> childGenotype(genotype.begin(), genotype.begin() + crossoverPoint);
    childGenotype.insert(childGenotype.end(), parent.genotype.begin() + crossoverPoint, parent.genotype.end());
    return childGenotype;
}
