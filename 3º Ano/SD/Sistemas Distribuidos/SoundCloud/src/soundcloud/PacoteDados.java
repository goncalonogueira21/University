/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package soundcloud;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;


public class PacoteDados implements Serializable {


    private final String accao;
    private final HashMap<String,String> argumentos;
    private byte[] musicaBytes;
    private ArrayList<String> etiquetas;

    public PacoteDados(String accao, HashMap<String, String> argumentos, byte[] musicaBytes, ArrayList<String> et) {
        this.accao = accao;
        this.argumentos = argumentos;
        this.musicaBytes = musicaBytes;
        this.etiquetas=et;
    }
    public byte[] getMusicaBytes() {
        return musicaBytes;
    }
    
    public ArrayList<String> getEtiquetas(){
        return etiquetas;
    }
    
    
    
    public String getAccao(){
        return accao;
    }
    
    public HashMap<String,String> getArgumentos(){
        return argumentos;
    }
}