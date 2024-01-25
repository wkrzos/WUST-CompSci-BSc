#include "ExperimentManager.h"
#include "Constants.h"

ExperimentManager::ExperimentManager(const std::string& filename) {
    resultsFile.open(filename);
    if (!resultsFile.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    // Write the header for the CSV file
    resultsFile << "Experiment Name,Population Size,Crossover Probability,Mutation Probability,Iterations,Fitness\n";
}

ExperimentManager::~ExperimentManager() {
    if (resultsFile.is_open()) {
        resultsFile.close();
    }
}

void ExperimentManager::runExperiment(int popSize, double crossProb, double mutProb, int iterations, const ATL::CString& experimentName) {
    CLFLnetEvaluator c_lfl_eval;
    c_lfl_eval.bConfigure(experimentName);

    GeneticAlgorithm algorithm(popSize, crossProb, mutProb, &c_lfl_eval);
    algorithm.runIterations(iterations, ExperimentManager::printFitness);

    double fitness = algorithm.getBestIndividual().getFitness();
    logResult(std::string(experimentName), fitness); // Convert ATL::CString back to std::string if needed
}

void ExperimentManager::printFitness(double fitness) {
    std::cout << "Fitness: " << fitness << std::endl;
}

void ExperimentManager::logResult(const std::string& experimentName, double fitness) {
    resultsFile << experimentName << "," << POP_SIZE << "," << CROSS_PROB << "," << MUT_PROB << "," << ITERATIONS << "," << fitness << "\n";
}
