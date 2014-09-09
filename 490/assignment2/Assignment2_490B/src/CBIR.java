/** 
 * Project 1
 * @author Terence Schumacher
 * @version 1.0
 * @brief Content-Based Image Retrieval. This is completed by executing two methods:
 *      By the image's intensity and by the image's color code. 
 * To Run:
 *      1. Open the .jar file
 *      2. 
*/

//import java.awt.BorderLayout;
//import java.awt.Graphics2D;
//import java.awt.Image;
//import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
//import java.awt.image.BufferedImage;
import java.awt.*;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.*;
import java.io.*;
//import java.util.ArrayList;
//import java.util.Collection;
//import java.util.HashMap;
//import java.util.List;
import java.util.Map;
//import java.util.Set;
//import java.util.TreeSet;
//import javax.imageio.ImageIO;
import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
//import javax.swing.Box;
//import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
//import javax.swing.JToolBar;
import javax.swing.SwingUtilities;
//import javax.swing.SwingWorker;
import javax.swing.*;



public class CBIR extends JFrame{
    
    private JLabel photographLabel = new JLabel();  //container to hold a large 
    private JButton [] button; //creates an array of JButtons
    private JCheckBox [] checkbox;
    private int [] buttonOrder = new int [101]; //creates an array to keep up with the image order
    private Double [] imageSize = new Double[101]; //keeps up with the image sizes
    private GridLayout gridLayout1;
    private GridLayout gridLayout2;
    private GridLayout gridLayout3;
    private GridLayout gridLayout4;
    private JPanel panelBottom1;
    private JPanel panelBottom2;
    private JPanel panelTop;
    private JPanel buttonPanel;
    private JCheckBox relevanceCheck;
    private JPanel [] subButtonPanel = new JPanel[101];
    private Double [][] intensityMatrix = new Double [101][26];
    private Double [][] colorCodeMatrix = new Double [101][64];
    private Map <Double , LinkedList<Integer>> map;
    int picNo = 0;
    int imageCount = 1; //keeps up with the number of images displayed since the first page.
    int pageNo = 1;
    private Double [][] relevanceMatrix = new Double [101][89];
    private Double [][] selectionMatrix = new Double [101][89];

    //readImage readIMG = new readImage();
    
