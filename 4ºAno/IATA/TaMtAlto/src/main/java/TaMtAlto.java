/*
Classe Principal, onde a interface e os Listeners são adicionados
 */


import org.json.simple.parser.ParseException;

import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.sql.Timestamp;

import java.awt.Color;

import org.jfree.ui.RefineryUtilities;

import javax.swing.*;

public class TaMtAlto extends JFrame implements KeyListener, ActionListener {
    private JTextArea displayArea;
    private JTextField typingArea;
    static final String newline = System.getProperty("line.separator");
    private final String newLine2 = System.getProperty("line.separator");
    ChavesPressionadas a=new ChavesPressionadas();
    private JPanel MainPanel;
    private JTextArea displayArea2;
    private JButton StartRecord;
    private JButton Historico;
    private JButton Metricas;
    private JScrollPane scrolll;


    public static void main(String[] args) throws IOException, ParseException {
        MonitSom ce = new MonitSom();

        UIManager.put("swing.boldMetal", Boolean.FALSE);


        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI(ce);
            }
        });

    }

   //Preparar a Interface
    public static void createAndShowGUI(MonitSom ce) {
        //Create and set up the window.
        TaMtAlto frame = new TaMtAlto("Merda2");
        frame.setContentPane(new TaMtAlto("Merda2").MainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


        frame.addComponentsToPane(ce);


        //Display the window.
        frame.pack();
        frame.addWindowListener( new WindowAdapter() {
            public void windowClosing(WindowEvent we) {
                Window window = we.getWindow();
                window.dispose();
                window.setVisible(false);

            }
        });
        frame.setVisible(true);
    }

    //Algumas componentes para a interface
    public void addComponentsToPane(MonitSom ce) {
        JTextArea display = displayArea;


        display.setEditable ( false );

    }

    public TaMtAlto(String name) {

        StartRecord.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
               MonitSom ce = new MonitSom();
               ce.recordAudio(TaMtAlto.this);
            }
        });
        Metricas.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Timestamp timestamp = new Timestamp(System.currentTimeMillis());
                displayArea.append("MOST PRESSED KEY IS " + a.KeyPressedMore() + "\n");
                displayArea.append("KEYSPERMINUTE ARE " + a.KeysPerMinute(timestamp) + "\n");
            }
        });
        Historico.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                XYLineChart_AWT chart = null;
                try {
                    chart = new XYLineChart_AWT("Histórico",
                            "Histórico de som registado");
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ParseException parseException) {
                    parseException.printStackTrace();
                }
                chart.pack( );
                RefineryUtilities.centerFrameOnScreen( chart );
                chart.setVisible( true );
                chart.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
            }
     });
    }
    public void AddText(float value){
        if(value >= 20){
            displayArea2.setForeground(Color.red);
            displayArea2.insert(String.valueOf(value) + newLine2, 0);

        }
        else {
            displayArea2.setForeground(Color.black);
            displayArea2.insert(String.valueOf(value) + newLine2, 0);
        }
    }

     public void keyTyped(KeyEvent e) {

    }

    public void keyPressed(KeyEvent e) {
        Timestamp timestamp = new Timestamp(System.currentTimeMillis());
        int keyCode= e.getKeyCode();
        a.addKeyPressed(KeyEvent.getKeyText(keyCode),timestamp);

        displayInfo(e, "KEY PRESSED: ");
    }

    public void keyReleased(KeyEvent e) {
    }

    public void actionPerformed(ActionEvent e) {

    }


    public void displayInfo(KeyEvent e, String keyStatus){


        int id = e.getID();
        String keyString;
        if (id == KeyEvent.KEY_TYPED) {
            char c = e.getKeyChar();
            keyString = "key character = '" + c + "'";
        } else {
            int keyCode = e.getKeyCode();
            keyString = "key code = " + keyCode
                    + " ("
                    + KeyEvent.getKeyText(keyCode)
                    + ")";
        }

        int modifiersEx = e.getModifiersEx();
        String modString = "extended modifiers = " + modifiersEx;
        String tmpString = KeyEvent.getModifiersExText(modifiersEx);
        if (tmpString.length() > 0) {
            modString += " (" + tmpString + ")";
        } else {
            modString += " (no extended modifiers)";
        }

        String actionString = "action key? ";
        if (e.isActionKey()) {
            actionString += "YES";
        } else {
            actionString += "NO";
        }

        String locationString = "key location: ";
        int location = e.getKeyLocation();
        if (location == KeyEvent.KEY_LOCATION_STANDARD) {
            locationString += "standard";
        } else if (location == KeyEvent.KEY_LOCATION_LEFT) {
            locationString += "left";
        } else if (location == KeyEvent.KEY_LOCATION_RIGHT) {
            locationString += "right";
        } else if (location == KeyEvent.KEY_LOCATION_NUMPAD) {
            locationString += "numpad";
        } else { // (location == KeyEvent.KEY_LOCATION_UNKNOWN)
            locationString += "unknown";
        }

        this.displayArea.append(keyStatus + newline
                + "    " + keyString + newline
                + "    " + modString + newline
                + "    " + actionString + newline
                + "    " + locationString + newline);

    }

    private void createUIComponents() {
        typingArea = new JTextField(20);
        typingArea.addKeyListener(this);
    }



}

