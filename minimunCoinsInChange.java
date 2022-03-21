
//given a number, return the optimized quantity of $100 $50 $25 $10 $5 $2 dollar bills and $1 $.50 $.25 $.10 $.5 $.1 cents 
public class Main {
    public static String ReturnChange(String value){
    	int qnt100,qnt50,qnt25,qnt10,qnt5,qnt2,qnt1,qnt50c,qnt25c,qnt10c,qnt5c,qnt1c=0;
    	int over1cValue, under1cValue;
    	String[] splitedValue= value.split(",");
    	
    	over1cValue = Integer.parseInt(splitedValue[0]);
    	under1cValue= Integer.parseInt(splitedValue[1]);
    	
		qnt100=over1cValue/100;
		over1cValue-=qnt100*100;
		qnt50=over1cValue/50;
		over1cValue-=qnt50*50;
		qnt25=over1cValue/25;
		over1cValue-=qnt25*25;
		qnt10=over1cValue/10;
		over1cValue-=qnt10*10;
		qnt5=over1cValue/5;
		over1cValue-=qnt5*5;
		qnt2=over1cValue/2;
		over1cValue-=qnt2*2;
		qnt1=over1cValue;
		over1cValue-=qnt1;
		
		qnt50c=under1cValue/50;
		under1cValue-=qnt50c*50;
		qnt25c=under1cValue/25;
		under1cValue-=qnt25c*25;
		qnt10c=under1cValue/10;
		under1cValue-=qnt10c*10;
		qnt5c=under1cValue/5;
		under1cValue-=qnt5c*5;
		qnt1c=under1cValue;
		under1cValue-=qnt1c;

		return "\n$100:"+qnt100+"\n$50:"+qnt50+"\n$25:"+qnt25+"\n$10:"+qnt10+"\n$5:"+qnt5+"\n$2:"+qnt2+"\n$1:"+qnt1+"\n$.50:"+qnt50c+"\n$.25:"+qnt25c+"\n$.10:"+qnt10c+"\n$.05:"+qnt5c+"\n%.01:"+qnt1c;
    }

    public static void main(String[] args) {
        String value = "98541,99";//do not enter '.' just ','
        System.out.println("Change: "+ReturnChange(value));
    }
}