    public static void main(String args[]) {
        
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                readImage image = new readImage();
                //image.writeColorCode();
                //image.writeIntensity();
                CBIR app = new CBIR();
                app.setVisible(true);
            }
        });
    }//end main
    
    
    /** 
     * Main object constructor. This constructs all of the facets of the JFrame/JWindow.
     */
    public CBIR() {
      //The following lines set up the interface including the layout of the buttons and JPanels.
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Icon Demo: Please Select an Image");        
        panelBottom1 = new JPanel();
        panelBottom2 = new JPanel();
        panelTop = new JPanel();
        buttonPanel = new JPanel();
        gridLayout1 = new GridLayout(4, 5, 5, 5);
        gridLayout2 = new GridLayout(2, 1, 5, 5);
        gridLayout3 = new GridLayout(1, 2, 5, 5);
        gridLayout4 = new GridLayout(4, 2, 5, 5);
        setLayout(gridLayout2);
        panelBottom1.setLayout(gridLayout1);
        panelBottom2.setLayout(gridLayout1);
        panelTop.setLayout(gridLayout3);
        add(panelTop);
        add(panelBottom1);
        photographLabel.setVerticalTextPosition(JLabel.BOTTOM);
        photographLabel.setHorizontalTextPosition(JLabel.CENTER);
        photographLabel.setHorizontalAlignment(JLabel.CENTER);
        photographLabel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));
        buttonPanel.setLayout(gridLayout4);
        panelTop.add(photographLabel);

        panelTop.add(buttonPanel);
        JButton previousPage = new JButton("Previous Page");
        JButton nextPage = new JButton("Next Page");
        JButton intensity = new JButton("Intensity");
        JButton colorCode = new JButton("Color Code");
        JButton relevant = new JButton("Intensity/Color Code");
        relevanceCheck = new JCheckBox("Relevance");
        JButton reset = new JButton("Reset Images");
        buttonPanel.add(previousPage);
        buttonPanel.add(nextPage);
        buttonPanel.add(intensity);
        buttonPanel.add(colorCode);
        buttonPanel.add(relevant);
        buttonPanel.add(relevanceCheck);
        buttonPanel.add(reset);
        
        
        nextPage.addActionListener(new nextPageHandler());
        previousPage.addActionListener(new previousPageHandler());
        intensity.addActionListener(new intensityHandler());
        colorCode.addActionListener(new colorCodeHandler());
        relevant.addActionListener(new relevantHandler());
        reset.addActionListener(new resetHandler());
        relevanceCheck.addItemListener(new relevantCheckHandler());
        setSize(1100, 750);
        
        // this centers the frame on the screen
        setLocationRelativeTo(null);
        button = new JButton[101];
        checkbox = new JCheckBox[101];
        
        /*This for loop goes through the images in the database and stores them as icons and adds
         * the images to JButtons and then to the JButton array
        */
        for (int i = 1; i < 101; i++) {
            ImageIcon icon;
            icon = new ImageIcon("src/images/" + i + ".jpg");
             if(icon != null){
                
                button[i] = new JButton(icon);
                checkbox[i] = new JCheckBox("Relevant");
                button[i].addActionListener(new IconButtonHandler(i, icon));
                checkbox[i].addActionListener(new radioListener());
                checkbox[i].setActionCommand(String.valueOf(i));
                buttonOrder[i] = i;
                imageSize[i] =  (Double)(double)(icon.getIconHeight() *  icon.getIconWidth());
            }//end if
        }//end for
        readIntensityFile();
        readColorCodeFile();
        displayFirstPage();
              
        for (int i = 0; i < 101; i++){
            for (int j = 0; j < 89; j++){
                relevanceMatrix[i][j] = -1.0;
                selectionMatrix[i][j] = -1.0;
            }//end j
        }//end i
        normalizationCalculator();
    }//end CBIR Constructor
    
    /**This method opens the intensity text file containing the intensity matrix with the histogram bin values for each image.
     * The contents of the matrix are processed and stored in a two dimensional array called intensityMatrix.
    */
    public void readIntensityFile(){

      Scanner read;
         try{
             read = new Scanner(new File ("intensity.txt"));
             for (int i = 1; i < 101; i++){
                for (int j = 0; j < 26; j++){
                    intensityMatrix[i][j] = read.nextDouble();
                }//end for j
             }//end for i
         }
         catch(FileNotFoundException EE){
           System.out.println("The file intensity.txt does not exist");
         }//end try/catch
    }//end readIntensityFile
    
    /**This method opens the color code text file containing the color code matrix with the histogram bin values for each image.
     * The contents of the matrix are processed and stored in a two dimensional array called colorCodeMatrix.
    */
    private void readColorCodeFile(){
  
      Scanner read;
         try{
           read = new Scanner(new File ("colorCode.txt"));       
           for (int i = 1; i < 101; i++){
                for (int j = 0; j < 64; j++){
                    colorCodeMatrix[i][j] = read.nextDouble();
                 }//end for j
              }//end for i
         }
         catch(FileNotFoundException EE){
           System.out.println("The file colorCode.txt does not exist");
         }//end try/catch
    }//end readColorCodeFile
    
    /**This method displays the first twenty images in the panelBottom.  The for loop starts at number one and gets the image
     * number stored in the buttonOrder array and assigns the value to imageButNo.  The button associated with the image is 
     * then added to panelBottom1.  The for loop continues this process until twenty images are displayed in the panelBottom1
    */
    private void displayFirstPage(){
      int imageButNo = 0;
      panelBottom1.removeAll(); 
      for(int i = 1; i < 21; i++){
        imageButNo = buttonOrder[i];
        panelBottom1.add(button[imageButNo]);
        if (relevanceCheck.isSelected())
            panelBottom1.add(checkbox[imageButNo]);
        imageCount ++;
      }//end for
      panelBottom1.revalidate();  
      panelBottom1.repaint();

    }//end displayFirstPage

    /** relevantCheckHandler
     * @brief enables/disables relevance check boxes for images in database. if selected,
     *          the check boxes are displayed. Deselection removes them from the bottom panel, but does
     *          not reset their selections.
     * @post disabling the checkbox display does not clear out their selections, only the reset button does so.
     */
    private class relevantCheckHandler implements ItemListener {

        public void itemStateChanged(ItemEvent e) {
            if(e.getStateChange() == ItemEvent.SELECTED){
               // System.out.println("Checked!");
                for (int i = 1; i < 101; i++) {buttonOrder[i] = i;
                    if (checkbox[i].isEnabled()){
                        checkbox[i].setSelected(false);
                    }//end if
                }//end for
                    imageCount = 1;
                int imageButNo = 0;
                panelBottom1.removeAll(); 
                for(int i = 1; i < 21; i++){
                    imageButNo = buttonOrder[i];

                    panelBottom1.add(button[imageButNo]);
                    if (relevanceCheck.isSelected())
                        panelBottom1.add(checkbox[imageButNo]);

                    imageCount ++;
                }//end for
                panelBottom1.revalidate();  
                panelBottom1.repaint();

            }
            else{
             //   System.out.println("Unchecked!");
               //repopulate buttons
                for (int i = 1; i < 101; i++) {buttonOrder[i] = i;
                    if (checkbox[i].isEnabled()){
                        checkbox[i].setSelected(false);
                    }//end if
                }//end for
                    imageCount = 1;
                int imageButNo = 0;
                panelBottom1.removeAll(); 
                for(int i = 1; i < 21; i++){
                    imageButNo = buttonOrder[i];

                    panelBottom1.add(button[imageButNo]);
                    if (relevanceCheck.isSelected())
                        panelBottom1.add(checkbox[imageButNo]);

                    imageCount ++;
                }//end for
                panelBottom1.revalidate();  
                panelBottom1.repaint();
            }//end if 
        }//end itemStateChanged

    }//end relevantCheckHandler
    
    /*This class implements an ActionListener for each iconButton.  When an icon button is clicked, the image on the 
     * the button is added to the photographLabel and the picNo is set to the image number selected and being displayed.
    */ 
    private class IconButtonHandler implements ActionListener{
      int pNo = 0;
      ImageIcon iconUsed;

      IconButtonHandler(int i, ImageIcon j){        //This is what populates
        pNo = i;
        iconUsed = j;  //sets the icon to the one used in the button
      }//end IconButtonHandler constructor

      public void actionPerformed( ActionEvent e){      //This is what sets the selected icon
        photographLabel.setIcon(iconUsed);
        picNo = pNo;
      }//end actionPerformed
    }//end iconButtonHandler
    
    /*This class implements an ActionListener for the nextPageButton.  The last image number to be displayed is set to the 
     * current image count plus 20.  If the endImage number equals 101, then the next page button does not display any new 
     * images because there are only 100 images to be displayed.  The first picture on the next page is the image located in 
     * the buttonOrder array at the imageCount
    */
