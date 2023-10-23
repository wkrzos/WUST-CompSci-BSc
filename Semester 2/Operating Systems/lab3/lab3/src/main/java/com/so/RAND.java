package com.so;

import java.util.*;

public class RAND {
    private int virtualMemorySize;
    private int physicalMemorySize;
    private List<Integer> referenceSequence;

    public RAND(int virtualMemorySize, int physicalMemorySize, List<Integer> referenceSequence) {
        this.virtualMemorySize = virtualMemorySize;
        this.physicalMemorySize = physicalMemorySize;
        this.referenceSequence = referenceSequence;
    }

    public void runRAND() {
        Set<Integer> physicalMemory = new HashSet<>();
        int pageFaults = 0;

        for (int reference : referenceSequence) {
            if (!physicalMemory.contains(reference)) {
                pageFaults++;

                if (physicalMemory.size() >= physicalMemorySize) {
                    // Remove a random page from physical memory
                    int randomPageIndex = new Random().nextInt(physicalMemorySize);
                    int pageToReplace = (int) physicalMemory.toArray()[randomPageIndex];
                    physicalMemory.remove(pageToReplace);
                }

                physicalMemory.add(reference);
            }
        }

        System.out.println("\nRAND Page Replacement");
        System.out.println("Virtual Memory Size: " + virtualMemorySize);
        System.out.println("Physical Memory Size: " + physicalMemorySize);
        System.out.println("Reference Sequence Length: " + referenceSequence.size());
        System.out.println("Page Faults: " + pageFaults);
    }
}