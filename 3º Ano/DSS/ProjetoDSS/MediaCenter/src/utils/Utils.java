package utils;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.List;
import Bussiness.Leitor;

public class Utils {
    
    private static final String CONNECTION_STR = "jdbc:mysql://localhost/gmedia?user=root&password=ZDW1NRIM&serverTimezone=UTC&useSSL=false";
    
    public static ResultSet QuerySelecao(String query){
        try{
            Connection con = DriverManager.getConnection(CONNECTION_STR);
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            return rs;
        }
        catch(SQLException e){
            System.out.println(e);
            return null;
        }
    }
    
    public static int QueryAtualizacao(String query){
        try{
            Connection con = DriverManager.getConnection(CONNECTION_STR);
            Statement rs = con.createStatement();
            return rs.executeUpdate(query);
        }
        catch(SQLException e){
            System.out.println(e);
            return 0;
        }
    }
    
    public static void copyFileUsingStream(String src, String dst) throws IOException {
        File source = new File(src);
        File dest = new File(dst);
        FileChannel sourceChannel = null;
        FileChannel destChannel = null;
        try {
            sourceChannel = new FileInputStream(source).getChannel();
            destChannel = new FileOutputStream(dest).getChannel();
            destChannel.transferFrom(sourceChannel, 0, sourceChannel.size());
        }finally{
            sourceChannel.close();
            destChannel.close();
        }
    }
    
    public static void deleteFiles(String nome){
        Leitor leitor = new Leitor();
        String path = leitor.getPath(nome);
        File file = new File(path); 
        file.delete();
    }
    
    
}
