import java.time.LocalDate;

public class Handler {
    float temp;
    int estacao;


    public Handler(){
        this.temp=0;
        this.estacao=0;
    }

    public void setTemp(float temp) {
        this.temp = temp;
    }

    public void setEstacao(int estacao) {
        this.estacao = estacao;
    }



    public String daEstacao(int estacao){
        String s=null;
        if(estacao==1) s = " outono/inverno";
        if(estacao==2) s = " verao/primavera";
        return s;
    }

    public String daDifTemp(float temp){
        float airCond=0;
        float conforto=0;
        String s=null;
        if(estacao==1){
            conforto=15;
            if(temp>=conforto){
                airCond=temp-conforto;
                s="aircondtioning-{" + airCond + "}";
            } else {
                airCond=conforto-temp;
                s="aircondtioning+{" + airCond + "}";
            }
        }
        if(estacao==2){
            conforto=25;
            if(temp>=conforto){
                airCond=temp-conforto;
                s="aircondtioning-{" + airCond + "}";
            } else {
                airCond=conforto-temp;
                s="aircondtioning+{" + airCond + "}";
            }
        }
        return s;
    }


    @Override
    public String toString() {
        return  "-> Estação= " + daEstacao(estacao) + " "  + daDifTemp(temp) ;
    }
}
