public class SNMPPar {
    double CPU;
    double RAM;


    public SNMPPar(){
        this.CPU=0;
        this.RAM=0;
    }



    public double getCPU() {
        return CPU;
    }

    public void setCPU(double CPU) {
        this.CPU = CPU;
    }

    public double getRAM() {
        return RAM;
    }

    public void setRAM(double RAM) {
        this.RAM = RAM;
    }


    public String imprime() {
        return  " , " +CPU +
                ", " + RAM;
    }


}

