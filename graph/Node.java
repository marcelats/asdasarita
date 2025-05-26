package graph;

import java.util.Vector;
import javax.swing.*;

import avaliador.AvaliadorNivelUmA;

import java.awt.Point;
import java.io.*;

/**  
  * Representa cada vértice (<code>Node</code>) do modelo (<code>Graph</code>). Isto é, os 
  * templates fonte, centro de serviço e sorvedouro do modelo. 
  *  
  * @author Thais Souza Aiza
  * @author André Felipe Rodrigues (algumas modificações)
  * @version 1.0
  */ 

public class Node implements Serializable{
	
	
    /**
     * Indica qual template foi inserido no modelo (<code>Graph</code>).
     */
	private ImageIcon img;

	/**
	 * Representa em qual coordenada x a imagem (template) foi inserida.
	 */
	private int x;

	/**
	 * Representa em qual coordenada y a imagem (template) foi inserida.
	 */
	private int y;
	
	/**
	 * Indica qual o tipo de </code>Node</code> que foi inserido no modelo.
	 */	
	private int tipoNo;
	
	/**
	 * Identifica o </code>Node</code> com uma chave única.
	 */
	private int idNo;
	
	/**
	 * Representa cada <code>Node</code> do modelo através de um nome.  
	 */	
	private String nomeCentroServico;
	
	/**
	 * Define o número de servidores do centro de serviço.
	 */
	private String numServidores;
	
	/**
	 * Indica qual a distribuição de serviço para cada centro de serviço.
	 */
	private String distribuicaoServico;	
	
	/**
	 * Indica qual o parâmetro analisado durante a simulação para o centro de
	 * serviço. Cada centro de serviço pode ter um ou mais parâmetros.
	 */
	private boolean tempoResposta;

	/**
	 * Indica qual o parâmetro analisado durante a simulação para o centro de
	 * serviço. Cada centro de serviço pode ter um ou mais parâmetros.
	 */
	private boolean throughput;
	
	/**
	 * Indica qual o parâmetro analisado durante a simulação para o centro de
	 * serviço. Cada centro de serviço pode ter um ou mais parâmetros.
	 */
	private boolean tamanhoFila;

	/**
	 * Indica qual a distribuição de chegada dos clientes para o template fonte.	 
	 */	
	private String distribuicaoChegada;
	
	/**
	 * Indica se serão geradas estatísticas da porcentagem de vezes em que o cliente
	 * encontrou fila vazia.
	 */
	private boolean estatisticaFilaVazia;

    /**
     * Indica se serão geradas estatísticas para o cálculo do número de clientes em 
     * cada fila.
     */
	private boolean comprimentoMaxMin;
	
	/**
	 * Define o número de filas do centro de serviço. Se o recurso tiver várias 
	 * filas em paralelo.
	 */
	private int numFilas;
	
	/**
	 * comentas 
	 */
	private String mediaFonte;
	
	/**
	 * Indica qual a seqüência a ser utilizada na geração do número 
	 * aleatório (fonte).
	 */
	private String sequenciaFonte;
	
	/**
	 * comentas
	 */
	private String media;

	/**
	 * Indica qual a seqüência a ser utilizada na geração do número 
	 * aleatório (centro de serviço).
	 */
	private String sequencia;
	
	/**
	 * Indica o desvio padrão - utilizado para probabilidades diferente da exponencial
	 */
	private String desvioPadrao;
	
	private String desvioPadraoFonte;
	
	
	/**
	 * Ponto mais provável - utilizado na distribuição triangular
	 */
	private String pontoMaisProvavel;
	
	private String pontoMaisProvavelFonte;
	/**
	 * Indica o número de voltas
	 */	
	private String numVoltas;
	
	/**
	 * Indica se o centro de serviço é o primeiro recurso do modelo.
	 */
	private boolean primRec;
	
//	public Ligacao proximoRecurso; //proximo recurso
			
	
	/**
	 * Indica se a escolha do próximo recurso é por probabilidade.	  
	 */
	private boolean prob;
	
	/**
	 * Indica se a escolha do próximo recurso é por número de voltas.
	 */
	private boolean ciclo;	
			
