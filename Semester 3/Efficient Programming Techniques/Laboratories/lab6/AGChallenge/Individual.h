#pragma once
#include <vector>
#include "Evaluator.h"

class Individual
{
public:
    Individual(std::vector<int> genotype, CLFLnetEvaluator* evaluator);
    Individual();
    Individual(const Individual& other);
    Individual(Individual&& other) noexcept;

    Individual& operator=(const Individual& other);
    Individual& operator=(Individual&& other) noexcept;

    void mutate(double probability);
    std::vector<Individual*> cross(const Individual* with) const;

    double getFitness() const;

private:
    std::vector<int> genotype;
    CLFLnetEvaluator* evaluator;
    double fitness;

};
