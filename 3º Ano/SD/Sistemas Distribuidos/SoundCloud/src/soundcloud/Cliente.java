/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package soundcloud;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

import java.util.HashMap;
import java.util.Scanner;
import java.net.*;
import java.util.ArrayList;
import java.util.Base64;

public class Cliente {
    private final static int porta = 55000;
    private final static String ip = "localhost";
    private static Socket clienteSocket;
    
    public static Scanner in = new Scanner(System.in);
    public static ObjectOutputStream o = null;
    public static ObjectInputStream i = null;
    public static HashMap<String, String> hash;
    public static String nick = null;
    public static PacoteDados p;
    public static OutputStream os = null;
    public static InputStream is = null;
    
    
    public static void main(String args[]) throws Exception{
        clienteSocket = new Socket(ip,porta);
         
        menuTipoUtilizador();
    }
    
    public static String menuInicial(){
        System.out.println("###################### SoundCloud ########################");
        System.out.println("#                                                        #");
        System.out.println("#   1 - Utilizador Artista                               #");
        System.out.println("#   2 - Sair da aplicação                                #");
	System.out.println("#                                                        #");
	System.out.println("#   Escolha uma opção:                                   #");
	System.out.println("##########################################################");
        String opt = in.next();

        if ( !(opt.equals("1") || opt.equals("2")))
             opt = menuInicial();
        return opt;
    }
    
    public static void menuTipoUtilizador() throws IOException, ClassNotFoundException{
        String opt;
        opt = menuInicial();
        
        do{
            if(opt.equals("1")){
                menuRegUtilizador();
            }else if(opt.equals("2")){
                        System.exit(0);
                    }
                }    
        while(true);
    }
    
    public static String menuUser(){
        String opt;
        
        System.out.println("################### Utilizador Menu ######################");
        System.out.println("#                                                        #");
        System.out.println("#   1 - Entrar                                           #");
        System.out.println("#   2 - Registar                                         #");
        System.out.println("#                                                        #");
        System.out.println("#   Escolha uma opção:                                   #");
        System.out.println("##########################################################");
        opt = in.next();
        
        if ( !(opt.equals("1") || opt.equals("2"))){
            opt = menuUser();
        }
        
        return opt;
    }  
    
    public static void menuRegUtilizador() throws IOException, ClassNotFoundException{
        String opt;
        
        opt = menuUser();
        
        if(opt.equals("1")){
            System.out.println("######################## Entrar ##########################");
            in.nextLine();
            System.out.println("#   Introduza um username                                #");
            String user = in.nextLine();
            System.out.println("#                                                        #");
            System.out.println("#   Introduza a password                                 #");
            String pw = in.nextLine();
            System.out.println("#                                                        #");
            System.out.println("##########################################################");
                 
            hash = new HashMap<>();
            hash.put(Server.NOME_Utilizador, user);
            hash.put(Server.PW_Utilizador, pw);
            byte[] a = null;
            ArrayList<String> b = null;
            p = new PacoteDados(Server.ENTRAR_Utilizador,hash,a,b);
                    
            o = new ObjectOutputStream(clienteSocket.getOutputStream());
            o.writeObject(p);
            o.flush();
                    
            BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
            String result = sktInput.readLine();
            System.out.println(result);
            if(result.equals("Entrou")){
                nick = user;
                menuPrincipal();
            }
            else{
                System.out.println("################   Autenticação falhada   ################\n");
                //System.exit(0);
            }
        }else{
            
            if(opt.equals("2")){
                System.out.println("####################### Registar #########################");
                System.out.println("#                                                        #");
                in.nextLine();
                System.out.println("#   Defina um username                                   #");
                String user = in.nextLine();
                System.out.println("#   Defina uma password                                  #");
                String pw = in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("##########################################################");

                hash = new HashMap<>();
                hash.put(Server.NOME_Utilizador, user);
                hash.put(Server.PW_Utilizador, pw);
                byte[] a = null;
                ArrayList<String> b = null;
                p = new PacoteDados(Server.REGISTAR_Utilizador,hash,a,b);

                o = new ObjectOutputStream(clienteSocket.getOutputStream());
                o.writeObject(p);
                o.flush();
                
                

                BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
                System.out.println("\n"+sktInput.readLine()+"\n");
        }
    }
}
    
    public static void menuPrincipal() throws IOException, ClassNotFoundException {
        System.out.println("################### Menu Principal #######################");
        System.out.println("#                                                        #");
        System.out.println("#   "+nick+"                                             #");
        System.out.println("#                                                        #");
        System.out.println("#   1 - Download Musica                                  #");
        System.out.println("#   2 - Upload Musica                                    #");
        System.out.println("#   3 - Search Musicas                                   #");
        System.out.println("#   4 - Logout                                           #");
        System.out.println("#                                                        #");
        System.out.println("#   Escolha uma opção                                    #");
        System.out.println("##########################################################");
        String opt = in.next();
           
        do {
            if(opt.equals("2")){
               menuUploadMusica();
            }
            if(opt.equals("1")){
               menuDownloadMusica(); 
            }    
            if(opt.equals("3")) {
               menuMusicas();
            }
            if(opt.equals("4")){
                logoutUtili();
            }
            else{  
               if (!(opt.equals("1") || opt.equals("2") || opt.equals("3"))) 
                   System.out.println("Opcão inválida!");
               menuPrincipal();
            }
        } while(!(opt.equals("1") || opt.equals("2") || opt.equals("3")));
    }
    
