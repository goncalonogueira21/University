package Bussiness;

import java.io.IOException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import Data.Administrador;
import Data.Conteudo;


public class MediaCenterFacade {
    
    private final GestaoUser gestUsers = new GestaoUser();
    private final GestaoConteudo gestConteudo = new GestaoConteudo();
    private final Leitor leitor = new Leitor();
    private User user;
    
    public boolean login(String login, String password){
        if(!gestUsers.existeUser(login)) return false;
        user = gestUsers.getUser(login);
        return (user.getPassword().equals(password));
    }
    
    public void logout(){
        user = null;
    }

    public boolean cria(String username, String email, boolean admin){
        return gestUsers.cria(username, email, admin);
    }
    
    public boolean remove(String login){
        return gestUsers.removeMembro(login);
    }
    
    public void changePassword(String newPass){
        gestUsers.changePassword(user.getUsername(), newPass);
    }
    
     public void changeMail(String newMail){
        gestUsers.changeMail(user.getUsername(), newMail);
        user.setEmail(newMail);
    }
     
     public boolean changeName(String newName){
         boolean res = gestUsers.changeName(user.getUsername(), newName);
         user.setUsername(newName);
         return res;
    }
    
    public User getUser(){
        return user;
    }
    
    public Conteudo getConteudo(String nome){
        return gestConteudo.get(nome);
    }
    
    public boolean userIsAdmin(){
        return user instanceof Administrador;
    }
    
    public int upload(String path, String name, String genero, String artista){
        return gestConteudo.upload(path, name, genero, artista);
    }
    
    public void play(List<Conteudo> conteudos){
        leitor.play(conteudos);
    }

    public boolean modifyContent(String nomeConteudo, String nome, String genero, String artista) {
        return gestConteudo.modifyContent(nomeConteudo, nome, genero, artista);
    }

    public void removeFromCollection(String contentName) {
        gestConteudo.delete(contentName);
    }
    
     public List<Conteudo> getConteudo(){
        return gestConteudo.getConteudo();
    }
    
     public List<Conteudo> getConteudoUser(){
         return gestConteudo.getConteudoUser(user.getID());
     }
     
    public List<Conteudo> getOrderedConteudo(int searchMode, String search, List<Conteudo> conteudo){
         return gestConteudo.orderConteudo(searchMode, search, conteudo);
    }

    public boolean downloadFile(String pathMusic, String pathFile) {
        try {
            utils.Utils.copyFileUsingStream(pathMusic, pathFile);
            return true;
        } catch (IOException ex) {
            Logger.getLogger(MediaCenterFacade.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }

    public void addToFromCollection(String toString) {
        gestConteudo.addToCollection(toString);
    }

    public String getPersonalGenero(String conteudoNome) {
        return gestConteudo.getPersonalGenero(user.getID(), conteudoNome);
    }
    
    public void setPersonalGenero(String conteudoNome, String genero){
        gestConteudo.setPersonalGenero(user.getID(),conteudoNome, genero);
    }

    public void removePersonalGenero(String nome) {
        gestConteudo.removePersonalGenero(user.getID(), nome);
    }
}
    
  
    
     
    
    
    


