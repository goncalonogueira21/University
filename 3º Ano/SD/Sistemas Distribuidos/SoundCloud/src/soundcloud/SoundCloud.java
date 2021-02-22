/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package soundcloud;

/**
 *
 * @author f6car
 */
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class SoundCloud implements Serializable {
    private Map<String, User> Utilizador;//Todos os Utilizadores registados
    private Map<String,Musica> Musicas;//Todas as musicas no SoundCloud
   
    
    private int nrSongsDownload;
    final int MaxUpload = 3;
    
    
    
    private Lock lock = new ReentrantLock();
    //variável condição usada para quando não há musicas
    private Condition naoMusicas = lock.newCondition();
    //variável condição usada para quando há downloads em excesso
    private Condition naoDownloads = lock.newCondition();
    
    
    
    //Construtor vazio
    public SoundCloud(){
        this.Utilizador = new HashMap<>();
        this.Musicas = new HashMap<>();
        this.nrSongsDownload=0;
        }
    
    //getters
    public Map<String,User> getUser(){
        return this.Utilizador;
    }
    
    public Map<String, Musica> getMusicas() {
        return this.Musicas;
    }
  
    //setters
    public void setUser(HashMap<String,User> p){
        this.Utilizador = p;
    }
    
   
    public void setMusicas(Map<String, Musica> m) {
        this.Musicas = m;
    }

    
    
    //metodo para registar um utilizador
    public boolean registaUtilizador(String nick, String pass){
        boolean res = false;
        
        lock.lock();
        try{
            if(!this.Utilizador.containsKey(nick)){
                User p = new User(nick,pass);
                this.Utilizador.put(nick, p);
                res = true;
            }
            
            return res;
            
        }finally{
            lock.unlock();
        }  
        
    }
   
   
    //Se o utilizador não estiver ativo, fica "online"
    public boolean AutenticaUser(String nick, String pass){
        boolean res = false;
        System.out.println(this.Utilizador);
        lock.lock();
        
        try{
            if(this.Utilizador.containsKey(nick)){
                if((!this.Utilizador.get(nick).isAtivo()) && this.Utilizador.get(nick).getPass().equals(pass)){
                    this.Utilizador.get(nick).setAtivo(true);
                    res = true;
                }
            }
            
             return res;
            
        }finally{
            lock.unlock();
        }
        
        
    }
        
    //metodo para fazer logout
    public void logoutUtilizador(String nick) {
            lock.lock();
            
            try {
                this.Utilizador.get(nick).setAtivo(false);
            } finally {
                lock.unlock();
            }
	}
    
    //metodo para dar upload de uma musica
    public String UploadMusica(String Nome, int ano, String artista, byte[] a,ArrayList<String> et) throws IOException{
        
        System.out.println(this.Utilizador);
        lock.lock();
        try{
        if(this.Musicas.containsKey(Nome)){
            return "Musica ja existe";
        }
         
        File outputFile = new File("Files/Servidor/"+Nome+".mp3");

        try ( FileOutputStream outputStream = new FileOutputStream(outputFile); ) {

        outputStream.write(a);  //write the bytes and your done. 

            } catch (Exception e) {
                  e.printStackTrace();
            }

        int size = this.Musicas.size()+1;
        Musica m = new Musica(size,Nome,ano,artista,et,0);
        this.Musicas.put(Nome,m);
        
        
        this.naoMusicas.signalAll();
        return "Upload bem sucedido";
    }catch(Exception e){
            System.err.println(e.toString());
            System.err.println(e.getMessage());
        return "Musica nao existe";
    }        
    
            finally{
            lock.unlock();
        }
    }
    
    //metodo para fazer download de uma musica
    public byte[] downloadMusica(int id) throws FileNotFoundException, IOException, InterruptedException{
        lock.lock();
        this.nrSongsDownload++;
        try{
            
            while (this.Musicas.isEmpty()){
                this.naoMusicas.await();
            }
            
            while(this.nrSongsDownload > this.MaxUpload){
                this.naoDownloads.await();
            }
            
        String nome = null;
        for (Map.Entry<String,Musica> musica : Musicas.entrySet()){
            if((musica.getValue().getId())==id){
                nome = musica.getKey();
                musica.getValue().aumentaDownload();
                break;
            }
        }
        if(nome==null) return null;
        
        File file = new File("Files/Servidor/"+nome+".mp3");
        byte[] bytesArray = new byte[(int) file.length()]; 
        FileInputStream fis = new FileInputStream(file);
        fis.read(bytesArray); //read file into bytes[]
        fis.close();
        System.out.println(bytesArray.length);
        return bytesArray;
        
        }catch(Exception e) {
            e.printStackTrace();
            System.err.println(e.getMessage());
            return null;
        }
        
        finally{
            this.nrSongsDownload--;
            this.naoDownloads.signalAll();
            lock.unlock();
        }
    }
    
    //metodo de procura de musicas por etiqueta
    public String searchMusicas(String etiqueta) throws InterruptedException{
        
        lock.lock();
        try{
         while (this.Musicas.isEmpty()) {
                this.naoMusicas.await();
            }
        StringBuilder sb = new StringBuilder();
        for (Map.Entry<String,Musica> m : Musicas.entrySet()){
            boolean existe = m.getValue().exiteEtiqueta(etiqueta);
            if (existe) {
                sb.append(m.toString());
            }         
        }
        
        return sb.toString();
        
        }finally{
            lock.unlock();
        }
    }
    
}