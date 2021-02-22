import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.*;
import java.io.IOException;
import org.json.simple.parser.ParseException;
public class Firebase {


    Firebase(){}


    public void ReadFireBase() throws IOException{

        String command = " curl https://soundreckoning-55568.firebaseio.com/.json";

        Process process = Runtime.getRuntime().exec(command);
        // process.getInputStream();

        try(BufferedReader br = new BufferedReader(
                new InputStreamReader(process.getInputStream(), "utf-8"))) {
            StringBuilder response = new StringBuilder();
            String responseLine = null;
            while ((responseLine = br.readLine()) != null) {
                response.append(responseLine.trim());
            }
          //  System.out.println(response.toString());
        }
    }

    public  List<Float> ReadFireBase2() throws IOException, ParseException {

        URL url = new URL ("https://soundreckoning-55568.firebaseio.com/.json");
        HttpURLConnection con = (HttpURLConnection)url.openConnection();
        //os dados da fire base podem ser lidos emitindo uma solicitação HTTP GET
        con.setRequestMethod("GET");
        con.setRequestProperty("Content-Type", "application/json;");
        con.setRequestProperty("Accept", "application/json");
        con.connect();
        int responsecode = con.getResponseCode();
        if (responsecode != 200) {
            throw new RuntimeException("HttpResponseCode: " + responsecode);
        }
        else {

            String inline = "";
            Scanner scanner = new Scanner(url.openStream());

            //Write all the JSON data into a string using a scanner
            while (scanner.hasNext()) {
                inline += scanner.nextLine();
            }
            //retiramos apenas informação pertinente da string e convertemos em float
            List<Float> sList = new LinkedList<Float>();
            String sAux ="";
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < inline.length(); i++) {
                if( inline.charAt(i)=='d' && inline.charAt(i+1)=='"' && inline.charAt(i+2)==':' && inline.charAt(i+3)=='"' ){
                    i=i+4;
                    for (; i < inline.length(); i++){
                        if(inline.charAt(i) == '"') break;
                        sb.append(inline.charAt(i));
                        sAux = sb.toString();
                    }
                    sList.add(Float.parseFloat(sAux));
                    sAux="";
                    sb = new StringBuilder();

                }
                if(i+3> inline.length()) break;
            }
           // System.out.println(sList);
        return  sList;
        }
    }

    public void DeleteAllDataFireBase() throws IOException {
        URL url = new URL ("https://soundreckoning-55568.firebaseio.com/.json");
        HttpURLConnection con = (HttpURLConnection)url.openConnection();
        con.setRequestMethod("DELETE");
        con.setRequestProperty("Content-Type", "application/json;");
        con.setRequestProperty("Accept", "application/json");
        con.setDoOutput(true);

    }


    public void WriteFireBase( float soundVal) throws IOException {

        //create  url object
        URL url = new URL ("https://soundreckoning-55568.firebaseio.com/.json");
        //Open a Connection
        HttpURLConnection con = (HttpURLConnection)url.openConnection();
        //os dados da fire base podem ser escritos emitindo uma solicitação HTTP PUT
        //POST create a new class
        // para enviar uma solicitação POST , temos que definir a propriedade do método de solicitação para POST
        con.setRequestMethod("POST");
        //temos de definir o cabeçalho da solicitação “content-type” como “application / json” para enviar o conteúdo da solicitação em formato JSON.
        con.setRequestProperty("Content-Type", "application/json;");
        con.setRequestProperty("Accept", "application/json");
        //temos de por o setDoOutput a true para podermos escrever data no  output stream:
        con.setDoOutput(true);

        // converter informação para json
        JSONObject sendData = new JSONObject();
        sendData.put("sound",  String.valueOf(soundVal) );

        String jsonInputString = sendData.toJSONString();
        //send data to firebase
       // System.out.println("string do json=     "+ jsonInputString );
        try(OutputStream os = con.getOutputStream()) {
            byte[] input = jsonInputString.getBytes("utf-8");
            os.write(input, 0, input.length);
        }
        //ler os dados que escrevemos
        try(BufferedReader br = new BufferedReader(
                new InputStreamReader(con.getInputStream(), "utf-8"))) {
            StringBuilder response = new StringBuilder();
            String responseLine = null;
            while ((responseLine = br.readLine()) != null) {
                response.append(responseLine.trim());
            }
          //  System.out.println(response.toString());
        }



    }



}