private class nextPageHandler implements ActionListener{

      public void actionPerformed( ActionEvent e){
          int imageButNo = 0;
          int endImage = imageCount + 20;
          if(endImage <= 101){
            panelBottom1.removeAll(); 
            for (int i = imageCount; i < endImage; i++) {
                imageButNo = buttonOrder[i];
                panelBottom1.add(button[imageButNo]);
            if (relevanceCheck.isSelected())
                panelBottom1.add(checkbox[imageButNo]);
                imageCount++;
            }//end for
            panelBottom1.revalidate();  
            panelBottom1.repaint();
          }//end if
      }//end actionPerformed
}//end nextPageHandler
    
    /*This class implements an ActionListener for the previousPageButton.  The last image number to be displayed is set to the 
     * current image count minus 40.  If the endImage number is less than 1, then the previous page button does not display any new 
     * images because the starting image is 1.  The first picture on the next page is the image located in 
     * the buttonOrder array at the imageCount
    */
    private class previousPageHandler implements ActionListener{

      public void actionPerformed( ActionEvent e){
          int imageButNo = 0;
          int startImage = imageCount - 40;
          int endImage = imageCount - 20;
          if(startImage >= 1){
            panelBottom1.removeAll();
            /*The for loop goes through the buttonOrder array starting with the startImage value
             * and retrieves the image at that place and then adds the button to the panelBottom1.
            */
            for (int i = startImage; i < endImage; i++) {
                  imageButNo = buttonOrder[i];
                  panelBottom1.add(button[imageButNo]);
                  if (relevanceCheck.isSelected())
                    panelBottom1.add(checkbox[imageButNo]);
                  imageCount--;
            }//end for
            panelBottom1.revalidate();  
            panelBottom1.repaint();
          }//end if
      }//end actionPerformed
    }//end previousPageHandler
    
    /** Manhattan Distance 
     * @brief Helps with the computation of the manhattan distance for each image selected.
     * @param base the base image histogram comparing to
     * @param ith the comparison image histogram
     * @param imageSizeI base image's size
     * @param imageSizeK comparison image's size
     * @param binSize size of histograms
     * @return tempTotal amount of difference between the two images
     */
