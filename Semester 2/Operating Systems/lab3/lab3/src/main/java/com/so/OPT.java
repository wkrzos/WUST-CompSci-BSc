package com.so;

import java.util.ArrayList;
import java.util.List;

public class OPT {

    private int physicalMemorySize;
    private int virtualMemorySize;
    private List<Integer> referenceSequence;
    List<Integer> physicalMemory = new ArrayList<>();

    public OPT(int physicalMemorySize, int virtualMemorySize, List<Integer> referenceSequence) {
        this.physicalMemorySize = physicalMemorySize;
        this.virtualMemorySize = virtualMemorySize;
        this.referenceSequence = referenceSequence;
    }

    public void runOPT() {

        int pageFaults = 0;
    
        for (int i = 0; i < referenceSequence.size(); i++) {
            int reference = referenceSequence.get(i);
    
            if (!physicalMemory.contains(reference)) {
                if (physicalMemory.size() >= physicalMemorySize) {
                    int pageToReplace = findPageToReplace(i);
                    physicalMemory.set(pageToReplace, reference);
                    pageFaults++; // Increment page faults when a page needs to be replaced
                } else {
                    physicalMemory.add(reference);
                    pageFaults++; // Increment page faults when a new page is added to the physical memory
                }
            }
        }
    
        System.out.println("\nOPT Page Replacement");
        System.out.println("Virtual Memory Size: " + virtualMemorySize);
        System.out.println("Physical Memory Size: " + physicalMemorySize);
        System.out.println("Reference Sequence Length: " + referenceSequence.size());
        System.out.println("Page Faults: " + pageFaults);
    }
    
    private int findPageToReplace(int currentIndex) {
        int pageToReplace = -1;
        int farthestIndex = currentIndex;

        for (int i = 0; i < physicalMemory.size(); i++) {
            int page = physicalMemory.get(i);
            int nextPageIndex = getNextAppearanceIndex(currentIndex, page);

            if (nextPageIndex == -1) {
                return i; // If a page will not be referenced again, replace it
            }

            if (nextPageIndex > farthestIndex) {
                farthestIndex = nextPageIndex;
                pageToReplace = i;
            }
        }

        return pageToReplace;
    }

    private int getNextAppearanceIndex(int currentIndex, int page) {
        for (int i = currentIndex + 1; i < referenceSequence.size(); i++) {
            if (referenceSequence.get(i) == page) {
                return i;
            }
        }

        return -1;
    }
}