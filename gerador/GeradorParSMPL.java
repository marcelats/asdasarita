package gerador;

import graph.Chegada;
import graph.Graph;
import graph.Node;
import graph.ProcessoLogicoParSMPL;
import graph.QueueL;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;


import javax.swing.JOptionPane;




/**
 * @author André Felipe Rodrigues
 * 
 * TODO COMENTAR O CÓDIGO E RETIRAR FUNÇOES DESNECESSÁRIAS NO CÓDIGO
 */
public class GeradorParSMPL extends Gerador {

	public static final String TAXA_SERVICO = "Ts";
	public static final String TAXA_CHEGADA = "Ta";
		
	// private boolean auxiliarLinhaNotDefinedYet;
	private boolean alreadyClosed;
	
	private int tidPai;
	private int tidPrimRec;

	

	
	Node processoLogicoVet[];
	
	/**
	 * Variável utilizada para armazenar as informações que serão gravadas no arquivo de  
	 * saída.
	 */
	private StringBuffer buffer = new StringBuffer(120);	
	
	
	/**
	 * Para impressão do relatório de estatísticas
	 */
		
	/* Definição de constantes */	
	private static final int tempoExecDefault = 20000;
	private static final String pontoVirgula = ";";
	
	private Controler c;
	
	private QueueL stack[];
	
//	private Vector jahEmpilhados = new Vector(0);
	
	
	
	/**
	 * Construtor da Classe.
	 * @param graph Recebe o modelo que irá gerar o programa de simulação.
	 */
	public GeradorParSMPL(Graph graph) {
  	
	  super(graph);
//	  auxiliarLinhaNotDefinedYet = true;	 
	  alreadyClosed = false;
	  
	  int numInitReq, numInitRel; // números inicias para request e release
	  int contFonte = 0;
	  
	  
		boolean jahAchou = false;
		for (int i = 0; i < graph.getSize(); i++){ // conta o número de fontes do grafo
			if (graph.getNode(i).isPrimRec()){
				contFonte++;
				if (!jahAchou)
				{
					tidPrimRec = graph.getNode(i).getTid();
					jahAchou = true;  // grava o Tid do primeiro recurso - recurso de entrada de tokens
				}
			}
		}
		
		numInitReq = contFonte+1;
		numInitRel = contFonte+2;	
		
		c = new Controler(graph, numInitReq, numInitRel); // gera números de case apropriados para request e release de cada centro de serviço
		
		stack = new QueueL[graph.getPLogicos().size()];
		for (int i = 0; i < graph.getPLogicos().size(); i++)
		{
			stack[i] = new QueueL();
		}
		

				
		for (int i=0; i < graph.getSize(); i++)
		{
			// se é centro de serviço
			int id = graph.getNode(i).getIdNo();
			if (graph.getNode(i).getTipoNo() == 2){
				stack[graph.getNode(i).getTid()].push(String.valueOf(id));  // montando vetores
				// OBSERVAÇÃO: AGORA NÃO HAVERÁ MAIS UMA ORDEM LÓGICA SEMI-GARANTIDA NA CRIAÇÃO DOS CASES
			}			
		}

		
	}

	
	/**
	 * Cria o arquivo que irá conter o programa de simulação.
	 */
	public void criaArquivo(){
		
	//	filename = graph.getNomeModelo();
		if ((filename != null) && (!filename.equals("")))
		{
			filename = "src/" +  filename + ".c";
				File f = new File(filename);
				if (f.exists()) 
					f.delete();
		}
	}
	
	public void criaArquivo(String filename)
	{
		this.filename = filename;
		criaArquivo();
	}



	/**
	 * Quando tempo de warm-up é definido como automático, ele é setado como 5%
	 * do tempo total de simulação
	 * @return
	 */
	/*private double generateWarmUpTime()
	{
		if ((graph.getTempoExecucao() != null) && (graph.getTamWarmUp().equals("0")))
		{
			double valor;
			valor = 0.05*Double.parseDouble(graph.getTempoExecucao());
			return valor;
		}
		else
			return 0;
	}
	*/
	
	/**
	 * Grava o valor da variável buffer no arquivo.
	 * @param buffer Variável que contém as informações a serem gravadas no arquivo.
	 */
	private void gravaArquivo(StringBuffer buffer) {
				
		
		try {          
            
			FileWriter out = new FileWriter(new File(filename),true);
			out.write(buffer.toString());
			out.write('\n');
			
			out.close();
            
		} catch(IOException ex) {
			ex.printStackTrace();
		}
	}//

	

	/**
	 * Gera o comando para limitar a execução da simulação:
	 * - por tempo;
	 * - por número de clientes que deixam o sistema ou
	 * - pelo número de ciclos do cliente no sisema.
	 */
	private void defineTempoMax(int tid){
		// definição do tempo máximo da simulação
		
		
		// só gera se o processo for um processo pai
		
		if (tid == tidPai)
		{
			buffer.delete(0,119);
			buffer.append(" float Te = ");
			if (graph.getTempoExecucao().equals("0")){
				JOptionPane.showMessageDialog(
						null,
						"Tempo de simulação definido automaticamente\n" +
						"Tempo padrão = " + tempoExecDefault,
						"Tempo de execução não especificado",
						JOptionPane.INFORMATION_MESSAGE);
				graph.setTempoExecucao(String.valueOf(tempoExecDefault));
			}
			buffer.append(graph.getTempoExecucao());
			buffer.append(pontoVirgula);
			gravaArquivo(buffer);	
	
			
			// definição do número máximo de entidades no sistema simulado
			// se for definido como 0, o simulação não pára devido ao número de entidades		
	/*		if (!graph.getNumeroMaximoEntidades().equals("0")){
				buffer.delete(0,119);
				buffer.append(" unsigned int Maximo_Entidades = 0, Num_Max_Entidades = ");
				buffer.append(graph.getNumeroMaximoEntidades());
				buffer.append(pontoVirgula);
				gravaArquivo(buffer);
			}*/
			
			/* VER O QUE FAZER EM RELAÇÃO AO NÚMERO DE CICLOS :-( TODO*/
				
			/*if (Double.parseDouble(graph.getNumeroCiclos()) != 0){
				buffer.delete(0,119);
				buffer.append(" unsigned int Num_Voltas = 0, Num_Max_Voltas = ");
				buffer.append(graph.getNumeroCiclos());
				buffer.append(pontoVirgula);
				gravaArquivo(buffer);;
				
			}*/
			// Se é definido pelo usuário, é setada uma variável para o reset
		}
	
		
	}
	
	/**
	 * por enquanto, só cria a variável de parada
	 * @param tid
	 */
/*	private void defineVariaveisAuxiliares(int tid)
	{
		buffer.delete(0,119);
		buffer.append(" int fim = 0;");
		gravaArquivo(buffer);
		
	}*/
	private void defineLookAheadPL(int tid)
	{   // TODO VERIFICAR COM SARITA :-(
		// TODO - definir lookahed do processo lógico (um double)
		buffer.delete(0,119);
		buffer.append(" double lookAhead = " + 
				((ProcessoLogicoParSMPL)graph.getPLogicos().get(tid)).getLookAhead() + ";");	
		gravaArquivo(buffer);
		
	}
	
	private void defineMaximoClientes()
	{
		buffer.delete(0,119);
		if ( (graph.getNumeroMaximoEntidades() != null) && (!graph.getNumeroMaximoEntidades().equals("0")) ) {
			buffer.append(" unsigned int Maximo_Entidades = 0, Num_Max_Entidades = ");
			buffer.append(graph.getNumeroMaximoEntidades());
			buffer.append(";");
			gravaArquivo(buffer);
		}
	}
	
