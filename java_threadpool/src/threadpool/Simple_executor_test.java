import java.util.ArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Simple_executor_test {

    private static final int NTHREADS = 10;

    public static void main(String[] args) {

		double result=0;


//		Integral_callable integral;
//		try {
//
//			for (double i = 0; i <6 ; i++) {
//				integral = new Integral_callable(-2,-1+i,1);
//				result+=integral.call();
//			}
//			System.out.println(result);
//
//		} catch (Exception e) {
//			e.printStackTrace();
//		}


		ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
		//ExecutorService executor = Executors.newCachedThreadPool();

		ArrayList<Future<Double>> call_list= new ArrayList<>();
		for(int i = 0; i<202; i++)
			call_list.add(executor.submit(new Integral_callable(-2,-1+i,1)));

		for(Future<Double> dub:call_list){
			try{
				System.out.println(dub.get());
				result+=dub.get();
			}
			 catch (InterruptedException | ExecutionException e) {
				e.printStackTrace();
			} finally{executor.shutdown();}
		}
		// This will make the executor accept no new threads
		// and finish all existing threads in the queue
		//executor.shutdown();

		// Wait until all threads finish
		while (!executor.isTerminated());
		System.out.println(result);
		System.out.println("Finished all threads");

		/////////////////////////////////////////////////

		int[] arr = new int[10];
		for (int i = 0; i <arr.length ; i++) {
			arr[i] = (int)(Math.random() * 100);
		}

		for (int i2 : arr) System.out.println(i2);


		MergeSort merging = new MergeSort(10);
		merging.sort(arr);

		for (int i1 : arr) System.out.println(i1);
	}
} 
