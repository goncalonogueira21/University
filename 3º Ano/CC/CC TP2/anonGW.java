import java.io.*;
import java.net.*;
import java.util.*;

public class anonGW {
private static final int porta = 80;
private static final int portaUDP = 6666;

private static Socket gatewaySocket;
private static BufferedReader in;
private static PrintWriter out = null;
private static InputStream in1 = null;
private static OutputStream out1 = null;


public static void main(String args[]) throws IOException, InterruptedException{

           List<String> anons = new ArrayList<>(); //estrutura que contem os reachable anongw 
           String target = args[0];
                
        
        
           for(int i=1;i<args.length;i++){
		anons.add(args[i]);
	   }
		
     	   AESencrp seguranca = new AESencrp();
        
        

           ServerSocket ws = new ServerSocket(porta);

           DatagramSocket ds = new DatagramSocket(portaUDP);
        
        
           new Thread(new UDPworker(ds, target)).start();
        
           System.out.println("esta a ouvir");
	
        
        
        while(true) {
            
            
            
           Socket cliente = ws.accept();
         
           int escolha =(int)(Math.random()*((anons.size()-0)));
        
           new Thread(new AnonGW_Worker(0,cliente,anons.get(escolha),seguranca)).start();
        

        }
    }
}