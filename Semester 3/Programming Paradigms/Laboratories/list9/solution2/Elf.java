package solution2;

import java.util.ArrayList;
import java.util.List;

public class Elf {
    private final int SIZE_OF_BOXES = 5;

    private BaubleType type;
    private int baubleCount;
    private List<Bauble> baubles;
    private boolean isBoxFull = false;

    public Elf(BaubleType type, int baubleCount) {
        this.type = type;
        this.baubleCount = baubleCount;
        this.baubles = new ArrayList<>();
    }

    public void addBaubles(Bauble bauble) {
        if(baubleCount == SIZE_OF_BOXES) {
            isBoxFull = true;
            System.out.println("Box is full!");
            return;
        }
        if(type == BaubleType.SPHERE_BIG_AND_SMALL) {
            if(bauble.getType() == BaubleType.SPHERE_BIG || bauble.getType() == BaubleType.SPHERE_SMALL) {
                baubleCount++;
                baubles.add(bauble);
                System.out.println("Bauble added: " + bauble.toString());
                return;
            }
            return;
        }
        if(bauble.getType() == type && !isBoxFull) {
            baubleCount++;
            baubles.add(bauble);
            System.out.println("Bauble added: " + bauble.toString());
        } else {
            System.out.println("Wrong bauble type: " + bauble);
        }
    }

    public String toStringBaublesArrayString() {
        StringBuilder stringBuilder = new StringBuilder();
        for(Bauble bauble : baubles) {
            stringBuilder.append(bauble.toString());
            stringBuilder.append("\n");
        }
        return stringBuilder.toString();
    }

    public boolean czyPasuje(Bauble bauble) {
        if(type == BaubleType.SPHERE_BIG_AND_SMALL) {
            return bauble.getType() == BaubleType.SPHERE_BIG || bauble.getType() == BaubleType.SPHERE_SMALL;
        } else {
            return bauble.getType() == type;
        }
    }

    @Override
    public String toString() {
        return "Elf{" +
                "type=" + type +
                ", baubleCount=" + baubleCount +
                ", baubles=" + baubles +
                ", isBoxFull=" + isBoxFull +
                '}';
    }

    public BaubleType getType() {
        return type;
    }

    public void setType(BaubleType type) {
        this.type = type;
    }

    public int getBaubleCount() {
        return baubleCount;
    }

    public void setBaubleCount(int baubleCount) {
        this.baubleCount = baubleCount;
    }

    public int getSIZE_OF_BOXES() {
        return SIZE_OF_BOXES;
    }

    public List<Bauble> getBaubles() {
        return baubles;
    }

    public void setBaubles(List<Bauble> baubles) {
        this.baubles = baubles;
    }

    public boolean isBoxFull() {
        return isBoxFull;
    }

    public void setBoxFull(boolean isBoxFull) {
        this.isBoxFull = isBoxFull;
    }
}
