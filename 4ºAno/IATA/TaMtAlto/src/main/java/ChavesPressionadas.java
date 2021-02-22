

import java.sql.Timestamp;
import java.util.*;


public class ChavesPressionadas {

    private HashMap<String, ParIntList> pressionadas;

    public ChavesPressionadas() {
        this.pressionadas = new HashMap<>();
    }


    public ChavesPressionadas(ChavesPressionadas gcs) {
        this.pressionadas = gcs.getPressionadas();
    }

    //get


    public HashMap<String, ParIntList> getPressionadas() {
        return pressionadas;
    }

    public void setPressionadas(HashMap<String, ParIntList> pressionadas) {
        this.pressionadas = pressionadas;
    }

    public boolean equals(Object object) {
        if (this == object) return true;
        if (object == null || getClass() != object.getClass()) return false;
        ChavesPressionadas aux = (ChavesPressionadas) object;
        return aux.getPressionadas().equals(this.getPressionadas());
    }

    public ChavesPressionadas clone() {
        return new ChavesPressionadas(this);
    }

    public void toString1() {
        String k;
        for (Map.Entry mapElement : pressionadas.entrySet()) {
            k = (String) mapElement.getKey();
            ParIntList a = (ParIntList) mapElement.getValue();
            System.out.print("key  = '" + k + "' " + a.toString() + "\n");

        }
        System.out.print("\n");
    }

    public void addKeyPressed(String k, Timestamp t) {
        ParIntList a;
        if (pressionadas.containsKey(k)) {

            a = pressionadas.get(k);
            a.addParIntList(t);
        } else {
            ArrayList<Timestamp> b = new ArrayList<Timestamp>();
            b.add(t);
            a = new ParIntList(1, b);
        }
        pressionadas.put(k, a);
    }

    public String KeyPressedMore() {
        int count = -1;
        String k = null;
        for (Map.Entry mapElement : pressionadas.entrySet()) {
            ParIntList a = ((ParIntList) mapElement.getValue());
            int c = a.getNumber();
            if (c > count) {
                count = c;
                k = (String) mapElement.getKey();
            }
        }
        return k;
    }


    public int KeysPerMinute(Timestamp t) {
        ArrayList<Timestamp> aux;
        ArrayList<Timestamp> both = new ArrayList<>(10000);

        for (Map.Entry mapElement : pressionadas.entrySet()) {
            ParIntList a = ((ParIntList) mapElement.getValue());
            aux = a.getTempo();
            both.addAll(aux);
        }
        long l1=t.getTime();
        long l2=both.get(0).getTime();
        long l3=l1-l2;
        int minutes = (int) ((l3 / (1000*60)) % 60);
        int seconds = (int) (l3 / 1000) % 60 ;
        float z = (float) (minutes + (Math.abs(seconds) / Math.pow(10, Math.floor(Math.log10(Math.abs(seconds)) + 1))));
        if(z!=0) {
            return (int) (both.size() / z);
        }else{
            return 0;
        }
    }
}
