package com.so;

import java.util.List;

public abstract class Algorithm {
    
    private int physicalMemorySize;
    private int virtualMemorySize;
    private List<Integer> referenceSequence;

    public Algorithm(int physicalMemorySize, int virtualMemorySize, List<Integer> referenceSequence) {
        this.physicalMemorySize = physicalMemorySize;
        this.virtualMemorySize = virtualMemorySize;
        this.referenceSequence = referenceSequence;
    }

}