public double manhattanDistance(Double[] base, Double[] ith, Double imageSizeI, 
                                                Double imageSizeK, int binSize){
    Double tempTotal = 0.0;
    for (int i = 0; i < binSize; i++){
        Double iRatio = base[i]/imageSizeI;
        Double kRatio = ith[i]/imageSizeK;       
        tempTotal += Math.abs(iRatio - kRatio);
    }//end for
    
    return tempTotal;
}//end manhattanDistance  

/** Distance Metric
 * @brief specific distance metric utilizing the normalized weight
 * @param base the base image histogram comparing to
 * @param ith the comparison image histogram
 * @param imageSizeI base image's size
 * @param imageSizeK comparison image's size
 * @param binSize size of histograms
 * @param w the normalized weight array
 * @return tempTotal amount of difference between the two images
 */
public double distanceMetric(Double[] base, Double[] ith, Double imageSizeI, 
                                                Double imageSizeK, int binSize, double [] w){
    Double tempTotal = 0.0;
    for (int i = 0; i < binSize; i++){
        Double iRatio = base[i]/imageSizeI;
        Double kRatio = ith[i]/imageSizeK;       
        tempTotal += (w[i] * Math.abs(iRatio - kRatio));
    }//end for
    
    return tempTotal;
}//end distanceMetric  

/** Normalization Calculator
 * @brief normalizes a combination of the intensity matrix and the color code matrix in order to calculate both.
 */
public void normalizationCalculator(){
  Double [][] featureSet = new Double[101][89];
  Double [] average = new Double[89];
  Double [] standardDev = new Double[89];
  
  Arrays.fill(average, 0.0);
  Arrays.fill(standardDev, 0.0);
  
      //set all of the photo bins into one 2d array
    for (int j = 1; j < 101; j++){
        for(int i = 0; i < 25; i++){
            featureSet[j][i] = intensityMatrix[j][i]/imageSize[j];
        }//end for
        for (int i = 25; i < 89; i++ ){
            featureSet[j][i] = colorCodeMatrix[j][i -25]/imageSize[j];
        }//end for
//        System.out.println("Intensity: \n" + Arrays.toString(intensityMatrix[j]));
//        System.out.println("Color Code: \n"+ Arrays.toString(colorCodeMatrix[j]));
//        System.out.println("Combination: \n" + Arrays.toString(featureSet[j]));
    }//end for j
    
    //calc average
    for (int j = 0; j < 89; j++){
        for (int i = 1; i < 101; i++){
            average[j] += featureSet[i][j];
        }//end i
        average[j] /= 100;
    }//end j
    
  //  System.out.println("Average:  \n" + Arrays.toString( average));
    
    //calc standard dev.
    for (int j = 0; j < 89; j++){
        for (int i = 1; i < 101; i++){
            standardDev[j] += Math.pow(Math.abs(featureSet[i][j] - average[j]),2);
           
        }//end i
           standardDev[j] /= 100;   //size - 1
           standardDev[j] = Math.sqrt(standardDev[j]);
           
    }//end j
    
    //System.out.println("Standard Deviation: \n" + Arrays.toString(standardDev));
    
    //check 0 case
    double min;
    if (standardDev[0] != 0.0)
         min = standardDev[0];
    else
        min = 1;
    for (int i = 1; i < 89; i++){
        if ((min > standardDev[i])&& (standardDev[i] != 0.0))
            min = standardDev[i];
    }//end if
  //  System.out.println("Minimum: " + min);
    
    //modify all zero results
    for (int i = 0; i < 89; i++){
        if ((standardDev[i] == 0.0)&&(average[i] != 0.0)){
            standardDev[i] = min*0.5;
        }//end if

     }//end for

   // System.out.println("Standard Deviation Revised: \n" + Arrays.toString(standardDev));
    
    //normalize featureSet
  //  System.out.println("Relevance Matrix: \n");
    for (int i = 1; i < 101; i++){
        for (int j = 0; j < 89; j++){
            if (standardDev[j] == 0.0){
                relevanceMatrix[i][j] = 0.0;
            }
            else
                relevanceMatrix[i][j] = (featureSet[i][j] - average[j])/standardDev[j];
        }//end for j
       // System.out.println( Arrays.toString(relevanceMatrix[i]));
    }//end for i
    
//    for (int i = 1; i < 101; i++){
//        System.out.println("image"+i+"\n"+Arrays.toString(relevanceMatrix[i]));
//    }
}//end normalizationCalculator

