public class Main{
    public static int collatzSteps(int n){
        int steps = 0;
        while(n!=1){
            if(n%2==0){
                n = n/2;
                steps++;
            }
            else{
                n = (3*n)+1;
                steps++;
            }
        	//System.out.println("N: "+ n + " Steps: " + steps);
        }
        return steps;
    }
	public static void main(String[] args) {
	    int maiorSteps=0, numDoMaior=0, flash=0, allSteps = 0;
	    for(int i=1;i<10000000;i++){
	        flash = collatzSteps(i);
            if(flash>maiorSteps){
                maiorSteps = flash;
                numDoMaior = i;
                allSteps += flash;
            }
	    }
       	System.out.println("MN: "+ numDoMaior + " MSteps: " + maiorSteps + " ASteps: " + allSteps); 
    }
}