	/**
	 * só gera controle de warm-up se o processo lógico for o pai ( que controla do tempo da simulação)
	 * @param tid
	 */
	/*private void defineVarWarmUp(int tid)
	{
	
		if (tid == tidPai)
		{
			buffer.delete(0,119);
			buffer.append(" char flag_reset = 0;\n");
			buffer.append(" float timeWarmUp = ");
			if ( (graph.getTamWarmUp() != null ) && (!graph.getTamWarmUp().equals("0")) ){
				buffer.append(graph.getTamWarmUp());			
			}
			else
			{
				buffer.append(String.valueOf(generateWarmUpTime()));
			}
			buffer.append(pontoVirgula);
			gravaArquivo(buffer);
		}
	}
	*/
	/**
	 * Gera o comando para determinar qual a seqüência a ser utilizada na geração do 
	 * número aleatório. Quando o comando smpl é executado a seqüência é setada para 1 
	 * e incrementada a medida em que é utilizada.
	 * @param sequencia Um valor <code>Integer</code> compreendido no intervalo 1..15.
	 * @param espaco Para formatação do arquivo de saída.
	 */
	private void geraStream(int indice, String espaco,boolean fonte){
		
		if (!fonte)
		{
			if ( (graph.getNode(indice).getSequencia() != null) && (!graph.getNode(indice).getSequencia().equals("0")))
			{	buffer.delete(0,119);
				buffer.append(espaco);
				buffer.append("stream(");
				buffer.append(graph.getNode(indice).getSequencia());
				buffer.append(");");
				gravaArquivo(buffer);
			}
		}
		else
		{
			if ( (graph.getNode(indice).getSequenciaFonte() != null) && (!graph.getNode(indice).getSequenciaFonte().equals("0")))
			{
				buffer.delete(0,119);
				buffer.append(espaco);
				buffer.append("stream(");
				buffer.append(graph.getNode(indice).getSequenciaFonte());
				buffer.append(");");
				gravaArquivo(buffer);
			}
			
		}
	}
	
	
	/**
	 * Gera a primitiva break.
	 *
	 */
	private void geraBreak(){
		
		buffer.delete(0,119);
		buffer.append("          break;");
		gravaArquivo(buffer);
			
	}

	
	/**
	 * Gera as variáveis para os tempos médios entre chegadas e serviço.
	 *
	 */
	private void defineVarTempos(int tid){
		
		buffer.delete(0,119);
		
		String nomeA = "Ta"; 	// Taxa Arrival
		String nomeB = "Ts";	// Taxa service
		
		buffer.delete(0,119);

					
		boolean colocouReal1 = false;

		// não tem problema em criar a real (agora float) antes, pois cada processo lógico deve ter pelo menos um nó
		// define tempo de chegada de centros de serviços que são primeiro recurso
		for (int i = 0; i < graph.getSize(); i++)
		{   // Centro de serviço de chegada		
			int tidP = graph.getNode(i).getTid(); // pega o tid do nó - ver se precisa as variáveis
			if ((graph.getNode(i).getTipoNo() == 2) && (graph.getNode(i).isPrimRec()) && (tidP == tid)){
				if (!colocouReal1)
				{
					buffer.append(" float ");
					colocouReal1 = true;
				}
				buffer.append(nomeA);
				buffer.append(String.valueOf(graph.getNode(i).getIdNo()));
				buffer.append(" = ");
				buffer.append(graph.getNode(i).getMediaFonte());
				buffer.append(";");
			}	
		}	
		
		gravaArquivo(buffer);
		buffer.delete(0,119);
			
		buffer.append(" float ");
		for (int i = 0; i< graph.getSize(); i++)
		{	// Define a taxa de serviço de todos centros de serviços
			int tidP = graph.getNode(i).getTid();
//			boolean jahVirg = false;
			if ((graph.getNode(i).getTipoNo() == 2) && (tidP == tid)){
				//buffer.append(", ");
				buffer.append(nomeB);
				buffer.append(String.valueOf(graph.getNode(i).getIdNo()));
				buffer.append(" = ");
				buffer.append(graph.getNode(i).getMedia());
				buffer.append(", ");
			}
		}
		
        int ivirg = buffer.lastIndexOf(",");
        if (ivirg!=-1)
			buffer.deleteCharAt(buffer.lastIndexOf(",")); // deleta virgula final
        buffer.append(";");
        
		gravaArquivo(buffer);
		
	}


	private void defineAuxiliares(int tid)
	{
		buffer.delete(0,119);
		buffer.append(" int i = 0;\n");
	    buffer.append(" int info;\n"); // contador
	    buffer.append(" int fim=0;");
	  //  buffer.append(" char nome_recurso[50];");
		gravaArquivo(buffer);
	}
	/**
	 * Gera as variáveis para as definições dos recursos que compoem o modelo a ser 
	 * implementado.   NÃO PRECISA MAIS DISSO :-(
	 *
	 */
/*	private void defineVarServer(int tid){
		
		buffer.delete(0,119);
		buffer.append(" int ");
		
		
		for (int i = 0; i < graph.getSize(); i++){
			if ((graph.getNode(i).getTipoNo() == 2) && (graph.getNode(i).getTid() == tid)){		
				String temp = graph.getNode(i).getNomeCentroServico();
				temp.replace(' ','_'); // tira espaços para o nome de uma variável			
				buffer.append(temp);
				buffer.append(", ");
			}			
		}
		// retira ultima virgula
		int temp = buffer.lastIndexOf(", ");
		if (temp!=-1)
		    buffer.delete(temp, buffer.length());
		// adiciona o ponto e vírgula
		buffer.append(";");
		gravaArquivo(buffer);
			        

	}*/
	
	/*
	 * Método de auxílio para não redefinir a mesma linha no código usado
	 * para os dois tipos de estatísticas
	 */
	/*private void defineLinhaTotClientes()
	{
		if (auxiliarLinhaNotDefinedYet)
		{
			buffer.delete(0,119);
			buffer.append(" unsigned int Total_Clientes = 0; ");
			gravaArquivo(buffer);
			
			auxiliarLinhaNotDefinedYet = false;
		}
	}*/


	/**
	 * Define as variáveis que serão utilizadas para os cálculos estatísticos:
	 * tamanho máximo e mínimo da fila associada ao recurso especificado.
	 *
	 */
/*	private void defineEstatMaxMin(int tid){
		
		String nomeMax = "Max";
		String nomeMin = "Min";
		
		
		buffer.delete(0,119);
		int cont = 0;
		
		int i = 0;
		for (i=0; i< graph.getSize(); i++) {
			if ( (graph.getNode(i).getTipoNo() == 2) && 
					(graph.getNode(i).getComprimentoMaxMin()) 
					&& ( tid == graph.getNode(i).getTid() ))
				cont++;
		}
		
		if (cont != 0) // só gera se o grafo define estatísticas
		{
			buffer.append(" unsigned int ");
			
			for (i = 0; i < graph.getSize(); i++)
			{
				Node temp = graph.getNode(i);
				if (  (temp.getTipoNo() == 2) && 
						(temp.getComprimentoMaxMin())
						&& (tid == graph.getNode(i).getTid())) // o nó mede estatística fila vazia
				{
					buffer.append(nomeMax);
					buffer.append(temp.getIdNo());
					buffer.append(" = 0");
					buffer.append(", ");
					buffer.append(nomeMin);
					buffer.append(temp.getIdNo());
					buffer.append(" = 1000");
					cont--;
					if (cont == 0) // não tem mais variáveis para adicionar, finaliza com ;
						buffer.append(";");
					else
						buffer.append(",");							
				}				
			}
			gravaArquivo(buffer);
			
			defineLinhaTotClientes();
		}	
	}
	*/
	/**
	 * Define as variáveis que serão utilizadas para os cálculos estatísticos: porcentagem
	 * de vezes em que o cliente encontra a fila vazia, associada ao recurso especificado.
	 */
/*	private void defineEstatFilaVazia(int tid){
		
		String nomeTotal = "Tot";
		String nomeVaz = "Vaz";
		
		
		buffer.delete(0,119);
		int cont = 0;
		
		int i = 0;
		for (i=0; i< graph.getSize(); i++) {
			if ( (graph.getNode(i).getTipoNo() == 2) && 
					(graph.getNode(i).getEstatisticaFilaVazia())
					&& (tid == graph.getNode(i).getTid()))
				cont++;
		}
		
		if (cont != 0) // só gera se o grafo define estatísticas
		{
			buffer.append(" unsigned int ");
			
			for (i = 0; i < graph.getSize(); i++)
			{
				Node temp = graph.getNode(i);
				if (  (temp.getTipoNo() == 2) && 
						(temp.getEstatisticaFilaVazia()) 
						&& (tid == graph.getNode(i).getTid())) // o nó mede estatística fila vazia
				{
					buffer.append(nomeTotal);
					buffer.append(temp.getIdNo());
					buffer.append(" = 0");
					buffer.append(", ");
					buffer.append(nomeVaz);
					buffer.append(temp.getIdNo());
					buffer.append(" = 0");
					cont--;
					if (cont == 0) // não tem mais variáveis para adicionar, finaliza com ;
						buffer.append(";");
					else
						buffer.append(",");							
				}				
			}
			gravaArquivo(buffer);
			
			defineLinhaTotClientes();
		}		
		
	}
	*/
	/**
	 * Define as variáveis necessárias para utilizar o método de análise Batch Means.
	 *
	 */
	/*private void defineBMeans(){
		if ( (graph.getTamanhoBatch() != null) && (!graph.getTamanhoBatch().equals("0")) ){
			buffer.delete(0,119);
			buffer.append(" float TBatch = 0;\n");
			buffer.append(" int r = 0;");
			gravaArquivo(buffer);
		}
	}*/
	
	
	//sem fila
	/*public void defineReesc(){
		
		
		
	}
	
	//sem fila
	public void defineVarBackoff(){
		
		int flag = 1;
		long ind = 1;
		
		
	}*/
	
	
	/**
	 * Declara e abre para escrita o arquivo de saída no código do programa de simulação.
	 * Este arquivo de saída conterá o relatório da simulação.
	 */
	private void defineArqSaida(int tid){
		
		buffer.delete(0,119);
		buffer.append(" FILE *p, *saida;");
		gravaArquivo(buffer);
		buffer.delete(0,119);
		
		StringBuffer buffer2 = new StringBuffer(300); // para suportar tamanhos maiores
		buffer2.delete(0,299);
		buffer2.append(" saida = fopen(\"");
		buffer2.append(System.getProperty("user.dir") + "/models/");
		buffer2.append(graph.getNomeModelo()+"_"+tid);
		buffer2.append(".out\",\"w\");\n"); // chegou a quase 100 caracteres já
		gravaArquivo(buffer2);
		
//		buffer.append(" if ((p = sendto(saida)) == NULL)\n");
//		buffer.append("    printf(\"Erro na saida \\n\");");
//		gravaArquivo(buffer);	
		
	}
	
