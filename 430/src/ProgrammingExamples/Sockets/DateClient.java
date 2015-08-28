/**
 * Created by rtdimpsey on 1/14/15.
 */
import java.net.*;
import java.io.*;

public class DateClient
{
    public static void main(String[] args)
    {
        try
        {
            String line;
            Socket sock = new Socket("127.0.0.1", 6013);
            InputStream inStream = sock.getInputStream();
            BufferedReader bufRead = new BufferedReader(new InputStreamReader(inStream));
            while ( (line = bufRead.readLine()) != null)
            {
                System.out.println(line);
            }
            sock.close();
        }
        catch (IOException ioe)
        {
            System.out.println(ioe);
        }
    }
}
