import java.io.*;
import java.util.Iterator;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

public class XLSXReaderWriter {

    public static void main(String[] args) throws IOException {
        File excelFile = new File("cidades.xlsx");
        FileInputStream fis = new FileInputStream(excelFile);
        FileWriter fw = new FileWriter("trabalho.pl");
        PrintWriter pw = new PrintWriter(fw);
        Local a=new Local();
        int flag=0;

        // we create an XSSF Workbook object for our XLSX Excel File
        XSSFWorkbook workbook = new XSSFWorkbook(fis);
        // we get first sheet
        XSSFSheet sheet = workbook.getSheetAt(0);

        // we iterate on rows

        for (Row row : sheet) {
            // iterate on cells for the current row
            Iterator<Cell> cellIterator = row.cellIterator();

            while (cellIterator.hasNext() && flag<6) {
                Cell cell = cellIterator.next();
                if (flag==0) a.setId(cell.toString());
                if (flag==1) a.setCity(cell.toString());
                if (flag==2) a.setLat(cell.toString());
                if (flag==3) a.setLng(cell.toString());
                if (flag==4) a.setCapital(cell.toString());
                if (flag==5) a.setAdmin(cell.toString());
                System.out.print(cell.toString() + ";");
                flag++;
            }
            pw.println(a.toString());
            System.out.println();
            flag=0;
        }

        workbook.close();
        fis.close();
        pw.close();
    }

}