/** Relevance Calculator
 * @brief calculates the intensity + color code on the normalized matrix
 */
public void relevanceCalculator(){
  Double [] average = new Double[89];
  Double [] standardDev = new Double[89];
  Double [] updatedWeight = new Double[89];
  double [] normalizedWeight = new double[89];
  Double [][] relevantSelected = new Double[101][89];
  
  for (int i = 1; i < 101; i++){
      for (int j = 0; j < 89; j++){
          relevantSelected[i][j] = -1.0; 
      }//end j
  }//end i

  Arrays.fill(average, 0.0);
  Arrays.fill(standardDev, 0.0);
  Arrays.fill(normalizedWeight, 0.0);
 
    //find selected values
  int index = 0;
    for (int i = 1; i < 101; i++ ){
        if (selectionMatrix[i][0] != -1.0){
            for (int j = 0; j < 89; j++)
                relevantSelected[index][j] = selectionMatrix[i][j];
            
            // System.out.println("Added Image " + i + ":\n" + Arrays.toString(relevantSelected[index]));
             index++;
        }//end if   
    }//end for i
  
   // System.out.println("Size: " + index);
    
    //calc mean
    for (int j = 0; j < 89; j++ ){
        for (int i = 1; i < index; i++){
            average[j] += relevantSelected[i][j]; 
        }//end i
        average[j] /= index;
    }//end j
    
     // System.out.println("Average:  \n" + Arrays.toString( average));
    
    //calc standard dev.
    for (int j = 0; j < 89; j++){
        for (int i = 1; i < index; i++){
            standardDev[j] += Math.pow(Math.abs(relevantSelected[i][j] - average[j]),2);
           
        }//end i
           standardDev[j] /= (index-1);   //size - 1
           standardDev[j] = Math.sqrt(standardDev[j]);
           
    }//end j
    
  //  System.out.println("Standard Deviation: \n" + Arrays.toString(standardDev));
    
    //check 0 case
    double min;
    if (standardDev[0] != 0.0)
         min = standardDev[0];
    else
        min = 1;
    
    for (int i = 1; i < 89; i++){
        if ((min > standardDev[i])&& (standardDev[i] != 0.0))
            min = standardDev[i];
    }//end if
   // System.out.println("Minimum: " + min);
    
    //modify all zero results
    for (int i = 0; i < 89; i++){
        if ((standardDev[i] == 0.0)&&(average[i] != 0.0)){
            standardDev[i] = min*0.5;
        }//end if
 
     }//end for

   // System.out.println("Standard Deviation Revised: \n" + Arrays.toString(standardDev));
    
    //calc updated weight
    Double sum = 0.0;
    for (int i = 0; i < 89; i++){
        if (standardDev[i] != 0.0)
            updatedWeight[i] = 1/standardDev[i];
        else{
             updatedWeight[i] = 0.0;   
       }//end if
        sum += updatedWeight[i];
    }//end for i
    
    //calc new normalization
    for (int i = 0; i < 89; i++){
        normalizedWeight[i] = updatedWeight[i]/sum;
    }
    
   //Calc Distance and repopulate                                             
     double [] distance = new double [101];
          int pic = (picNo);
          double picSize = imageSize[pic+1];
          TreeMap<Double, Integer> treeMap = new TreeMap<Double, Integer>();

          for (int i = 1; i < 101; i++){
                try{
                distance[i] =  distanceMetric(relevanceMatrix[picNo], 
                            relevanceMatrix[i], picSize, imageSize[i], 89, normalizedWeight);
                  treeMap.put(distance[i], i);
                }
                catch(Exception ex){
                    System.out.println("Bad data @ " + i);
                    ex.printStackTrace();
                }//end try/catch
            }//end for
          
          //set button order
          int btnIndex = 1;
           for (Double key: treeMap.keySet()){
              buttonOrder[btnIndex] = treeMap.get(key);
              btnIndex++;
           }//end for key
           
            //repopulate the buttons           
             imageCount = 1;
            for (int i = imageCount; i < 21; i++) {
                    panelBottom1.add(button[buttonOrder[i]]);
                    
            }//end for i
            int imageButNo = 0;
          int endImage = imageCount + 20;
          if(endImage <= 101){
            panelBottom1.removeAll(); 
            for (int i = imageCount; i < endImage; i++) {
                    imageButNo = buttonOrder[i];
                    panelBottom1.add(button[imageButNo]);
                    panelBottom1.add(checkbox[imageButNo]);
                    imageCount++;
            }//end for i  
            panelBottom1.revalidate();  
            panelBottom1.repaint();
          
        }//end if picNo
          
}//end relevanceCalculator
    
    /*This class implements an ActionListener when the user selects the intensityHandler button.  The image number that the
     * user would like to find similar images for is stored in the variable pic.  pic takes the image number associated with
     * the image selected and subtracts one to account for the fact that the intensityMatrix starts with zero and not one.
     * The size of the image is retrieved from the imageSize array.  The selected image's intensity bin values are 
     * compared to all the other image's intensity bin values and a score is determined for how well the images compare.
     * The images are then arranged from most similar to the least.
     */
    private class intensityHandler implements ActionListener{
        
      public void actionPerformed( ActionEvent e){
          if (picNo == 0){
              System.out.println("You must select a photo!");
              return;
          }//end check
          
          double [] distance = new double [101];
          int pic = (picNo-1);
          double picSize = imageSize[pic+1];
          TreeMap<Double, Integer> treeMap = new TreeMap<Double, Integer>();
          
          for (int i = 1; i < 101; i++){
              //grab distance from manhattan
            try{
                distance[i] =  manhattanDistance(intensityMatrix[picNo], 
                        intensityMatrix[i], picSize, imageSize[i], 26);
                treeMap.put(distance[i], i);
                
            }
            catch(Exception ex){
                System.out.println("Bad data @ " + i);
                ex.printStackTrace();
            }//end try/catch
          }//end for
          
          int index = 1;
          for (Double key: treeMap.keySet()){
              buttonOrder[index] = treeMap.get(key);
              index++;
              
          }//end for key
       
          imageCount = 1;
          for (int i = imageCount; i < 21; i++) {
                    panelBottom1.add(button[buttonOrder[i]]);
          }//end for
           
          //repopulate buttons
          int imageButNo = 0;
          int endImage = imageCount + 20;
          if(endImage <= 101){
            panelBottom1.removeAll(); 
            for (int i = imageCount; i < endImage; i++) {
                    imageButNo = buttonOrder[i];
                    panelBottom1.add(button[imageButNo]);
                    if (relevanceCheck.isSelected())
                        panelBottom1.add(checkbox[imageButNo]);
                    imageCount++;
            }//end for
            panelBottom1.revalidate();  
            panelBottom1.repaint();
          }//end if endImage

          }//end actionPerformed
      }//end intensityHandler 
    
  
    
    /*This class implements an ActionListener when the user selects the colorCode button.  The image number that the
     * user would like to find similar images for is stored in the variable pic.  pic takes the image number associated with
     * the image selected and subtracts one to account for the fact that the intensityMatrix starts with zero and not one. 
     * The size of the image is retrieved from the imageSize array.  The selected image's intensity bin values are 
     * compared to all the other image's intensity bin values and a score is determined for how well the images compare.
     * The images are then arranged from most similar to the least.
     */ 
    private class colorCodeHandler implements ActionListener{

      public void actionPerformed( ActionEvent e){
          if (picNo == 0){
              System.out.println("You must select a photo!");
              return;
          }//end check
          
          double [] distance = new double [101];
          int pic = (picNo);
          double picSize = imageSize[pic+1];
          TreeMap<Double, Integer> treeMap = new TreeMap<Double, Integer>();

          for (int i = 1; i < 101; i++){
              //grab distance from manhattan
                try{
                distance[i] =  manhattanDistance(colorCodeMatrix[picNo], 
                            colorCodeMatrix[i], picSize, imageSize[i], 26);
                  treeMap.put(distance[i], i);
                }
                catch(Exception ex){
                    System.out.println("Bad data @ " + i);
                    ex.printStackTrace();
                }//end try/catch
            }//end for
          
          //set button order
          int index = 1;
           for (Double key: treeMap.keySet()){
              buttonOrder[index] = treeMap.get(key);
              index++;
           }//end for key
           
            //repopulate the buttons           
             imageCount = 1;
            for (int i = imageCount; i < 21; i++) {
                    panelBottom1.add(button[buttonOrder[i]]);
                    
            }//end for i
            int imageButNo = 0;
          int endImage = imageCount + 20;
          if(endImage <= 101){
            panelBottom1.removeAll(); 
            for (int i = imageCount; i < endImage; i++) {
                    imageButNo = buttonOrder[i];
                    panelBottom1.add(button[imageButNo]);
                    if (relevanceCheck.isSelected())
                        panelBottom1.add(checkbox[imageButNo]);
                    imageCount++;
            }//end for i  
            panelBottom1.revalidate();  
            panelBottom1.repaint();
          }//end if

      }//end actionPerformed
    }//end colorCodeHandler
   
