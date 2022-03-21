import java.util.Scanner;

public class Contato {
	private String nome;
	private String numero;
	private String email;
	public Contato(){
		this.nome = "NULL";
		this.numero ="NULL";
		this.email = "NULL";
	}
	public String getNome(){
		return this.nome;
	}
	public String getNumero(){
		return this.numero;
	}
	public String getEmail(){
		return this.email;
	}
	public void setNome(String nome){
		this.nome=nome;
	}
	public void setNumero(String numero){
		this.numero = numero;
	}
	public void setEmail(String email){
		this.email=email;
	}
}

import java.util.ArrayList;
import java.util.Iterator;
/*(1) - Insere novo contato na agenda
(2) - Exibe o número total de contatos da agenda
(3) - Exibe um contato (pesquisa pelo nome)
(4) - Exclui um contato (pesquisa pelo nome)
(5) - Exibe todos os contatos da agenda
(0) - Sair*/
public class Agenda{
	private ArrayList<Contato> agenda;
	public Agenda(){
		agenda = new ArrayList<Contato>();
	}
	public void insereContato(Contato alguem){
		agenda.add(alguem);
	}
	public int getTamanho(){
		return agenda.size();
	}
	public String getContatoPorNome(String nome){
		for(int i=0;i<agenda.size();i++){
			if(agenda.get(i).getNome()==nome){
				return agenda.get(i).getNumero();
			}
		}
		return "Nao encontrado";
	}
	public int excluiContatoPorNome(String nome){
		for(Contato aux:agenda){
			if(aux.getNome()==nome){
				agenda.remove(agenda.indexOf(aux.getNome()));
				return 1;
			}
		}
		//ou
	    agenda.remove(nome);
		return 0;
	}
	public Contato getContato(int pos){
		return agenda.get(pos);
	}
}

public class Main{//TestaAgenda
	public static void main (String[] args){
		Agenda agenda = new Agenda();
		Scanner input = new Scanner(System.in);
		Contato contato = new Contato();
		int escolha=0;
		while(true){
			System.out.println("(1) Inserir novo contato\n(2) Exibir o numero total de contatos\n(3) Exibir um contato(pesquisar o nome)\n(4) Excluir um contato(pelo nome)\n(5) Exibir todos os contatos\n(6) Sair");
			escolha=input.nextInt();
			switch(escolha){
				case 1:{
					System.out.println("Nome:");
					contato.setNome(input.next());
					System.out.println("Numero:");
					contato.setNumero(input.next());
					System.out.println("Email:");
					contato.setEmail(input.next());
					
					agenda.insereContato(contato);
				    System.out.println("Adicionado");
				    break;
				}
				case 2:{
                    System.out.println("Tamanho: "+agenda.getTamanho());   
				    break;
				}
				case 3:{
				    System.out.println("Insira o Nome: ");
                    System.out.println(agenda.getContatoPorNome(input.next()));
                    break;
				}
				case 4:{
                    System.out.println("Insira o Nome: ");
                    agenda.excluiContatoPorNome(input.next());
                    System.out.println("Excluido");
                    break;
				}
				case 5:{
                    for(int i=0;i<agenda.getTamanho();i++){
                        System.out.println("Nome: "+agenda.getContato(i).getNome()+"Numero: "+agenda.getContato(i).getNumero()+"Email: "+agenda.getContato(i).getEmail());
                    }
                    break;
				}
			}
			System.out.println("Continuar?(1)Sim(0)Nao");
			if(input.nextInt()==0)
			    break;
		}
	}
}
