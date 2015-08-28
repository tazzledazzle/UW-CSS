

/**
 * SummationThread
 * Runs the summation program
 * @version 1.0
 * @author Terence Schumacher
 * @created 1/22/2014
 */
public class SummationThread
{
    /** main
     * @brief Runs the summation Thread class
     * @param argv arguments passed to the summation child.
     * @return summation of argv.
     */
    public static void main(String argv[])
    {
        if (argv.length != 1)   //check valid argv length
            System.err.println("Invalid number of Arguments");

        String arg = argv[0];
        summation child = new summation(arg); //create new thread
        child.start();  //execute thread
        try
        {
            child.join();   // complete child thread
        }
        catch (InterruptedException intE) {}
    }
}


