package Bussiness;

import java.util.ArrayList;
import java.util.List;

public class Membro extends User{
    
    private List<String> amigos;

    public Membro(String username, String password, String mail, int id) {
        super(username, password, mail, id);
        amigos = new ArrayList<>();
    }
    
    public Membro(String username, String email){
        this(username, "", email, 0);
    }

    public List<String> getAmigos() {
        return amigos;
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
