package Presentation;

import Bussiness.User;
import static Bussiness.Main.FACADE;


public class EditProfilFrame extends javax.swing.JFrame {

     public EditProfilFrame() {
        initComponents();
        
        User currentUser = FACADE.getUser();
        
        this.mailText.setText(currentUser.getEmail());
        this.nameText.setText(currentUser.getUsername());
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        pass = new javax.swing.JPasswordField();
        jLabel2 = new javax.swing.JLabel();
        Back = new javax.swing.JButton();
        ChangePassword = new javax.swing.JButton();
        SetMailButton = new javax.swing.JButton();
        SetNameButton = new javax.swing.JButton();
        mailText = new java.awt.TextField();
        nameText = new java.awt.TextField();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        pass.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                passActionPerformed(evt);
            }
        });

        jLabel2.setText("EDIT YOUR PROFIL PLEASE");

        Back.setText("Back");
        Back.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                BackActionPerformed(evt);
            }
        });

        ChangePassword.setText("Set Password");
        ChangePassword.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ChangePasswordActionPerformed(evt);
            }
        });

        SetMailButton.setText("Set Mail");
        SetMailButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                SetMailButtonActionPerformed(evt);
            }
        });

        SetNameButton.setText("Set Name");
        SetNameButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                SetNameButtonActionPerformed(evt);
            }
        });

        mailText.setText("textField1");
        mailText.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                mailTextActionPerformed(evt);
            }
        });

        nameText.setText("textField1");
        nameText.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                nameTextActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jLabel2)
                .addGap(99, 99, 99))
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Back)
                        .addContainerGap(284, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(pass)
                            .addComponent(mailText, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(nameText, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 166, Short.MAX_VALUE))
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 23, Short.MAX_VALUE)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(SetNameButton, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 95, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(SetMailButton, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 95, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(59, 59, 59))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(18, 18, 18)
                                .addComponent(ChangePassword)
                                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(40, 40, 40)
                .addComponent(jLabel2)
                .addGap(39, 39, 39)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(pass, javax.swing.GroupLayout.PREFERRED_SIZE, 19, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(ChangePassword))
                        .addGap(27, 27, 27)
                        .addComponent(SetMailButton))
                    .addComponent(mailText, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(32, 32, 32)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(SetNameButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 78, Short.MAX_VALUE)
                        .addComponent(Back)
                        .addGap(21, 21, 21))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(nameText, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void BackActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_BackActionPerformed
       this.dispose(); 
    }//GEN-LAST:event_BackActionPerformed

    private void ChangePasswordActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ChangePasswordActionPerformed
        String newPass = pass.getText();
        FACADE.changePassword(newPass);
        new ErrorFrame("Password changed with success.");
    }//GEN-LAST:event_ChangePasswordActionPerformed

    private void SetMailButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_SetMailButtonActionPerformed
        String newMail = mailText.getText();
        FACADE.changeMail(newMail);
        new ErrorFrame("Email changed with success.");
    }//GEN-LAST:event_SetMailButtonActionPerformed

    private void SetNameButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_SetNameButtonActionPerformed
        String newName = nameText.getText();
        if(FACADE.changeName(newName)){
            new ErrorFrame("Name changed with success.");
        }else{
            new ErrorFrame("There is already an user with this name.");
        }
    }//GEN-LAST:event_SetNameButtonActionPerformed

    private void mailTextActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_mailTextActionPerformed
        SetMailButtonActionPerformed(evt);
    }//GEN-LAST:event_mailTextActionPerformed

    private void nameTextActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_nameTextActionPerformed
        SetNameButtonActionPerformed(evt);
    }//GEN-LAST:event_nameTextActionPerformed

    private void passActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_passActionPerformed
        ChangePasswordActionPerformed(evt);
    }//GEN-LAST:event_passActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton Back;
    private javax.swing.JButton ChangePassword;
    private javax.swing.JButton SetMailButton;
    private javax.swing.JButton SetNameButton;
    private javax.swing.JLabel jLabel2;
    private java.awt.TextField mailText;
    private java.awt.TextField nameText;
    private javax.swing.JPasswordField pass;
    // End of variables declaration//GEN-END:variables
}
