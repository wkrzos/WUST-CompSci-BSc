package old;


import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class PageAllocationExample {
    public static void main(String[] args) {
        // Create processes with their page sets and reference sequences
        Set<Integer> pageSet1 = new HashSet<>(Arrays.asList(1, 2, 3, 4, 5));
        List<Integer> referenceSequence1 = Arrays.asList(1, 2, 3, 4, 5, 1, 2, 3, 4, 5);
        Process process1 = new Process(1, pageSet1, referenceSequence1);

        Set<Integer> pageSet2 = new HashSet<>(Arrays.asList(6, 7, 8, 9, 10));
        List<Integer> referenceSequence2 = Arrays.asList(6, 7, 8, 9, 10, 6, 7, 8, 9, 10);
        Process process2 = new Process(2, pageSet2, referenceSequence2);

        List<Process> processes = Arrays.asList(process1, process2);

        // Set the total number of frames available
        int frameCount = 10;

        // Run the page replacement algorithm with LRU
        PageReplacementAlgorithm algorithm = new PageReplacementAlgorithm(frameCount, processes);
        algorithm.runLRU();
        algorithm.printPageToFrameMap();
    }
}