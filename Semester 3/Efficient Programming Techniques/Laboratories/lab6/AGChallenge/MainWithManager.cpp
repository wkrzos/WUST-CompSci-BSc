#include "Evaluator.h"
#include "Optimizer.h"
#include "Timer.h"
#include "GeneticAlgorithm.h"
#include "Constants.h"
#include "ExperimentManager.h"

#include <exception>
#include <iostream>
#include <random>

int main(int argc, char** argv) {
    ExperimentManager manager("experiment_results.csv");

    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b00"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b01"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b02"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b03"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b04"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b05"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b06"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b07"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b08"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("104b09"));

    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b00"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b01"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b02"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b03"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b04"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b05"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b06"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b07"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b08"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("114b09"));

    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b00"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b01"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b02"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b03"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b04"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b05"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b06"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b07"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b08"));
    manager.runExperiment(POP_SIZE, CROSS_PROB, MUT_PROB, ITERATIONS, _T("128b09"));

    return 0;
}