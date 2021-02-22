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

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Server {
    private static final int porta = 55000;
    private static SoundCloud k = null;
    
    //Acções do Utilizador
    public static final String REGISTAR_Utilizador = "RegistarUtilizador";
    public static final String NOME_Utilizador = "NomeUtilizador";
    public static final String PW_Utilizador = "PasswordUtilizador";
    public static final String ENTRAR_Utilizador = "EntrarUtilizador";
    public static final String SAIR_Utilizador = "SairUtilizador";
    public static final String Upload_Musica = "UploadMusica";
    public static final String Nome_Musica = "NomeMusica";
    public static final String Ano_Musica = "AnoMusica";
    public static final String Interprete_Musica = "InterpreteMusica";
    public static final int Nr_Download = 0;
    public static final String Search_Musicas = "SearchMusicas";
    public static final String Download_Musica = "DownloadMusica";
    public static final String Id_Musica = "IdMusica";
    public static final String Etiqueta_Musica = "EtiquetaMusica";
    
   
    
    public static void main(String args[]) throws IOException{
        ServerSocket ws = new ServerSocket(porta);
        
        SoundCloud k = new SoundCloud();
        //ArrayList<String> e = new ArrayList<>();
        //ArrayList<String> et = new ArrayList<>();
        //byte[] a = null;
        //e.add("trap");
        //e.add("rap");
        //et.add("rock");
        //et.add("indie");
        //Exemplos de vários utilizadores 
        //k.registaUtilizador("gil","123");
        //k.registaUtilizador("carlos","321");
        //Exemplos de várias musicas
        //k.UploadMusica("BabushkaBoi",2019,"ASAP ROCKY",a,e);
        //k.UploadMusica("SoWhat",2018,"JEPARDS",a,et);
        //k.UploadMusica("ViewFromTheAfternoon",2007,"Artic Monkeys", a, et);
        //k.UploadMusica("NoSuprises",1997, "RadioHead", a, et);
        
        
        
        while(true) {
            Socket cliente = ws.accept();
            System.out.println("Entrou no servidor\nIP: " + cliente.getInetAddress());

            new Thread(new Handler(cliente,k)).start();
        }
    }    
}