/** relevantHandler
 * @brief handles the intensity/color code button. Calculates the relevance on the normalized
 *        matrix, if no images are selected for the relevance matrix the original matrix is used.
 */ 
private class relevantHandler implements ActionListener{
   
    public void actionPerformed(ActionEvent e){
      if (picNo == 0){
        System.out.println("You must select a photo!");
        return;
     }//end check
     
     if (relevanceCheck.isSelected())
        relevanceCalculator();
     else{ 
         int index = 101;
         Double [] average = new Double[89];
         Double [] standardDev = new Double[89];
         double [] normalizedWeight = new double[89];
         Double [] updatedWeight = new Double[89];
         Double [][] relevantSelected= new Double[101][89];
        
         for (int i = 1; i < 101; i++){
                for (int j = 0; j < 89; j++){
                     relevantSelected[i][j] = relevanceMatrix[i][j]; 
             }//end j
         }//end i
           
        Arrays.fill(average, 0.0);
        Arrays.fill(standardDev, 0.0);
        Arrays.fill(normalizedWeight, 0.0);
   
        //calc mean
        for (int j = 0; j < 89; j++ ){
            for (int i = 1; i < index; i++){
                average[j] += relevantSelected[i][j]; 
            }//end i
            average[j] /= index;
        }//end j
    
       //System.out.println("Average:  \n" + Arrays.toString( average));
    
        //calc standard dev.
        for (int j = 0; j < 89; j++){
            for (int i = 1; i < index; i++){
                standardDev[j] += Math.pow(Math.abs(relevantSelected[i][j] - average[j]),2);
        }//end i
            standardDev[j] /= (index-1);   //size - 1
            standardDev[j] = Math.sqrt(standardDev[j]);   
        }//end j
    
       // System.out.println("Standard Deviation: \n" + Arrays.toString(standardDev));
    
        //check 0 case
        double min;
        if (standardDev[0] != 0.0)
             min = standardDev[0];
        else
            min = 1;
    
        for (int i = 1; i < 89; i++){
            if ((min > standardDev[i])&& (standardDev[i] != 0.0))
                min = standardDev[i];
        }//end if
       // System.out.println("Minimum: " + min);
    
        //modify all zero results
        for (int i = 0; i < 89; i++){
            if ((standardDev[i] == 0.0)&&(average[i] != 0.0)){
                standardDev[i] = min*0.5;
            }//end if

         }//end for

       // System.out.println("Standard Deviation Revised: \n" + Arrays.toString(standardDev));

        //calc updated weight
        Double sum = 0.0;
        for (int i = 0; i < 89; i++){
            if (standardDev[i] != 0.0)
                updatedWeight[i] = 1/standardDev[i];
            else{
                 updatedWeight[i] = 0.0;   
           }//end if
            sum += updatedWeight[i];
        }//end for i

        //calc new normalization
        for (int i = 0; i < 89; i++){
            normalizedWeight[i] = updatedWeight[i]/sum;
        }


       //Calc Distance and repopulate                                             
         double [] distance = new double [101];
              int pic = (picNo);
              double picSize = imageSize[pic+1];
              TreeMap<Double, Integer> treeMap = new TreeMap<Double, Integer>();

              for (int i = 1; i < 101; i++){
                  //grab distance from manhattan
                    try{
                    distance[i] =  distanceMetric(relevanceMatrix[picNo], 
                                relevanceMatrix[i], picSize, imageSize[i], 89, normalizedWeight);
                      treeMap.put(distance[i], i);
                    }
                    catch(Exception ex){
                        System.out.println("Bad data @ " + i);
                        ex.printStackTrace();
                    }//end try/catch
                }//end for

              //set button order
              int btnIndex = 1;
               for (Double key: treeMap.keySet()){
                  buttonOrder[btnIndex] = treeMap.get(key);
                  btnIndex++;
               }//end for key

                //repopulate the buttons           
                 imageCount = 1;
                for (int i = imageCount; i < 21; i++) {
                        panelBottom1.add(button[buttonOrder[i]]);

                }//end for i
                int imageButNo = 0;
              int endImage = imageCount + 20;
              if(endImage <= 101){
                panelBottom1.removeAll(); 
                for (int i = imageCount; i < endImage; i++) {
                        imageButNo = buttonOrder[i];
                        panelBottom1.add(button[imageButNo]);
                        imageCount++;
                }//end for i  
                panelBottom1.revalidate();  
                panelBottom1.repaint();

            }//end if picNo

         }//end if
    }//end actionPerformed
}//end relevantHandler

