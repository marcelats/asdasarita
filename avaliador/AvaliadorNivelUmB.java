package avaliador;
import frames.Probabilidades;
import graph.Graph;
import graph.Node;

import java.io.*;
import javax.swing.*;


/**
 * Classe que implementa o m   dulo Avaliador N   vel 1B. Respons   vel por verificar se est    correto.
 * A verifica      o ocorre antes da parametriza      o do modelo. 
 * @author Thais Souza Aiza
 * @author Andr    Felipe Rodrigues (m   todo verificaValoresMinimos)
 * @version 1.0 
 */
public class AvaliadorNivelUmB implements Serializable{
	
	/**
	 * Utilizado para mostrar ao usu   rio mensagens.
	 */
	JFrame frame;
	
	/**
	 * Indica qual o tipo do modelo.
	 */
	public String tipoModelo = "";
	
	/**
	 * Indica se o modelo est    certo ou errado. 
	 */
	boolean erro = false;
	        
	/**
	 * Indica se o modelo cont   m erros.
	 */
	boolean result = false;
	        
	/**
	 * Indica o n   mero de fontes do modelo.
	 */
	int numFonte;        
	
	/**
	 * Indica o n   mero de centros de servi   o do modelo.
	 */
	int numCS;        
	
	/**
	 * Indica o n   mero de sorvedouros do modelo.
	 */
	int numSorvedouro;
	
	/**
	 * Indica se todas as liga      es est   o corretas ou n   o.
	 */
	int ligaOK = 0;
    
    /**
     * Indica se o modelo tem fonte ou n   o. Para os casos de modelo fechado o modelo n   o 
     * possui fonte.
     */    
	boolean temFonte = false;
    
    /**
     * Indica se o modelo tem sorvedouro ou n   o. Para os casos de modelo fechado o modelo 
     * n   o possui sorvedouro.
     */    
	boolean temSorvedouro = false;
	
	/**
	 * M   todo que verifica se o grafo possui todas as liga      es necess   rias. Isto    ,
	 * verifica se o modelo n   o possui elementos sem liga      es.
	 * @param graph Modelo
	 * @return Um valor <code>boolean</code> true se o modelo possui todas as liga      es 
	 * e false faltam liga      es.
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
	  * M   todo respons   vel para verificar se o modelo     um modelo v   lido ou n   o.
	  * Caso o modelo n   o seja v   lido uma mensagem de Erro     enviada para o usu   rio.
	  * @param graph Modelo
	  * @return Um valor <code>boolean</code> true se o modelo     v   lido e false se o 
	  * modelo     inv   lido.
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
								"Modelo Inv   lido!!! Especifique um Modelo",
								"ASDA - Erro",
								JOptionPane.ERROR_MESSAGE);
				erro = true;
				
				result = false;
				
			}
			else{
				/*
				 * Verifica se o tamanho do grafo     igual
				 */
				
				if (graph.getSize() == 1){
					
					/*
					 * Exibe para o usu   rio mensagens de erro, pois faltam templates para 
					 * serem espeficicados
					 */
					
					switch (graph.getTipoNo(i)){
						case 1: JOptionPane.showMessageDialog(frame,
						                        "Modelo Inv   lido!!! Especifique o template Centro de Servi   o",
						                        "ASDA - Erro",
						                        JOptionPane.ERROR_MESSAGE);
								erro = true;				
								result = false;
								break;
						case 2: JOptionPane.showMessageDialog(frame,
												"Modelo Inv   lido!!! Especifique o template Fonte",
												"ASDA - Erro",
												JOptionPane.ERROR_MESSAGE);
								erro = true;				
								result = false;
								break;
						case 3: JOptionPane.showMessageDialog(frame,
												"Modelo Inv   lido!!! Especifique os templates Fonte e Centro de Servi   o",
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
										"Modelo Inv   lido!!! Especifique o template Fonte",
										"ASDA - Erro",
										JOptionPane.ERROR_MESSAGE);
						erro = true;				
						result = false;
					}
					else{
						if ((numFonte > 0) && (numCS > 0) && (numSorvedouro == 0)){
							JOptionPane.showMessageDialog(frame,
											"Modelo Inv   lido!!! Especifique o template Sorvedouro",
											"ASDA - Erro",
											JOptionPane.ERROR_MESSAGE);
							erro = true;				
							result = false;							
						}
						else{
							if ((numFonte > 0) && (numCS > 0) && (numSorvedouro > 0)){
							JOptionPane.showMessageDialog(frame,
											"Modelo Inv   lido!!! Especifique as liga      es",
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
	 * M   todo respons   vel por verificar qual     o tipo do modelo.
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
		
		/* verifica a consist   ncia do grafo - n   o avalia n   s */
		if (graph.getNomeModelo() == null)
		{
			JOptionPane.showMessageDialog(
					null,
					"O modelo n   o tem nome",
					"ASDA - Erro: Modelo sem nome",
					JOptionPane.ERROR_MESSAGE);
			return false;
		}else if (graph.getTempoExecucao() == null)
		 {
				JOptionPane.showMessageDialog(
						null,
						"Tempo de execu      o n   o definido - defina-o em parametriza      o do modelo",
						"ASDA - Erro",
						JOptionPane.ERROR_MESSAGE);
				return false;
		 }
		else if (graph.getNumeroMaximoEntidades() == null)
			graph.setNumeroMaximoEntidades("0");
		else if (graph.getWarmUp() == null)
		{
			graph.setWarmUp("autom   tico");
		}
		else if (graph.getTamanhoBatch() == null)
			graph.setTamanhoBatch("0");
		else if (graph.getChegadaSize() < 1)
		{
			JOptionPane.showMessageDialog(
					null,
					"    necess   rio definir ao menos uma chegada para o modelo",
					"ASDA - Chegadas n   o definidas",
					JOptionPane.ERROR_MESSAGE);
			return false;
		}
		
		/* vefirifa a consist   ncia dos n   s do grafo */
		int cont = 0;
		for (int i = 0; i < graph.getSize(); i++)			
		{
			Node temp = graph.getNode(i); // percorrendo os n   s
			if (temp.getTipoNo() == 2) 	// se     centro de servi   o
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
							"Defina a m   dia de servi   o no n    " + temp.getNomeCentroServico(), 
							"ASDA - Erro na m   dia do centro de servi   o",
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
							"Defina corretamente o n   mero de servidores do n    " + temp.getNomeCentroServico(), 
							"ASDA - N   mero de servidores inv   lido",
							JOptionPane.ERROR_MESSAGE);
					return false;
				}
				else if (temp.getSize() > 1) // se est    ligado a mais de um n   
				{
					if ( (Probabilidades.somaLig(temp) > 100.5) || (Probabilidades.somaLig(temp) < 99.99))
					{
						JOptionPane.showMessageDialog(
								null,
								"Probabilidade das liga      es do n    "
									+ temp.getNomeCentroServico()
									+ "n   o est   o definidas corretamente", 
								"ASDA - Probabilidades definidas inv   lida para o n   ",
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
								"Defina a m   dia de chegada na fonte. N    = " + temp.getNomeCentroServico(),
								"ASDA - Erro no centro de servi   o souce",
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
						"ASDA - Nome do n    n   o definido",
						JOptionPane.ERROR_MESSAGE);
			else
				JOptionPane.showMessageDialog(
						null,
						cont + "tiveram seus nomes definidos automaticamente",
						"ASDA - Nomes de algus n   s n   o definidos",
						JOptionPane.ERROR_MESSAGE);
			return false;
		}
			
		
		return true;
	}
}
