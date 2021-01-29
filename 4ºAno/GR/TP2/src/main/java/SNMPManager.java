import java.io.*;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.text.SimpleDateFormat;
import java.util.*;
import org.snmp4j.CommunityTarget;
import org.snmp4j.PDU;
import org.snmp4j.Snmp;
import org.snmp4j.Target;
import org.snmp4j.TransportMapping;
import org.snmp4j.event.ResponseEvent;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.smi.Address;
import org.snmp4j.smi.GenericAddress;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.OctetString;
import org.snmp4j.smi.VariableBinding;
import org.snmp4j.transport.DefaultUdpTransportMapping;
import org.snmp4j.util.*;


public class SNMPManager  {

    Snmp snmp = null;
    String address;
    Map<String,SNMPPar> data;







    public SNMPManager(String address, Map<String, SNMPPar> data) {
        this.address = address;
        this.data = data;
    }


    /*
     * Port 161 is used for Read and Other operations
     * Port 162 is used for the trap generation
     */


    public void start() throws IOException {
        TransportMapping<org.snmp4j.smi.UdpAddress> transport = new DefaultUdpTransportMapping();
        snmp = new Snmp(transport);
        transport.listen();
    }


    public String getAsString(OID oid) throws IOException {
        ResponseEvent event = get(new OID[]{oid});
        return event.getResponse().get(0).getVariable().toString();
    }


    public ResponseEvent get(OID[] oids) throws IOException {
        PDU pdu = new PDU();
        for (OID oid : oids) {
            pdu.add(new VariableBinding(oid));
        }
        pdu.setType(PDU.GET);
        ResponseEvent event = snmp.send(pdu, getTarget(), null);
        if (event != null) {
            return event;
        }
        throw new RuntimeException("GET timed out");
    }


    private Target<Address> getTarget() {
        Address targetAddress = GenericAddress.parse(address);
        CommunityTarget<Address> target = new CommunityTarget<>();
        target.setCommunity(new OctetString("gr2020"));
        target.setAddress(targetAddress);
        target.setRetries(2);
        target.setTimeout(1500);
        target.setVersion(SnmpConstants.version2c);
        return target;
    }

    public void execSnmpwalk(String oid) {
    TreeUtils treeUtils = new TreeUtils(snmp, new DefaultPDUFactory());
    List<TreeEvent> events = treeUtils.getSubtree(getTarget(), new OID(oid));
        if(events == null || events.size() == 0) {
        System.out.println("No result returned.");
        System.exit(1);
    }
    // Handle the snmpwalk result.
        for (TreeEvent event : events) {
        if(event == null) {
            continue;
        }
        if (event.isError()) {
            System.err.println("oid [" + oid + "] " + event.getErrorMessage());
            continue;
        }
        VariableBinding[] varBindings = event.getVariableBindings();
        if(varBindings == null || varBindings.length == 0) {
            continue;
        }
        for (VariableBinding varBinding : varBindings) {
            if (varBinding == null) {
                continue;
            }

                    data.put(varBinding.getVariable().toString(),null);
                //System.out.println(varBinding.getVariable().toString());
        }
    }

}
    // memória ram disponivel na maquina virtual obtida atraves do oid 1.3.6.1.2.1.25.2.3.1.5.1
    private static final double ramTotal =5008164;

    public double calRamPerc(double valor){
        if(valor ==0) return 0;
        return round ((valor * 100 / ramTotal),2);

    }


    private static double round(double value, int places) {
        if (places < 0) throw new IllegalArgumentException();

        BigDecimal bd = new BigDecimal(Double.toString(value));
        bd = bd.setScale(places, RoundingMode.HALF_UP);
        return bd.doubleValue();
    }


    public static final String PROCESS_TABLE_OID = "1.3.6.1.2.1.25.4.2.1"; //hrSWRunTable
    //1.3.6.1.2.1.25.4.2.1.2.

    private List<Integer> getProcessIndexes(String process) {
        List<Integer> indexes = new ArrayList<>();
        if (process == null || process.isEmpty()) return indexes;

        TableUtils tUtils = new TableUtils(snmp, new DefaultPDUFactory());


        List<TableEvent> events = tUtils.getTable(getTarget(), new OID[]{new OID("." + PROCESS_TABLE_OID)}, null, null);

        for (TableEvent event : events) {
            if (event.isError()) {
                continue;
            }
            for (VariableBinding vb : event.getColumns()) {
                String key = vb.getOid().toString();
                String value = vb.getVariable().toString();
                if (!value.equalsIgnoreCase(process))
                    continue;
                //logger.fine("Find process OID entry: "+key);
                int index;
                String[] strs = key.split("\\.");

                index = Integer.parseInt(strs[strs.length - 1]);
                indexes.add(index);

            }
        }
            return indexes;

    }