	/**
	 * Gera o comando SMPL para a inicialização do modelo de simulação.
	 *
	 */
	private void nomeParametro(int tid){
		
		buffer.delete(0,119);
		buffer.append("  smpl(0,\"");
		buffer.append(graph.getNomeModelo() + "_" + tid);
		buffer.append("\");");
		gravaArquivo(buffer);
		
	}
	
	
	/**
	 * Gera o comando <code>facility</code> para a definição dos recursos que compoem o 
	 * sistema.
	 */
	private void geraDefServer(int tid){
		
		for (int i = 0; i < graph.getSize() ; i++)
		{			
			if ((graph.getNode(i).getTipoNo() == 2) && (tid == graph.getNode(i).getTid())){				
				buffer.delete(0,119);  // agora não associa mais com a variável criada
			/*	buffer.append(" ");
				buffer.append(graph.getNode(i).getNomeCentroServico());
				buffer.append(" = facility(\"");*/
				buffer.append(" facility(\"");
				buffer.append(graph.getNode(i).getNomeCentroServico());
				buffer.append("\","); 
				buffer.append(graph.getNode(i).getNumServidores());
				buffer.append(");");
				gravaArquivo(buffer);				
			}		
			
		}
		
	}
	
	/**
	 * Escalona o primeivo evento a ocorrer no caso de sistema com uma única entrada, ou todos
	 * os eventos que devem ser escalonados antes do início da simulação para modelos de
	 * sistemas fechados.
	 */
	private void geraPrimeiroEvento(int tid){
			
		int id, numCase = 1;

		
		buffer.delete(0,119);
		
		for (int i = 0; i < graph.getSize(); i++){ // conta o número de fontes do grafo e acerta os numCase
			if (graph.getNode(i).isPrimRec() && (tid == graph.getNode(i).getTid())){
				id = graph.getNode(i).getIdNo();
				c.setCase(numCase,id);
			    numCase++;
			}
		}
		
		if (tid == tidPrimRec)
		{
			if (graph.getTipoModelo().equals("aberto")){
				
				if (graph.getChegadaSize() >= 1)
				{
					for (int i = 0; i < graph.getChegadaSize(); i++)
					{
						Chegada temp = graph.getChegada(i);
						if (temp.getNumeroClientes() > 1)
						{
							buffer.append("   for (i = 0; i < ");
							buffer.append(temp.getNumeroClientes());
							buffer.append(" ; i++)\n");
							buffer.append("      schedule(");
						}
						else 
							buffer.append("   schedule(");
					
						buffer.append(c.getCase(graph.getNode(temp.getNodeIndex()).getIdNo()) + ",");
						buffer.append(temp.getTempoChegada());
						/*buffer.append(", Customer);");*/
						
						buffer.append(", Customer, ");
						buffer.append(tid + ");");
						
						gravaArquivo(buffer);
						buffer.delete(0,119);
					}
				}
			
			}
		}
	}
	
	/**
	 * Gera o comando de repetição, limitando a simulação por:
	 * - tempo,
	 * - número de clientes que passam pelo sistema,
	 * - número de voltas no sistema 
	 * - método de análise Batch Means.
	 *
	 */
	private void geraLoop(){
		
		buffer.delete(0,119);
		
		buffer.append("  while ( !fim )");

		/*if ( (graph.getNumeroCiclos() != null) && (!graph.getNumeroCiclos().equals("0")) ) {
			buffer.append(" while (Num_Voltas <= Num_Max_Voltas) ");
		} 
		else {
			if (  ( (graph.getTempoExecucao() != null) && (!graph.getTempoExecucao().equals("0") )
					&& (graph.getNumeroMaximoEntidades().equals("0") ) )  ) 
			{
				buffer.append(" while ( (time() < Te) "); // somente por tempo
				
				if ( (graph.getTamanhoBatch() != null) && (!graph.getTamanhoBatch().equals("0")) ){
					buffer.append("&& (r == 0) )");
				} else {
					buffer.append(")");
				}
			}
			else {
				if ( ((graph.getTempoExecucao().equals("0") || (graph.getTempoExecucao()==null)) )
						&& (graph.getNumeroMaximoEntidades() != null)) {
					buffer.append(" while ((Maximo_Entidades < Num_Max_Entidades) ");
					if (graph.getTamanhoBatch() != null) {
						buffer.append("&& (r == 0) )");
					} else {
						buffer.append(")");
					}
				} else {
					buffer.append(" while( (time() < Te) && (Maximo_Entidades < Num_Max_Entidades)");
					if ( (graph.getTamanhoBatch() != null) && (!graph.getTamanhoBatch().equals("0")) ) {
						buffer.append("&& (r== 0) )");
					} else {
						buffer.append(")");
					}
				}
			}
		}		*/
		gravaArquivo(buffer);
			
	}
	
	private void geraParada(int tid)
	{
		if (tid == tidPai)
		{
			int indice = indicePLogico(tid);
			int tidProx=0;
			if (graph.getSize() > 3)
				tidProx = ((ProcessoLogicoParSMPL)graph.getPLogicos().get(indice+1)).getTid();
			
			geraComentario("verificando o tempo de simulação","      ");
			buffer.delete(0,119);
			buffer.append("    if (clock_sim() > Te)");
			gravaArquivo(buffer);
			
			geraSchedule(1000,"0.0","       ",tidProx);			
		}
		
	}
	
	/**
	 * Implementa o comando <code>cause</code>.
	 * 
	 */
	private void geraCause(){
		
		buffer.delete(0,119);
		buffer.append("    cause(&Event,&Customer);");
		gravaArquivo(buffer);
		
	}
	
	/**
	 * Gera o comando <code>switch</code>.
	 *
	 */
	private void geraSwitch(){
		buffer.delete(0,119);
		buffer.append("    switch(Event)");
		gravaArquivo(buffer);	
		
	}
	
	/**
	 * Gera a primitiva case.
	 * @param numeroEvento Um valor <code>Integer</code>.
	 */
	private void geraCase(int numeroEvento){
		
		buffer.delete(0,119);
		buffer.append("        case ");
		buffer.append(numeroEvento);
		buffer.append(" : ");
		gravaArquivo(buffer);
	}
	
		
	/**
	 * Gera o comando schedule para o primeiro recurso.
	 * @param numeroEvento
	 * @param numeroRecurso Um valor <code>Integer</code> que indica o recurso corrente. (indice do nodes graph)
	 */

	private void geraProximaChegada(int numReq, int numeroRecurso, int numEvento, int tid){
		
		buffer.delete(0,119);
		// geraSchedule(numReq,numeroRecurso,false,null);
		geraSchedule(numReq,"0.0","          ",tid);
		
		geraStream(numeroRecurso,"          ", true);
		
		//chama agora o proximo recurso e nao a fonte
	//	if (graph.getNode(numeroRecurso).isProb()){
			buffer.delete(0,119);
			String secParam = geraStringSchedule(numeroRecurso,true);
			geraSchedule(numEvento,secParam,"          ", tid);
	//		geraSchedule(numEvento,numeroRecurso,true,GeradorSMPL.TAXA_CHEGADA);

			buffer.delete(0,119);
		//}		
	}	
	
