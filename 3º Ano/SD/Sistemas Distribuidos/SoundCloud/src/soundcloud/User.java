/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package soundcloud;

import java.io.Serializable;
import java.util.Objects;

/**
 *
 * @author f6car
 */
public class User implements Serializable {
    
    
    private String nick;
    private String pass;
    private Boolean ativo;
 
     //Construtores
    public User(){
        this.nick = "";
        this.pass = "";
        this.ativo=false;
        }
    
    public User(String s, String p){
        this.nick = s;
        this.pass = p;
        this.ativo=false;
    }  
    
    public User(User u){
        this.nick = u.getNick();
        this.pass = u.getPass();
        this.ativo=u.isAtivo();
    }

    
    
    //getters
    public String getNick() {
        return nick;
    }
    public String getPass() {
        return pass;
    }
    
    public Boolean isAtivo(){
        return ativo;
    }
    //setters
    public void setNick(String nick) {
        this.nick = nick;
    }
    public void setPass(String pass) {
        this.pass = pass;
    }
    public void setAtivo(Boolean ativo){
        this.ativo=ativo;
    }
    
    
    
    //clone
    @Override
    public User clone(){
        return new User(this);
    }
    
    //toString
    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("***Utilizador***\n");
        s.append("Utilizador: ").append(this.getNick()).append("\n");
	s.append("Password: ").append( this.getPass()).append("\n");
        s.append("Ativo " ).append(this.ativo).append("\n");
        return s.toString();
    }
    
    //Equals
    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
	if ((o == null) || (o.getClass() != this.getClass())){
            return false;
        }else {
            User c = (User) o;
            return (this.getNick().equals(c.getNick()) && (this.getPass().equals(c.getPass())));}
    }    

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 97 * hash + Objects.hashCode(this.nick);
        hash = 97 * hash + Objects.hashCode(this.pass);
        hash = 97 * hash + Objects.hashCode(this.ativo);
        return hash;
    }

    
}

