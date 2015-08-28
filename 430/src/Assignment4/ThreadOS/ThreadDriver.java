package Assignment4.ThreadOS;

public class ThreadDriver
{
	public static void main (String[] argsv)
	{
		 String[] args = new String[2];

		args[0] = "ping"; args[1] = "10000";
		new PingPong(args).start();

		args[0] = "PING"; args[1] = "90000";
		new PingPong(args).start();
	}
}