package Bussiness;

import Presentation.LoginFrame;

public class Main {
    
     public static final MediaCenterFacade FACADE  = new MediaCenterFacade();; 
     
     public static void main(String[] args){
         java.awt.EventQueue.invokeLater(() -> {
             new LoginFrame().setVisible(true);
         });
     }
}
