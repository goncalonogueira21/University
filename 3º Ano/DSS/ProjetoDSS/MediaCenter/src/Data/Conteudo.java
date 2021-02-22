package Data;

import java.util.Objects;

public class Conteudo {
    
    private String nome;
    private String genero;
    private String artista;
    private boolean video;
    private int contador;

    public Conteudo(String nome, String genero, String artista, boolean video) {
        this.nome = nome;
        this.artista = artista;
        this.genero = genero;
        this.video = video;
        this.contador = 1;
    }
    
    public boolean search(String search){
       if(nome.toLowerCase().contains(search))
           return true;
       if(artista.toLowerCase().contains(search))
           return true;
       if(genero.toLowerCase().contains(search))
           return true;
        return false;
    }


    public String getNome() {
        return nome;
    }

    public String getGenero() {
        return genero;
    }
    
    public String getArtista() {
        return artista;
    }

    public boolean isVideo() {
        return video;
    }

    public int getContador() {
        return contador;
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
        final Conteudo other = (Conteudo) obj;
        if (!Objects.equals(this.nome, other.nome)) {
            return false;
        }
        if (!Objects.equals(this.video, other.video)) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Conteudo{" + " nome=" + nome + ", genero=" + genero + ", artista=" + artista + ", video=" + video + ", contador=" + contador + '}';
    }
}
