package avaliador;
import frames.Probabilidades;
import graph.Graph;
import graph.Node;

import java.io.*;
import javax.swing.*;


/**
 * Classe que implementa o módulo Avaliador Nível 1B. Responsável por verificar se está correto.
 * A verificação ocorre antes da parametrização do modelo. 
 * @author Thais Souza Aiza
 * @author André Felipe Rodrigues (método verificaValoresMinimos)
 * @version 1.0 
 */
public class AvaliadorNivelUmB implements Serializable{
	
	/**
	 * Utilizado para mostrar ao usuário mensagens.
	 */
	JFrame frame;
	
	/**
	 * Indica qual o tipo do modelo.
	 */
	public String tipoModelo = "";
	
	/**
	 * Indica se o modelo está certo ou errado. 
	 */
	boolean erro = false;
	        
	/**
	 * Indica se o modelo contém erros.
	 */
	boolean result = false;
	        
	/**
	 * Indica o número de fontes do modelo.
	 */
	int numFonte;        
	
	/**
	 * Indica o número de centros de serviço do modelo.
	 */
	int numCS;        
	
	/**
	 * Indica o número de sorvedouros do modelo.
	 */
	int numSorvedouro;
	
	/**
	 * Indica se todas as ligações estão corretas ou não.
	 */
	int ligaOK = 0;
    
    /**
     * Indica se o modelo tem fonte ou não. Para os casos de modelo fechado o modelo não 
     * possui fonte.
     */    
	boolean temFonte = false;
    
    /**
     * Indica se o modelo tem sorvedouro ou não. Para os casos de modelo fechado o modelo 
     * não possui sorvedouro.
     */    
	boolean temSorvedouro = false;
	
	/**
	 * Método que verifica se o grafo possui todas as ligações necessárias. Isto é,
	 * verifica se o modelo não possui elementos sem ligações.
	 * @param graph Modelo
	 * @return Um valor <code>boolean</code> true se o modelo possui todas as ligações 
	 * e false faltam ligações.
	 */
	public int verificaLigacoes(Graph graph){
		
		ligaOK = 1;

		for (int k = 0; ((k < graph.getSize())); k++){
		//for (int k = 0; ((k < graph.getSize()) && (ligaOK == 1)); k++){
			if ((graph.getNode(k).getTipoNo() == 2) || (graph.getNode(k).getTipoNo() == 3)){
				if (graph.getNode(k).getChega() >= 1){
					ligaOK = 1;
					
				}
				else{
					ligaOK = 0;
				}
			}			
		}
		
		return ligaOK;
	}

	 /**
	  * Método responsável para verificar se o modelo é um modelo válido ou não.
	  * Caso o modelo não seja válido uma mensagem de Erro é enviada para o usuário.
	  * @param graph Modelo
	  * @return Um valor <code>boolean</code> true se o modelo é válido e false se o 
	  * modelo é inválido.
	  */
	 public boolean  verificaValidadeDoModelo(Graph graph){
	 	
		result = false;        
		numFonte = 0;        
		numCS = 0;        
		numSorvedouro = 0;
         
        erro = false;

		for (int j = 0; (j < graph.getSize()); j++){
						
			switch (graph.getNode(j).getTipoNo()){
				case 1: numFonte = numFonte + 1;
				        break;
				case 2: numCS = numCS + 1;
				        break;
				case 3: numSorvedouro = numSorvedouro + 1;
				        break; 
			}
		}
		
		int i = 0;
		while (erro == false){
	
			if (graph.getSize() == 0){
				JOptionPane.showMessageDialog(frame,
								"Modelo Inválido!!! Especifique um Modelo",
								"ASDA - Erro",
								JOptionPane.ERROR_MESSAGE);
				erro = true;
				
				result = false;
				
			}
			else{
				/*
				 * Verifica se o tamanho do grafo é igual
				 */
				
				if (graph.getSize() == 1){
					
					/*
					 * Exibe para o usuário mensagens de erro, pois faltam templates para 
					 * serem espeficicados
					 */
					
					switch (graph.getTipoNo(i)){
						case 1: JOptionPane.showMessageDialog(frame,
						                        "Modelo Inválido!!! Especifique o template Centro de Serviço",
						                        "ASDA - Erro",
						                        JOptionPane.ERROR_MESSAGE);
								erro = true;				
								result = false;
								break;
						case 2: JOptionPane.showMessageDialog(frame,
												"Modelo Inválido!!! Especifique o template Fonte",
												"ASDA - Erro",
												JOptionPane.ERROR_MESSAGE);
								erro = true;				
								result = false;
								break;
						case 3: JOptionPane.showMessageDialog(frame,
												"Modelo Inválido!!! Especifique os templates Fonte e Centro de Serviço",
												"ASDA - Erro",
												JOptionPane.ERROR_MESSAGE);
								erro = true;				
								result = false;
								break;
					}
				}
				else{ 	
					//inverter...	
					if (verificaLigacoes(graph) == 1){
				/*			JOptionPane.showMessageDialog(frame,
											"Modelo Correto!!!",
											"ASDA",
											JOptionPane.INFORMATION_MESSAGE);*/
							erro = true;				
							result = true;
							
						}					 
					else{
					
					if ((numFonte == 0) && (numSorvedouro > 0) && (numCS > 0)){
						JOptionPane.showMessageDialog(frame,
										"Modelo Inválido!!! Especifique o template Fonte",
										"ASDA - Erro",
										JOptionPane.ERROR_MESSAGE);
						erro = true;				
						result = false;
					}
					else{
						if ((numFonte > 0) && (numCS > 0) && (numSorvedouro == 0)){
							JOptionPane.showMessageDialog(frame,
											"Modelo Inválido!!! Especifique o template Sorvedouro",
											"ASDA - Erro",
											JOptionPane.ERROR_MESSAGE);
							erro = true;				
							result = false;							
						}
						else{
							if ((numFonte > 0) && (numCS > 0) && (numSorvedouro > 0)){
							JOptionPane.showMessageDialog(frame,
											"Modelo Inválido!!! Especifique as ligações",
											"ASDA - Erro",
											JOptionPane.ERROR_MESSAGE);
							erro = true;				
							result = false;	
							}
						}						
							
						}
					}
				}
			}
			
			i++;
			
		}//Fim do while


	 
	 return result;
	 }
	 	 
