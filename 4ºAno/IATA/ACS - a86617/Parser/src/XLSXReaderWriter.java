import java.io.*;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Locale;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

public class XLSXReaderWriter {

    public static void main(String[] args) throws IOException {
        File excelFile = new File("Anexo-temperatura.xlsx");
        FileInputStream fis = new FileInputStream(excelFile);
        FileWriter fw = new FileWriter("logger.pl");
        PrintWriter pw = new PrintWriter(fw);
        Handler a=new Handler();
        int flag=0;
        ArrayList<Float> temp= new ArrayList<>();
        ArrayList<Integer> estacao = new ArrayList<>();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss", Locale.ENGLISH);


        // we create an XSSF Workbook object for our XLSX Excel File
        XSSFWorkbook workbook = new XSSFWorkbook(fis);
        // we get first sheet
        XSSFSheet sheet = workbook.getSheetAt(0);

        // we iterate on rows

        for (Row row : sheet) {
            // iterate on cells for the current row
            Iterator<Cell> cellIterator = row.cellIterator();
            pw.println("Dados= { ");
            while (cellIterator.hasNext() && flag<6 ) {
                Cell cell = cellIterator.next();
               if(flag==0) a.setEstacao(checkSeason(LocalDate.parse(cell.toString(),formatter)));
               if(flag==4) a.setTemp(Float.parseFloat(cell.toString()));
                pw.println(cell.toString()+",");
                System.out.print(cell.toString() + ",");
                flag++;

            }
            pw.println(" }");
            pw.println(a.toString());
            pw.println();
            System.out.println();
            flag=0;
        }




        workbook.close();
        fis.close();
        pw.close();
    }

    private static int checkSeason(LocalDate data) {
        int a=0;
        if ((data.getDayOfMonth() > 22 && data.getMonthValue() > 9) || (data.getDayOfMonth() < 20 && data.getMonthValue() < 3))
            a = 1; // outono+inverno
        if ((data.getDayOfMonth() >= 20 && data.getMonthValue() >= 3) || (data.getDayOfMonth() <= 22 && data.getMonthValue() <= 9))
            a = 2; // verao+primavera
        return a;
    }




}