/** resetHandler
 * @brief resets the JForm to it's original order/integrity/state. all values returned.
 */
private class resetHandler implements ActionListener{
   
    public void actionPerformed(ActionEvent e){
        relevanceCheck.setSelected(false);
        picNo = 0;
        photographLabel.setIcon(null);
        for (int i = 1; i < 101; i++) {buttonOrder[i] = i;
            if (checkbox[i].isEnabled()){
                checkbox[i].setSelected(false);
            }//end if
        }//end for
            imageCount = 1;
        int imageButNo = 0;
        panelBottom1.removeAll(); 
        for(int i = 1; i < 21; i++){
            imageButNo = buttonOrder[i];

            panelBottom1.add(button[imageButNo]);
            if (relevanceCheck.isSelected())
                panelBottom1.add(checkbox[imageButNo]);
            
            imageCount ++;
        }//end for
        panelBottom1.revalidate();  
        panelBottom1.repaint();
    }//end actionPerformed
}//end resetHandler

/** radioListener
 * @brief calculates which check box is clicked by adding the entries of the relevance matrix
 *          to another holder matrix.
 */
private class radioListener implements ActionListener {

    public void actionPerformed(ActionEvent e){
        //System.out.println("Image " +e.getActionCommand());
        int imageGrabbed = Integer.parseInt(e.getActionCommand());
        if (selectionMatrix[imageGrabbed][1] == -1.0){
            for (int i = 0; i < 89; i++)
                selectionMatrix[imageGrabbed][i] = relevanceMatrix[imageGrabbed][i];
            //System.out.println(Arrays.toString(selectionMatrix[imageGrabbed]));
        }//end if
        else{
         for (int i = 0; i < 89; i++)
             relevanceMatrix[imageGrabbed][i] = -1.0; 
            //System.out.println(Arrays.toString(relevanceMatrix[imageGrabbed]));
        }//end else

       // System.out.println(Arrays.toString(relevanceMatrix[Integer.parseInt(e.getActionCommand())]));
        //System.out.println("e "+e.toString());
    }//end actionperformed
}//end radiolistener


}//end Program
   