	/**
	 * Indica o número de arestas que o nó possuiu.
	 */
	private int chega;	
	
	/**
	 * Verifica se as todas as ligações do modelo <code>Graph</code> estão corretas.
	 */
	

	/**
	 *  Vetor que armazena as arestas (<code>Arc</code>).
	 *  Inicializado com 0, mas ele vai crescendo a medida 
	 *  que novas arestas vão sendo inseridas.
	 */
	private Vector arcs = new Vector(0);
	
	
	/**
	 * Para saber de qual processo lógico esse centro de serviço pertece
	 * Obs: somente é aceito processos lógicos previamente criados no modelo
	 */
	private int tid;
	
	
	/*
	 * Vetor que armazena todos os destinos dos arcos que originam de um determinado nó
	 */
	 

	// Vector ligacoes = new Vector(10);
	 
	/**	 
	 * Construtor da classe.
	 * @param x armazena a posição x (em pixels) da figura.
	 * @param y armazena a posição y (em pixels) da figura.
	 * @param img guarda a imagem desenhada.
	 * @param tipoNo armazena qual é o tipo do vértice (<code>Node</code>).              
	 *               - 1: Fonte
	 * 				 - 2: Centro de Serviço
	 *               - 3: Sorvedouro 	
	 * @param chega utilizado para verificar se os nós do tipo 2 e 3 são destinos de arcos.						
	 * @param nomeCentroServico armazena o nome do centro de serviço. Se o nó for do tipo 1 o valor 
	 * armazenado será "fonte" e se for do tipo 3 será "sorvedouro".  
	 */

	public Node(int x, int y, ImageIcon img, int tipoNo, int idNo, int chega, String nomeCentroServico){
		this.x = x;
		this.y = y;
		this.img = img;		
		this.tipoNo = tipoNo;
		this.idNo = idNo;
		this.chega = chega;
		this.nomeCentroServico = nomeCentroServico;
	
	}


	/**	 
	 * Construtor da classe.
	 * @param x armazena a posição x (em pixels) da figura.
	 * @param y armazena a posição y (em pixels) da figura.
	 * @param img  guarda a imagem desenhada.
	 * @param tipoNo armazena qual é o tipo do vértice (<code>Node</code>).              
	 *               - 1: Fonte
	 * 				 - 2: Centro de Serviço
	 *               - 3: Sorvedouro 							
	 * @param nomeCentroServico armazena o nome do centro de serviço. Se o nó for do tipo 1 o valor 
	 * armazenado será "fonte" e se for do tipo 3 será "sorvedouro".  
	 */
	
	public Node(int x, int y, ImageIcon img, int tipoNo, int idNo, String nomeCentroServico){
		this.x = x;
		this.y = y;
		this.img = img;		
		this.tipoNo = tipoNo;
		this.idNo = idNo;
		this.nomeCentroServico = nomeCentroServico;
	}
	
	

	/**
	 * Retorna a posição x do nó (<code>Node</code>).
	 * @return Um valor <code>Integer</code> que especifica a posição x em pixels 
	 * do nó.
	 */
	public int getX(){
		return this.x;
	}
	
	/**
	 * Retorna a posição y do nó (<code>Node</code>).
	 * @return Um valor <code>Integer</code> que especifica a posição y em pixels 
	 * do nó.
	 */
	public int getY(){
		return this.y;
	}
	
	/**
	 * Retorna o tamanho do vetor de arcos.
	 * @return Um valor <code>Integer</code>.
	 */
	public int getSize(){        
		return arcs.size();
	}
	
	/**
	 * Configura o nome do centro de serviço.
	 * @param nomeCentroServico Um valor <code>String</code> que contém 
	 * somente caracteres alfanuméricos (0..9,a..z,A..Z).
	 */
	public void setNomeCentroServico(String nomeCentroServico){
		this.nomeCentroServico = nomeCentroServico;
	}
	
	/**
	 * Configura o número de arestas que o nó é destino.
	 * Toda vez que uma nova aresta é adicionada ao nó de destino o valor de
	 * <code>chega</code> é incrementado. 
	 * @param aux Um valor <code>Integer</code> que é acrescentado a <code>chega</code>.
	 */
	public void setChega(int aux){		
		this.chega = this.chega + aux;		
	}
	
