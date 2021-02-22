/*
Classe com os métodos para Desenhar o Gráfico
 */

import java.awt.*;
import java.io.IOException;
import java.util.List;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.ui.ApplicationFrame;
import org.jfree.ui.RefineryUtilities;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.json.simple.parser.ParseException;

import javax.swing.*;

public class XYLineChart_AWT extends ApplicationFrame {

    public XYLineChart_AWT(String applicationTitle, String chartTitle) throws IOException, ParseException {
        super(applicationTitle);
        JFreeChart xylineChart = ChartFactory.createXYLineChart(
                chartTitle,
                "Time",
                "dB",
                createDataset(),
                PlotOrientation.VERTICAL,
                true, true, false);

        ChartPanel chartPanel = new ChartPanel(xylineChart);
        chartPanel.setPreferredSize(new java.awt.Dimension(560, 367));
        final XYPlot plot = xylineChart.getXYPlot();

        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer();
        renderer.setSeriesPaint(0, Color.black);
        plot.setRenderer(renderer);
        setContentPane(chartPanel);
    }

    public XYDataset createDataset() throws IOException, ParseException {
        final XYSeries grafico = new XYSeries("Grafico");
        Firebase fb = new Firebase();
        List<Float> f = fb.ReadFireBase2();
        float a=0;
       for(float fa: f){
           grafico.add(a,fa);
           a+=0.05;

       }

        final XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(grafico);
        return dataset;
    }
}