import java.io.*;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.Arrays;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;




/**
 *
 * @author f6car
 */
public class UDPtemp implements Runnable{

   
    
    private AESencrp seguranca;
    private int PortaAtual;
    private String target;
    private byte[] bufferreceive;
    private byte[] buffersend;
   
    
    //private int type;
    
    //private Socket cliente;
    
    
     public UDPtemp(int porta, String Target){
      this.PortaAtual=porta;
      this.target=Target;
      
    }
    
   
 public int getPortaAtual() {
        return PortaAtual;
    }

    public String getTarget() {
        return target;
    }
   
    
   

    public void run() {
        
        seguranca = new AESencrp();
        this.bufferreceive = new byte[4116];
        this.buffersend = new byte[4096];
        int status=0;
        DatagramSocket server = null;
        try {
            server = new DatagramSocket(this.PortaAtual);
	
        } catch (SocketException ex) {
            Logger.getLogger(UDPtemp.class.getName()).log(Level.SEVERE, null, ex);
        }
         
            try {
		//receber pedido
		
                DatagramPacket dp = new DatagramPacket(this.bufferreceive,this.bufferreceive.length);
               
		server.receive(dp);

                Socket gatewaySocket = new Socket(this.getTarget(),80);

                while(true){
                    
                    BufferedOutputStream os = new BufferedOutputStream(gatewaySocket.getOutputStream());
                   
                    int nr_bytes;
		    byte[] recebido = new byte[4116];
                    byte[] decriptado;
			
                    while ((nr_bytes = dp.getData().length) > 0){
			
			recebido=dp.getData();

			//System.out.println("ANTES DE DESENCRIPTAR= " + new String(recebido,Charset.defaultCharset()));

			byte[] slice = Arrays.copyOfRange(recebido, 0, 4);

			int tam = ByteBuffer.wrap(slice).getInt();

			byte[] importante = Arrays.copyOfRange(recebido,4,tam+4);

                        decriptado=this.seguranca.decrypt(importante);

			//System.out.println("DEPOIS DE DESENCRIPTAR= " + new String(decriptado,Charset.defaultCharset()));
			

                         os.write(decriptado);
                         os.flush();

                         break;  
                        
                    }
                    break;
                }
                while(true){
		//enviar dados
                    DataInputStream tcp_client_in = new DataInputStream(gatewaySocket.getInputStream());
                   
                    int nr_bytes=0;
                    int seq=0;
		    byte[] encriptado2;
                    while ((nr_bytes = tcp_client_in.read(this.buffersend)) > 0){
				byte[] aux = new byte[nr_bytes];

				System.arraycopy(this.buffersend, 0, aux, 0, nr_bytes);

                                //System.out.println("O que recebi = " + new String(this.buffersend,Charset.defaultCharset()));
		
				encriptado2=seguranca.encrypt(aux);

				byte[] tam2 = ByteBuffer.allocate(4).putInt(encriptado2.length).array();

				byte[] c = new byte[tam2.length + encriptado2.length];

				System.arraycopy(tam2, 0, c, 0, tam2.length);

				System.arraycopy(encriptado2, 0, c, tam2.length, encriptado2.length);

				//System.out.println("DEPOIS DE ENCRIPTAR= " + new String(encriptado2,Charset.defaultCharset()));
				
				
                        	DatagramPacket dp2 = new DatagramPacket(c, c.length, dp.getAddress(), dp.getPort());

                        	server.send(dp2);
				System.out.println("Pacote enviado");
					
                        
                       
                }
      			 break;
                }
                    
                    
               
                } catch (IOException ex) {
           
        } catch (Exception ex) {
           
        }finally{
            }
            }
                
        }
