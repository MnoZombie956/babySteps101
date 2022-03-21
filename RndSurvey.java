import java.util.Scanner;
import java.security.SecureRandom;

public class Enquete {
	private int[] scores;
	private int qnt=0;
	private int quickSum=0;
  private String place;
    
	public Enquete(String name) {
	       this.place=name;
	       this.qnt=0;
	       this.quickSum=0;
	       this.scores=new int[500];
	}
	private int freqScore(int ofThis){
		int qntOfThis=0;
		for(int j=0;j<qnt;j++){
			if(scores[j]==ofThis){
				qntOfThis++;
			}
		}
		return qntOfThis;
	}
	public String getName(){
		return place;
	}
	public void insertScores(int score){
		scores[qnt]=score;
		qnt++;
	}
	public double getMedia(){
		for(int i=0;i<qnt;i++){
			quickSum += scores[i];
		}
		return (double)quickSum/qnt;
	}
	public void showFreq(){
		for(int i=0;i<=10;i++){
			System.out.println("Score["+(i)+"]: "+freqScore(i)+" times\n");
		}
	}
	public void getQnt(){
		System.out.println("Number of participants: "+qnt+"\n");
	}
}

public class Main {
	public static void main(String[] args){
		String name;
		int quantity;

		Scanner input = new Scanner(System.in);
		SecureRandom gen = new SecureRandom();

		System.out.println("Enter the name of the survey: ");
		name=input.nextLine();
		Enquete bandeijao = new Enquete(name);
		
    System.out.println("Enter the number of participants of "+bandeijao.getName()+": ");
		quantity=input.nextInt();

		for(int i=0;i<quantity;i++){
			bandeijao.insertScores(gen.nextInt(11));
		}
		bandeijao.showFreq();
		bandeijao.getQnt();
		System.out.println("Media: "+bandeijao.getMedia()+"\n");
	}
}
