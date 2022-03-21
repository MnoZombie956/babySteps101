import java.util.Scanner;

public class Pessoa {
	private String nome;
	private String contato;
	public Pessoa(String nome, String contato){
		this.nome = nome;
		this.contato = contato;
	}
	public String getContato(){
		return this.contato;
	}
	public String getNome(){
		return this.nome;
	}
}

public class Lote {
	private String descricao;
	private Lance maiorLance;
	
	public Lote(String descricao) {
		this.descricao = descricao;
		maiorLance = new Lance();
	}
	public void verificaLance(Lance lance) {
        if(lance.getValor() > this.maiorLance.getValor() ) {
            this.setMaiorLance(lance);
        }
	} 
	private void setMaiorLance(Lance lance) {
		this.maiorLance=lance;
	}
	public String getDescricao() {
		return this.descricao;
	}
	public Lance getMaiorLance() {
	    return maiorLance;
	}
}

public class Lance {
	private double valor;
	private Pessoa pessoa;
	public Lance(){
		this.valor = 0;
		this.pessoa = new Pessoa("ninguem","empty");
	}
	public void setValor (double valor) {
		this.valor=valor;
	}
	public void setPessoa(Pessoa pessoa){
		this.pessoa = pessoa;
	}
	public double getValor () {
		return this.valor;
	}
	public Pessoa getPessoa (){
	    return pessoa;
	}
}

public class Leilao{//leilao
	private Lote[] lote;
	private Lance lance;
	private int n;
	private int untiln;
	
	public Leilao (int n) {
		this.lote = new Lote[n];
		this.n=n;
		this.untiln=0;
	}
	public boolean adicionaLote(Lote lote){
		this.lote[untiln] = lote;
		untiln++;
		return true;
	}
	public boolean recebeLance(Lance lance,String descricao) {
		this.lance=lance;
		for(int i=0;i<untiln;i++){
			if(descricao.equals(lote[i].getDescricao())){
				lote[i].verificaLance(lance);
			}
		}
		return true;
	}
	public void imprimeLotes(){
	    System.out.println("=================");
        for(int i = 0;i<untiln;i++){
            /*
            System.out.println("Para o lote "+lote[i].getDescricao()+" o maior lance eh "+lote[i].getMaiorLanceV());
            System.out.println("E a pessoa eh "+lote[i].getMaiorLanceN());*/
            System.out.println("Lote "+i+"º: "+lote[i].getDescricao());
            System.out.println("=================");
        }
	}
	public void encerraLeilao(){
        System.out.println("Fim de leilao\nLotes e seus respectivos ganhadores");
        System.out.println("=================");
        for(int i=0;i<untiln;i++){
            System.out.println("Lote: "+lote[i].getDescricao());
            //System.out.println("testeMPN: "+lote[i].getMaiorLance().getPessoa().getNome());
            System.out.println("Maior lance: "+lote[i].getMaiorLance().getValor());
            System.out.println("Pessoa: "+lote[i].getMaiorLance().getPessoa().getNome());
            System.out.println("Contato: "+lote[i].getMaiorLance().getPessoa().getContato());
            System.out.println("=================");
        }
	}
}

public class Main {//teste leilao
	public static void main (String[] args){
		boolean sucesso=false;
		int n;
		int exit=0;
		double valor=0;
        String descricao;
        String nome;
        String contato;
		Scanner input = new Scanner(System.in);
		Leilao leilao;
		Lance lance;
		Lote lote;
        
		System.out.println("Quantos Lotes ?");
		n=input.nextInt();
		System.out.println("Numero de Lotes atual eh: "+n);
		
        leilao = new Leilao(n);
		
		
		while(exit==0){
    		System.out.println("Qual operação?\n(1)Adicionar os Lotes     (3)Lance de uma pessoa\n(2)Listar lotes     (4)Encerrar Leilao\n(5)Sair");
    	
    		n=input.nextInt();
    		switch(n){
    		    case 1:{
    		        System.out.println("Adiciona a descricao: ");
    		        descricao=input.next();
    		        System.out.println("Descricao eh: "+descricao);
    		        lote = new Lote(descricao);
                    leilao.adicionaLote(lote);
                    break;
    		    }
    		    case 2:{
    		        leilao.imprimeLotes();
    		        break;
    		    }
    		    case 3:{
    		        System.out.println("Nome da pessoa:");
    		        nome=input.next();
    		        System.out.println("Pessoa eh: "+nome);
    		        System.out.println("Contato da pessoa: ");
    		        contato=input.next();
    		        System.out.println("Contato da pessoa eh: "+contato);
    		        
    		        Pessoa pessoa= new Pessoa(nome,contato);
    		        
    		        System.out.println("Insira a descricao do lance da pessoa: ");
    		        descricao=input.next();
    		        System.out.println("Descricao eh: "+descricao);
    		        System.out.println("Insira o lance da pessoa: ");
    		        valor=input.nextDouble();
    		        System.out.println("O valor do lance eh:"+valor);
    		        
    		        lance= new Lance();
    		        lance.setPessoa(pessoa);
    		        lance.setValor(valor);
    		        
    		        sucesso=leilao.recebeLance(lance,descricao);
    		        
    		        if(sucesso==true){
    		            System.out.println("Foi registrado para "+nome+" de contato "+contato+" o lance para o lote "+descricao+" num valor de "+valor);
    		        }else{
    		            System.out.println("Não foi possivel registrar o Lance");
    		        }
    		        break;
    		    }
    		    case 4:{
    		        leilao.encerraLeilao();
    		        break;
    		    }
    		    case 5:{
    		        System.out.println("Se sair todas as informações serão descartadas!\nProsseguir ? (1)Sim (0)Nao");
    		        n=input.nextInt();
    		        if(n==1){
    		            exit=1;
    		        }
    		        break;
    		    }
    		}
		}
	}
}
