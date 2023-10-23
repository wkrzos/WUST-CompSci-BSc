package old;


import java.util.*;

class PageReplacementAlgorithm {
    private int frameCount;
    private List<Process> processes;
    private Map<Integer, Integer> pageToFrameMap;
    private Deque<Integer> pageQueue;

    public PageReplacementAlgorithm(int frameCount, List<Process> processes) {
        this.frameCount = frameCount;
        this.processes = processes;
        this.pageToFrameMap = new HashMap<>();
        this.pageQueue = new LinkedList<>();
    }

    public void runLRU() {
        int errors = 0;
        int time = 0;

        List<Page> pages = new ArrayList<>();
        for (int i = 0; i < frameCount; i++) {
            pages.add(new Page(i));
        }

        int[] frames = new int[frameCount];
        Arrays.fill(frames, -1);

        for (int i = 0; i < frameCount; i++) {
            frames[i] = -1;
        }

        for (Process process : processes) {
            Set<Integer> pageSet = process.getPageSet();
            List<Integer> referenceSequence = process.getReferenceSequence();

            for (int req : referenceSequence) {
                boolean done = false;
                for (int i = 0; i < frameCount; i++) {
                    if (frames[i] == req) {
                        pages.get(req).setLastUsed(time);
                        done = true;
                        break;
                    }
                }

                if (!done) {
                    for (int i = 0; i < frameCount; i++) {
                        if (frames[i] == -1) {
                            frames[i] = req;
                            pages.get(req).setArriveTime(time);
                            pages.get(req).setLastUsed(time);
                            errors++;
                            done = true;
                            break;
                        }
                    }
                }

                if (!done) {
                    int max = 0;
                    int toDelete = -1;
                    for (int i = 0; i < frameCount; i++) {
                        if (time - pages.get(frames[i]).getLastUsed() > max) {
                            toDelete = i;
                            max = time - pages.get(frames[i]).getLastUsed();
                        }
                    }
                    frames[toDelete] = req;
                    pages.get(req).setArriveTime(time);
                    pages.get(req).setLastUsed(time);
                    errors++;
                }
                time++;
            }
        }
    }

    public void printPageToFrameMap() {
        System.out.println("Page to Frame mapping:");
        for (Map.Entry<Integer, Integer> entry : pageToFrameMap.entrySet()) {
            int page = entry.getKey();
            int frame = entry.getValue();
            System.out.println("Page " + page + " -> Frame " + frame);
        }
    }
}
