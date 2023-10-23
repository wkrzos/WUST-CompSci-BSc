package com.so;

import java.util.*;

public class PageReplacementSimulation {

    private int virtualMemorySize;
    private int physicalMemorySize;
    private List<Integer> referenceSequence;

    public PageReplacementSimulation(int virtualMemorySize, int physicalMemorySize) {
        this.virtualMemorySize = virtualMemorySize;
        this.physicalMemorySize = physicalMemorySize;
        this.referenceSequence = generateReferenceSequence();
    }

    List<Integer> generateReferenceSequence() {
        List<Integer> sequence = new ArrayList<>();

        // Generowanie ciągu odwołań do stron
        Random random = new Random();
        int localityRange = virtualMemorySize / 10; // Zakładamy lokalność odwołań na 10% całej pamięci wirtualnej

        for (int i = 0; i < 1000; i++) {
            int page = random.nextInt(virtualMemorySize);
            int localityOffset = random.nextInt(localityRange);
            int reference = (page + localityOffset) % virtualMemorySize;
            sequence.add(reference);
        }

        return sequence;
    }

    public int getVirtualMemorySize() {
        return virtualMemorySize;
    }

    public void setVirtualMemorySize(int virtualMemorySize) {
        this.virtualMemorySize = virtualMemorySize;
    }

    public int getPhysicalMemorySize() {
        return physicalMemorySize;
    }

    public void setPhysicalMemorySize(int physicalMemorySize) {
        this.physicalMemorySize = physicalMemorySize;
    }

    public List<Integer> getReferenceSequence() {
        return referenceSequence;
    }

    public void setReferenceSequence(List<Integer> referenceSequence) {
        this.referenceSequence = referenceSequence;
    }
}

