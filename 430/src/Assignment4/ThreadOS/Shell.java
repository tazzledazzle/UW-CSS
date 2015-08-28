package Assignment4.ThreadOS;

// PingPong 4 4 & PingPong 5 5 & PingPong 6 6
// PingPong 4 4 ; PingPong 5 5 ; PingPong 6 6
// PingPong 4 4 ; PingPong 5 5 & PingPong 6 6

class Shell extends Thread
{
    private String name = "none";
    public Shell()
    {
        SysLib.cout("Welcome to the Shell!~~~~");
    }
    public Shell(String args[])
    {
        name = args[1];
        SysLib.cout("Welcome to the Shell!~~~");
        SysLib.cout("Shell Constructor running. name = " + name + "\n");
    }

    public boolean checkExit(String commands[])
    {
        return !(commands[0].compareTo("exit") == 0);
    }
    public void run()
    {
        boolean runnable = true;
        int count = 1;
        while(runnable)
        {
            SysLib.cout("Shell["+ count +"]: ");
            StringBuffer buffer = new StringBuffer();
            SysLib.cin(buffer);
            String[] commands = SysLib.stringToArgs(buffer.toString());
            if(commands.length < 1)
            {
                continue;   //reprint Shell[i]:
            }
            runnable = checkExit(commands);
            if(!runnable)   // if "exit" entered
                 break;
            SysLib.cout("\n");
            count += 1;

            String[] cmdSplitSemi = buffer.toString().split(";");
            String[] cmdSplitAmp = buffer.toString().split("&");
            String cmdSplitMulti = buffer.toString();

            processCommands(cmdSplitAmp, cmdSplitSemi, cmdSplitMulti);
        }
        SysLib.cout("Bye...\n");
        SysLib.sync();
        SysLib.exit();
    }

    public void processCommands(String [] cmdSplitAmp, String [] cmdSplitSemi, String cmdSplitMulti)
    {
        boolean checkAmp = false, checkSemi = false;
        if(cmdSplitSemi.length > 1) checkSemi = true;
        if(cmdSplitAmp.length > 1) checkAmp = true;

        if (checkAmp && checkSemi) {    //if multiple argments
            execComMulti(cmdSplitMulti);
        }
        else if (checkAmp) {    // &
            execComAmp(cmdSplitAmp);
        }
        else // ;
            execComSemi(cmdSplitSemi);
    }
    
    public void execComSemi(String [] args)
    {
        for (int i = 0; i < args.length; i++){
            String[] commands = SysLib.stringToArgs(args[i]);
            SysLib.cout(commands[0] + ": \n\t");
            if (SysLib.exec(commands) < 0)
                return;
            SysLib.join();
        }
    }

    public void execComAmp(String [] args)
    {
        int processCount = 0;
        for (int i = 0; i < args.length; i++){
            String[] commands = SysLib.stringToArgs(args[i]);

            SysLib.cout(commands[0] + "\n\t");
            if (SysLib.exec(commands) < 0)
                processCount--;
            processCount++; //otherwise increment
        }

        for (int j = 0; j < processCount; j++)  //collect children
            SysLib.join();
    }

    public void execComMulti(String args)
    {
        String[] cmdSplitSemi = args.toString().split(";");

        for (int i = 0; i < cmdSplitSemi.length; i++)
        {
            SysLib.cout(cmdSplitSemi[i]+"\n");
            String[] cmdSplitAmp = cmdSplitSemi[i].split("&");
            if (cmdSplitAmp.length == 1)
                execCMD(cmdSplitSemi[i]);
            else
                execComAmp(cmdSplitAmp);
        }
    }

    public void execCMD(String argument)
    {
        String [] args = SysLib.stringToArgs(argument);
        if (SysLib.exec(args) > 0)
            SysLib.join();
    }
}