	/**
	 * Configura a distribuição de chegada dos clientes.
	 * As distribuições podem ser:
	 *  - Exponencial (expntl);
	 *  - Hiperexponencial;
	 *  - Erlang;
	 *  - Triangular;
	 *  - Uniforme;
	 *  - Do Usuário. 
	 * @param distribuicaoChegada Um valor <code>String</code> que recebe um valor pré-
	 * definido que depende do tipo de distribuição escolhida. A versão 1.0 do ASDA só 
	 * permite distribuições exponenciais (expntl).
	 */
	public void setDistribuicaoChegada(String distribuicaoChegada){
		this.distribuicaoChegada = distribuicaoChegada;
	}

	/**
	 * Configura a distribuição de serviço.
	 * As distribuições podem ser:
	 *  - Exponencial (expntl);
	 *  - Hiperexponencial;
	 *  - Erlang;
	 *  - Triangular;
	 *  - Uniforme;
	 *  - Do Usuário. 
	 * @param distribuicaoServico Um valor <code>String</code> que recebe um valor pré-
	 * definido que depende do tipo de distribuição escolhida. A versão 1.0 do ASDA só 
	 * permite distribuições exponenciais (expntl).
	 */
	
	public void setDistribuicaoServico(String distribuicaoServico){
		this.distribuicaoServico = distribuicaoServico;
	}


	/*
	 * vetor sai
	 */
	 
/*	public void addLigacao(Ligacao proximoRecurso){
		ligacoes.add(proximoRecurso);		
	}	 
	
	public void setLigacao(int destino){
		Ligacao proximoRecurso = new Ligacao(destino);
		
		ligacoes.add(proximoRecurso);
		
	}
	



	public void removeLigaco(int idNo){
		this.ligacoes.remove(idNo);
	}
*/

    /**
     * Configura quais parâmetros serão analisados. 
     * @param varTempoResposta Um valor <code>boolean</code> que quando verdadeiro o 
     * parâmetro Tempo de Resposta será analisado.
     */	
	public void setTempoResposta(boolean varTempoResposta){
		this.tempoResposta = varTempoResposta;
	}
	
	/**
	 * Configura quais parâmetros serão analisados.
	 * @param varThroughput Um valor <code>boolean</code> que quando verdadeiro o 
     * parâmetro Throughput será analisado.
	 */	
	public void setThroughput(boolean varThroughput){
		this.throughput = varThroughput;
	}
	
	/**
	 * Configura quais parâmetros serão analisados.
	 * @param varTamanhoFila Um valor <code>boolean</code> que quando verdadeiro o 
     * parâmetro Tamanho da Fila será analisado.
	 */
	public void setTamanhoFila(boolean varTamanhoFila){
		this.tamanhoFila = varTamanhoFila;
	}
	
	/**
	 * Configura se serão geradas estatísticas para o cálculo da porcentagem de vezes em 
	 * que o cliente encontra a fila vazia
	 * @param estatisticaFilaVazia Um valor <code>boolean</code>.
	 */
	public void setEstatisticaFilaVazia(boolean estatisticaFilaVazia){
		this.estatisticaFilaVazia = estatisticaFilaVazia;
	}

	/**
	 * Configura  se serão geradas estatísticas para o cálculo do número de clientes em 
     * cada fila.
	 * @param comprimentoMaxMin Um valor <code>boolean</code>.
	 */
	public void setComprimentoMaxMin(boolean comprimentoMaxMin){
		this.comprimentoMaxMin = comprimentoMaxMin;
	}
	
	/**
	 * Configura o número de filas do centro de serviço se o recurso tiver várias filas em 
	 * paralelo
	 * @param numFilas Um valor <code>Integer</code> maior ou igual a 0 (zero).
	 */
	public void setNumFilas(int numFilas){
		this.numFilas = numFilas;
	}
	
	/**
	 * Configura o número de servidores do centro de serviço.
	 * @param numServidores Um valor <code>Integer</code> maior ou igual a 0 (zero).
	 */
	public void setNumServidores(String numServidores){
		this.numServidores = numServidores;
	}

