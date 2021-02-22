package Bussiness;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import static Bussiness.Main.FACADE;
import Data.ConteudoDAO;
import Data.Conteudo;
import utils.Utils;
import static utils.Utils.copyFileUsingStream;
   

public class GestaoConteudo {
    
    public static final String PATH = System.getProperty("user.dir")+"\\files\\";
    private static final String[] EXTENSIONS_VIDEO = {"mp4"};
    private static final String[] EXTENSIONS_MUSICA = {"mp3", "wav"};
    
    private final ConteudoDAO conteudos = new ConteudoDAO();
    
    public Conteudo get(String nome){
        return conteudos.get(nome);
    }
    
    // returns , 3 = erro no file, 2 ja esta na sua collecao, 1 ja esta na app, 0 = addicionado
    public int upload(String path, String name, String genero, String artista){
        String extension = path.substring(path.length()-3);
        int idUser = FACADE.getUser().getID();
        
        if(!extensionOk(extension))
            return 3;
        
        if(!conteudos.containsKey(name)){
            try {
                copyFileUsingStream(path, PATH+name+"."+extension);
            } catch (IOException ex) { return 3; }
            Conteudo conteudo = new Conteudo(name, genero, artista, extensionIsVideo(extension));
            conteudos.put(conteudo.getNome(), conteudo);
            conteudos.addicionarNaCollecao(idUser, name);
            return 0;
        }
        else if (!conteudos.estaNaCollecao(idUser, name)){
            conteudos.addicionarNaCollecao(idUser, name);
            conteudos.incrementaContador(name);
            return 1;
        }
        else return 2;
    }
    
    public boolean addToCollection(String nome){
        if (conteudos.estaNaCollecao(FACADE.getUser().getID(), nome))
            return false;
        
        conteudos.addicionarNaCollecao(FACADE.getUser().getID(), nome);
        conteudos.incrementaContador(nome);
        return true;
    }
    
    public void delete(String nome){
        conteudos.retirarDaCollecao(FACADE.getUser().getID(), nome);
        conteudos.decrementarContador(nome);
        if(conteudos.contador(nome)<=0){
            conteudos.remove(nome);
            Utils.deleteFiles(nome);
        }
    }
    
    public List<Conteudo> getConteudo(){
        Collection<Conteudo> conteudosCollection = conteudos.values();
        List<Conteudo> conteudosList = new ArrayList<>(conteudosCollection);
        return conteudosList;
    }
    
    public List<Conteudo> getConteudoUser(int idUser){
        List<Conteudo> conteudosList = getConteudo();
        List<Conteudo> conteudosCollection = new ArrayList<>();
        
        for(Conteudo c : conteudosList){
            if(conteudos.estaNaCollecao(idUser, c.getNome())){
                conteudosCollection.add(c);
            }
        }
        return conteudosCollection;
    }
    
    public List<Conteudo> orderConteudo(int searchMode, String search, List<Conteudo> conteudo){
         List<Conteudo> conteudosList2 = new ArrayList<>();
        
         conteudo.stream().filter((c) -> ("".equals(search) || c.search(search.toLowerCase()))).forEachOrdered((c) -> {
             conteudosList2.add(c);
        });
        
        switch (searchMode) {
            case 1:
                conteudosList2.sort((Conteudo o1, Conteudo o2) -> o1.getNome().toLowerCase().compareTo(o2.getNome().toLowerCase()));
                break;
            case 2:
                conteudosList2.sort((Conteudo o1, Conteudo o2) -> o2.getNome().toLowerCase().compareTo(o1.getNome().toLowerCase()));
                break;
            case 3:
                conteudosList2.sort((Conteudo o1, Conteudo o2) -> o1.getArtista().toLowerCase().compareTo(o2.getArtista().toLowerCase()));
                break;
            case 4:
                conteudosList2.sort((Conteudo o1, Conteudo o2) -> o2.getArtista().toLowerCase().compareTo(o1.getArtista().toLowerCase()));
                break;
            case 5:
                conteudosList2.sort((Conteudo o1, Conteudo o2) -> o1.getGenero().toLowerCase().compareTo(o2.getGenero().toLowerCase()));
                break;
            case 6:
                conteudosList2.sort((Conteudo o1, Conteudo o2) -> o2.getGenero().toLowerCase().compareTo(o1.getGenero().toLowerCase()));
                break;
            case 7:
                Collections.shuffle(conteudosList2);
                break;
            default:
                break;
        }
         return conteudosList2;    
    }
    
    private boolean extensionOk(String extension){
        return Arrays.stream(EXTENSIONS_MUSICA).anyMatch(extension::equals) || 
                Arrays.stream(EXTENSIONS_VIDEO).anyMatch(extension::equals);
    }
    
    private boolean extensionIsVideo(String extension){
        return Arrays.stream(EXTENSIONS_VIDEO).anyMatch(extension::equals);
    }

    boolean modifyContent(String nomeConteudo, String nome, String genero, String artista) {
        if(!nomeConteudo.equals(nome)&&conteudos.containsKey(nome)) return false;
        
        Leitor leitor = new Leitor();
        String antigoPath = leitor.getPath(nomeConteudo);
        String extension = antigoPath.substring(antigoPath.length()-3);
        
        conteudos.update(nomeConteudo, nome, genero, artista);
        
        if(!nomeConteudo.equals(nome))
        try {
            copyFileUsingStream(leitor.getPath(nomeConteudo), PATH+nome+"."+extension);
            new File(leitor.getPath(nomeConteudo)).delete();
        } catch (IOException ex) {
            Logger.getLogger(GestaoConteudo.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return true;
    }

    String getPersonalGenero(int id, String conteudoNome) {
        int idContent= conteudos.getId(conteudoNome);
        return conteudos.personalGenero(id, idContent);
    }
    
    void setPersonalGenero(int idUser, String conteudoNome, String genero){
        int idContent= conteudos.getId(conteudoNome);
        conteudos.setPersonalGenero(idUser, idContent, genero);
    }
    
    void removePersonalGenero(int idUser, String conteudoNome){
        int idContent= conteudos.getId(conteudoNome);
        conteudos.deletePersonalGenero(idUser, idContent);
    }
}

        
