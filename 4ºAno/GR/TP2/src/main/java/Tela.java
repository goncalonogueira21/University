import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;


import org.jfree.ui.RefineryUtilities;
import org.json.simple.parser.ParseException;
import org.snmp4j.smi.OID;

public class Tela extends javax.swing.JFrame {
    private JPanel MainPanel;
    private JTextField addr;
    private JTextField host;
    private JButton startButton;
    private JTable table1;
    private JButton High;
    private JButton Medium;
    private JButton Low;
    private JLabel pooling;
    private JLabel status;
    private JLabel status2;
    private JButton searchButton;
    private JTextField textField1;
    private JTable ProcessesList;
    private boolean isRunning;
    DefaultTableModel model;
    DefaultTableModel model1;
    HashMapHist hist = new HashMapHist();


    public Tela() throws FileNotFoundException {
        initComponents();
        isRunning = false;
        model = (DefaultTableModel) table1.getModel();
        RowSorter<TableModel> sorter = new TableRowSorter<>(model);
        table1.setRowSorter(sorter);

        //carrega processos do ficheiro de historico na map
        File myObj1 = new File("ManagerLogger");
        Scanner myReader1 = new Scanner(myObj1);
        while (myReader1.hasNextLine()) {
            String data1 = myReader1.nextLine();
            ArrayList<String> line = new ArrayList<>(Arrays.asList(data1.split("\\s*,\\s*")));
            String pro= line.get(0);
            hist.addSNMPPar(pro,Double.parseDouble(line.get(1)),Double.parseDouble(line.get(2)));
        }
        myReader1.close();


        // Constroi lista de processos guardados no historico
        ArrayList<String> procHist = hist.processesList();
        ProcessesList.setModel(new javax.swing.table.DefaultTableModel(
                new Object [][] {
                },
                new String [] {
                        "Process"
                }));
        model1 = (DefaultTableModel) ProcessesList.getModel();
        RowSorter<TableModel> sorter1 = new TableRowSorter<>(model1);
        ProcessesList.setRowSorter(sorter1);
        model1.setRowCount(0);
        for(String p : procHist){
            //System.out.print(p+ "\n");
            model1.insertRow(model1.getRowCount(), new Object[]{p});
        }



    }

    public static int pooling_freq_interface=35; // default pooling da interface
    public static int pooling_freq_manager=30000; // default pooling do manager

    private void initComponents(){
        try
        {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }
        setContentPane(MainPanel);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        startButton.addActionListener(this::butStartActionPerformed);
        High.setBackground(Color.green);
        Low.setBackground(Color.WHITE);
        Medium.setBackground(Color.WHITE);
        table1.setModel(new javax.swing.table.DefaultTableModel(
                new Object [][] {
                },
                new String [] {
                        "Process", "CPU Usage(%)", "RAM Usage(%)"
                }
        ));
        High.addActionListener(e -> {
            if (pooling_freq_interface!=35) {
                pooling_freq_interface=35;
                pooling_freq_manager=30000;
                High.setBackground(Color.green);
                Medium.setBackground(Color.WHITE);
                Low.setBackground(Color.WHITE);
                System.out.println("high pooling");
            }

        });
        Medium.addActionListener(e -> {
            if (pooling_freq_interface!=65) {
                pooling_freq_interface=65;
                pooling_freq_manager=90000;
                Medium.setBackground(Color.green);
                Low.setBackground(Color.WHITE);
                High.setBackground(Color.WHITE);
                System.out.println("medium pooling");
            }
        });
        Low.addActionListener(e -> {
            if (pooling_freq_manager!=95) {
                pooling_freq_manager=95;
                pooling_freq_manager=150000;
                Low.setBackground(Color.green);
                High.setBackground(Color.WHITE);
                Medium.setBackground(Color.WHITE);
                System.out.println("low pooling");
            }
        });
        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!textField1.getText().equals("")) {


                    Chart chart = null;
                    try {
                        chart = new Chart(hist, textField1.getText());
                    } catch (IOException | ParseException ioException) {
                        ioException.printStackTrace();
                    }
                    chart.pack();
                    RefineryUtilities.centerFrameOnScreen(chart);
                    chart.setVisible(true);
                    chart.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                }
            }
        });


        pack();
    }


    private void butStartActionPerformed(java.awt.event.ActionEvent evt){
        if (isRunning) {
            return;
        }
        isRunning = true;
        Table table = new Table();
        new Thread(table).start();
    }




    public static void main(String[] args){
        java.awt.EventQueue.invokeLater(() -> {
            try {
                new Tela().setVisible(true);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        });

    }




    class Table implements Runnable{

        public void run() {
            final int[] a1 = {0};
            ScheduledExecutorService exec = Executors.newSingleThreadScheduledExecutor();
            exec.scheduleAtFixedRate(() -> {
                try {

                    Map<String, SNMPPar> data = new HashMap<>();
                    SNMPManager client = new SNMPManager(addr.getText(), data);
                    Alarms alarm= new Alarms();
                    client.start();
                    String sysDescr = client.getAsString(new OID("1.3.6.1.2.1.1.1.0"));
                    System.out.println(sysDescr);
                    host.setText(sysDescr);
                    if(a1[0] ==0) {
                        status.setText("App starting");
                        status2.setText("Waiting for more samples");
                        a1[0] =1;
                    } else {
                        status.setText("");
                        status2.setText("");
                    }


                    client.execSnmpwalk("1.3.6.1.2.1.25.4.2.1.2");
                    client.preencheHash(1,pooling_freq_manager);

                    System.out.println("1 amostra");
                    Thread.sleep(pooling_freq_manager);

                    client.preencheHash(2,pooling_freq_manager);
                    alarm.checkValues();
                    System.out.println("2 amostra");


                    ArrayList<ArrayList<String>> res = new ArrayList<>();
                    File myObj = new File("logger");
                    Scanner myReader = new Scanner(myObj);
                    while (myReader.hasNextLine()) {
                        String data1 = myReader.nextLine();
                        ArrayList<String> items = new ArrayList<>(Arrays.asList(data1.split("\\s*,\\s*")));
                        res.add(items);
                    }
                    myReader.close();
                    model.setRowCount(0);
                    for(ArrayList a : res) {
                        model.insertRow(model.getRowCount(), new Object[]{a.get(0),a.get(1),a.get(2)});
                    }


                } catch (IOException | InterruptedException e ) {
                    System.out.println("An error occurred.");
                    e.printStackTrace();
                }
            }, 0, pooling_freq_interface, TimeUnit.SECONDS);
        }
    }

}
