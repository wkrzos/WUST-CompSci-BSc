package com.so;

import java.util.*;

public class APPROX{
    private int virtualMemorySize;
    private int physicalMemorySize;
    private List<Integer> referenceSequence;
    List<Integer> physicalMemory = new ArrayList<>();

    public APPROX(int virtualMemorySize, int physicalMemorySize, List<Integer> referenceSequence) {
        this.virtualMemorySize = virtualMemorySize;
        this.physicalMemorySize = physicalMemorySize;
        this.referenceSequence = referenceSequence;
    }

    public void runAPPROX() {
        int pageFaults = 0;

        for (int reference : referenceSequence) {
            if (physicalMemory.contains(reference)) {
                // Page hit
                continue;
            } else if (physicalMemory.size() < physicalMemorySize) {
                // Physical memory has space, add the page
                physicalMemory.add(reference);
            } else {
                // Physical memory is full, replace a page using approximate algorithm
                int pageToReplace = getApproximatePageToReplace(reference);
                physicalMemory.set(pageToReplace, reference);
            }

            pageFaults++;
        }

        System.out.println("\nApproximate Page Replacement");
        System.out.println("Virtual Memory Size: " + virtualMemorySize);
        System.out.println("Physical Memory Size: " + physicalMemorySize);
        System.out.println("Reference Sequence Length: " + referenceSequence.size());
        System.out.println("Page Faults: " + pageFaults);
    }

    private int getApproximatePageToReplace(int reference) {
        int pageToReplace = 0;
        int minDistance = Integer.MAX_VALUE;

        for (int i = 0; i < physicalMemorySize; i++) {
            int page = physicalMemory.get(i);
            int distance = getReferenceDistance(reference, page);

            if (distance == 0) {
                return i; // Found an exact match, replace it
            }

            if (distance < minDistance) {
                minDistance = distance;
                pageToReplace = i;
            }
        }

        return pageToReplace;
    }

    private int getReferenceDistance(int reference1, int reference2) {
        return Math.abs(reference1 - reference2);
    }
}