/**
 * Project: Assignment 1 (Intensity Matrixes and Color Code Matrixes)
 * @author Terence Schumacher
 * @version 1.1
 * @since 2014-7-2
 * 
*/

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.lang.Object.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
import javax.imageio.ImageIO;

/** Read Image
 * @brief reads an image pixel by pixel and distributes their combined red, 
 *        green, and blue values into a histogram array. The Arrays are then 
 *        transferred into a 2D array which can be referred to as a Matrix. This
 *        Matrix is then written to a text file for future usage. 
 */
public class readImage
{
  int imageCount = 1;
  double intensityBins [] = new double [26];
  double intensityMatrix [][] = new double[100][26];
  double colorCodeBins [] = new double [64];
  double colorCodeMatrix [][] = new double[100][64];

  /* Read Image
     Each image is retrieved from the file.  The height and width are found for 
     the image and the getIntensity and
   * getColorCode methods are called.
  */
  public readImage()
  {
    while(imageCount < 101){    //begin the loop
      try
      {
         // System.out.println("Try Reading " + imageCount);
         BufferedImage image = ImageIO.read(new File("src/images/"+imageCount+".jpg"));
        getIntensity(image, image.getHeight(),image.getWidth());
         //write value to intensityMatrix
        for (int i = 0; i < intensityBins.length; i++)
            intensityMatrix[imageCount-1][i] = intensityBins[i];   
        for (int i = 0; i < intensityBins.length; i++)   
            intensityBins[i] = 0;
 
        //write values to colorCodeMatrix
        getColorCode(image, image.getHeight(), image.getWidth());
        for (int i = 0; i < colorCodeBins.length; i++)  
            colorCodeMatrix[imageCount-1][i] = colorCodeBins[i];
        for (int i = 0; i < colorCodeBins.length; i++)
            colorCodeBins[i] = 0;                              
        
        imageCount++;  
      } 
      catch (IOException e)
      {
        System.out.println("Error occurred when reading the file.");
      }
    }
    writeIntensity();
    writeColorCode();
  }//end constructor
  
  //intensity method 
/** GetIntensity
 * @brief
 * @param image
 * @param height
 * @param width
 */
  public void getIntensity(BufferedImage image, int height, int width){

      for (int i = 0; i < width; i++){
          for ( int j = 0; j < height; j++){
          //get the rgb values from the pixel
            Color c = new Color(image.getRGB(i,j));
            double red = 0.299*(c.getRed());
            double green = 0.587*(c.getGreen());
            double blue = 0.114*(c.getBlue());
    // get I = 0.299(R) + 0.587(G) + 0.114(B)
            double I = red + green + blue;
         // add to specific histogram bin
            addToIntensityHistogram(I);
          }//end for j
      }//end for i
      //check total pixel values
      double histogramValues = 0;
      for (double x : intensityBins)
          histogramValues += x;
      assert(histogramValues == height*width);
  }//end getIntensity
 
  /** getColorCode
   * @brief gets the Color Code coordinating with each pixel within the buffered Image
   * @param image BufferedImage representing the image we are compiling the histogram for
   * @param height
   * @param width
   */
  public void getColorCode(BufferedImage image, int height, int width){
      //get red green and blue
         for (int i = 0; i < width; i++){
          for ( int j = 0; j < height; j++){
            Color c = new Color(image.getRGB(i,j));
            
            double red = (c.getRed());
            String redBinary = String.format("%8s", Integer.toBinaryString((int)red)).replace(' ', '0');
            
            double green = (c.getGreen());
            String greenBinary = String.format("%8s", Integer.toBinaryString((int)green)).replace(' ', '0');

            double blue = (c.getBlue());
            String blueBinary = String.format("%8s", Integer.toBinaryString((int)blue)).replace(' ', '0');

             String temp6Byte = redBinary.substring(0, 2) + greenBinary.substring(0,2) + blueBinary.substring(0,2);
             int tempBit = Integer.parseInt(temp6Byte, 2);
             colorCodeBins[tempBit]++;

          }//end j
         }//end i
  }//end getColorCode
  
  
  ///////////////////////////////////////////////
  //add other functions you think are necessary//
  ///////////////////////////////////////////////
  /**
   * Add To Intensity Histogram
   */
  public void addToIntensityHistogram(double I){
      // divide by 10 and stick the integer into the corresponding histogram bin 
      int index = (int)I / 10;
      intensityBins[index]++;
  }//end addToHistogram
 
  //This method writes the contents of the colorCode matrix to a file named colorCodes.txt.
  /**
   * Write Color Code
   */
  public void writeColorCode() {
    /////////////////////
    ///your code///
    /////////////////
      //write colorCodeMatrix to the text file
      try{
      PrintWriter writer = new PrintWriter("colorCode.txt");
      for (int i = 0; i < 100; i++){
          for (int j = 0; j < 64; j++){
            writer.print(colorCodeMatrix[i][j] + " ");
          }
          writer.println();
      }

        writer.close();
      }
      catch (FileNotFoundException e){}
  }
  
  //This method writes the contents of the intensity matrix to a file called intensity.txt
    /**
   *  Write Intensity
   */
  public void writeIntensity(){
    /////////////////////
    ///your code///
    /////////////////
      //write intensityMatrix to file
      try{
        PrintWriter writer = new PrintWriter("intensity.txt");
        for (int i = 0; i < 100; i++){
           for (int j = 0; j < 26; j++){
            writer.print(intensityMatrix[i][j] + " ");}
           writer.println();
        }
            writer.close();
         }
       catch (FileNotFoundException e){}
  }
  
    /**
   * Main (Logging and Testing Purposes)
   */
  public static void main(String[] args)
  {
    new readImage();
  }

}
