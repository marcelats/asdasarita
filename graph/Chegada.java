package graph;
import java.io.*;


/**
 * Adiciona e remove as chegadas de clientes no sistema.
 * @author Thais Souza Aiza
 * @author André Felipe Rodrigues 
 * 			(adição do parametro nodeIndex e métodos relacionados)
 * @version 1.0 
 */
public class Chegada implements Serializable {

    /**
     * Número de clientes que chegam no sistema.
     */
    private int   numeroClientes;
    /**
     * Tempo de chegada dos clientes no sistema.
     */
    private float tempoChegada;
    
    /**
     * Indice do nó o qual a chegada se refere
     */
    private int nodeIndex;

    /**
     * Construtor da classe.
     * @param numeroClientes Um valor <code>Integer</code> que representa o número de 
     * clientes que chegam no sistema.
     * @param tempoChegada Um valor <code>float</code> que representa o tempo de chegada 
     * dos clientes no sistema.
     */
    public Chegada(int numeroClientes, float tempoChegada, int nodeIndex) {
        this.numeroClientes = numeroClientes;
        this.tempoChegada   = tempoChegada;
        this.nodeIndex = nodeIndex;
    }

    /**
     * Retorna o numero de clientes que chegam no sistema.
     * @return Um valor <code>Integer</code> maior ou igual a 0 (zero).
     */    
    public int getNumeroClientes() {
        return numeroClientes;
    }

    /**
     * Retorna o tempo de chegada dos clientes no sistema.
     * @return Um valor <code>float</code> maior ou igual a 0 (zero).
     */
    public float getTempoChegada() {
        return tempoChegada;
    }

    /**
     * Configura o número de clientes que chegam no sistema.
     * @param numeroClientes Um valor <code>Integer</code> maior ou igual a 0 (zero).
     */
    public void setNumeroClientes(int numeroClientes) {
        this.numeroClientes = numeroClientes;
    }
    /**
     * retorna o índice do nó a qual essa chegada se refere
     * @return indice de nó no vetor nodes de graph
     */
	public int getNodeIndex() {
		return nodeIndex;
	}

	/**
	 * seta o indice corretamente
	 * @param nodeIndex
	 */
	public void setNodeIndex(int nodeIndex) {
		this.nodeIndex = nodeIndex;
	}

	/**
    * Configura o tempo de chegada dos clientes no sistema.
    * @param tempoChegada Um valor <code>float</code> maior ou igual a 0 (zero).
    */
	public void setTempoChegada(float tempoChegada) {
		this.tempoChegada = tempoChegada;
	}

}