	/**
	 * Função que gera o reset para o warm-up
	 * 
	 * NÃO SEI SE TEM AS FUNÇÕES IMPLEMENTADAS DE WARM-UP PARA PARSMPL TODO :-( 
	 *
	 */
/*	private void geraWarmUp()
	{
		buffer.delete(0,119);
		buffer.append("   if ( (!flag_reset) && (time() > timeWarmUp) )\n   {");
		gravaArquivo(buffer);
		buffer.delete(0,119);
		buffer.append("      reset();\n");
		buffer.append("      flag_reset = 1;");
		gravaArquivo(buffer);
		
		buffer.delete(0,119);
		
		
		// resetando valores de Fila Vazia e Comprimento Max/Min
		boolean totClientes = false;
		boolean temEst;
		boolean ident;
		
		for (int i = 0; i < graph.getSize(); i++)
		{
			Node temp = graph.getNode(i);
			if (temp.getTipoNo() == 2)
			{
				ident = false;
				temEst = false;
				if (temp.getComprimentoMaxMin()) // especifica comprimento max/min
				{
					totClientes = true;
					temEst = true;
					buffer.append("      Max");
					ident = true;
					buffer.append(temp.getIdNo());
					buffer.append(" = 0; ");
					buffer.append("Min");
					buffer.append(temp.getIdNo());
					buffer.append(" = 1000; ");
				}
				
				if (temp.getEstatisticaFilaVazia())
				{
					totClientes = true;
					temEst = true;
					if (!ident)
						buffer.append("      Tot"); // conserto de identação
					else
						buffer.append("Tot");
					buffer.append(temp.getIdNo());
					buffer.append(" = 0; ");
					buffer.append("Vaz");
					buffer.append(temp.getIdNo());
					buffer.append(" = 0;");					
				}
				
				if (temEst) //temEst serve para identificar se houve necessidade 
				{								// de geração de código para esse cs
					gravaArquivo(buffer);
					buffer.delete(0,119);
				}
			}
		}

		if (totClientes)
		{
			buffer.delete(0,119);
			buffer.append("      Total_Clientes = 0;");
			gravaArquivo(buffer);
			
		}
		
		if ( (graph.getNumeroMaximoEntidades()!=null) && (!graph.getNumeroMaximoEntidades().equals("0")))
		{
			buffer.delete(0,119);
			buffer.append("      Maximo_Entidades = 0;");
			gravaArquivo(buffer);
		}
		
		buffer.delete(0,119);
		buffer.append("   }");
		gravaArquivo(buffer);		
		
	}
	*/
	/**
	 * @param distribuicao
	 * 
	 * TAMBÉM NÃO SEI SE IMPLEMENTA ESTATÍSTICAS BATCH :-(
	 */
	private void geraBatch(String distribuicao)
	{
		buffer.delete(0,119);
		buffer.append("             ");
		buffer.append("TBatch = ");
		buffer.append(distribuicao);
		buffer.append(";\n");
		buffer.append("             ");
		buffer.append(" r = obs(TBatch);");
		gravaArquivo(buffer);		
	}
	

	/**
	 * Gera a linha: schedule (destino, distri(TsIDCS), Customer); se true
	 * 			   e schedule (destino, 0.0, Customer); se false
	 * @param destino 
	 * @param numeroRecurso
	 * @param distribuicao true o false
	 * @author André Felipe Rodrigues
	 */
	/*private void geraSchedule(int destino, int numeroRecurso, boolean distribuicao, String tipo)
	{
		buffer.delete(0,119);
		buffer.append("            schedule(");
		buffer.append(destino+", ");
		if (distribuicao)
		{
			buffer.append(graph.getNode(numeroRecurso).getDistribuicaoServico());
			buffer.append("(" + tipo);
			buffer.append(graph.getNode(numeroRecurso).getIdNo()+ ")");			
		}
		else
			buffer.append(" 0.0");
		
		buffer.append(", Customer);");
		gravaArquivo(buffer);		
	}*/
	
	
	/**
	 * gera schedule adicionado para a utilização de outras probabilidades (hiperexponencial, etc)
	 * @param destino primeiro parametro do schedule
	 * @param tempo segundo parametro do schedule
	 * @param espaco o tanto de espaço de identação que se quer dar
	 * @author André Felipe Rodrigues
	 */
	
	private String geraStringSchedule(int indice, boolean chegada)
	{
		String ret = "0.0";
		Node temp = graph.getNode(indice);
		if (chegada)
		{
			if (temp.isPrimRec())
			{
				if (temp.getDistribuicaoChegada().equals("expntl"))
				{
					ret = temp.getDistribuicaoChegada() 
						+ "(" + GeradorSMPL.TAXA_CHEGADA 
						+ temp.getIdNo() 
						+ ")";					
				}
				else if ( (temp.getDistribuicaoChegada().equals("hyperx")) 
							|| (temp.getDistribuicaoChegada().equals("normal")) 
							|| (temp.getDistribuicaoChegada().equals("erlang"))
							|| (temp.getDistribuicaoChegada().equals("uniform"))
							)
				{
					ret = temp.getDistribuicaoChegada() 
					+ "(" + GeradorSMPL.TAXA_CHEGADA 
					+ temp.getIdNo() 
					+ ", "
					+ temp.getDesvioPadraoFonte()
					+ ")";	
				}				
			}
		}
		else
		{
			if (temp.getDistribuicaoServico().equals("expntl"))
			{
				ret = temp.getDistribuicaoServico() 
					+ "(" + GeradorSMPL.TAXA_SERVICO 
					+ temp.getIdNo() 
					+ ")";					
			}
			else if ( (temp.getDistribuicaoServico().equals("hyperx")) 
						|| (temp.getDistribuicaoServico().equals("normal")) 
						|| (temp.getDistribuicaoServico().equals("erlang"))
						|| (temp.getDistribuicaoServico().equals("uniform"))
						)
			{
				ret = temp.getDistribuicaoServico() 
				+ "(" + GeradorSMPL.TAXA_SERVICO 
				+ temp.getIdNo() 
				+ ", "
				+ temp.getDesvioPadrao()
				+ ")";	
			}	
			
		}		
		return ret;
		
	}
	
	private void geraSchedule(int destino, String tempo, String espaco, int tid)
	{
		buffer.delete(0,119);
		buffer.append(espaco);
		buffer.append("schedule(" + destino + ",");
		buffer.append(tempo);
		buffer.append(", Customer, PL" + tid + ");");
		gravaArquivo(buffer);		
	}
	
	/**
	 * Implementa a primitiva para a liberacao do recurso (facilidade).
	 * @param numeroEvento 
	 * @param numeroRecurso Um valor <code>Integer</code> que indica o recurso corrente.
	 */
	private void geraRequest(int numeroRecurso, int tid){
	
				
		/*if (graph.getNode(numeroRecurso).getComprimentoMaxMin() == true){
			geraEstatisticaMaxMin(numeroRecurso);
		}
		if (graph.getNode(numeroRecurso).getEstatisticaFilaVazia() == true){
			geraEstatisticaFilaVazia(numeroRecurso);
		}*/
		buffer.delete(0,119);
		buffer.append("          if (request(");
		String temp = graph.getNode(numeroRecurso).getNomeCentroServico();
		temp.replace(' ','_');
		buffer.append("\"" + temp + "\"");		
		buffer.append(", Event, Customer, 0, PL" + tid + ") == 0)");
		gravaArquivo(buffer);

	}
	
	
	/**
	 * Gera o comando <code>release</code> para a liberação do recurso.
	 * @param numeroRecurso Um valor <code>Integer</code> que indica o recurso corrente. 
	 * @param numeroEvento Um valor <code>Integer</code>.
	 * @param totalRecurso Um valor <code>Integer</code> que indica o número de recursos 
	 */
	private void geraRelease(int numeroRecurso){		
		buffer.delete(0,119);
		buffer.append("          release(");
		String temp = graph.getNode(numeroRecurso).getNomeCentroServico();
		temp.replace(' ','_');
		buffer.append("\"" + temp + "\"");
		buffer.append(", Customer);");
		
	   gravaArquivo(buffer);
	}
	
	
	/**
	 * @param indice
	 * @param espaco
	 * 
	 * VER SE VAI TER ESSAS ESTATÍSTICAS NO PARSMPL TODO :-(
	 */
/*	private void geraContagemMaximoEntidades(int indice, String espaco)
	{
		if ( (graph.getNumeroMaximoEntidades()!= null) && (!graph.getNumeroMaximoEntidades().equals("0")) )
		{	
			buffer.delete(0,119);
			if (espaco!=null)
				buffer.append(espaco);
			buffer.append("          Maximo_Entidades++;");
			gravaArquivo(buffer);
		}
	}
*/	
	/**
	 * @param indice
	 * VER SE VAI TER ESTATISTICAS NO PARSMPL TODO :-(
	 */
/*	private void geraCodeEstatisticas(int indice)
	{
		buffer.delete(0,119);
		
		Node temp = graph.getNode(indice);
		if ( (temp.getEstatisticaFilaVazia()) || (temp.getComprimentoMaxMin()) )
		{	
			buffer.append("          Total_Clientes = inq(");
			buffer.append(temp.getNomeCentroServico());
			buffer.append(");");
			gravaArquivo(buffer);
			buffer.delete(0,119);
		}

		buffer.delete(0,119);
		
		if (temp.getComprimentoMaxMin())
		{
			buffer.append("          if (Total_Clientes > Max");
			buffer.append(temp.getIdNo());
			buffer.append(")\n");
			buffer.append("             Max");
			buffer.append(temp.getIdNo());
			buffer.append(" = Total_Clientes;\n");
			buffer.append("         else\n");
			buffer.append("          if (Total_Clientes < Min");
			buffer.append(temp.getIdNo());
			buffer.append(")\n");
			buffer.append("             Min");
			buffer.append(temp.getIdNo());
			buffer.append(" = Total_Clientes;");
			gravaArquivo(buffer);
			buffer.delete(0,119);
			
		}
		
		buffer.delete(0,119);
		
		if (temp.getEstatisticaFilaVazia())
		{
			buffer.append("          if (Total_Clientes == 0)\n");
			buffer.append("             Vaz");
			buffer.append(temp.getIdNo());
			buffer.append("++;\n");
			buffer.append("          Tot");
			buffer.append(temp.getIdNo());
			buffer.append("++;");
			gravaArquivo(buffer);
			buffer.delete(0,119);
		}
			
	}*/
	
