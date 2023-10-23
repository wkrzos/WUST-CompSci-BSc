package com.so;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

public class FIFO {

    private int physicalMemorySize;
    private int virtualMemorySize;
    private List<Integer> referenceSequence;
    List<Integer> physicalMemory = new ArrayList<>();

    public FIFO(int physicalMemorySize, int virtualMemorySize, List<Integer> referenceSequence) {
        this.physicalMemorySize = physicalMemorySize;
        this.virtualMemorySize = virtualMemorySize;
        this.referenceSequence = referenceSequence;
    }

    public void runFIFO() {

        Set<Integer> physicalMemory = new HashSet<>();
        Queue<Integer> pageQueue = new LinkedList<>();
        int pageFaults = 0;
    
        for (int reference : referenceSequence) {
            if (!physicalMemory.contains(reference)) {
                if (physicalMemory.size() >= physicalMemorySize) {
                    int pageToReplace = pageQueue.poll();
                    physicalMemory.remove(pageToReplace);
                }
    
                pageQueue.offer(reference);
                physicalMemory.add(reference);
                pageFaults++; // Increment page faults when a page is not found
            }
        }
    
        System.out.println("\nFIFO Page Replacement");
        System.out.println("Virtual Memory Size: " + virtualMemorySize);
        System.out.println("Physical Memory Size: " + physicalMemorySize);
        System.out.println("Reference Sequence Length: " + referenceSequence.size());
        System.out.println("Page Faults: " + pageFaults);
    }
}
