import java.util.ArrayList;
import java.sql.Timestamp;

public class ParIntList {
    private int number;
    private ArrayList<Timestamp> tempo;




    public ParIntList(int number, ArrayList<Timestamp> tempo) {
        this.number = number;
        this.tempo = tempo;
    }

    public int getNumber() {
        return number;
    }


    public ArrayList<Timestamp> getTempo() {
        return tempo;
    }


    public void addParIntList( Timestamp t){
        this.number=number+1;
        this.tempo.add(t);
    }

    @Override
    public String toString() {
        return "number of times pressed=" + number +
                ", times=" + tempo
                ;
    }
}
