package solution1;
import java.util.ArrayList;
import java.util.List;

public abstract class Elf {
    public final int SIZE_OF_BOX = 1;

    protected String rodzajPudelka;
    protected int liczbaBombek;
    protected List<Bauble> baubles;
    protected boolean isBoxFull;

    public Elf(String rodzajPudelka) {
        this.rodzajPudelka = rodzajPudelka;
        this.liczbaBombek = 0;
        this.baubles = new ArrayList<>();
    }

    public abstract void dodajBombke(Bauble bombka);

    public abstract boolean czyPasuje(Bauble bombka);

    public boolean czyPudelkoPelne() {return isBoxFull; };

    protected void wyswietlKomunikat(String komunikat) {
        System.out.println(komunikat);
    }

    public String toStringBaublesArrayString() {
        StringBuilder stringBuilder = new StringBuilder();
        for(Bauble bauble : baubles) {
            stringBuilder.append(bauble.toString());
            stringBuilder.append("\n");
        }
        return stringBuilder.toString();
    }

    @Override
    public String toString(){
        return("Elf = { rodzajPudelka = " + rodzajPudelka + ", liczbaBombek = " + liczbaBombek + " }");
    }

    public int getSIZE_OF_BOX() {
        return SIZE_OF_BOX;
    }

    public String getRodzajPudelka() {
        return rodzajPudelka;
    }

    public void setRodzajPudelka(String rodzajPudelka) {
        this.rodzajPudelka = rodzajPudelka;
    }

    public int getLiczbaBombek() {
        return liczbaBombek;
    }

    public void setLiczbaBombek(int liczbaBombek) {
        this.liczbaBombek = liczbaBombek;
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