	/**
	 * Método responsável por verificar qual é o tipo do modelo.
	 * @param graph Modelo
	 * @return O tipo do modelo. Aberto, fechado ou misto.
	 */
	public String  verificaTipoModelo(Graph graph){
		if (verificaLigacoes(graph) == 1){
			if ((numFonte == 0) && (numSorvedouro == 0)){
				graph.setTipoModelo("fechado");
				tipoModelo = "fechado";
				System.out.println(tipoModelo);
			}
			else{
				graph.setTipoModelo("aberto");
			}
	
		}
		return tipoModelo;			
	}
	
	public boolean verificaValoresMinimos(Graph graph)
	{
		
		/* verifica a consistência do grafo - não avalia nós */
		if (graph.getNomeModelo() == null)
		{
			JOptionPane.showMessageDialog(
					null,
					"O modelo não tem nome",
					"ASDA - Erro: Modelo sem nome",
					JOptionPane.ERROR_MESSAGE);
			return false;
		}else if (graph.getTempoExecucao() == null)
		 {
				JOptionPane.showMessageDialog(
						null,
						"Tempo de execução não definido - defina-o em parametrização do modelo",
						"ASDA - Erro",
						JOptionPane.ERROR_MESSAGE);
				return false;
		 }
		else if (graph.getNumeroMaximoEntidades() == null)
			graph.setNumeroMaximoEntidades("0");
		else if (graph.getWarmUp() == null)
		{
			graph.setWarmUp("automático");
		}
		else if (graph.getTamanhoBatch() == null)
			graph.setTamanhoBatch("0");
		else if (graph.getChegadaSize() < 1)
		{
			JOptionPane.showMessageDialog(
					null,
					"É necessário definir ao menos uma chegada para o modelo",
					"ASDA - Chegadas não definidas",
					JOptionPane.ERROR_MESSAGE);
			return false;
		}
		
		/* vefirifa a consistência dos nós do grafo */
		int cont = 0;
		for (int i = 0; i < graph.getSize(); i++)			
		{
			Node temp = graph.getNode(i); // percorrendo os nós
			if (temp.getTipoNo() == 2) 	// se é centro de serviço
			{
				if ((temp.getNomeCentroServico() == null) || (temp.getNomeCentroServico().equals("")))
				{
					cont++;
					temp.setNomeCentroServico("CS_" + temp.getIdNo());
				}	
				else if (temp.getMedia() == null)
				{
					JOptionPane.showMessageDialog(
							null,
							"Defina a média de serviço no nó " + temp.getNomeCentroServico(), 
							"ASDA - Erro na média do centro de serviço",
							JOptionPane.ERROR_MESSAGE);
					return false;
				}
				else if (temp.getSequencia() == null)
					temp.setSequencia("0");
				else if ( (temp.getNumServidores() == null) || (temp.getNumServidores().equals("0"))
						|| (Integer.parseInt(temp.getNumServidores()) < 1) )
				{
					JOptionPane.showMessageDialog(
							null,
							"Defina corretamente o número de servidores do nó " + temp.getNomeCentroServico(), 
							"ASDA - Número de servidores inválido",
							JOptionPane.ERROR_MESSAGE);
					return false;
				}
				else if (temp.getSize() > 1) // se está ligado a mais de um nó
				{
					if ( (Probabilidades.somaLig(temp) > 100.5) || (Probabilidades.somaLig(temp) < 99.99))
					{
						JOptionPane.showMessageDialog(
								null,
								"Probabilidade das ligações do nó "
									+ temp.getNomeCentroServico()
									+ "não estão definidas corretamente", 
								"ASDA - Probabilidades definidas inválida para o nó",
								JOptionPane.ERROR_MESSAGE);
						return false;
					}
				}
				
				if (temp.isPrimRec())
				{
					if (temp.getMediaFonte() == null)
					{
						JOptionPane.showMessageDialog(
								null,
								"Defina a média de chegada na fonte. Nó = " + temp.getNomeCentroServico(),
								"ASDA - Erro no centro de serviço souce",
								JOptionPane.ERROR_MESSAGE);
						return false;
					}
					else if (temp.getSequenciaFonte() == null)
						temp.setSequenciaFonte("0");
				}
			}
		}
		
		if (cont > 0)
		{
			if (cont == 1)
				JOptionPane.showMessageDialog(
						null,
						cont + "teve seu nome definido automaticamente",
						"ASDA - Nome do nó não definido",
						JOptionPane.ERROR_MESSAGE);
			else
				JOptionPane.showMessageDialog(
						null,
						cont + "tiveram seus nomes definidos automaticamente",
						"ASDA - Nomes de algus nós não definidos",
						JOptionPane.ERROR_MESSAGE);
			return false;
		}
			
		
		return true;
	}
}