	/**
	 * 
	 * @param media
	 */
	public void setMedia(String media){
		this.media = media;
	}
	
	/**
	 * Configura qual a seqüência a ser utilizada na geração do número 
	 * aleatório. 
	 * @param sequencia Um valor <code>Integer</code> compreendido entre 0..15.
	 */
	public void setSequencia(String sequencia){
		this.sequencia = sequencia;
	}
	
	/**
	 * 
	 * @param numVoltas
	 */
	public void setNumVoltas(String numVoltas){
		this.numVoltas = numVoltas;
	}

	/*public Ligacao getLigacao(int i){
		return (Ligacao)ligacoes.get(i);
	}
	
	public int getIdNoProximoRecurso(int i){
		Ligacao ligacao = (Ligacao)ligacoes.get(i);		
		return ligacao.idNoDestino;
	}
	
	public int getLigacoesSize(){
		return ligacoes.size();
	}
	*/
    /**
     * Representa a localização no espaço de coordenadas (x,y).  
     * @param p Um valor <code>Integer</code>.
     */
	public void setPosition(Point p){
		this.x = (int) p.getX();
		this.y = (int) p.getY();
	}
	
	/**
	 * Retorna a identificação do nó (<code>Node</code>). Cada nó possui um valor único que 
	 * serve para identificá-lo no modelo (<code>Graph</code>). O valor inicial do primeiro 
	 * nó do modelo começa com 0 (zero).
	 * @return Um valor <code>Integer</code> maior ou igual a 0.
	 */
	public int getIdNo(){
		return this.idNo;
	}
	
	/**
	 * Retorna o tipo do nó. Cada nó pode ser de 3 tipos:
	 *  1 - fonte;
	 *  2 - centro de serviço;
	 *  3 - sorvedouro. 
	 * @return Um valor <code>Integer</code> compreendido entre 1..3.
	 */
	public int getTipoNo(){
		return this.tipoNo;
	}

    /**
     * Retorna o nome do centro de serviço.  
     * @return Um valor <code>String</code> que contém somente caracteres alfanuméricos
     * (0..9,a..z,A..Z). Se o nó for do tipo 1 o valor de retorno será fonte e se o nó 
     * for do tipo 3 o valor retornado será sorvedouro.
     */
	public String getNomeCentroServico(){
		return this.nomeCentroServico;
	}
	
	/**
	 * Retorna a distribuição de chegada escolhida pelo usuário.
	 * @return Um valor <code>String</code>. A versão 1.0 do ASDA só permite distribuições 
	 * exponenciais. Valor de retorno "expntl". 
	 */
	public String getDistribuicaoChegada(){
		return this.distribuicaoChegada;
	}

	/**
	 * Retorna a distribuição de serviço escolhida pelo usuário.
	 * @return Um valor <code>String</code>. A versão 1.0 do ASDA só permite distribuições 
	 * exponenciais. Valor de retorno "expntl". 
	 */	
	public String getDistribuicaoServico(){
		return this.distribuicaoServico;
	}
	
	/**
	 * Retorna <code>true</code> se o parâmetro Tempo de Resposta será analisado, caso 
	 * contrário retorna <code>false</code>.
	 * @return Um valor <code>boolean</code>.
	 */
	public boolean getTempoResposta(){
		return this.tempoResposta;
	}

	/**
	 * Retorna <code>true</code> se o parâmetro Throughput será analisado, caso 
	 * contrário retorna <code>false</code>.
	 * @return Um valor <code>boolean</code>.
	 */	
	public boolean getThroughput(){
		return this.throughput;
	}

	/**
	 * Retorna <code>true</code> se o parâmetro Tamanho da Fila será analisado, caso 
	 * contrário retorna <code>false</code>.
	 * @return Um valor <code>boolean</code>.
	 */	
	public boolean getTamanhoFila(){
		return this.tamanhoFila;
	}
	
