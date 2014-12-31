========================
BUILD OUTPUT DESCRIPTION
========================

To Run:
There are two ways to do this:

-Executing the .jar

I am including all necessary documents regarding assignment 1 within a zip folder. In order to run the .jar file, you must first unzip the .zip file and within that folder will be the assignment1_490B.jar. Double clicking on this file will run the CBIR program. *Note: do not remove the .jar file from the unzipped directory and try to run the program. It will crash because it cannot find the image resources bundled within the unzipped folder. This is unexpected behavior and I have not found a foolproof solution to it.

-From the command line

To run the project from the command line, go to the unzipped folder's directory in your command line tool and type the following:

java -jar "Assignment1_490B.jar" 

To Use:
I used the sample code provided by the instructor, here are the steps for usage once the program has loaded:
-Scroll through photos using the previous and next page buttons.
-Select a photo for expanded viewing by clicking on the photo's icon.
-With a photo selected, press the intensity button to sort photographs according to that photo's intensity matrix.
-With a photo selected, press the color code button to sort photographs according to that photo's color code matrix.

Note:
* pressing the intensity or color code buttons without an image selected results in a console output informing you that you must select a photo in order to sort the photo library's content.
* Removal of the jar file from the same directory as the images will result in a program crash.
