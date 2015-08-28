
/**
 * Created by tazzledazzle on 2/16/15.
 *
 * Computational Work
 * computes fibonacci up to 45
 *
 */
class TestThread3a extends Thread {

    public TestThread3a() {}
    public int fibonacci(int n){
        if (n == 0){
            return 0;
        }
        else if (n == 1){
            return 1;
        }
        else
            return fibonacci(n-1) + fibonacci(n-2);
    }
    public void run() {
        int sum = 0;
        for (int i = 0; i < 100; i++){
            for (int j = 0; j < 35; j++){
                sum += fibonacci(j);
            }
            sum = 0;
            for (int j = 0; j < 35; j++){
                sum += fibonacci(j);
            }
            sum = 0;
            for (int j = 0; j < 35; j++){
                sum += fibonacci(j);
            }

        }
        SysLib.exit();
    }
}
