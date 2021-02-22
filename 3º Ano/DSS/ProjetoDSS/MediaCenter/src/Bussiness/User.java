package Bussiness;

import java.util.Objects;

public abstract class User {
    
    protected String email;
    protected String password;
    protected String username;
    protected int ID;

    public User(String username, String password, String mail, int ID) {
        this.email = mail;
        this.password = password;
        this.username = username;
        this.ID = ID;
    }
    
    @Override
    public int hashCode() {
        int hash = 3;
        hash = 97 * hash + Objects.hashCode(this.username);
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final User other = (User) obj;
        if (!Objects.equals(this.username, other.username)) {
            return false;
        }
        return true;
    }    

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public String getUsername() {
        return username;
    }
    
    public int getID(){
        return ID;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setID(int ID) {
        this.ID = ID;
    }
    
    

    @Override
    public String toString() {
        return "User{" + "email=" + email + ", password=" + password + ", username=" + username + '}';
    }
}
