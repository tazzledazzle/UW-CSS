import java.awt.GridLayout;
import javax.swing.JFrame;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.util.Arrays;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import src.com.musicg.math.rank.ArrayRankDouble;
import src.com.musicg.representation.timedomain.AmplitudeTimeDomainRepresentation;
import src.com.musicg.representation.timedomain.FrequencyTimeDomainRepresentation;
import src.com.musicg.representation.timedomain.TimeDomainRepresentation;
import src.com.musicg.math.statistics.*;
import src.com.musicg.math.statistics.ZeroCrossingRate;
import src.com.musicg.pitch.PitchHandler;
import src.com.musicg.dsp.FastFourierTransform;
import src.com.musicg.wave.WaveHeader;
import src.com.musicg.wave.WaveInputStream;
import src.com.musicg.wave.Wave;

/**
 * @project Assignment 4 -- Audio Machine Learning System
 * @version 1.0
 * @author tazzledazzle
 */
public class AudioFeature extends JFrame {
    Runtime rt = Runtime.getRuntime();
    Process pr;
    private JPanel bottomPanel;
    private JPanel upperPanel;
    private JPanel buttonPanel;
    private JPanel featureSelectPanel;
    private GridLayout gridlayout1;
    private BoxLayout box;
    private JScrollPane scroll;
    private JScrollPane scroller;
    File [] totalRecordings = new File[41];
        //list selection things
    private JList list;
    private DefaultListModel listModel;
    private JTextArea output = new JTextArea(12, 60);

    
    private AudioInputStream [] audioStream;
    private AudioFormat [] audioFormat;

    String featureFile = "src/feature_definitions_1.xml";
    PrintWriter writer;
   
