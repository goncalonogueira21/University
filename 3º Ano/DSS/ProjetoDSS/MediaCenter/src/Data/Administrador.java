package Data;

import Bussiness.User;
import Bussiness.User;

public class Administrador extends User{

    public Administrador(String username, String password, String mail, int id) {
        super(username, password, mail, id);
    }
    
    public Administrador(String username, String email){
        this(username, "", email, 0);
    }
    
    @Override
    public boolean equals(Object obj) {
       return super.equals(obj);
    }
    
     @Override
    public String toString() {
        return super.toString()+" | Admin";
    }    
}
