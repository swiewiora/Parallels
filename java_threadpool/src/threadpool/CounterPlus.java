public class CounterPlus implements Runnable {
    
  private Integral_callable integral;

  public CounterPlus(Integral_callable integral) {
    this.integral = integral;
  }

  public void run() {

      try {
          integral.call();
      } catch (Exception e) {
          e.printStackTrace();
      }
  }
}
