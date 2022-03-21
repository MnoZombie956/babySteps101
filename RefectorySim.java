import java.util.Scanner;

public class Semana {
    private int i=0;
    private double qntKcal;
    public String nomeDias[]={"Dom","Seg","Ter","Qua","Qui","Sex","Sab"};
    private Dia dias[] = new Dia[7];
    public Semana() {
        for(int i=0;i<7;i++)
            this.dias[i] = new Dia();
    }
    public String getDiaE(int i){
        return nomeDias[i];
    }
    public void showDiaE(int i){
        System.out.println(nomeDias[i]);
    }
    public Dia getDia(int i){
        return dias[i];
    }
    public void showAllRefeicoes(){
        for(int i=0;i<7;i++){
            System.out.println(nomeDias[i]);
            this.getDia(i).showRefeicoes();
        }
    }
    public double calcKcal(){
        for(int i=0;i<7;i++)
            for(int j=0;j<6;j++)
                qntKcal += getDia(i).getRefeicao(j).getKcal();
                
        return qntKcal;
    }
}

public class Dia {
    private String horarios[]={"Cafe da Manha","Lanche da Manha","Almoço","Lanche da Tarde","Jantar","Ceia"};
    private int i=0;
    private Refeicao refeicoes[] = new Refeicao[6];
    public Dia () {
        for(int k=0;k<6;k++)
            this.refeicoes[k] = new Refeicao();
    }
    public void showHorarioE(int k){
        System.out.println(horarios[k]);
    }
    public String getHorarioE(int i){
        return horarios[i];
    }
    public Refeicao getRefeicao(int k){
        return refeicoes[k];
    }
    public void showRefeicoes(){
        for(int k=0;k<6;k++){
            System.out.println(horarios[k]+": "+this.refeicoes[k].getDescricao());
        }
    }
}

public class Refeicao {
    private String descricao;
    private double kcal;
    public Refeicao(){
        this.descricao="Empty";
        this.kcal=0;
    }
    public void setDescricao(String descricao){
        this.descricao=descricao;
    }
    public void setKcal(double kcal){
        this.kcal=kcal;
    }
    public String getDescricao(){
        return descricao;
    }
    public double getKcal(){
        return kcal;
    }
}

public class Main {
    public static int analiseR(int r,int min,int max){
        Scanner input = new Scanner(System.in);
        if(r<min||r>max){
            System.out.println("Only one of the values above\nRe enter:");
            r=input.nextInt();
        }
        return r;
    }
    public static void main(String[] args){
        int n=0;
        int choice1, choice2;
        int exit=0;
        double kcal;
        String descricao;
        Semana semana = new Semana();
        Scanner input = new Scanner(System.in);
        
        while(exit==0){
            System.out.println("SISTEMA DE CARDAPIOS\n(1)Adicionar Refeicao\n(2)Editar Refeicao\n(3)Excluir Refeicao\n(4)Listar Refeicoes\n(5)Calculate kCal");
            n=input.nextInt();
            switch(n){
                case 1:{
                    for(int i=0;i<7;i++){
                        semana.showDiaE(i);
                        for(int j=0;j<6;j++){
                            semana.getDia(i).showHorarioE(j);
                            
                            System.out.println("Insira a Descricao: ");
                            descricao=input.next();
                            System.out.println("Insira quantas Kcal: ");
                            kcal=input.nextDouble();
                            
                            semana.getDia(i).getRefeicao(j).setDescricao(descricao);
                            semana.getDia(i).getRefeicao(j).setKcal(kcal);
                        }
                    }
                    break;
                }
                case 2:{
                    System.out.println("Editar qual dia?\n(1)Dom\n(2)Seg\n(3)Ter\n(4)Qua\n(5)Qui\n(6)Sex\n(7)Sab");
                    choice1=input.nextInt();
                    choice1=analiseR(choice1,1,7);
                    System.out.println("Editar qual refeicao?\n(1)Cafe da Manha\n(2)Lanche da Manha\n(3)almoco\n(4)Lanche da Tarde\n(5)Jantar\n(6)Ceia");
                    choice2=input.nextInt();
                    choice2=analiseR(choice2,1,6);
                    System.out.println("Re-insira a descrição: ");
                    descricao=input.next();
                    System.out.println("Re-insira quantas Kcal: ");
                    kcal=input.nextDouble();
                    
                    semana.getDia(choice1-1).getRefeicao(choice2-1).setDescricao(descricao);
                    semana.getDia(choice1-1).getRefeicao(choice2-1).setKcal(kcal);
                    System.out.println("Editado com sucesso no dia "+semana.getDiaE(choice1-1)+" a refeicao "+semana.getDia(choice1-1).getRefeicao(choice2-1).getDescricao()+" do horario "+semana.getDia(choice1-1).getHorarioE(choice2-1));
                    break;
                }
                case 3:{
                    System.out.println("Excluir para qual dia?\n(1)Dom\n(2)Seg\n(3)Ter\n(4)Qua\n(5)Qui\n(6)Sex\n(7)Sab");
                    choice1=input.nextInt();
                    choice1=analiseR(choice1,1,7);
                    System.out.println("Excluir para qual refeicao?\n(1)Cafe da Manha\n(2)Lanche da Manha\n(3)almoco\n(4)Lanche da Tarde\n(5)Jantar\n(6)Ceia");
                    choice2=input.nextInt();
                    choice2=analiseR(choice2,1,6);
                    
                    //semana.dias[choice1-1].refeicoes[choice2-1].setDescricao(null);
                    semana.getDia(choice1-1).getRefeicao(choice2-1).setDescricao("Nada Adicionado");
                    //semana.dias[choice1-1].refeicoes[choice2-1].setKcal(0);
                    semana.getDia(choice1-1).getRefeicao(choice2-1).setKcal(0);
                    System.out.println("Excluido com sucesso no dia "+semana.getDiaE(choice1-1)+" a refeicao "+semana.getDia(choice1-1).getRefeicao(choice2-1).getDescricao()+" do horario "+semana.getDia(choice1-1).getHorarioE(choice2-1));
                    break;                    
                }
                case 4:{
                    semana.showAllRefeicoes();
                    break;
                }
                case 5:{
                    System.out.println("Quantidade de Kcal: "+semana.calcKcal());
                    break;
                }
                default:{
                    System.out.println("Only one of the numbers above");
                }
            }
        }
    }
}
