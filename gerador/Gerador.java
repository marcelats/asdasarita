package gerador;
import graph.Graph;

/**
 * Classe abstrata gerador que contém os métodos necessários para
 * a geração de código de uma simulação 
 * @author André Felipe Rodrigues 
 * @version 1.0
 */

public abstract class Gerador
{
	/**
	 * Armazena os nós, arcos e todas as informações do modelo.
	 */
	protected Graph graph;  	// para dar visibilidade aos filhos
	
	/**
	 * o nome do arquivo no qual o código será gerado
	 */
	protected String filename;  // para dar visibilidade aos filhos
	
	/**
	 * Construtor básico e mínimo para a classe Gerador e filhos
	 * @param graph Grafo = modelo do qual o código será gerado
	 */
	public Gerador(Graph graph)
	{
		this.graph = graph;
	}
	
	/**
	 * @return Returns the filename.
	 */
	public String getFilename() {
		return filename;
	}

	/**
	 * @param filename The filename to set.
	 */
	public void setFilename(String filename) {
		this.filename = filename;
	}



	/**
	 * Método do qual é responsável para criar o arquivo do código 
	 * que será gerado
	 * Como a geração do código é diferente para cada tipo de linguagem,
	 * esse método deve ser implementado independentemente
	 */
	abstract public void criaArquivo();


	/**
	 * Método responsável por ler o arquivo gabarito e gerar o código da simulação
	 * @param gabarito
	 */
	abstract public void leGabarito(String gabarito);
}