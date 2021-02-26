package org.snmp4j.agent.tutorial;

import org.snmp4j.smi.Integer32;
import org.snmp4j.smi.OctetString;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;


public class Eventos {

    private String nome;
    private LocalDateTime data;
    private String validade;
    private String antes;
    private String durante;
    private String depois;


    public Eventos(String nome, LocalDateTime data, String validade, String antes, String durante, String depois) {
        this.nome = nome;
        this.data = data;
        this.validade = validade;
        this.antes = antes;
        this.durante = durante;
        this.depois = depois;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setData(LocalDateTime data) {
        this.data = data;
    }

    public void setValidade(String validade) {
        this.validade = validade;
    }

    public void setAntes(String antes) {
        this.antes = antes;
    }

    public void setDepois(String depois) {
        this.depois = depois;
    }

    public void setDurante(String durante) {
        this.durante = durante;
    }

    public String getNome() {
        return nome;
    }

    public LocalDateTime getData() {
        return data;
    }

    public String getValidade() {
        return validade;
    }

    public String getAntes() {
        return antes;
    }

    public String getDepois() {
        return depois;
    }

    public String getDurante() {
        return durante;
    }

    @Override
    public String toString() {
        return "Eventos{" +
                "nome='" + nome + '\'' +
                ", data=" + data +
                ", validade=" + validade +
                ", antes='" + antes + '\'' +
                ", durante='" + durante + '\'' +
                ", depois='" + depois + '\'' +
                '}';
    }






    public GrEventsMib.GrMIBEventsEntryRow updateEntryRow(GrEventsMib.GrMIBEventsEntryRow row, int counter){
        row.setGrMIBEventsIndex(new Integer32(counter));
        row.setGrMIBEventsNome(new OctetString(getNome()));
        row.setGrMIBEventsValidade(new OctetString(getValidade()));

        long years;
        long months;
        long days;
        long hours;
        long minutes;
        LocalDateTime tempDateTime = LocalDateTime.now();


            years = tempDateTime.until( data, ChronoUnit.YEARS );
            tempDateTime = tempDateTime.plusYears( years );

            months = tempDateTime.until( data, ChronoUnit.MONTHS );
            tempDateTime = tempDateTime.plusMonths( months );

          days = tempDateTime.until( data, ChronoUnit.DAYS );
            tempDateTime = tempDateTime.plusDays( days );


          hours = tempDateTime.until( data, ChronoUnit.HOURS );
            tempDateTime = tempDateTime.plusHours( hours );

             minutes = tempDateTime.until( data, ChronoUnit.MINUTES );
            tempDateTime = tempDateTime.plusMinutes( minutes );



        //System.out.println(years + " Anos, " + months + " Meses, " + days + " Dias, " + hours + " Horas, " + minutes + " Minutos" );

        //if (tempDateTime.isAfter(LocalDateTime.parse(validade))){
            //remover row
        //}
        if(years==0 && months==0 && days==0 && hours==0 && minutes==0 ){
            row.setGrMIBEventsAno(new Integer32(0));
            row.setGrMIBEventsMes(new Integer32(0));
            row.setGrMIBEventsDia(new Integer32(0));
            row.setGrMIBEventsHora(new Integer32(0));
            row.setGrMIBEventsMinutos(new Integer32(0));
            row.setGrMIBEventsMensagem(new OctetString(getDurante()));
        }
        else if(tempDateTime.isBefore(data)){
            row.setGrMIBEventsAno(new Integer32((int)years));
            row.setGrMIBEventsMes(new Integer32((int)months));
            row.setGrMIBEventsDia(new Integer32((int)days));
            row.setGrMIBEventsHora(new Integer32((int)hours));
            row.setGrMIBEventsMinutos(new Integer32((int)minutes));
            row.setGrMIBEventsMensagem(new OctetString(getAntes()));

        } else {
            row.setGrMIBEventsAno(new Integer32(Math.abs((int)years)));
            row.setGrMIBEventsMes(new Integer32(Math.abs((int)months)));
            row.setGrMIBEventsDia(new Integer32(Math.abs((int)days)));
            row.setGrMIBEventsHora(new Integer32(Math.abs((int)hours)));
            row.setGrMIBEventsMinutos(new Integer32(Math.abs((int)minutes)));
            row.setGrMIBEventsMensagem(new OctetString(getDepois()));
        }
        return row;
    }

}
