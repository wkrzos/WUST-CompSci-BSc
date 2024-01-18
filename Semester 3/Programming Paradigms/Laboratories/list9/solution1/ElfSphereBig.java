package solution1;
public class ElfSphereBig extends Elf {

    public ElfSphereBig() {
        super("Kula");
    }

    @Override
    public void dodajBombke(Bauble bombka) {
        if (bombka instanceof BaubleSphereBig) {
            liczbaBombek++;
            baubles.add(bombka);
            wyswietlKomunikat("Bombka dodana!");
            // Logika dla pełnego pudełka
            if (liczbaBombek == SIZE_OF_BOX) {
                isBoxFull = true;
                wyswietlKomunikat("Pudelko z kulami jest pełne!");
            }
        } else {
            wyswietlKomunikat("Jasny gwint! Bombka nie pasuje do pudełka!");
        }
    }

    @Override
    public boolean czyPasuje(Bauble bombka) {
        return bombka instanceof BaubleSphereBig;
    }

    @Override
    public String toString(){
        return("ElfSphereBig = { rodzajPudelka = " + rodzajPudelka + ", liczbaBombek = " + liczbaBombek + " }");
    }
}

// Analogicznie dla ElfSopelka i ElfGrzybka
