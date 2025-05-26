package graph;
import java.io.*;


/**  
  * Responsável pelas ligações entre os vértices do grafo. Indica o nó 
  * de origem e o nó de destino de cada ligação.
  *  
  * @author Thais Souza Aiza
  * @version 1.0
  */ 
public class Arc implements Serializable {

    
    /**
     * Indica qual é o nó de origem do arco.
     */       
    public Node begin;

	/**
	 * Indica qual é o nó de destino do arco.
	 */       
    public Node end;
    
    /**
     * Indica qual a idNo (identificação) do nó de destino do arco.
     */
    
    public int  idNo;
    
    /**
     * Indica qual o tipo do nó de destino do arco.
     */
    public int  tipoNo;
    
    /**
     * Indica qual a probabilidade do nó de origem ir para o nó de destino.
     */
    public String probabilidade;

    /**
     * Construtor da classe.
     * @param begin nó de origem do arco
     * @param end nó de destino do arco
     * @param idNo identifica o nó de destino do arco
     * @param tipoNo identifica o tipo do nó de destino do arco
     * @param probabilidade indica a probabilidade do nó de origem ir para o nó de destino do arco
     */
    public Arc(Node begin, Node end, int idNo, int tipoNo, String probabilidade) {

        this.begin   = begin;
        this.end     = end;
        this.idNo    = idNo; 
        this.tipoNo  = tipoNo; 
        this.probabilidade = probabilidade;
    }

    
    /**
     * Retorna a identificação do nó de destino do arco.
     * @return Um valor <code>integer</code> especificando a idNo do nó de destino.
     */
    public int getIdNoArc() {
        return idNo;
    }

    /**
     * Retorna qual é a coordenada inicial (origem) x para desenhar o arco.
     * @return Um valor <code>integer</code> especificando a coordenada inicial x0. 
     */
    public int getX0() {
        return begin.getX();
    }

    /**
     * Retorna qual é a coordenada inicial (origem) y para desenhar o arco.
     * @return Um valor <code>integer</code> especificando a coordenada inicial y0.
     */
    public int getY0() {
        return begin.getY();
    }

    /**
     * Retorna qual é a coordenada final (destino) x para desenhar o arco.     *  
     */
    public int getX1() {
        return end.getX();
    }

    /**
     * Retorna qual é a coordenada final (destino) y para desenhar o arco.
     */
    public int getY1() {
        return end.getY();
    }


    /**
     * Retorna o nó de origem do arco. Todos os métodos da classe <code>Node</code> podem
	 * ser acessados.
     * @return Um objeto <code>Node</code>.
     */    
    public Node getNodeA() {
        return this.begin;
    }

	/**
	 * Retorna o nó de destino do arco. Todos os métodos da classe <code>Node</code> podem
	 * ser acessados.
	 */	
	public Node getNodeB() {
		return this.end;
	}


    
    /**
     * Configura a probabilidade do nó de origem ir para o nó de destino.
     * @param probabilidade - Um valor <code>String</code> no formato de um numero real cujo 
     * faixa de valores varia de 0 a 100 para especificar a probabilidade.
     */
    public void setProbabilidade(String probabilidade){
    	this.probabilidade = probabilidade;
    }
    
    /**
     * Retorna o valor da probabilidade do nó de origem ir para o nó de destino.
     * @return Um valor <code>String</code>.
     */
    //Retorna a probabilidade
    public String getProbabilidade(){
    	return this.probabilidade;
    }
    	
}


/*--- Formatted in Sun Java Convention Style on Qua, Abr 28, '04 ---*/


/*------ Formatted by Jindent 3.51 Gold 1.12 Trial --- http://www.jindent.com ------*/
