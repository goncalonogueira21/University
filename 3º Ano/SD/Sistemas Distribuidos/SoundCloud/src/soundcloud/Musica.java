/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package soundcloud;

import java.util.ArrayList;
import java.util.Objects;

/**
 *
 * @author f6car
 */
public class Musica {

    private int id;
    private String nome;
    private int ano;
    private String interprete;
    private ArrayList<String> etiquetas;
    private int descarregada;
    
    //construtores
    public Musica(int id, String nome, int ano, String interprete, ArrayList<String> etiquetas, int descarregada) {
        this.id = id;
        this.nome = nome;
        this.ano = ano;
        this.interprete = interprete;
        this.etiquetas = etiquetas;
        this.descarregada = descarregada;
    }
    
    //getters
    public int getId() {
        return id;
    }

    public String getNome() {
        return nome;
    }

    public int getAno() {
        return ano;
    }

    public String getInterprete() {
        return interprete;
    }

    public ArrayList<String> getEtiquetas() {
        return etiquetas;
    }

    public int getDescarregada() {
        return descarregada;
    }

   
        
    @Override
    public int hashCode() {
        int hash = 3;
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Musica other = (Musica) obj;
        if (this.id != other.id) {
            return false;
        }
        if (this.descarregada != other.descarregada) {
            return false;
        }
        if (!Objects.equals(this.nome, other.nome)) {
            return false;
        }
        if (!Objects.equals(this.ano, other.ano)) {
            return false;
        }
        if (!Objects.equals(this.interprete, other.interprete)) {
            return false;
        }
        if (!Objects.equals(this.etiquetas, other.etiquetas)) {
            return false;
        }
        return true;
    }
    
    public boolean exiteEtiqueta (String etiqueta) {
    
        return this.etiquetas.contains(etiqueta);
    }
    
    public void aumentaDownload (){
        descarregada++;
    }
    
        @Override
    public String toString() {
        return "Musica{" + "id=" + id + ", nome=" + nome + ", ano=" + ano + ", interprete=" + interprete + ", etiquetas=" + etiquetas + ", descarregada=" + descarregada + "}";
    }
    
  
}