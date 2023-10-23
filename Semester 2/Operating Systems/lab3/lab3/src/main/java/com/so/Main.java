package com.so;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Main {

    private static int virtualMemorySize = 10000; // Przykładowy rozmiar pamięci wirtualnej
    private static int physicalMemorySize = 1000; // Przykładowy rozmiar pamięci fizycznej
    private static int numberOfPages = 1000; // Liczba stron

    public static void main (String[] args) {

        List<Integer> referenceSequence = generateReferenceSequence(virtualMemorySize, physicalMemorySize);

        FIFO fifo = new FIFO(physicalMemorySize, virtualMemorySize, referenceSequence);
        fifo.runFIFO();

        OPT opt = new OPT(physicalMemorySize, virtualMemorySize, referenceSequence);
        opt.runOPT();

        LRU lru = new LRU(physicalMemorySize, virtualMemorySize, referenceSequence);
        lru.runLRU();

        APPROX approx = new APPROX(physicalMemorySize, virtualMemorySize, referenceSequence);
        approx.runAPPROX();

        RAND rand = new RAND(physicalMemorySize, virtualMemorySize, referenceSequence);
        rand.runRAND();
    }

    static List<Integer> generateReferenceSequence(int virtualMemorySize, int physicalMemorySize) {
        List<Integer> sequence = new ArrayList<>();

        // Generowanie ciągu odwołań do stron
        Random random = new Random();
        int localityRange = virtualMemorySize / 10; // Zakładamy lokalność odwołań na 10% całej pamięci wirtualnej

        for (int i = 0; i < numberOfPages; i++) {
            int page = random.nextInt(virtualMemorySize);
            int localityOffset = random.nextInt(localityRange);
            int reference = (page + localityOffset) % virtualMemorySize;
            sequence.add(reference);
        }

        return sequence;
    }

    static void printSequence(List<Integer> sequence) {
        for (int reference : sequence) {
            System.out.print(reference + " ");
        }
        System.out.println();
    }
}
