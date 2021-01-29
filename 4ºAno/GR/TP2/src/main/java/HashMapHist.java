import java.util.*;

public class HashMapHist {
    private Map<String, ArrayList<SNMPPar>> hist;


    public HashMapHist() {
        this.hist = new HashMap<>();
    }


    public HashMapHist(HashMapHist gcs) {
        this.hist = gcs.getPressionadas();
    }

    //get


    public Map<String, ArrayList<SNMPPar>> getPressionadas() {
        return hist;
    }

    public void setHist(Map<String, ArrayList<SNMPPar>> hist) {
        this.hist = hist;
    }

    public boolean equals(Object object) {
        if (this == object) return true;
        if (object == null || getClass() != object.getClass()) return false;
        HashMapHist aux = (HashMapHist) object;
        return aux.getPressionadas().equals(this.getPressionadas());
    }

    public HashMapHist clone() {
        return new HashMapHist(this);
    }

    public void addSNMPPar(String k, double c, double r) {
        SNMPPar a = new SNMPPar();
        a.setCPU(c);
        a.setRAM(r);
        ArrayList<SNMPPar> b = new ArrayList<>();

        if (hist.containsKey(k)) {
            b=hist.get(k);
        }
        b.add(a);
        hist.put(k,b);
    }

    public ArrayList<String> processesList(){
        ArrayList<String> a = new ArrayList<>(hist.keySet());
        return a;
    }

    public ArrayList<SNMPPar> allValues(String p){
        ArrayList<SNMPPar> a = new ArrayList<>(hist.get(p));
        return a;
    }


}