	private int correctID(int id)
	{
		int ret = -1;
		
		for (int i = 0; ((i < graph.getSize()) && (ret == -1)); i++)
			if (graph.getNode(i).getIdNo() == id)
				ret = i;
		
		return ret;
		
	}

	private void geraIfAleatorio(int numInicial, int numFinal)
	{
		buffer.delete(0,119);
		buffer.append("          if (( " + 
				numInicial + " <= Aleatorio) && ( Aleatorio <= " + numFinal + ") )");
		gravaArquivo(buffer);
		
	}
	
	private void geraComentario(String comment, String espaco)
	{
		buffer.delete(0,119);
		if ((comment != null) && (espaco != null))
			buffer.append("\n" + espaco + "/* " + comment + " */" );
		gravaArquivo(buffer);
		buffer.delete(0,119);
		
	}
	
	private int indicePLogico(int tid)
	{
		for (int i=0; i < graph.getPLogicos().size(); i++)
		{
			if (((ProcessoLogicoParSMPL)graph.getPLogicos().get(i)).getTid() == tid)
			{
				return i;
			}
		}
		
		return -1;
			
	}
	
	/**
	 * @param tid
	 * 
	 */
	private void geraCase1000(int tid)
	{
		geraComentario("Término da simulação","        ");
		buffer.delete(0,119);
		if (tid == tidPai) // gera o case 1000 do processo pai
		{
			geraCase(1001);
			
			buffer.delete(0,119);
			buffer.append("          fim = 1;");
			gravaArquivo(buffer);
			
			geraBreak();		
		}
		else
		{
			// descobrindo em que indice do vetor de pLogicos está o tid
			// se indice = final - encontramos o ultimo pLogico - gera um case soh especial
			// senão, gera 2 cases, um para pl(indice+1) e outro para pl(indice-1)
			// OBS: não importa a ordem de parada dos processos lógicos - então tomou-se a abordagem sequencial
			int indice = indicePLogico(tid);
			if (indice == -1)
				JOptionPane.showMessageDialog(null,"Problema com alocação de tids - código gerado está incorreto\n +" +
						"Conserto Manual");
			else
			{
				int tidAnt, tidPos;
				tidAnt = ((ProcessoLogicoParSMPL)graph.getPLogicos().get(indice-1)).getTid();
				if (indice == graph.getPLogicos().size()-1) // caso dp PL final
				{
					geraCase(1000);
					geraSchedule(1001,"0.0","          ",tidAnt);
					
					buffer.delete(0,119);
					buffer.append("          fim = 1;");
					gravaArquivo(buffer);
					
					geraBreak();
				}
				else // outros PLS do meio (1000 passa sinal para frente, 1001 retorna sinal)
				{
					tidPos = ((ProcessoLogicoParSMPL)graph.getPLogicos().get(indice+1)).getTid();
					geraCase(1000);
					geraSchedule(1000,"0.0","          ",tidPos);
					geraBreak();
					
					geraCase(1001);
					geraSchedule(1001,"0.0","          ",tidAnt);
					
					buffer.delete(0,119);
					buffer.append("          fim = 1;");
					gravaArquivo(buffer);
					
					geraBreak();
					
				}
			}
					
		}

	}
	
	/**
	 * Método que analisa e verifica se já houve empilhamento do centro de serviço
	 * @param v Vetor que armazena o id de nós que já foram empilhados
	 * @param id O valor do id do centro de serviço que está consultando
	 * @return Retorna true se já foi empilhado, e false caso contrário
	 * @author André Felipe Rodrigues
	 */
/*	private boolean jahFoiEmpilhado(Vector v, int id)
	{
		boolean flag = false;
		int i = 0;
		boolean ret;

		if (v.size() == 0 ) // se vetor vazio
			ret = false;
		else
		{
			while ( (!flag) && ( i < v.size()) ) // percorre o vetor
			{
				String temp = (String)v.get(i);
				if ( Integer.parseInt(temp) == id ) // achou ocorrência do id no vetor
					flag = true;
				else
					i++;
			}		
			ret = ( i < v.size() ? true : false );
		}		
		return ret;
	}*/
	
	private void geraChaves(String espaco, boolean abre)
	{
		buffer.delete(0,119);
		if (abre)
			buffer.append(espaco + "{");
		else
			buffer.append(espaco + "}");
		gravaArquivo(buffer);
	}
	/**
	 * Gera os eventos que constituem a simulação.
	 * @author André Felipe Rodrigues
	 */
	private void geraEventos(int tid){
		
		int id = 0;		// variável que armazena o id do nó que está gerando eventos
		int indice = 0;		// variável que armazena o indice desse nó no vetor de nós do grafo - corretivo
		int numCase;
		
	//	StackL stack = new StackL(); 		// pilha que armazena os centros de seriço que serão processados
	//	Vector jahEmpilhados = new Vector(0); // armazena os id de centros de serviços que já foram processados
		

		if (tid == tidPrimRec)
		{
			for (int i = 0; i < graph.getSize(); i++){ // conta o número de fontes do grafo
				if (graph.getNode(i).isPrimRec()){
					id = graph.getNode(i).getIdNo();
					indice = correctID(id);
					numCase = c.getCase(id);
					geraCase(numCase);
				    geraProximaChegada(c.getRequest(id),indice,numCase,graph.getNode(i).getTid());
	/*				if (!jahFoiEmpilhado(jahEmpilhados, id))  // verifica se o id do cs já foi empilhado antes
					{	stack.push(String.valueOf(id)); // armazendo como Strings pq é object
						jahEmpilhados.add(String.valueOf(id));
					}*/
					geraBreak();
					break; // OBSERVAR AKI TBEM
				}
			}	
		}
			
		
		// ***** laço de geração de todos eventos *******
		while (!stack[tid].isEmpty()) // enquanto a pilha não está vazia
		{
			
			id = Integer.parseInt((String)stack[tid].pop()); // desempilha
			
			indice = correctID(id);	 
			
			// gerando comentário do centro de serviço
			geraComentario(" centro de serviço = " 
					+ graph.getNode(indice).getNomeCentroServico(),"        ");
			
			// ****** gerando request  ****
			geraCase(c.getRequest(id)); // gerando request do nó com identificação id			
			
		//	geraCodeEstatisticas(indice);
		//	geraStream(indice,"          ", false); não gera stream para cada nó no ParSMPL - é definido no pai
			
			// o tid no request não muda
			// o tid desses schedules também não (é atendimento de serviço, gera um schedule para o release
			// o release está sempre no mesmo processo lógico em que o nó está
			geraRequest(indice, graph.getNode(indice).getTid());
			String secParam = geraStringSchedule(indice,false);
			if ( (graph.getTamanhoBatch()!=null) && (!graph.getTamanhoBatch().equals("0")) )
			{
				geraChaves("          ",true);
				geraBatch(secParam);
				geraSchedule(c.getRelease(id),"TBatch","             ", graph.getNode(indice).getTid());
				geraChaves("          ", false);
			}
			else // para gerar estatísticas Batch
				geraSchedule(c.getRelease(id),secParam,"             ", graph.getNode(indice).getTid());
				
			geraBreak();
				
			// **** liberação do recurso ****
			geraCase(c.getRelease(id)); 
			geraRelease(indice);

			
			// ****** verifica as conexões do grafo e gera os schedule apropriados ********
			if (graph.getNode(indice).getSize() >= 2) // tem duas ligações - tbém tem que verificar fim do grafo
			{
				graph.getNode(indice).setProb(true);
				if (graph.getNode(indice).isProb()) // se é por probabilidade
				{
					buffer.delete(0,119);
					buffer.append("          Aleatorio = randompar(1,10000);");
					gravaArquivo(buffer);
					int cont = 0;
					int limiteInf = 1;
					int limiteSup;
					int idTemp; //,indiceProx ;
					while (cont < graph.getNode(indice).getSize() )
					{
						if (graph.getNode(indice).getArc(cont).getNodeB().getTipoNo() == 2) // é centro de serviço
						{
							double tempNumber;
							tempNumber = Double.parseDouble(graph.getNode(indice).getArc(cont).getProbabilidade());
							tempNumber = tempNumber*100 + limiteInf - 1;
							limiteSup = (int)tempNumber;
														
							geraIfAleatorio(limiteInf, limiteSup);
							limiteInf = limiteSup + 1;
							idTemp = graph.getNode(indice).getArc(cont).getNodeB().getIdNo();
							//indiceProx = correctID(idTemp);
							// String secParam2 = geraStringSchedule(indiceProx,false);
							geraSchedule(c.getRequest(idTemp),"0.0","           ",graph.getNode(indice).getArc(cont).getNodeB().getTid());
							buffer.delete(0,119); 
							
						/*	if (!jahFoiEmpilhado(jahEmpilhados, idTemp)) // depois de gerado if, empilha o recurso
							{
								stack.push(String.valueOf(idTemp)); // empilha recurso	
								jahEmpilhados.add(String.valueOf(idTemp));
							}	*/						
						}
						else
						{
							if ( 	(graph.getNode(indice).getArc(cont).getNodeB().getTipoNo() == 3) 
									&& (graph.getNumeroMaximoEntidades()!= null) 
									&& (!graph.getNumeroMaximoEntidades().equals("0")) ){ // está ligado ao nó final e gera MaximoEntidades
								double tempNumber;
								tempNumber = Double.parseDouble(graph.getNode(indice).getArc(cont).getProbabilidade());
								tempNumber = tempNumber*100 + limiteInf - 1;
								limiteSup = (int)tempNumber;
															
								geraIfAleatorio(limiteInf, limiteSup);
								limiteInf = limiteSup + 1;
			//					geraContagemMaximoEntidades(indice,"   ");								
								buffer.delete(0,119);
							}
							
				//			geraCase1000(tid); // case de finalização (saida do sistema)
							
						}
						cont++;	
					}
				}
				geraBreak();
			
			}
			else // só tem uma ligação possível - verificar se não é fim do grafo
			{
				if (graph.getNode(indice).getArc(0).getNodeB().getTipoNo() == 2) // não está ligado ao destino
				{
					Node temp = graph.getNode(indice).getArc(0).getNodeB();
					id = temp.getIdNo();
					indice = correctID(id);
			//		String secParam2 = geraStringSchedule(indice,false);
					geraSchedule(c.getRequest(id),"0.0","             ", temp.getTid());
					
			/*		if (!jahFoiEmpilhado(jahEmpilhados, id))
					{
						stack.push(String.valueOf(id)); // empilha recurso	
						jahEmpilhados.add(String.valueOf(id));
					}*/
				}
				else if (graph.getNode(indice).getArc(0).getNodeB().getTipoNo() == 3){ // está ligado a saída
			//		geraContagemMaximoEntidades(indice,"");
					//geraCase1000(tid);
				}
				geraBreak();
			}
		}
		geraCase1000(tid);
	}
	
