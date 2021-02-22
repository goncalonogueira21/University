/*
Classe responsavel por monotorizar o Som
 */

import javax.sound.sampled.*;
import java.io.*;
import java.util.ArrayList;


public class MonitSom {


        protected boolean running;
        private ByteArrayOutputStream out;
        final static float MAX_8_BITS_SIGNED = Byte.MAX_VALUE;
        final static float MAX_8_BITS_UNSIGNED = 0xff;
        final static float MAX_16_BITS_SIGNED = Short.MAX_VALUE;
        final static float MAX_16_BITS_UNSIGNED = 0xffff;
        private AudioFormat format;
        private float level;
        public ArrayList<Float> valueOut = new ArrayList<Float>();
        public int f = 0;


        private AudioFormat getFormat() {
            format = new AudioFormat(1000f, 16, 1, true, false);
            return format;
        }

      //Metodo para iniciar a captura de som
        public void recordAudio(TaMtAlto m) {
            try {
                final AudioFormat format = getFormat();
                DataLine.Info info = new DataLine.Info(
                        TargetDataLine.class, format);
                final TargetDataLine line = (TargetDataLine)
                        AudioSystem.getLine(info);
                line.open(format);
                line.start();
                Runnable runner = new Runnable() {
                    int bufferSize = (int) format.getSampleRate()
                            * format.getFrameSize();
                    byte buffer[] = new byte[bufferSize];

                    public void run() {
                        int readPoint = 0;

                        out = new ByteArrayOutputStream();
                        running = true;
                        int sum=0;
                        while (running) {
                            int count =
                                    line.read(buffer, 0, buffer.length);
                            calculateLevel(buffer,0,0);
                            //System.out.println(level);
                            if (valueOut.size() <10){
                                valueOut.add(level);
                            }else {valueOut.remove(0);
                            valueOut.add(level);}
                                //da.AddText2(valueOut);
                                //System.out.println(valueOut);

                            m.AddText(level);
                            System.out.println(level);

                            //add data soud to write in fire base
                            Firebase firebase = new Firebase();
                            try {
                                firebase.WriteFireBase(level);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }

                            f++;
                            if (count > 0) {
                                out.write(buffer, 0, count);
                            }
                        }

                        line.stop();

                    }
                };
                Thread captureThread = new Thread(runner);
                captureThread.start();
            } catch (LineUnavailableException e) {
                System.err.println("Line unavailable: " + e);
                System.exit(-2);
            }
        }

//Metodo responsavel por converter o som captado em Decibéis
        private void calculateLevel (byte[] buffer,
                                     int readPoint,
                                     int leftOver) {
            int max = 0;
            boolean use16Bit = (format.getSampleSizeInBits() == 16);
            boolean signed = (format.getEncoding() ==
                    AudioFormat.Encoding.PCM_SIGNED);
            boolean bigEndian = (format.isBigEndian());
            if (use16Bit) {
                for (int i=readPoint; i<buffer.length-leftOver; i+=2) {
                    int value = 0;

                    int hiByte = (bigEndian ? buffer[i] : buffer[i+1]);
                    int loByte = (bigEndian ? buffer[i+1] : buffer [i]);
                    if (signed) {
                        short shortVal = (short) hiByte;
                        shortVal = (short) ((shortVal << 8) | (byte) loByte);
                        value = shortVal;
                    } else {
                        value = (hiByte << 8) | loByte;
                    }
                    max = Math.max(max, value);
                }
            } else {

                for (int i=readPoint; i<buffer.length-leftOver; i++) {
                    int value = 0;
                    if (signed) {
                        value = buffer [i];
                    } else {
                        short shortVal = 0;
                        shortVal = (short) (shortVal | buffer [i]);
                        value = shortVal;
                    }
                    max = Math.max (max, value);
                }
            }

            if (signed) {
                if (use16Bit) { level = (float) max / MAX_16_BITS_SIGNED; }
                else { level = (float) max / MAX_8_BITS_SIGNED; }
            } else {
                if (use16Bit) { level = (float) max / MAX_16_BITS_UNSIGNED; }
                else { level = (float) max / MAX_8_BITS_UNSIGNED; }
            }
                level = (float) (level * 20 * Math.log10(100));
        }


    }

