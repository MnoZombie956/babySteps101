import java.util.Scanner;

public class Contador{
    private int h,m;
    private int type;
    public Contador(int type) {
        this.type=type;
        resetTimer();
    }
    public void ticTac() {
        if(this.type==24){
            this.m++;
            if(this.m==60 && this.h<24){
                this.h++;
                this.m=0;
            }
        }else{
            this.m++;
            if(this.m==60){
                this.h++;
                this.m=0;
            }
            if(this.h==12 && this.m==0){
                this.h=-1;
            }
            if(this.h==13 && this.m == 0){
                this.h=1;
            }
        }
    }
    public void resetTimer(){
        if(this.type==12){
            this.h=12;
        }else{
            this.h=0;
        }
        this.m=0;
    }
    public int getHour () {
        return h;
    }
    public int getMin () {
        return m;
    }
}

public class Relogio{
    private int type;
    Contador timing;
    public Relogio (int type){
        timing = new Contador(type);
        this.type=type;
    }
    public void showTimes(){
        if(this.type==24){
            do{
                if(timing.getMin()<10){
                    System.out.println(">"+ timing.getHour() +":0"+ timing.getMin()+" hours");
                }else{
                    System.out.println(">"+ timing.getHour() +":"+ timing.getMin()+" hours");
                }
                timing.ticTac();
            }while(timing.getHour()<24);
        }else{
            while(timing.getHour()!=-1){
                if(timing.getMin()<10){
                    System.out.println("> "+timing.getHour() +":0"+ timing.getMin()+" A.M.");
                }else{
                    System.out.println("> "+timing.getHour() +":"+ timing.getMin()+" A.M.");
                }
                timing.ticTac();
            }timing.resetTimer();
            while(timing.getHour()!=-1){
                if(timing.getMin()<10){
                    System.out.println("> "+timing.getHour() +":0"+ timing.getMin()+" P.M.");
                }else{
                    System.out.println("> "+timing.getHour() +":"+ timing.getMin()+" P.M.");
                }
                timing.ticTac();
            }
        }
    }
}

public class Main{
	public static void main(String[] args) {
	    int type;
	    Scanner input = new Scanner(System.in);
		System.out.println("What is the hour format ? (24||12)");
		type=input.nextInt();
	    
	    Relogio r = new Relogio(type);
	    r.showTimes();
	}
}
