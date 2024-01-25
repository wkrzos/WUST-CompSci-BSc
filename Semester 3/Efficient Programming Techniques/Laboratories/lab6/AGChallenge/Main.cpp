#include "Evaluator.h"
#include "Optimizer.h"
#include "Timer.h"
#include "GeneticAlgorithm.h"
#include "Constants.h"

#include <exception>
#include <iostream>
#include <random>

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

int main(int argc, char** argv) {
    random_device maskSeedGenerator;
    int maskSeed = static_cast<int>(maskSeedGenerator());

    srand(time(NULL));

    CString s_test;
    runLFLExperiment("104b01");

    // Other experiments (commented out for now)
    /*
    runIsingSpinGlassExperiment(81, 0, maskSeed);
    runLeadingOnesExperiment(50, maskSeed);
    runMaxSatExperiment(25, 0, 4.27f, maskSeed);
    runNearestNeighborNKExperiment(100, 0, 4, maskSeed);
    runOneMaxExperiment(100, maskSeed);
    runRastriginExperiment(200, 10, maskSeed);
    */

    return 0;
}
