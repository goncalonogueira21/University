import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;


import java.util.Properties;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;



public class Alarms {



    final String username = "gpn.slb@gmail.com";
    final String password = "gr20202021";

    public void sendMail(String process, String value, int aux){
    Properties props = new Properties();
        props.put("mail.smtp.starttls.enable", "true");
        props.put("mail.smtp.auth", "true");
        props.put("mail.smtp.host", "smtp.gmail.com");
        props.put("mail.smtp.port", "587");

    Session session = Session.getInstance(props,
            new javax.mail.Authenticator() {
                protected PasswordAuthentication getPasswordAuthentication() {
                    return new PasswordAuthentication(username, password);
                }
            });

        try {

        Message message = new MimeMessage(session);
        message.setFrom(new InternetAddress("gpn@gmail.com"));
        message.setRecipients(Message.RecipientType.TO,
                InternetAddress.parse("g1.nogueira.slb@hotmail.com"));
        message.setSubject("Alarm");

            if(aux==1) {
                message.setText("Hey there, something might happened because the process " + process + " is currently at " + value + " of CPU usage. Go check it out fast!");
            }
            if(aux==2) {
                message.setText("Hey there, something might happened because the process " + process + " is currently at " + value + " of RAM usage. Go check it out fast!");
            }

        Transport.send(message);

        System.out.println("Done");

    } catch (MessagingException e) {
        throw new RuntimeException(e);
    }
}






    public final double CPU_Treshold=50.0;
    public final double RAM_Treshold=50.0;

    public void checkValues() throws IOException {
        PrintWriter writer = new PrintWriter(new FileWriter("AlarmsLogger",true));
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
        File myObj = new File("logger");
        Scanner myReader = new Scanner(myObj);
        while (myReader.hasNextLine()) {
            String data1 = myReader.nextLine();
            ArrayList<String> line = new ArrayList<>(Arrays.asList(data1.split("\\s*,\\s*")));
            if(Double.parseDouble( line.get(1))>CPU_Treshold) {
                Date date = new Date();
                sendMail(line.get(0),line.get(1),1);
                writer.println("At the time " + formatter.format(date) + " the process -> " + line.get(0) + "  surpassed the threshold for CPU Usage with " + line.get(1));
            }
            if(Double.parseDouble(line.get(2))>RAM_Treshold) {
                Date date = new Date();
                sendMail(line.get(0),line.get(2),2);
                writer.println("At the time " + formatter.format(date) + " the process -> " + line.get(0) + "  surpassed the threshold for RAM Usage with " + line.get(2));
            }
        }
        myReader.close();
        writer.close();
    }


}
