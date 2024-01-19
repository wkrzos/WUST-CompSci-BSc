package solution1;
public class ElfSphereBigAndSmall extends Elf {

    public ElfSphereBigAndSmall() {
        super("Kula");
    }

    @Override
    public void dodajBombke(Bauble bombka) {
        if (czyPasuje(bombka)) {
            liczbaBombek++;
            baubles.add(bombka);
            wyswietlKomunikat("Bombka dodana!");
            // Logika dla pełnego pudełka
            if (liczbaBombek == SIZE_OF_BOX && numberOfBoxes > 0) {
                numberOfBoxes--;
                wyswietlKomunikat("Pudelko z kulami jest pełne! Elf rzucił je za siebie i wziął nowe!");
            } else if (liczbaBombek == SIZE_OF_BOX && numberOfBoxes == 0) {
                isElfDone = true;
                wyswietlKomunikat("Elf nie ma już pudełek!");
            }
        } else {
            wyswietlKomunikat("Bombka nie pasuje do pudełka!");
        }
    }

    @Override
    public boolean czyPasuje(Bauble bombka) {
        return bombka instanceof BaubleSphereSmall || bombka instanceof BaubleSphereBig;
    }

    @Override
    public String toString(){
        return("ElfSphereBigAndSmall = { rodzajPudelka = " + rodzajPudelka + ", liczbaBombek = " + liczbaBombek + " }");
    }
}

// Analogicznie dla ElfSopelka i ElfGrzybka
