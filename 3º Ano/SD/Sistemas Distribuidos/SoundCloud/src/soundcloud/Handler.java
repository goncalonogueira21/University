/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package soundcloud;


import java.io.ObjectInputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Base64;

public class Handler implements Runnable {
    private final Socket s;
    private final SoundCloud sk;
    private ObjectInputStream sInput;
    private PrintWriter sOutput;
    
    //construtor por argumentos
    public Handler(Socket cliente, SoundCloud sk){
        this.s = cliente;
        this.sk = sk;
        this.sInput = null;
        this.sOutput = null;
    }

    @Override
    public void run() {
        try{
            do {
                this.sInput = new ObjectInputStream(s.getInputStream());
    		this.sOutput = new PrintWriter(s.getOutputStream());
    				
    		PacoteDados pacote = (PacoteDados) sInput.readObject();

    		if (pacote.getAccao().equals(Server.REGISTAR_Utilizador)) {
                    System.err.println("Recebeu Registar Utilizador");
                    String nick = pacote.getArgumentos().get(Server.NOME_Utilizador);
                    String pw = pacote.getArgumentos().get(Server.PW_Utilizador);
                    

                    System.out.println("USER: " + nick + " Password " + pw);
                    boolean existe = sk.registaUtilizador(nick, pw);

                    if(existe){
                        sOutput.println("Registado com Sucesso");
                    }else{
                        sOutput.println("Utilizador já existe");
                    }	
                    sOutput.flush();
    		}
                if (pacote.getAccao().equals(Server.ENTRAR_Utilizador)){
                        System.err.println("Pacote Entrar");
                        String nick = pacote.getArgumentos().get(Server.NOME_Utilizador);
                        String pw = pacote.getArgumentos().get(Server.PW_Utilizador);
                    
                        boolean on = false;
                        
                        if(sk.getUser().containsKey(nick)){
                           on = sk.getUser().get(nick).isAtivo();
                        }
                       System.out.println("Ativo " + on);
                        System.out.println("USER: " + nick + " " + pw);
                        boolean existe = sk.AutenticaUser(nick, pw);
    						
                        if(existe && !on){
    			    sOutput.println("Entrou");
                        }else{ 
                            sOutput.println("Nao Entrou");
                        }
                        sOutput.flush();
                    }
                
                if(pacote.getAccao().equals(Server.SAIR_Utilizador)){
                    System.err.println("Pacote Sair");

                    String user = pacote.getArgumentos().get(Server.NOME_Utilizador);
                    sk.logoutUtilizador(user);
                }
                
                    if(pacote.getAccao().equals(Server.Upload_Musica)){
                        System.err.println("Pacote Upload");
                        String nomeMusica = pacote.getArgumentos().get(Server.Nome_Musica);
                        int Ano = Integer.parseInt(pacote.getArgumentos().get(Server.Ano_Musica));
                        String artista = pacote.getArgumentos().get(Server.Interprete_Musica);
                        ArrayList<String> et = pacote.getEtiquetas();
                        byte[] a = pacote.getMusicaBytes();
                         
                        String existe = sk.UploadMusica(nomeMusica,Ano,artista,a,et);
    						
    			sOutput.println(existe);
                        
                        sOutput.flush();
                    }
                    if(pacote.getAccao().equals(Server.Download_Musica)){
                        System.out.println("Pacote Download");
                        int id = Integer.parseInt(pacote.getArgumentos().get(Server.Id_Musica));
                        System.out.println(id);
                        byte[] musicaB = sk.downloadMusica(id);
                        
                        if(musicaB == null)
                            sOutput.println("Erro de Download");
                        else {
                            String s = Base64.getEncoder().encodeToString(musicaB);
                            sOutput.println(s);
                        }
                        sOutput.flush();
                        }  
                    if(pacote.getAccao().equals(Server.Search_Musicas)){
                        System.out.println("Pacote Search");
                        String etiqueta = pacote.getArgumentos().get(Server.Etiqueta_Musica);
                        String resposta = sk.searchMusicas(etiqueta);
                        
                        if (resposta.equals("")) sOutput.println("Nao existe musicas com essa etiqueta");
                        
                        else{ sOutput.println(resposta);
                        }
                        sOutput.flush();
                          
                        
                    }
            }while(true);
        }catch (Exception e) {
        }        
    }    
}