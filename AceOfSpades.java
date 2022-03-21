import java.util.Random;
import java.util.Scanner;

public class Jogador {
    private Carta[] cards;
    private int cardsQuant;
    public Jogador(int n){
        cardsQuant=n;
        this.cards = new Carta[n];
        for(int i=0;i<n;i++){
            cards[i] = new Carta();
        }
    }
    public Carta getCards(int i){
        return this.cards[i];
    }
    public void setCards(int i,String suits,int value){
        if(value==0){//para o rand nao gerar zeros
            value++;
        }
        cards[i].setSuits(suits);
        cards[i].setValue(value);
    }
    public void showAllCards(){
        for(int i=0;i<cardsQuant;i++){
            System.out.println("Card["+(i+1)+"]: "+cards[i].getSuits()+", "+cards[i].getValue());
        }
    }
    public void removeCard(int i){
        for(int j=i;j<cardsQuant-1;j++){
            cards[j].setValue(cards[j+1].getValue());
            cards[j].setSuits(cards[j+1].getSuits());
        }
        cards[cardsQuant-1].setValue(0);
        cards[cardsQuant-1].setSuits("none");
        cardsQuant--;
    }
}

public class Baralho{
    private Carta[] cards;
    private String[] suitsNames = {"Copas","Ouros","Paus","Espadas"};
    //Hearts, Diamonds, Clubs, Spades
    public Baralho(){
        this.cards = new Carta[54];
        for(int i=0,j=0,k=1;i<52;i++,j++,k++){
            cards[i] = new Carta();
            cards[i].setSuits(suitsNames[j]);
            cards[i].setValue(k);
            if(j == 3){
                j=-1;
            }
            if(k == 13){
                k=0;
            }
        }
    }
    public String getSuits(int i){
        return suitsNames[i];
    }
    public void showCards(){
        for(int i=0;i<52;i++){
            System.out.printf("Card["+(i+1)+"]: "+cards[i].getSuits()+" "+cards[i].getValue()+"\n");
        }
    }
}

public class Carta{
    private String suits;
    private int value;
    public Carta(){
        this.suits="NULL";
        this.value=0;
    }
    public String getSuits(){
        return this.suits;
    }
    public int getValue(){
        return this.value;
    }
    public void setSuits(String suits){
        this.suits=suits;
    }
    public void setValue(int value){
        this.value=value;
    }
}

public class Main {//Mesa
    public static void Uno(){
        Random random = new Random();
        Scanner input = new Scanner(System.in);
    	Baralho deck = new Baralho();
    

    	int n;//quantidade de cartas
    	int flashp1;//para receber entradas dos players
    	int flashp2;// ||
    }
    public static void SimpleAtiv() {
        Random random = new Random();
        Scanner input = new Scanner(System.in);
    	Baralho deck = new Baralho();
    	
    	int p1Wins=0;
    	int p2Wins=0;
    	int rounds=0;
    
    	int n;//quantidade de cartas
    	int flashp1;//para receber entradas dos players
    	int flashp2;// ||
    	
    	deck.showCards();
    	
    	System.out.println("How many cards for each ?");
    	n=input.nextInt();
    	
    	do{
    	    System.out.println("How many rounds ?");//fica mais interessante
    	    rounds=input.nextInt();
    	    if(rounds>n){
    	        System.out.println("There isn't enough cards for that many rounds !");
    	    }
    	}while(rounds>n);
    	
    	Jogador p1 = new Jogador(n);
    	Jogador p2 = new Jogador(n);
    	
    	for(int i=0;i<n;i++){//quem dá as cartas é a mesa
    	    p1.setCards(i,deck.getSuits(random.nextInt(4)),random.nextInt(14));
    	    p2.setCards(i,deck.getSuits(random.nextInt(4)),random.nextInt(14));
    	}
    	
    	
    	for(int roundsCounter=0;roundsCounter<rounds;roundsCounter++){//enquanto ninguem ganhar...
    	    System.out.print("\033[H\033[2J"); //clear screen
            System.out.flush(); 
            
    		System.out.println("p1 cards");
    		p1.showAllCards();
    		System.out.println("p2 cards");
    		p2.showAllCards();
    		System.out.println("P1: "+p1Wins+" P2: "+p2Wins);
    		
    	    do{
                System.out.println("P1 play your card: ");
                flashp1=input.nextInt();
    	    }while(flashp1>n||flashp1<1);
    	    do{
    	        System.out.println("P2 play your card: ");
    	        flashp2=input.nextInt();
    	    }while(flashp2>n||flashp2<1);
    	    
    	    if(p1.getCards(flashp1-1).getValue()>p2.getCards(flashp2-1).getValue()){//caso p1 tenah um valor maior que o do p2
    	        p1Wins++;//p1 ganha o round
    	    }else if(p1.getCards(flashp1-1).getValue()==p2.getCards(flashp2-1).getValue()){//caso iguais, compare os naipes
    		    if(p1.getCards(flashp1-1).getSuits()=="Ouros"){
    		        p1Wins++;
    		    }
    		    if(p2.getCards(flashp1-1).getSuits()=="Ouros"){
    		        p2Wins++;
    		    }
    	    }else{//caso contrario p2 ganha o round
    	        p2Wins++;
    	    }
    	    
    	    p1.removeCard(flashp1-1);//tira a carta usada do baralho
    	    p2.removeCard(flashp2-1);
    	    n--;
    	}
    	if(p1Wins>=p2Wins){
    	    System.out.println("It's over, p1 is the winner!!!");
    	}else if(p1Wins==p2Wins){
    	    System.out.println("Oh no ! It's a Draw !");
    	}else{
    	    System.out.println("It's over, p2 is the winner!!!");
    	}
    }
	public static void main(String[] args) {
	    Scanner input = new Scanner(System.in);
	    int game=0;
	    System.out.println("Select the game:\n(1)Uno\n(2)SimpleAtiv");
	    game=input.nextInt();
	    
        System.out.print("\033[H\033[2J"); //clear screen
        System.out.flush(); 
	
	    switch(game){
	        case 1:{
	            //Uno();
	            System.out.print("not yet");
	            break;
	        }
	        case 2:{
	            SimpleAtiv();
	            break;
	        }
	    }
	}
}