	private void fechaArquivo()
	{
		if (!alreadyClosed)
		{
			buffer.delete(0,119);
			buffer.append("  fclose(saida);");
			gravaArquivo(buffer);
		}
			
	}
	
	/**
	 * Gera o relatório final (padrão do smpl) no programa de simulação.
	 *
	 */
	private void geraRelatorioFinal(int tid){
		
		buffer.delete(0,119);
		//buffer.append("   report();");
		
		buffer.append("  fprintf(saida,\"TempoSimulado: %f\\n\", clock_sim() );\n");
		gravaArquivo(buffer);
		
		buffer.delete(0,119);
		for (int i=0; i < graph.getSize(); i++)
		{
			Node temp = graph.getNode(i);
			if ((temp.getTipoNo()==2) && (temp.getTid() == tid))
			{
				buffer.append("  fprintf(saida,\"Utilizacao (\\\"" + temp.getNomeCentroServico() + "\\\") = %g\\n\", utilizacao_recurso(\"" + 
						temp.getNomeCentroServico() + "\"));");
				gravaArquivo(buffer);
				buffer.delete(0,119);
				buffer.append("  fprintf(saida,\"Comprimento medio fila (\\\"" + temp.getNomeCentroServico() + "\\\") = %g\\n\", comprimento_medio_fila(\"" + 
						temp.getNomeCentroServico() + "\"));");
				gravaArquivo(buffer);
				buffer.delete(0,119);
				buffer.append("  fprintf(saida,\"Periodo medio ocupado (\\\"" + temp.getNomeCentroServico() + "\\\") = %g\\n\", periodo_medio_ocupado(\"" + 
						temp.getNomeCentroServico() + "\"));");
				gravaArquivo(buffer);
				buffer.delete(0,119);
				
			}
		}
		gravaArquivo(buffer);
	}
	
	/**
	 * Gera as variáveis (contadores) para o caso de número de voltas definidas para os 
	 * clientes em um determinado servidor.
	 *
	 */
/*	private void geraContadores(){
		
		String nomeContador = "N";
		boolean flag = true;
		
		buffer.delete(0,119);
		
		int i = 0;
		
		while ((graph.getSize() > i) && (flag)){
			
			if (graph.getNode(i).isCiclo()){
				
				flag = false;
				
			}
		}
		
		if (!flag){
			
			
			
			buffer.append("   unsigned int ");
			
			do{
				
				buffer.append(nomeContador);
				buffer.append(graph.getNode(i).getIdNo());
				buffer.append(" = ");
				StringBuffer aux = new StringBuffer(graph.getNode(i).getNumVoltas());
				buffer.append(aux.reverse()); 
				i++;
				if (graph.getSize() > i){
					buffer.append(";");
				}
				else{
					buffer.append(", ");
				}
				
			} while(graph.getSize() > i);
			gravaArquivo(buffer);
			
		}
	}
	*/
	
	
	/**
	 * Gera relatório com as estatísticas das filas dos recursos especificados pelo usuário.
	 *
	 */
/*	private void geraRelatEstMaxMin(){
		
		buffer.delete(0,119);
		
		boolean title = false;
		
		for (int i = 0; i < graph.getSize(); i++)
		{
			Node temp = graph.getNode(i);
			if (temp.getTipoNo() == 2)
			{
				if (temp.getComprimentoMaxMin()) // tem que gerar para ComprimentoMaxMin
				{
					buffer.delete(0,119);
					if (!title)  // escreve título da geração de relatórios para esta estatística
					{
						buffer.append("   fprintf(saida,\"\\n\\nRelatório - Máximo e Mínimo das Filas \\n \"); ");
						gravaArquivo(buffer);
						buffer.delete(0,119);
						title = true;
					}
					
					buffer.append("   fprintf(saida,\"\\n Maximo clientes recurso "
							+ temp.getNomeCentroServico() 
							+ " : %i \", Max"
							+ temp.getIdNo()
							+ ");");
					gravaArquivo(buffer);
					
					buffer.delete(0,119);
					buffer.append("   fprintf(saida,\"\\n Mínimo clientes recurso "
							+ temp.getNomeCentroServico() 
							+ " : %i \", Min"
							+ temp.getIdNo()
							+ ");");
					gravaArquivo(buffer);
				}
								
			}
		}
		
	}
		*/

	/**
	 * Gera relatório com as estatísticas das filas dos recursos especificados pelo usuário: 
	 * porcentagem de vezes na qual o clienet encontra a fila vazia.
	 */
/*	private void geraRelatFilaVazia(){
		
		buffer.delete(0,119);
		
		boolean title = false;
		
		for (int i = 0; i < graph.getSize(); i++)
		{
			Node temp = graph.getNode(i);
			if (temp.getTipoNo() == 2)
			{
				if (temp.getComprimentoMaxMin()) // tem que gerar para ComprimentoMaxMin
				{
					buffer.delete(0,119);
					if (!title)  // escreve título da geração de relatórios para esta estatística
					{
						buffer.append("   fprintf(saida,\"\\n\\nRelatório - Total de Vezes - Fila Vazia \\n \"); ");
						gravaArquivo(buffer);
						buffer.delete(0,119);
						title = true;
					}
					
					buffer.append("   fprintf(saida,\"\\n Total de Clientes do recurso "
							+ temp.getNomeCentroServico() 
							+ " : %i \", Tot"
							+ temp.getIdNo()
							+ ");");
					gravaArquivo(buffer);
					
					buffer.delete(0,119);
					buffer.append("   fprintf(saida,\"\\n Total clientes que encontraram fila vazia no recurso "
							+ temp.getNomeCentroServico() 
							+ " : %i \", Vaz"
							+ temp.getIdNo()
							+ ");");
					gravaArquivo(buffer);
				}
								
			}
		}
		
	
	}
	
	
*/
	
	
	private void geraDefPLogicos()
	{
		ProcessoLogicoParSMPL temp;
		for (int i=0; i < graph.getPLogicos().size(); i++)
		{
			temp = (ProcessoLogicoParSMPL)graph.getPLogicos().get(i);
			buffer.delete(0,119);
			buffer.append("#define PL" + temp.getTid() + "   " + temp.getTid());
			gravaArquivo(buffer);
		}
		
	}
	
	private void paiRegistraPvm(int tid)
	{
		if (tid == tidPai)
		{
			buffer.delete(0,119);
			geraComentario("identifica processo pai", "  ");
			buffer.append("  tid_processo_pai = pvm_mytid();");
			gravaArquivo(buffer);
			buffer.delete(0,119);
		/*	geraComentario("pega tempo inicial de spawn","  " );
			buffer.append("gettimeofday (&t3, (struct timezone*)0);");
			gravaArquivo(buffer);*/
		}
	}
	
	
	private void geraPvmSpawn()
	{
		buffer.delete(0,119);
		
		for (int i=0; i < graph.getPLogicos().size(); i++)
		{
			int tidAtual = ((ProcessoLogicoParSMPL)(graph.getPLogicos().get(i))).getTid();
		
			if (tidAtual != tidPai)
			{
				buffer.append("  info = pvm_spawn(SLAVENAME" + tidAtual + ", (char**)0, 0, \"\", 1, &tid_pl" + tidAtual + ");");
				gravaArquivo(buffer);
				buffer.delete(0,119);
				buffer.append("  if ( info < 1)\n");
				buffer.append("  {\n       printf(\"Trouble spawning slaves. Aborting. Error codes are:\\n\");");
				gravaArquivo(buffer);
				buffer.delete(0,119);
				buffer.append("       printf(\"TID %d\\n\", tid_pl" + tidAtual + ");");
				gravaArquivo(buffer);
				buffer.delete(0,119);
				
				for (int j=i; j >= 0; j--) // gera pvm_kill de processos já startados
				{
					int tidAux = ((ProcessoLogicoParSMPL)(graph.getPLogicos().get(j))).getTid();
					if (tidAux != tidPai)  
					{
						buffer.delete(0,119);
						buffer.append("       pvm_kill( tid_pl" + tidAux + ");");
						gravaArquivo(buffer);
					}
				}
				
				buffer.delete(0,119);
				buffer.append("       pvm_exit();\n       exit(1);\n  }");
				gravaArquivo(buffer);
				buffer.delete(0,119);
				
			}
				
		}
			
	}
	