    public static final String PROCESS_PERF_TABLE_OID  = "1.3.6.1.2.1.25.5.1.1";//hrSWRunPerfTable
    public static final String[] PROCESS_PERF_TABLE_ENTRIES = {"",
            "hrSWRunPerfCPU",
            "hrSWRunPerfMem"};
    public List<SNMPTriple> getProcessData(String processName) throws IOException {
        List<SNMPTriple> resList = new ArrayList<>();
        List<Integer> prIndexes = this.getProcessIndexes(processName);
        if(prIndexes.size() == 0)
            return  resList;

        //logger.fine("Query process stats");
        PDU pdu = new PDU();
        for(Integer idx: prIndexes)
        {
            for ( int i=1; i< PROCESS_PERF_TABLE_ENTRIES.length; i++) {
                if(PROCESS_PERF_TABLE_ENTRIES[i].length()==0)continue;
                pdu.add(new VariableBinding(new OID("."+PROCESS_PERF_TABLE_OID+"."+i+"."+idx)));
                //logger.info("Adding " + "."+PROCESS_PERF_TABLE_OID+"."+i+"."+idx);
            }
        }
        pdu.setType(PDU.GET);
        Map<String, String> res = new HashMap<>(prIndexes.size() * 2);
        ResponseEvent event = snmp.send(pdu, getTarget(), null);
        if(event != null) {
            VariableBinding[] binds = event.getResponse().toArray();
            for(VariableBinding b: binds)
            {
                res.put(b.getOid().toString(), b.getVariable().toString());
                //logger.info(b.getOid().toString() +", "+ b.getVariable().toString());
            }
        }
        //logger.info("result: "+res);
        for(int i=1;i<PROCESS_PERF_TABLE_ENTRIES.length; i++) {
            if(PROCESS_PERF_TABLE_ENTRIES[i].length()==0)continue;
            BigDecimal data = new BigDecimal(0);
            for(Integer idx: prIndexes)
            {
                data = data.add(new BigDecimal(res.get(PROCESS_PERF_TABLE_OID+"."+i+"."+idx)));
            }
            SNMPTriple aux = new SNMPTriple("", PROCESS_PERF_TABLE_ENTRIES[i], data.toString());
            resList.add(aux);

        }
        return resList;
    }

    //preenche SNMPPar para associar ao processo na hash data
    public SNMPPar aux(SNMPTriple a,SNMPTriple b){
        SNMPPar res = new SNMPPar();
        res.setCPU(round(Double.parseDouble(a.getValue()),5));
        res.setRAM(calRamPerc(Double.parseDouble(b.getValue())));
        return res;
    }


    public void preencheHash(int v, int pooling_freq) throws IOException {
        //Date date = new Date();
        PrintWriter writer = new PrintWriter("logger", "UTF-8");
        PrintWriter writer2 = new PrintWriter(new FileWriter("ManagerLogger",true));
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
        //writer2.println("Time, " + formatter.format(date));
        SNMPPar res=new SNMPPar();
        List<SNMPTriple> resList;
        for (Map.Entry<String,SNMPPar> entry : data.entrySet()){


            try {
                resList = getProcessData(entry.getKey());
                if (v == 1) {
                    entry.setValue(aux(resList.get(0), resList.get(1)));

                } else if (resList.size() > 0) {
                    double cpu1 = entry.getValue().getCPU();
                    double cpu2 = Double.parseDouble(resList.get(0).getValue());
                    res.setCPU((round(((Math.abs(cpu1 - cpu2) )*10 / pooling_freq)*100,2)));
                    res.setRAM(calRamPerc(Double.parseDouble(resList.get(1).getValue())));
                    entry.setValue(res);
                    writer2.println( entry.getKey() + entry.getValue().imprime());

                } else {
                    /*double cpu1 = entry.getValue().getCPU();
                    res.setCPU(round(cpu1/pooling_freq,5));
                    res.setRAM(entry.getValue().getRAM());
                    entry.setValue(res);*/
                    continue;
                }

                writer.println( entry.getKey() + entry.getValue().imprime());
                // System.out.println("Process: " + entry.getKey() + " " +entry.getValue().imprime());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        writer.close();
        writer2.close();
    }
}