	/**
	 * Retorna <code>true</code> se a porcentagem de vezes em que o cliente encontra a fila 
	 * vazia será calculado, caso contrário retorna <code>false</code>.
	 * @return Um valor <code>boolean</code>.
	 */
	public boolean getEstatisticaFilaVazia(){
		return this.estatisticaFilaVazia;
	}
	
	/**
	 * Retorna <code>true</code> se serão geradas as estatísticas para o cálculo do número 
	 * de clientes em cada fila.
	 * @return Um valor <code>boolean</code>.
	 */
	public boolean getComprimentoMaxMin(){
		return this.comprimentoMaxMin;
	}
	
	/**
	 * Retorna o número de filas do centro de serviço. Se valor maior que 0 (zero) o servidor possuiu 
	 * filas em paralelo.
	 * @return Um valor <code>Integer</code> maior ou igual a 0.
	 */
	public int getNumFilas(){
		return numFilas;
	}
	
	/**
	 * Retorna o número de servidores do centro de serviço.
	 * @return Um valor <code>Integer</code> maior ou igual a 0.
	 */
	public String getNumServidores(){
		return this.numServidores;
	}
	
	/**
	 * @return a media...melhorar
	 */
	public String getMedia(){
		return media;
	}
	
    /**
     * @return A quantidade de voltas...melhorar...
     */
	public String getNumVoltas(){
		return numVoltas;
	}
	
	/**
	 * Retorna qual a seqüência a ser utilizada na geração do número 
	 * aleatório.
	 * @return sequencia - Um valor <code>String</code> compreendido entre 0..15. 
	 */
	public String getSequencia(){
		return sequencia;
	}
	
	/**
	 * Adiciona um arco ao vetor de arcos. Cada nó possui um vetor de arcos que indica com 
	 * quais nós o nó de origem se conecta.
	 * O arco somente é desenhando após a consistência da ligação for confirmada. 
	 * @param node 
	 * @param ligacao
	 * @param idNo
	 * @param tipoNo
	 * @param probabilidade
	 */
	public void addArc(Node node, int idNo, int tipoNo, String probabilidade){
	    
		boolean desenha;
		
		AvaliadorNivelUmA avalia = new AvaliadorNivelUmA();
		
		Arc arc = new Arc(this,node,idNo,tipoNo,probabilidade);
		
		//Verifica se a ligação está correta.		
		desenha = avalia.verifica(arc.begin.tipoNo,arc.end.tipoNo);
		if (desenha) {			
			arcs.add(arc);
			
			System.out.println("origem arco "+arc.getNodeA());
			
			
			if (arc.begin.getTipoNo() == 1){				
				node.setPrimRec(true);						
			}
/*			else{
				node.setPrimRec(false);
			}*/
			// node.setLigacao(arc.end.idNo);
			node.setChega(1);	
		}
		else{
			JOptionPane.showMessageDialog(
				null,
				"Ligação não permitida!!!",
				"ASDA - Erro",
				JOptionPane.ERROR_MESSAGE);
		}
	}
	
	
	

	/**
	 * Retorna a identificação do arco. Toda vez que um nó se conecta a outro nó através
	 * de um arco uma posição no vetor de arcos para aquele nó é preenchida. Cada arco 
	 * de um determinado nó possui uma identificação única que é a sua posição no vetor.
	 * @param i posiçao do arco no vetor de arcos.
	 * @return o arco que está armazenado na posição que foi passada como parâmetro.
	 */
	public Arc getArc(int i){		
		return (Arc)arcs.get(i);
	}
	
	/**
	 * Armazena a imagem do template que foi inserido no modelo (<code>Graph</code>).
	 * @param img Um objeto do tipo T*.gif localizado na pasta asda\imgIcones.
	 */
	public void setImage(ImageIcon img){
		this.img = img;
	}

	/**
	 * Retorna a imagem correspondente ao nó inserido no modelo (<code>Graph</code>).
	 * @return img - Um objeto do tipo T*.gif localizado na pasta asda\imgIcones.
	 */
	public ImageIcon getImage(){
		return this.img;
	}
	
	/**
	 * Remove todos os elementos do vetor de arcos.	 
	 */
	public void removeAllElements(){
		this.arcs.removeAllElements();
	}