	private void paiPreparaTabelas(int tid)
	{
		
		buffer.delete(0,119);
		if (tid == tidPai)
		{
			geraComentario("inicializa tabela de tids","  ");
			buffer.delete(0,119);
			buffer.append("  for (i=0; i < " + graph.getPLogicos().size() + "; i++)\n");
			buffer.append("  {\n");
			buffer.append("      tabela_tids[i] = 0;\n");
			buffer.append("  }");
			gravaArquivo(buffer);
			
			geraPvmSpawn();

			buffer.delete(0,119);
			buffer.append("  tabela_tids[PL" + tidPai + "]");
			buffer.append(" = tid_processo_pai;");
			gravaArquivo(buffer);
			
			// associando tids de escravos à tabela
			for (int i=0; i < graph.getPLogicos().size(); i++)
			{
				int tidAtual = ((ProcessoLogicoParSMPL)(graph.getPLogicos().get(i))).getTid();
				if (tidAtual != tidPai)
				{
					buffer.delete(0,119);
					buffer.append("  tabela_tids[PL" + tidAtual + "] = tid_pl" + tidAtual + ";");
					gravaArquivo(buffer);
				}
			}
		}
	}
	
	
	private void defineSlaveNames()
	{
	
		for (int i=0; i < graph.getPLogicos().size(); i++)
		{
			ProcessoLogicoParSMPL temp = (ProcessoLogicoParSMPL)(graph.getPLogicos().get(i));
			int tidAtual = temp.getTid();
			
			if (tidAtual != tidPai)
			{
				StringBuffer stemp = new StringBuffer(filename);
				stemp.delete(stemp.length()-2,stemp.length());
				
			
				buffer.delete(0,119);
				// colocando caminho completo
				buffer.append("#define SLAVENAME" + tidAtual + "   \"" + System.getProperty("user.dir") + "/src/" + graph.getNomeModelo() + "_" + tidAtual + "\"");
				gravaArquivo(buffer);
			}
		}
	}
	
	private void paiEnviaTabelas()
	{
		buffer.delete(0,119);
		buffer.append("  pvm_pkint(tabela_tids," + graph.getPLogicos().size() + ", 1);");
		gravaArquivo(buffer);
		buffer.delete(0,119);
		 
		geraComentario(" Envia o valor da semente para os processos filhos "," ");
		
		buffer.delete(0,119);
		buffer.append("  pvm_pkint(&valor_semente,1,1);");
		gravaArquivo(buffer);
		
		// enviando os dados para os filhos
		for (int i=0; i < graph.getPLogicos().size(); i++)
		{
			int tidAtual = ((ProcessoLogicoParSMPL)(graph.getPLogicos().get(i))).getTid();
			if (tidAtual != tidPai)
			{
				buffer.delete(0,119);
				buffer.append("  pvm_send(tid_pl" + tidAtual + ", 0);");
				gravaArquivo(buffer);
			}
		}
		
		
	}
	
	
	private void defineVarPls()
	{
		buffer.delete(0,119); 
		buffer.append(" int tid_processo_pai, ");
		for (int i = 0; i < graph.getPLogicos().size(); i++)
		{
			int tidAtual = ((ProcessoLogicoParSMPL)(graph.getPLogicos().get(i))).getTid();
			if (tidAtual != tidPai)
			{
				buffer.append("tid_pl" + tidAtual);
				buffer.append(", ");				
			}
		}
		buffer.deleteCharAt(buffer.lastIndexOf(","));
		buffer.append(";");
		gravaArquivo(buffer);
	}
	
	private void iniciaClockCanais(int tid)
	{
		{
			buffer.delete(0,119);
			buffer.append("  proc_local = PL" + tid + ";");
			gravaArquivo(buffer);
			
			for (int i=0; i < graph.getPLogicos().size(); i++)
			{
				int tidAtual = ((ProcessoLogicoParSMPL)(graph.getPLogicos().get(i))).getTid();
				if (tidAtual != tid)
				{
					buffer.delete(0,119);
					buffer.append("  clock_canais[PL" + tidAtual + "] = 0.0;");
					gravaArquivo(buffer);
				}
			}
		}
	}
	
	private void geraStream(String arg)
	{
		buffer.delete(0,119);
		buffer.append("  stream(" + arg + ");");
		gravaArquivo(buffer);
	}
	
	private void defineMyTid(int tid)
	{
		if (tid != tidPai)
		{
			buffer.delete(0,119);
			buffer.append(" int my_tid;");
			gravaArquivo(buffer);
		}
	}
	
	private void defineValorSemente(int tid)
	{
	//	if (tid == tidPai)
	//	{
			buffer.delete(0,119);
			buffer.append(" int valor_semente = 1;");
			gravaArquivo(buffer);
//		}
	}
	
	private void escravoRecebeTabelaTid(int tid)
	{
		if (tid != tidPai)
		{
			buffer.delete(0,119);
			buffer.append("  pvm_recv(tid_processo_pai, " + tidPai + ");\n");
			buffer.append("  pvm_upkint(tabela_tids, " + 
					graph.getPLogicos().size() + ", 1);\n");
			buffer.append("  pvm_upkint(&valor_semente,1,1);");
			gravaArquivo(buffer);
		}
		
	}
	
	
	/**
	 * 
	 */
	public void leGabarito(String gabarito)
	{
		// criar um gabarito de controle
		// aqui vai chamando a leitura de gabarito - se for filho, chama um gabarito, se for pai chama outro
		
		int plAtual=0;
		int pl=0;
		int plPai=0;
		boolean achouPai=false;
		
		
	    
		while (pl < graph.getPLogicos().size())
		{
			if ( (!achouPai) && ((ProcessoLogicoParSMPL)graph.getPLogicos().get(pl)).isProcessoPai())
			{
				plPai = pl;
				achouPai = true;
			}
			
			plAtual = ((ProcessoLogicoParSMPL)graph.getPLogicos().get(pl)).getTid();
			if ((achouPai) && (plAtual == plPai))
			{  
			    criaArquivo(graph.getNomeModelo()+ "_PAI_" + plAtual); // cria o pl pai
			    leGabarito2("gabaritos/GABARITO_PAI.DAT", plAtual); // gabarito para o pai			    
			}
			else
			{			
				criaArquivo(graph.getNomeModelo()+ "_" + plAtual); // para cada processo lógico vai criar um arquivo .c
				leGabarito2("gabaritos/GABARITO_PL.DAT", plAtual); //  gabarito para o filho
			}		
			
			pl++;		
			
		}
		
		tidPai = plPai;
		criaMakeFile();
		
		
	}
	
	
	/**
	 * Cria o Makefile do ParSMPL de acordo com os nomes dos arquivos criados
	 * 
	 */
	private void criaMakeFile()
	{
		File f = new File("src/Makefile.aimk");

		if (f.exists())
			f.delete();
		
			try {
				FileWriter fw = new FileWriter(f,true);
				
				FileReader fr = new FileReader("gabaritos/MAKEFILEGAB.DAT");
				BufferedReader gab = new BufferedReader(fr);
				String linha = new String();
				while (( linha = gab.readLine()) != null)
				{
					if (linha.indexOf("%")!=0) //copiar toda a linha
					{
						fw.write(linha);	
						fw.write("\n");
					}
					else
					{
						switch (linha.charAt(1))
						{
							case '1':
								fw.write(new String("CPROGS	=	"));
								for (int i=0; i < graph.getPLogicos().size(); i++)
								{
									ProcessoLogicoParSMPL pl = (ProcessoLogicoParSMPL)graph.getPLogicos().get(i);
									if (pl.isProcessoPai())
									{
										fw.write(graph.getNomeModelo() + "_PAI_" + pl.getTid()+ "\t");
									}
									else
									{
										fw.write(graph.getNomeModelo() + "_" + pl.getTid()+ "\t");
									}
								}
								fw.write("\n");
								break;
							case '2':
								for (int i=0; i < graph.getPLogicos().size(); i++)
								{
									ProcessoLogicoParSMPL pl = (ProcessoLogicoParSMPL)graph.getPLogicos().get(i);
									if (pl.isProcessoPai())
									{
										fw.write(graph.getNomeModelo() + "_PAI_" + pl.getTid() + 
												": $(SDIR)/" + graph.getNomeModelo() + "_PAI_" + pl.getTid() + ".c" + 
												" $(XDIR) $(CC) $(CFLAGS) -o $@ $(SDIR)/" + 
												graph.getNomeModelo() + "_PAI_" + pl.getTid() + ".c" + 
												" ../randpar.o ../parsmpl.o $(LFLAGS) $(LIBS)\n\n");
									}
									else
									{
										fw.write(graph.getNomeModelo() + "_" + pl.getTid() + 
												": $(SDIR)/" + graph.getNomeModelo() + "_" + pl.getTid() + ".c" + 
												"$(XDIR)	$(CC) $(CFLAGS) -o $@ $(SDIR)/" + 
												graph.getNomeModelo() + "_" + pl.getTid() + ".c" +
												 " ../randpar.o ../parsmpl.o $(LFLAGS) $(LIBS)\n\n");
									}
								}								
								break;
						    
						}
					}
				}
					fw.close();
				
				
			} catch (IOException e) {
				JOptionPane.showMessageDialog(
						null,
						"ASDA - ERRO",
						"Não foi possível criar arquivo Makefile.aimk",
						JOptionPane.ERROR_MESSAGE);
				e.printStackTrace();
			}
			
			
		}
		
	
	