    /** Constructor
     * @brief creates JFrame instance of AudioFeature Class
     * @see writing to the audioFeatures.arff file is handled in the main constructor for now,
     *      although it might be better to handle such changes within an action listener with selection
     *      of specific audio files.
     */
    public AudioFeature(){
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Audio Feature Analyzer");
        setSize(750,450);
        setResizable(false);
        bottomPanel = new JPanel();
        upperPanel = new JPanel();
        buttonPanel = new JPanel();
        featureSelectPanel = new JPanel();
        setLayout(new GridLayout(2,1,5,5));
        gridlayout1 = new GridLayout(4,5,5,5);
        box = new BoxLayout(buttonPanel, BoxLayout.Y_AXIS);
        setLocationRelativeTo(null);
        audioStream = new AudioInputStream[41];
        audioFormat = new AudioFormat[41];
        
        //buttons
        JButton clear = new JButton("Clear");
        JButton j48 = new JButton("J48");
        JButton smo = new JButton("SMO");
        JButton zeroR = new JButton("Zero R");
        JButton naiveBayes = new JButton("Naive Bayes");
        clear.addActionListener(new clearListener());
        j48.addActionListener(new j48Listener());
        smo.addActionListener(new smoListener());
        zeroR.addActionListener(new zeroRListener());
        naiveBayes.addActionListener(new naiveBayesListener());
        listModel = new DefaultListModel();
        
        //text areas
        JTextArea selection = new JTextArea(9, 30);
        selection.setLineWrap(true);
        selection.setWrapStyleWord(true);
        try{ 
         writer = new PrintWriter("audioFeatures.arff");
         configureFile();
        }catch (Exception e){}
          for (int i = 1; i < 21; i++){
              
            totalRecordings[i] = new File("src/audio/music/mu" + i + ".wav");
          
            try{
                String audioType = "MUSIC";
                audioStream[i] = AudioSystem.getAudioInputStream(totalRecordings[i]);
                WaveHeader wavFile = new WaveHeader(new FileInputStream(totalRecordings[i]));
                 Wave  wave = new Wave(new WaveInputStream(new FileInputStream(totalRecordings[i])));
                TimeDomainRepresentation tdr = new TimeDomainRepresentation(wave);
                FrequencyTimeDomainRepresentation ftdr = new FrequencyTimeDomainRepresentation(tdr.getWave());
                AmplitudeTimeDomainRepresentation atdr = new AmplitudeTimeDomainRepresentation(tdr.getWave());
                ftdr.buildSpectrogram();
                Mean mean = new Mean();
                ZeroCrossingRate zcr = new ZeroCrossingRate(atdr.getNormalizedAmplitudes(),1);
                StandardDeviation stdv = new StandardDeviation();
                stdv.setValues(atdr.getNormalizedAmplitudes());
                ArrayRankDouble ard = new ArrayRankDouble();
                mean.setValues(atdr.getNormalizedAmplitudes());
                SpectralCentroid sp = new SpectralCentroid(atdr.getNormalizedAmplitudes());    
                PitchHandler ph = new PitchHandler();
                
                writer.print(wavFile.getAudioFormat());
                writer.print(","+wavFile.getSampleRate());
                writer.print(","+wavFile.getBitsPerSample());
                writer.print(","+wavFile.getBlockAlign());
                writer.print(","+wavFile.getByteRate());
                writer.print(","+wavFile.getChannels());
                writer.print(","+wavFile.getChunkSize());
                writer.print(","+ftdr.getFftSampleSize());
                writer.print(","+ftdr.getFramesPerSecond());
                writer.print(","+ftdr.getNumFrames());
                writer.print(","+ftdr.getNumFrequencyUnit());
                writer.print(","+ftdr.getUnitFrequency());
                writer.print(","+atdr.getTimeStep());
                writer.print(","+ard.getMaxValueIndex(atdr.getNormalizedAmplitudes()));
                writer.print(","+ard.getMinValueIndex(atdr.getNormalizedAmplitudes()));
                writer.print(","+mean.evaluate());
                writer.print(","+zcr.evaluate());
                writer.print(","+stdv.evaluate());
                writer.print(","+sp.evaluate());
                writer.print(","+audioType);
                writer.println();
            }
            catch (Exception e){
                e.printStackTrace();
            }
            audioFormat[i] = audioStream[i].getFormat();
            listModel.addElement(totalRecordings[i]);
           }
            for (int i = 21; i < 41; i++){
                totalRecordings[i] = new File("src/audio/speech/sp" + (i-20) + ".wav");
                
                try{
                    String audioType = "SPEECH";
                audioStream[i] = AudioSystem.getAudioInputStream(totalRecordings[i]);
                WaveHeader wavFile = new WaveHeader(new FileInputStream(totalRecordings[i]));
                 Wave  wave = new Wave(new WaveInputStream(new FileInputStream(totalRecordings[i])));
                TimeDomainRepresentation tdr = new TimeDomainRepresentation(wave);
                FrequencyTimeDomainRepresentation ftdr = new FrequencyTimeDomainRepresentation(tdr.getWave());
                AmplitudeTimeDomainRepresentation atdr = new AmplitudeTimeDomainRepresentation(tdr.getWave());
                ftdr.buildSpectrogram();
                Mean mean = new Mean();
                ZeroCrossingRate zcr = new ZeroCrossingRate(atdr.getNormalizedAmplitudes(),1);
                StandardDeviation stdv = new StandardDeviation();
                stdv.setValues(atdr.getNormalizedAmplitudes());
                ArrayRankDouble ard = new ArrayRankDouble();
                mean.setValues(atdr.getNormalizedAmplitudes());
                SpectralCentroid sp = new SpectralCentroid(atdr.getNormalizedAmplitudes()); 
                PitchHandler ph = new PitchHandler();
                
                writer.print(wavFile.getAudioFormat());
                writer.print(","+wavFile.getSampleRate());
                writer.print(","+wavFile.getBitsPerSample());
                writer.print(","+wavFile.getBlockAlign());
                writer.print(","+wavFile.getByteRate());
                writer.print(","+wavFile.getChannels());
                writer.print(","+wavFile.getChunkSize());
                writer.print(","+ftdr.getFftSampleSize());
                writer.print(","+ftdr.getFramesPerSecond());
                writer.print(","+ftdr.getNumFrames());
                writer.print(","+ftdr.getNumFrequencyUnit());
                writer.print(","+ftdr.getUnitFrequency());
                writer.print(","+atdr.getTimeStep());
                writer.print(","+ard.getMaxValueIndex(atdr.getNormalizedAmplitudes()));
                writer.print(","+ard.getMinValueIndex(atdr.getNormalizedAmplitudes()));
                writer.print(","+mean.evaluate());
                writer.print(","+zcr.evaluate());
                writer.print(","+stdv.evaluate());
                writer.print(","+sp.evaluate());
                writer.print(","+audioType);
                writer.println();
            }
            catch (Exception e){
                e.printStackTrace();
            }
            audioFormat[i] = audioStream[i].getFormat();
            listModel.addElement(totalRecordings[i]);
            }

        list = new JList(listModel);
        list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        list.setSelectedIndex(0);
        writer.close();
        
        
        scroll = new JScrollPane(list, 
                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, 
                JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        
        
        scroller = new JScrollPane(output, 
                JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, 
                JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        
        buttonPanel.setLayout(box);
        
        add(upperPanel);
        add(bottomPanel);
        //upperPanel.add(selection);
        upperPanel.add(scroll);
        upperPanel.add(featureSelectPanel);
        upperPanel.add(buttonPanel);
        buttonPanel.add(j48);
        buttonPanel.add(smo);
        buttonPanel.add(zeroR);
        buttonPanel.add(naiveBayes);
        buttonPanel.add(clear);
        
        JLabel label = new JLabel("Output:");        
        bottomPanel.add(label);     //add label
        bottomPanel.add(scroller);  //and scroll panel
   
    }//end constructor
    
    /** configureFile
     * @brief writes out the attributes list in the .arff format so that weka can 
     *          interpret each value correctly. It includes a string name and type characteristic.
     */
    public void configureFile(){
                writer.println("@relation jAudio");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Audio Format\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Sample Rate\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Bits Per Sample\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Block Align\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Byte Rate\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Channels\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Chunk Size\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"FFT Sample Size\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Frames Per Second\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Number of Frames\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Number of Frequency Units\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Unit Frequency\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Time Step\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Maximum Amplitude\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Minimum Amplitutde\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Mean\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Zero Crossing Rate\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Standard Deviation\" NUMERIC");
                writer.print("@ATTRIBUTE");
                writer.println("\"Spectral Centroid\" NUMERIC");
                writer.print("@ATTRIBUTE ");
                writer.println("\"Audio Type\" {MUSIC,SPEECH}");
                writer.println("@DATA");
    }//end configureFile
    
    /** displayFindings
     * @brief outputs learning findings to the output text area.
     * @see j48Listener
     * @see smoListener
     * @see zeroRListener
     * @see naiveBayesListener
     */
    public void displayFindings() {
          //output
       BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
 
                String line=null;
                try{
                    while((line=input.readLine()) != null) {
                       // System.out.println(line);
                        output.append(line+"\n");
                    }//end while
                }
                catch(IOException ioe) {}
                
//                try{
//                    int exitVal = pr.waitFor();
//                    System.out.println("Exited with error code "+exitVal);
//                }catch(Exception ie){
//                } 
    
    }
    
    /** clearListener
     * @brief controls the output area and clears away excessive logging
     */
   private class clearListener implements ActionListener {
        
        public void actionPerformed(ActionEvent e) {
            output.setText(" ");
        }//end ap
    }//end clearListener
   
   /** j48Listener
    * @biref one machine learning statistic
    */
   private class j48Listener implements ActionListener {
       
       public void actionPerformed(ActionEvent e){
           try{
                pr = rt.exec("java weka.classifiers.trees.J48 -t audioFeatures.arff -i");
                output.setText("");
                displayFindings();
           }
           catch(IOException ioe){
               
           }
       }//end ap
   }//end j48Listener
   
   /** smoListener
    * @biref one machine learning statistic
    */
   public class smoListener implements ActionListener {
       
       public void actionPerformed(ActionEvent e){
           try{
            pr = rt.exec("java weka.classifiers.functions.SMO -C 1.0 -L 0.001 -P 1.0E-12 -N 0 -V -1 -W 1 -t audioFeatures.arff");
            output.setText("");
            displayFindings();
           }
           catch(IOException ioe){}
       }//end ap
   }//end smoListener
   
   /** zeroRListener
    * @biref one machine learning statistic
    */
   public class zeroRListener implements ActionListener {
       
       public void actionPerformed(ActionEvent e){
           try{
            pr = rt.exec("java weka.classifiers.rules.ZeroR  -t audioFeatures.arff");
            output.setText("");
            displayFindings();
           }
           catch(IOException ioe) {}
       }//end ap
   }//end zeroRListener
   
   /** naiveBayesListener
    * @biref one machine learning statistic
    */
   public class naiveBayesListener implements ActionListener {
       public void actionPerformed(ActionEvent e){
           try{
            pr = rt.exec("java weka.classifiers.bayes.NaiveBayes -t audioFeatures.arff -i"); 
            output.setText("");
            displayFindings();
           }
           catch(IOException ioe) {}
       }//end ap
   }//end naiveBayesListener
   
    /** main
     * @biref runs the program
     * @param args holds the parameters entered in via command line in an array
     */
    public static void main(String args[]){
       // System.out.println("Hello World!");
        SwingUtilities.invokeLater(new Runnable(){
            public void run() {
                AudioFeature app = new AudioFeature();
                app.setVisible(true);
                
            }
        });
    }


}
