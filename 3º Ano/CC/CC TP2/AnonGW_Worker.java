
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.Arrays;


public class AnonGW_Worker implements Runnable {

    // Variaveis de instancia
    private AESencrp seguranca;
    private DatagramSocket ds;
    private Socket cliente;
    private String AnonTarget;
    private int type;
    private int porta=6666;
    
    
    
    
   
    public int getType() {
        return type;
    }
    
    public Socket getCliente(){
        return this.cliente;
    }
    
    public String getAnonTarget(){
        return this.AnonTarget;
    }


       
    // Construtor

    public AnonGW_Worker(int type, Socket z, String anon, AESencrp a ) {
        //this.server = server;
        this.type = type;
        this.cliente=z;
        this.AnonTarget=anon;
	this.seguranca = a;
    
    }
    
    

    // Funcionalidades

    public void run(){
        try{
            
                 InetAddress ip = InetAddress.getByName(this.AnonTarget);
            
            //switch (this.getType()){
              //  case 0:{
                    //BufferedOutputStream os = new BufferedOutputStream(this.server.getOutputStream());
                    DataInputStream tcp_client_in = new DataInputStream(this.cliente.getInputStream());
                    
                    
                    if(type==0){
                  
                    int seq = 0;
                    ds = new DatagramSocket();
                   
                    
                    //enviar ack
                    String ack = "ACK";
                    byte[] bufferACK=ack.getBytes();
                    DatagramPacket dpACK = new DatagramPacket(bufferACK,bufferACK.length,ip,porta);
                    ds.send(dpACK);
                    
                    //receber Syn
                    byte[] bufferSYN = new byte[10];
                    DatagramPacket dpSYN = new DatagramPacket(bufferSYN, bufferSYN.length);
                    ds.receive(dpSYN);
                    byte[] bufferRESPONSE = new byte[10];
                    bufferRESPONSE=dpSYN.getData();
                    String msg = new String(bufferRESPONSE,0,dpSYN.getLength());
                    
                    if(msg.equals("SYN")){
                        
                    System.out.println(msg);
                    
                    //enviar ackfinal
                    
                    ds.send(dpACK);
                    type=1;
                    
                    }
                    
                    else{
                        type=-1;
                    }
                    
                    }
                    
                    //RECEBER NOVA PORTA
                    byte[] nrPorta = new byte[10];
                    byte[] portaResponse = new byte[10];
                    DatagramPacket dpPORTA = new DatagramPacket(nrPorta, nrPorta.length);
                    ds.receive(dpPORTA);
                    portaResponse = dpPORTA.getData();
                    String portaaux = new String(portaResponse,0,dpPORTA.getLength());
                    int portaFINAL= Integer.parseInt(portaaux);
                    System.out.println(portaFINAL);
                    if(type==1){
                     byte[] buffer = new byte[4096];
                     int nr_bytes = 0;
                     byte[] encriptado;
		//enviar pedido
                    while ((nr_bytes = tcp_client_in.read(buffer)) > 0){

                                

                         	encriptado=seguranca.encrypt(buffer);

				byte[] tam = ByteBuffer.allocate(4).putInt(encriptado.length).array();

				byte[] c = new byte[tam.length + encriptado.length];

				System.arraycopy(tam, 0, c, 0, tam.length);

				System.arraycopy(encriptado, 0, c, tam.length, encriptado.length);

				//System.out.println("ANTES DE DESENCRIPTAR= " + new String(encriptado,Charset.defaultCharset()));
				

				DatagramPacket dp = new DatagramPacket(c, c.length, ip, portaFINAL);
				
                        	ds.send(dp);

                        	break;
                    }
                  
                   
                   
                   
                   
            
		//receber conteudo do peer2
                    BufferedOutputStream os = new BufferedOutputStream(this.cliente.getOutputStream());
                   
		while(true){
                    int nr_bytes1 = 0;
                    //int seq = 0;
		    byte[] buffer2 = new byte[4116];
                    DatagramPacket dp = new DatagramPacket(buffer2,buffer2.length);
                    ds.receive(dp);
	            byte[] recebido = new byte[4116];
                    byte[] decriptado;
	
                    
				
                            recebido=dp.getData();
				
				
			    byte[] slice = Arrays.copyOfRange(recebido, 0, 4);

			    int tam = ByteBuffer.wrap(slice).getInt();
				
			    byte[] importante = Arrays.copyOfRange(recebido,4,tam+4);

			    //System.out.println("ANTES DE DESENCRIPTAR PEER 1= " + new String(importante,Charset.defaultCharset()));

                            decriptado=this.seguranca.decrypt(importante);

			    //System.out.println("DEPOIS DE DESENCRIPTAR123= " + new String(decriptado,Charset.defaultCharset()));

                            //System.out.println("DEPOIS DE DESENCRIPTAR PEER 1= " + new String(decriptado,Charset.defaultCharset()));
			    
			    os.write(decriptado);
                            os.flush();
			    //System.out.println("DEPOIS DE DESENCRIPTAR PEER 1= " + new String(decriptado,Charset.defaultCharset()));
			    
				
                 
                    

          		}
                    
                    }
            
            }
        
            
        catch (Exception e){
            
        }
        finally {
		
                type=-1;
        }
        
    }
}