	/**
	 * Através dos comandos do arquivo gabarito determina a próxima primitiva a 
	 * ser executada.
	 *
	 */
	private void leGabarito2(String gabarito, int tid){
		
		FileReader arq;
		try {
			arq = new FileReader(gabarito);
			BufferedReader sai = new BufferedReader(arq);		
			String linha = new String();
			while ((linha = sai.readLine()) != null){
				if (linha.indexOf("%") != 0){ // se não começa com %, então copia toda a linha	
					buffer.delete(0,119);
					buffer.append(linha);
					gravaArquivo(buffer);
					buffer.delete(0,119);
				}								
				else{					
					//primitivas do gerador devem ser executadas
					switch (linha.charAt(1))
					{
						case '0': defineTempoMax(tid); 
								  break;
						case '1': //definições
								  defineVarTempos(tid); 
					//			  defineVarWarmUp(tid);    // não implementando warm-up por enquanto
								//  defineVarServer(tid);  // não precisa - os servers são strings no método agora
						//		  defineEstatMaxMin(tid);  
						//		  defineEstatFilaVazia(tid);
								  defineMaximoClientes();
						//		  defineBMeans();
								  defineLookAheadPL(tid);
								  defineValorSemente(tid);
								  defineVarPls();
								  defineMyTid(tid); // soh para filhos
								  defineAuxiliares(tid);
								  defineArqSaida(tid);	
								  break;
						case '2': nomeParametro(tid);
						          geraStream("valor_semente");
								break;
								//definição dos recursos do modelo
						case '3': geraDefServer(tid);
								break;
								//escalona eventos antes do inicio da simulação
						case '4': geraPrimeiroEvento(tid); 
								break;
								//limitante da simulação*/
						case '5': geraLoop();

								break;
						case '6': geraCause();
								break;
						case '7': geraSwitch();
								break;
								//eventos que constituem a simulação
						case '8': geraEventos(tid);
								break;
								//relatório padrão - colocar o if
						case '9': geraRelatorioFinal(tid);
								break;
						/*		  //definições
						case 'A': geraContadores();
								  break;
								  */
								  //relatório de estatísticas
						case 'C': //geraRelatEstMaxMin();
								  break;
								  //relatório de estatísticas
						case 'D': //geraRelatFilaVazia();
								  break;
								
								  //implementa warmup - not yet
						case 'G': //geraWarmUp();
								  break;
						
						case 'E': fechaArquivo();
								  break;	
								  
						case 'H': geraDefPLogicos();
							      break;
					    case 'I': defineSlaveNames(); 
					              break;
					    case 'J': paiRegistraPvm(tid);
					    		  break;
					    case 'K': paiPreparaTabelas(tid);
				    		  break;
					    case 'L':  paiEnviaTabelas();
				    		  break;
					    case 'M': // escravoIniciaTid();
				    		  break;
					    case 'N':  escravoRecebeTabelaTid(tid);
				    		  break;
					    case 'O': iniciaClockCanais(tid);
				    		  break;
				        case 'P': // parada da simulação no pai
				        	  geraParada(tid);
				        	  break;
					    
					}
				
				}
			
			}
			sai.close();
			


		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
					
	}
	
	/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& CLASSE INTERNA CONTROLER &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
	/**
	 * Classe interna que auxilia a geração de código
	 * responsável por organizar o número do evento para cada nó (os cases)
	 * Com essa classe agora é possível, sabendo-se o id do nó do grafo,
	 * saber qual o número do evento request e release respectivos
	 * @author André
	 */
	private class Controler
	{
		private int nRequest[];
		private int nRelease[];
		private int nCase[];
		private int id[];
		
		
		public Controler(Graph g)
		{
			this(g,2,3);
		}
		
		/**
		 * Construtor da classe Controler
		 * Cria os vetores de armazenamento já com os valores corretos
		 * para os releases e requests de cada nó.
		 * @param g Grafo da classe gerador já consistente e existente
		 */
		public Controler(Graph g, int num1, int num2)
		{
			int n = 0;
			
			for (int i = 0; i < graph.getSize(); i++)
			{
				if (g.getNode(i).getTipoNo() == 2) // contagem dos nós centro de serviço
					n++;
			}
			
			nRequest = new int[n];  // alocagem de memória
			nRelease = new int[n];
			id = new int[n];
			nCase = new int[n];
			
			for (int i=0; i < n; i++){ // zera todos valores nCase
				nCase[i] = 0;
			}
			
			int contador1=num1, contador2=num2; // contadores auxilires começando com 2 e 3
			
			for (int i = 0, j = 0; i < g.getSize(); i++)  // atribuição dos valores request e release
			{
				if (g.getNode(i).getTipoNo() == 2)
				{
					id[j] = g.getNode(i).getIdNo();
					nRequest[j] = contador1;
					nRelease[j] = contador2;
					contador1 += 2;
					contador2 += 2;					
					j++;								
				}
			}
		}
		
		/**
		 * retorna o valor do case request para o no <code> idN </code>
		 * @param idN id do nó que se quer saber o request especificado
		 * @return retorna o valor do request especificado para idN
		 * retorna 0 se não encontrado (note que não será gerado nenhum case 0:
		 * portanto, o retorno de zero representa algum erro
		 */
		public int getRequest(int idN)
		{
			int retorno = 0;
			int i = 0;
			boolean flag = true;
			while ( (flag) && (i < id.length)) // procura do nó pelo vetor
			{
				if (id[i] == idN)
				{
					retorno = nRequest[i];
					flag = false;
				}
				i++;
			}			
			return retorno; 			
		}
		
		/**
		 * retorna o valor do case release para o no <code> idN </code>
		 * @param idN id do nó que se quer saber o request especificado
		 * @return retorna o valor do release especificado para idN
		 * retorna 0 se não encontrado (note que não será gerado nenhum case 0:
		 * portanto, o retorno de zero representa algum erro
		 */
		public int getRelease(int idN)
		{
			int retorno = 0;
			int i = 0;
			boolean flag = true;
			while ( (flag) && (i < id.length))
			{
				if (id[i] == idN)
				{
					retorno = nRelease[i];
					flag = false;
				}
				i++;
			}			
			return retorno;			
		}
		
		/**
		 * retorna o valor do case armazenado para o nó <code> idN </code>
		 * @param idN id do nó que estamos procurando o valor do case
		 * @return retorna o número do case apropriado para o nó
		 */
		public int getCase(int idN)
		{
			int retorno = 0;
			int i = 0;
			boolean flag = true;
			while ( (flag) && (i < id.length))
			{
				if (id[i] == idN)
				{
					retorno = nCase[i];
					flag = false;
				}
				i++;
			}			
			return retorno;	
		}
		
		/**
		 * coloca o valor de case inicial para o nó (usado para nós fonte (source))
		 * @param valorCase valor do case que queremos colocar
		 * @param idNo id do nó que deve ser colocado o valor do case inicial
		 */
		public void setCase(int valorCase, int idNo)
		{
			int i = 0;
			boolean flag = true;
			while ( (flag) && (i < id.length))
			{
				if (id[i] == idNo) // achou o o lugar certo para a atribuição
				{
					nCase[i] = valorCase;
					flag = false;
				}
				i++;
			}				
		}
		
		/**
		 * Método que imprime no console os valores dessa estrutura inteira
		 * Método utilizado para testes da classe
		 */
		public void print()
		{
			for (int i = 0; i < id.length; i++)
			{
				System.out.println("\nID = " + id[i]);
				System.out.println("Numero Request = " + nRequest[i]);
				System.out.println("Numero Release = " + nRelease[i]);
				System.out.println("Valor do case (valor = 0 -> não nó source): " + nCase[i]);
			}
		}		
		
		/* &&&&&&&&&&&&&&&&&&&&&&&&&& FIM DA CLASSE INTERNA &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
		
		

	}

}