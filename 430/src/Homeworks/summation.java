
/** summation
 * @brief Thread class to compute summation
 * @version 1.0
 * @author Terence Schumacher
 * @created 1/22/2014
 */
class summation extends Thread {

    //attributes
    private int sum;
    private String params;
    /** constructor
     * @param param number passed to summations to compute sum
     */
    summation(String param) { params = param; }

    /** Run
     * @brief runs the summation, calculates the sum and prints it out
     *
     */
    public void run()
    {
        int i, upper = Integer.valueOf(params);
        sum = 0;

        for (i = 1; i <= upper; i++)
            sum += i;

        System.out.println("Sum = " + sum);
    }
}