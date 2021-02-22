
import java.util.*;
import java.net.*;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.lang.Thread;
import java.nio.ByteBuffer;
/**
 *
 * @author f6car
 */
public class UDPworker implements Runnable {

    
    
    private DatagramSocket server;
    private int anonTemp;
    
    private String targetServer;
    
    //private int type;
    
    //private Socket cliente;
    
    
    public UDPworker(DatagramSocket ds, String target){
      this.server=ds;
      this.targetServer=target;
    }
    
    public DatagramSocket getServer() {
        return server;
    }

    public String getTargetServer() {
        return targetServer;
    }
    
    
   

    @Override
    public synchronized void run() {
      
	
       
        this.anonTemp=6667;
        DatagramPacket dpACK = null;
        int status=0;
        int DISPONIVEL=0;
        while(true ){ 
            try {
                while(DISPONIVEL!=0){ 
                    try {
                        
                        wait();
                        
                    } catch (InterruptedException ex) {
                        Logger.getLogger(UDPworker.class.getName()).log(Level.SEVERE, null, ex);
                    }
            }
                    
                    
                DISPONIVEL=1;
                if(status==0){
                //RECEBER ACK
                byte[] receberACK = new byte[10];
                dpACK = new DatagramPacket(receberACK,receberACK.length);
                server.receive(dpACK);
                byte[] SYNresponse = new byte[10];
                SYNresponse=dpACK.getData();
                String msg = new String(SYNresponse,0,dpACK.getLength());
                System.out.println(msg);
                
                status=1;
                }
                
                if(status==1){
                //enviar SYN
                    String ack = "SYN";
                    byte[] bufferACK=ack.getBytes();
                    DatagramPacket dpSYN = new DatagramPacket(bufferACK,bufferACK.length,dpACK.getAddress(),dpACK.getPort());
                    server.send(dpSYN);
                    
                    
                    status=2;
                
                }

		System.out.println("");
                
                if(status==2){
                    //receber ackFINAL
                    byte[] ACKFINAL = new byte[10];
                    DatagramPacket dpRECEIVEACK = new DatagramPacket(ACKFINAL, ACKFINAL.length);
                    server.receive(dpRECEIVEACK);
                    byte[] SYNresponse = new byte[10];
                    SYNresponse=dpRECEIVEACK.getData();
                    String msg = new String(SYNresponse,0,dpRECEIVEACK.getLength());
                    System.out.println(msg);

                    new Thread(new UDPtemp(this.anonTemp, targetServer)).start();
	
                 
			//enviar nova porta

                    byte[] bufferPORTA = (String.valueOf(this.anonTemp)).getBytes();
                    DatagramPacket dpPORTA = new DatagramPacket(bufferPORTA,bufferPORTA.length,dpRECEIVEACK.getAddress(),dpRECEIVEACK.getPort());
                    server.send(dpPORTA);
                    
                    if(this.anonTemp==6700){
                        
                        this.anonTemp=6667;
                        
                    }
                    
                    else{
                        this.anonTemp++;
                    }
                    
                    
                    status=0;
                    DISPONIVEL=0;
                    notifyAll();
                    
                    
                    
                    
                }
                
                }
           catch (IOException ex) {                
               
           }                
                 
              
                finally{
            }

            }
                
        }
    }

    