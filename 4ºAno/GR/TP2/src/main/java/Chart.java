import java.awt.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.ui.ApplicationFrame;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.json.simple.parser.ParseException;


public class Chart extends ApplicationFrame {

    public Chart(HashMapHist hist, String p) throws IOException, ParseException {
        super("Line Chart");
        JFreeChart xylineChart = ChartFactory.createXYLineChart(
                "Cpu and Ram usage over time",
                "Time",
                "Percentage",
                createDataset(hist,p),
                PlotOrientation.VERTICAL,
                true, true, false);

        ChartPanel chartPanel = new ChartPanel(xylineChart);
        chartPanel.setPreferredSize(new java.awt.Dimension(560, 367));
        final XYPlot plot = xylineChart.getXYPlot();

        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer();
        renderer.setSeriesPaint(0, Color.RED);
        renderer.setSeriesStroke(0, new BasicStroke(2.0f));
        renderer.setSeriesPaint(1, Color.BLUE);
        renderer.setSeriesStroke(1, new BasicStroke(2.0f));

        plot.setRenderer(renderer);
        plot.setBackgroundPaint(Color.white);
        plot.setRangeGridlinesVisible(false);
        plot.setDomainGridlinesVisible(false);


        setContentPane(chartPanel);
    }

    public XYDataset createDataset(HashMapHist hist,String p) throws IOException, ParseException {
        final XYSeries grafico = new XYSeries("CPU");
        final XYSeries grafico1 = new XYSeries("RAM");
        ArrayList<SNMPPar> a = new ArrayList<>(hist.allValues(p));
        float q=0;
        for(SNMPPar s : a ){
            grafico.add(q,s.getCPU());
            grafico1.add(q,s.getRAM());
            q+=0.05;
        }


        final XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(grafico);
        dataset.addSeries(grafico1);
        return dataset;
    }
}