	/**
	 * Retorna se a escolha para o próximo recurso é por ciclo.
	 * @return ciclo - Um valor <code>boolean</code>.
	 */
	public boolean isCiclo() {
		return ciclo;
	}

	/**
	 * Retorna se a escolha para o próximo recurso é por probabilidade.
	 * @return prob - Um valor <code>boolean</code>.
	 */
	public boolean isProb() {
		return prob;
	}
	


	/**
	 * Configura se a escolha para o próximo recurso é por ciclo.
	 * @param ciclo - Um valor <code>boolean</code>.
	 */
	public void setCiclo(boolean ciclo) {
		this.ciclo = ciclo;
	}

	/**
	 * Configura se a escolha para o próximo recurso é por ciclo.
	 * @param prob - Um valor <code>boolean</code>.
	 */
	public void setProb(boolean prob) {
		this.prob = prob;
	}


	/**
	 * Retorna se o centro de serviço é o primeiro recurso. Somente há um centro de serviço 
	 * com o valor de primRec = true.
	 * @return primRec - Um valor <code>boolean</code>.
	 */
	public boolean isPrimRec() {
		return primRec;
	}

	/**
	 * Configura se o centro de serviço é o primeiro recurso. Somente o centro de serviço que
	 * está ligado a fonte é configurado como primeiro recurso.
	 * @param primRec - Um valor <code>boolean</code>.
	 */
	public void setPrimRec(boolean primRec) {
		this.primRec = primRec;
	}

	/**
	 * @return
	 */
	public String getMediaFonte() {
		return mediaFonte;
	}

   /**
	* Retorna qual a seqüência a ser utilizada na geração do número 
	* aleatório.
	* @return sequenciaFonte - Um valor <code>String</code> compreendido entre 0..15.
	*/ 
	public String getSequenciaFonte() {
		return sequenciaFonte;
	}

	/**
	 * @param mediaFonte
	 */
	public void setMediaFonte(String mediaFonte) {
		this.mediaFonte = mediaFonte;
	}

	/**
	 * Configura qual a seqüência a ser utilizada na geração do número 
	 * aleatório. 
	 * @param sequenciaFonte Um valor <code>Integer</code> compreendido entre 0..15.
	 */
	public void setSequenciaFonte(String sequenciaFonte) {
		this.sequenciaFonte = sequenciaFonte;
	}


	public void setX(int x) {
		this.x = x;
	}


	public void setY(int y) {
		this.y = y;
	}


	public void setTipoNo(int tipoNo) {
		this.tipoNo = tipoNo;
	}


	public void setIdNo(int idNo) {
		this.idNo = idNo;
	}


	public int getChega() {
		return chega;
	}



	public ImageIcon getImg() {
		return img;
	}


	public void setImg(ImageIcon img) {
		this.img = img;
	}


	public Vector getArcs() {
		return arcs;
	}


	public String getDesvioPadrao() {
		return desvioPadrao;
	}


	public void setDesvioPadrao(String desvioPadrao) {
		this.desvioPadrao = desvioPadrao;
	}


	public String getPontoMaisProvavel() {
		return pontoMaisProvavel;
	}


	public void setPontoMaisProvavel(String pontoMaisProvavel) {
		this.pontoMaisProvavel = pontoMaisProvavel;
	}


	public void setArcs(Vector arcs) {
		this.arcs = arcs;
	}
	
	public String toString()
	{
		return getNomeCentroServico();
	}


	public String getDesvioPadraoFonte() {
		return desvioPadraoFonte;
	}


	public void setDesvioPadraoFonte(String desvioPadraoFonte) {
		this.desvioPadraoFonte = desvioPadraoFonte;
	}


	public String getPontoMaisProvavelFonte() {
		return pontoMaisProvavelFonte;
	}


	public void setPontoMaisProvavelFonte(String pontoMaisProvavelFonte) {
		this.pontoMaisProvavelFonte = pontoMaisProvavelFonte;
	}

	/**
	 * @return Returns the tid.
	 */
	public int getTid() {
		return tid;
	}
	/**
	 * @param tid The tid to set.
	 */
	public void setTid(int tid) {
		this.tid = tid;
	}
}
