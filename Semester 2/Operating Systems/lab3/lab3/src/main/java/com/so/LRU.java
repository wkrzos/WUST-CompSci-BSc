package com.so;

import java.util.*;

public class LRU {
    private int virtualMemorySize;
    private int physicalMemorySize;
    private List<Integer> referenceSequence;

    public LRU(int virtualMemorySize, int physicalMemorySize, List<Integer> referenceSequence) {
        this.virtualMemorySize = virtualMemorySize;
        this.physicalMemorySize = physicalMemorySize;
        this.referenceSequence = referenceSequence;
    }

    public void runLRU() {
        List<Integer> physicalMemory = new ArrayList<>();
        List<Integer> pageOrder = new ArrayList<>();
        int pageFaults = 0;

        for (int reference : referenceSequence) {
            if (physicalMemory.contains(reference)) {
                // Page hit, update its position in the page order
                pageOrder.remove((Integer) reference);
                pageOrder.add(reference);
            } else {
                // Page fault, replace the least recently used page
                pageFaults++;

                if (physicalMemory.size() >= physicalMemorySize) {
                    int pageToReplace = pageOrder.get(0);
                    physicalMemory.remove((Integer) pageToReplace);
                    pageOrder.remove(0);
                }

                physicalMemory.add(reference);
                pageOrder.add(reference);
            }
        }

        System.out.println("\nLRU Page Replacement");
        System.out.println("Virtual Memory Size: " + virtualMemorySize);
        System.out.println("Physical Memory Size: " + physicalMemorySize);
        System.out.println("Reference Sequence Length: " + referenceSequence.size());
        System.out.println("Page Faults: " + pageFaults);
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