#include "Evaluator.h"
#include "Optimizer.h"
#include "Timer.h"
#include "GeneticAlgorithm.h"
#include "Constants.h"
#include "ExperimentManager.h"

#include <exception>
#include <iostream>
#include <random>

/*
int main(int argc, char** argv) {
    random_device maskSeedGenerator;
    int maskSeed = static_cast<int>(maskSeedGenerator());

    srand(time(NULL));

    CString s_test;
    runLFLExperiment("104b00");

    return 0;
}
*/

void printFitness(double fitness) {
    cout << "Fitness: " << fitness << endl;
}

void runExperiment(CLFLnetEvaluator& configuredEvaluator) {
    try {
        GeneticAlgorithm algorithm(POP_SIZE, CROSS_PROB, MUT_PROB, &configuredEvaluator);
        algorithm.runIterations(ITERATIONS, printFitness);

        cout << "Final fitness: " << endl;
        printFitness(algorithm.getBestIndividual().getFitness());
    }
    catch (exception& c_exception) {
        cout << c_exception.what() << endl;
    }
}

void runLFLExperiment(const CString& sNetName) {
    CLFLnetEvaluator c_lfl_eval;
    c_lfl_eval.bConfigure(sNetName);
    runExperiment(c_lfl_eval);
}