    public static void menuUploadMusica() throws IOException, ClassNotFoundException{
        System.out.println("################### Upload musica ########################");
        System.out.println("#                                                        #");
        System.out.println("#   "   + nick  );
        System.out.println("#                                                        #");
        in.nextLine();
        System.out.println("#   Indique nome Musica                                  #");
        String NomeMusica = in.nextLine();
        System.out.println("#   Indique Interprete Musica                                #");
        String Interprete = in.nextLine();
        boolean nr = true;
        String Ano = "";
        while(nr) {
        System.out.println("#   Indique Ano da Musica                                #");
          Ano = in.nextLine();
            try {
                int a = Integer.parseInt(Ano);
                nr = false;
            } catch (Exception e) {
                    System.out.println("Not a number");
            }
        
        };
        System.out.println("#   Indique  as etiquetas. Pressione 'q' quando acabar   #");
       
        ArrayList<String> et = new ArrayList<>();
        int i=1;
        String e = "";
       while(!e.equals("q")) {
        System.out.println("#########    Etiqueta "+i+"       ##################");
                     e = in.nextLine();
                    if (e.equals("q") == false ) et.add(e);
                    i++;    
        
    }
        System.out.println("##########################################################");

        hash = new HashMap<>();
        hash.put(Server.Nome_Musica, NomeMusica);
        hash.put(Server.Interprete_Musica, Interprete);
        hash.put(Server.Ano_Musica,Ano);
        //passar para bytes a musica
        try {
                File file = new File("Files/musicasUpload/"+NomeMusica+".mp3");
            byte[] bytesArray = new byte[(int) file.length()]; 
            FileInputStream fis = new FileInputStream(file);
            fis.read(bytesArray); //read file into bytes[]
            fis.close();

            p = new PacoteDados(Server.Upload_Musica,hash,bytesArray,et);

            o = new ObjectOutputStream(clienteSocket.getOutputStream());
            o.writeObject(p);
            o.flush();

            BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
            System.out.println("\n"+sktInput.readLine()+"\n");
        } catch (Exception k) {
            System.err.println("Musica nao existe");
        }
        System.out.println ("Prima Enter para continuar");
        in.nextLine();
   
    }
    
    public static void menuDownloadMusica() throws IOException, ClassNotFoundException{
        System.out.println("############### Menu Download  ###########################");
        System.out.println("#                                                        #");
        System.out.println("#   "   + nick  );
        System.out.println("#                                                        #");
        in.nextLine();
        System.out.println("#   Indique o id da musica                           #");
        String id = in.nextLine();
        System.out.println("#                                                        #");
        System.out.println("##########################################################");
        
        hash.put(Server.Id_Musica, id);
        ArrayList<String> al = null;
        byte[] a = null;
        p = new PacoteDados(Server.Download_Musica,hash,a,al);

        o = new ObjectOutputStream(clienteSocket.getOutputStream());
        o.writeObject(p);
        o.flush();
        
        BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
        String s = sktInput.readLine();
        if(s.equals("Erro de Download")) 
            System.out.println("id nao existe");
        else{
        File outputFile = new File("Files/Cliente/"+id+".mp3");
            
        try ( FileOutputStream outputStream = new FileOutputStream(outputFile); ) {
         a =  Base64.getDecoder().decode(s);
        outputStream.write(a);  
        
            } catch (Exception e) {
                  e.printStackTrace();
            }
        }
           System.out.println ("Prima Enter para continuar");
                    in.nextLine();
        menuPrincipal();
            }    			
        
    
    
    public static void menuMusicas()throws IOException, ClassNotFoundException{
        System.out.println("###############    Menu Search    ########################");
        System.out.println("#                                                        #");
        System.out.println("#   "   + nick  );
        System.out.println("#                                                        #");
        System.out.println("#   1 - Indique a etiqueta.                              #");
        System.out.println("#   2 - Regressar ao menu anterior                       #");
        System.out.println("##########################################################");
        String opt = "";
        
        do {    	
            opt = in.nextLine();
            if(opt.equals("1")){
                System.out.println ("Etiqueta");
                String etiqueta = in.nextLine();
                byte[] a = null;
                hash = new HashMap<>();
                hash.put(Server.Etiqueta_Musica,etiqueta);
                p = new PacoteDados(Server.Search_Musicas,hash,a,null);

                o = new ObjectOutputStream(clienteSocket.getOutputStream());
                o.writeObject(p);
                o.flush();
                
                
                    BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
                    //System.out.println("\n"+sktInput.readLine()+"\n");
                    String inp = sktInput.readLine();
                    String[] arrOfStr = inp.split("(?<=})");
                    for (String u: arrOfStr)
                    System.out.println(u+"\n");
                
                
                System.out.println ("Prima Enter para continuar");
                    in.nextLine();
                menuPrincipal();
            } 
        } while(!(opt.equals("1")));
    }
    
    
    private static void logoutUtili() throws IOException, ClassNotFoundException {
    	hash = new HashMap<>();
        hash.put(Server.NOME_Utilizador, nick);
        byte[]a = null;
        ArrayList<String> al = null;
        p = new PacoteDados(Server.SAIR_Utilizador,hash,a,al);
        
        o = new ObjectOutputStream(clienteSocket.getOutputStream());
        o.writeObject(p);
        o.flush();
        
        nick = null;
        System.exit(0);
    }
    
}
