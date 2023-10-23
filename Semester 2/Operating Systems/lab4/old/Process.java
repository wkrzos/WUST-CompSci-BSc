package old;


import java.util.List;
import java.util.Set;

class Process {
    private int processId;
    private Set<Integer> pageSet;
    private List<Integer> referenceSequence;

    public Process(int processId, Set<Integer> pageSet, List<Integer> referenceSequence) {
        this.processId = processId;
        this.pageSet = pageSet;
        this.referenceSequence = referenceSequence;
    }

    public int getProcessId() {
        return processId;
    }

    public Set<Integer> getPageSet() {
        return pageSet;
    }

    public List<Integer> getReferenceSequence() {
        return referenceSequence;
    }
}