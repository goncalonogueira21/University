package Data;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.sql.ResultSet;
import java.sql.SQLException;
import Bussiness.Membro;
import Bussiness.User;

import static utils.Utils.QueryAtualizacao;
import static utils.Utils.QuerySelecao;

public class UsersDAO implements Map<String,User> {         
    
    @Override
    public int size() {
        int i=0;
        ResultSet rs = QuerySelecao("SELECT * FROM users;");
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
    public boolean containsValue(Object arg0) {
        if((arg0 instanceof Administrador)){
            Administrador admin = (Administrador) arg0;
            Administrador adminInDBB = (Administrador) get(admin.getUsername());
            return admin.equals(adminInDBB);
        } else if((arg0 instanceof Membro)){
            Membro membro = (Membro) arg0;
            Membro membroInBDD = (Membro) get(membro.getUsername());
            return membro.equals(membroInBDD);
        }
        return false;
    }

    @Override
    public User put(String arg0, User arg1) {
        String name = arg1.getUsername();
        String mail = arg1.getEmail();
        String password = arg1.getPassword();
        int admin = (arg1 instanceof Administrador ? 1 : 0);
        String query = "insert into users (name,password,email,admin) values ('"+name+"','"+password+"','"+mail+"','"+admin+"');";
        QueryAtualizacao(query);
        return arg1;
    }

    @Override
    public User remove(Object arg0) {
        if(!(arg0 instanceof String)) return null;
        
        String name = (String) arg0;
        User user = get(name);
        if (user == null) return null;
        
        if (QueryAtualizacao("delete from users where name='"+name+"';") > 0)
            return user;
        else
            return null;
    }

    @Override
    public void clear() {
        QueryAtualizacao("delete from users;");
    }
    
     @Override
    public boolean containsKey(Object arg0) {
        return get(arg0) != null;
    }

    @Override
    public Collection<User> values() {
        List<User> users = new ArrayList<>();
        ResultSet rs = QuerySelecao("SELECT * FROM users;");
        try {
            while ( rs.next() ) {
                String name =  rs.getString("name");
                String password =  rs.getString("password");
                String email =  rs.getString("email");
                int id = rs.getInt("ID");
                if(rs.getInt("admin") == 1)
                    users.add(new Administrador(name,password,email, id));
                else
                    users.add(new Membro(name, password, email, id));
            }
        } catch (SQLException ex) {}
        return users;
    }

    @Override
    public User get(Object nameObject) {
        if(!(nameObject instanceof String))
            return null;
        
        String name = (String)nameObject;
        ResultSet rs = QuerySelecao("SELECT * FROM users WHERE name=\""+name+"\";");
        try {
                rs.next();
                String password =  rs.getString("password");
                String email =  rs.getString("email");
                int id = rs.getInt("id");
                if(rs.getInt("admin") == 1)
                    return new Administrador(name,password,email, id);
                else
                    return new Membro(name, password, email, id);
        } catch (SQLException ex) {
            return null;
        }
    }

    @Override
    public void putAll(Map<? extends String, ? extends User> arg0) {
        arg0.forEach((k, v) -> {
		put(k,v);
	});
    }

    @Override
    public Set<String> keySet() {
        Set<String> names = new HashSet<>();
        
        ResultSet rs = QuerySelecao("SELECT * FROM users;");
        try {
            while ( rs.next() ) {
                String name =  rs.getString("name");
                names.add(name);
            }
        } catch (SQLException ex) {}
        return names;
    }

    public void changeMail(String username, String newMail) {
        QueryAtualizacao("update users set email='"+newMail+"' WHERE name ='"+username+"';");
    }

    public void changeName(String username, String newName0) {
        QueryAtualizacao("update users set name='"+newName0+"' WHERE name ='"+username+"';");
    }
    
    public void changePassword(String username, String newPass){
        QueryAtualizacao("update users set password='"+newPass+"' WHERE name ='"+username+"';");
    }
    
    @Override
    public Set<Entry<String, User>> entrySet() {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}   
 