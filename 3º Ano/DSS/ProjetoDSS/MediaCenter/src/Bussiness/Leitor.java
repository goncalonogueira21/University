package Bussiness;

import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.File;
import static java.io.File.separator;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import Data.Conteudo;

public class Leitor {
    
    public void play(List<Conteudo> conteudos){
        try {
            
            String contentPlaylist = "";
            for(Conteudo c : conteudos){
                contentPlaylist =contentPlaylist+(getPath(c.getNome())+"\n");
            }

            File file = new File(GestaoConteudo.PATH+"playlist.vlc");
            file.delete();
            BufferedWriter writer = new BufferedWriter(new FileWriter(file));
            writer.write(contentPlaylist);
            writer.close();        
            
            ProcessBuilder pb = new ProcessBuilder("C:\\Program Files\\VideoLAN\\VLC\\vlc.exe", GestaoConteudo.PATH+"playlist.vlc");
            Process start = pb.start();
     
        } catch (IOException ex) {
            Logger.getLogger(Leitor.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public String getPath(String nome){
        List<String> result;
       	try (Stream<Path> walk = Files.walk(Paths.get(GestaoConteudo.PATH))) {
		 result = walk.filter(Files::isRegularFile)
				.map(x -> x.toString()).collect(Collectors.toList());
	} catch (IOException e) {
		return "";
	}
        
      for(String s : result){
          String[] splits=s.replaceAll(Pattern.quote(separator), "\\\\").split("\\\\");
          String name = splits[splits.length-1];
          String namewithoutExtension = name.substring(0,name.length()-4);
          if(namewithoutExtension.toLowerCase().equals(nome.toLowerCase()))
              return s;
      }
      return "";
    }
}
