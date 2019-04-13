import java.util.concurrent.Callable;

public class Integral_callable implements Callable<Double>{


    private double dx;
    private double xp;
    private double xk;
    public int N;

    public Integral_callable(double xp, double xk, double dx) {

        this.xp = xp;
        this.xk = xk;
        this.N = (int) Math.ceil((xk-xp)/dx);
        this.dx = (xk-xp)/N;
        System.out.println("Creating an instance of Integral_callable");
        System.out.println("xp = " + xp + ", xk = " + xk + ", N = " + N);
        System.out.println("dx requested = " + dx + ", dx final = " + this.dx);

    }

    private double getFunction(double x) {
        return (4*x)+0.5;
    }

    public double compute() {
        double integral = 0;
        int i;
        for(i=0; i<N; i++){
            double x1 = xp+i*dx;
            double x2 = x1+dx;
            integral = ((getFunction(x1) + getFunction(x2))/2.)*dx;
        }
        return integral;
    }

    @Override
    public Double call() throws Exception {

        double integral = compute();
        System.out.println("Partial integral: " + integral);
        return integral;
    }


}