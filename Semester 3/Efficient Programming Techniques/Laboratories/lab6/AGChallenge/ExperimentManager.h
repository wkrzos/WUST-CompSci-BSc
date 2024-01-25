#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "GeneticAlgorithm.h"
#include "Evaluator.h"

class ExperimentManager {
private:
    std::ofstream resultsFile;

public:
    ExperimentManager(const std::string& filename);
    ~ExperimentManager();
    void runExperiment(int popSize, double crossProb, double mutProb, int iterations, const ATL::CString& experimentName);
    static void printFitness(double fitness); // Define a similar function within the class
    void logResult(const std::string& experimentName, double fitness);
};
