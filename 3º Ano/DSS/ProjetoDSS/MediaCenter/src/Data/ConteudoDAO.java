package Data;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

import java.util.ArrayList;
import java.util.List;
import java.sql.ResultSet;
import java.sql.SQLException;
import static Bussiness.Main.FACADE;

import static utils.Utils.QueryAtualizacao;
import static utils.Utils.QuerySelecao;

public class ConteudoDAO implements Map<String,Conteudo>{

    public void update(String nomeConteudo, String nome, String genero, String artista){
        QueryAtualizacao("update conteudos set nome='"+nome+"', genero='"+genero+"', artista='"+artista+"' WHERE nome='"+nomeConteudo+"';");
    }
    
    public void incrementaContador(String name){
        int contador = contador(name);
        contador++;
        updateContador(name, contador);
    }
    
    public void decrementarContador(String name){
        int contador = contador(name);
        contador--;
        updateContador(name, contador);
    }
    
    public boolean estaNaCollecao(int idUser, String name){
        int idConteudo = idConteudo(name);
        ResultSet rs = QuerySelecao("SELECT * FROM conteudos_link WHERE id_user='"+idUser+"' AND id_conteudo='"+idConteudo+"';");
        try {
            while ( rs.next() ) {
                return rs.getInt("id") >= 0;
            }
        } catch (SQLException ex) {}
        return false;
    }
    
    public void retirarDaCollecao(int idUser, String name){
        int idConteudo = idConteudo(name);
        QueryAtualizacao("delete from conteudos_link WHERE id_user='"+idUser+"' AND id_conteudo='"+idConteudo+"';");
    }
    
    public void addicionarNaCollecao(int idUser, String name){
        int idConteudo = idConteudo(name);
        QueryAtualizacao("insert into conteudos_link (id_user,id_conteudo) values('"+idUser+"','"+idConteudo+"');");
    }
    
    public int contador(String name){
        ResultSet rs = QuerySelecao("SELECT * FROM conteudos WHERE nome='"+name+"';");
        try {
            rs.next();
            return rs.getInt("contador");
        } catch (SQLException ex) {}
        return 0;
    }
    
    private void updateContador(String name, int newCoutnador){
         QueryAtualizacao("update conteudos set contador='"+newCoutnador+"' WHERE nome ='"+name+"';");
    }
    
    private int idConteudo(String name){
        ResultSet rs = QuerySelecao("SELECT * FROM conteudos WHERE nome='"+name+"';");
        try {
            rs.next();
            return rs.getInt("id");
        } catch (SQLException ex) {}
        return 0;
    }
    
    @Override
    public int size() {
        int i=0;
        ResultSet rs = QuerySelecao("SELECT * FROM conteudos;");
        try {
            while ( rs.next() ) i++;
        } catch (java.sql.SQLException ex) {}
        return i;
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public boolean containsKey(Object arg0) {
        return null != get(arg0);
    }

    @Override
    public boolean containsValue(Object arg0) {
         if(!(arg0 instanceof Conteudo)) return false;
        Conteudo admin = (Conteudo) arg0;
        Conteudo adminInDBB = get(admin.getNome());
        return admin.equals(adminInDBB);
    }

    @Override
    public Conteudo get(Object arg0) {
       if(!(arg0 instanceof String))
            return null;
        String name = (String)arg0;
        ResultSet rs = QuerySelecao("SELECT * FROM conteudos WHERE nome=\""+name+"\";");
        try {
            while ( rs.next() ) {
                int id = rs.getInt("ID");
                String nome =  rs.getString("nome");
                String genero =  rs.getString("genero");
                String artista =  rs.getString("artista");
                boolean video = rs.getInt("musicaOuVideo") == 1;
                if(!"".equals(personalGenero(FACADE.getUser().getID(), id))){
                    genero = personalGenero(FACADE.getUser().getID(), id);
                }
                Conteudo conteudo = new Conteudo(nome, genero, artista, video);
                return conteudo;
            }
        } catch (SQLException ex) {}
        return null;
    }

    @Override
    public Conteudo put(String arg0, Conteudo arg1) {
        QueryAtualizacao("insert into conteudos (nome,musicaOuVideo,artista,genero,contador) values ('"+arg1.getNome()+"','"+(arg1.isVideo()?"1":"0")+"','"+arg1.getArtista()+"','"+arg1.getGenero()+"','"+arg1.getContador()+"');");
        return arg1;
    }

    @Override
    public Conteudo remove(Object arg0) {
        if(!(arg0 instanceof String)) return null;
        
        String adminName = (String) arg0;
        Conteudo conteudoObject = get(adminName);
        if (conteudoObject == null) return null;
        
        if (QueryAtualizacao("delete from conteudos where nome='"+adminName+"';") > 0)
            return conteudoObject;
        else
            return null;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Conteudo> arg0) {
         arg0.forEach((k, v) -> {
		put(k,v);
	});
    }

    @Override
    public void clear() {
         QueryAtualizacao("delete from conteudos;");
    }

    @Override
    public Collection<Conteudo> values() {
        List<Conteudo> conteudos = new ArrayList<>();
        
        ResultSet rs = QuerySelecao("SELECT * FROM conteudos;");
        
        try {
            while ( rs.next() ) {
                int id = rs.getInt("ID");
                String nome =  rs.getString("nome");
                String genero =  rs.getString("genero");
                String artista =  rs.getString("artista");
                boolean video = rs.getInt("musicaOuVideo") == 1;
                
                if(FACADE.getUser() != null &&!"".equals(personalGenero(FACADE.getUser().getID(), id))){
                    genero = personalGenero(FACADE.getUser().getID(), id);
                }
                Conteudo conteudo = new Conteudo( nome, genero, artista, video);
                conteudos.add(conteudo);
            }
        } catch (SQLException ex) {
           
        }
        return conteudos;
    }
    
    public int getId(String nome){
        ResultSet rs = QuerySelecao("SELECT * FROM conteudos where nome='"+nome+"';");
        
        try {
            while ( rs.next() ) {
                return rs.getInt("ID");
            }
        } catch (SQLException ex) {
           
        }
        return 0;
    }

    public String personalGenero(int idUser, int idContent){
        ResultSet rs = QuerySelecao("SELECT * FROM view where id_user='"+idUser+"' AND id_content ='"+idContent+"';");
        try {
            while ( rs.next() ) {
                return rs.getString("genero");
            }
        } catch (SQLException ex) {
           
        }
        return "";
    }
    
    public void setPersonalGenero(int idUser, int idContent, String genero){
        if(personalGenero(idUser, idContent) == "")
            QueryAtualizacao("insert into view (genero,id_user,id_content) values('"+genero+"','"+idUser+"','"+idContent+"');");
        else
            QueryAtualizacao("update view set genero='"+genero+"' WHERE id_user ='"+idUser+"' AND id_content='"+idContent+"';");
    }
    
    public void deletePersonalGenero(int idUser, int idContent){
        QueryAtualizacao("delete from view WHERE id_user='"+idUser+"' AND id_content='"+idContent+"';");
    }

    
    @Override
    public Set<Entry<String, Conteudo>> entrySet() {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
    @Override
    public Set<String> keySet() {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}
