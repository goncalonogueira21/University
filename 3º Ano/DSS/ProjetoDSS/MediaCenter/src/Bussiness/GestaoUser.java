package Bussiness;

import Data.UsersDAO;
import Data.Administrador;

public class GestaoUser {

    private final UsersDAO users = new UsersDAO();
    
    boolean cria(String username, String email, boolean admin){
       if(users.containsKey(username))
           return false;
       
       User newUser;
       
       if(admin)
            newUser = new Administrador(username, email);
       else
            newUser = new Membro(username, email);
       
       users.put(newUser.getUsername(), newUser);
       return true;
    }
    
    boolean removeMembro(String name){
        return users.remove(name) != null;
    }
    
    void changePassword(String login, String newPassword){
       users.changePassword(login, newPassword);
    }
    
    void changeMail(String login, String newMail) {
        users.changeMail(login, newMail);
    }
    
    boolean changeName(String oldName, String newName) {
        if(users.containsKey(newName))
           return false;

        users.changeName(oldName, newName);
        return true;
    }
    
    boolean existeUser(String name){
        return users.containsKey(name);
    }
     
    User getUser(String name){
        return users.get(name);
    }
}
    