package frames;
import graph.Arc;
import graph.Graph;
import graph.Node;

import java.awt.*;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.*;
import java.util.*;
import java.util.List;
import java.util.regex.*;
import javax.swing.*;

import asda.UsuarioCadastro;


        
/**
 * Classe que desenha todos os elementos do modelo. 
 * @author Thais Souza Aiza
 * @author Andr  Felipe Rodrigues
 * 		   cria  o do m todo findValidID (corre  o de um erro existente na cria  o do grafo)
 * @version 1.0
 */

public class Desenho extends JLabel{
	
	/**
	 * Cria um novo objeto da classe <code>Graph</code> quando um novo desenho   iniciado.
	 */
	public Graph graph = new Graph();
	
	public boolean isSave = false;
	
	/**
	 * Desenha a cabe a da seta.
	 */	
	public DesenhaSeta lig = new DesenhaSeta();
	
	/**
	 * Inicializa a coordenada x que indica a posi  o do mouse.
	 */
	int mouseX = 0;
	
	/**
	 * Inicializa a coordenada y que indica a posi  o do mouse.
	 */
	int mouseY = 0;
	
	/**
	 * Indica se o lugar onde o mouse est  pode ser desenhada uma linha.
	 */
	private boolean isDrawingMouseLine = false;
	
	/*
	 * Como todos os simbolos possuem tamanhos iguais, 
	 * nao   preciso armazenar largura e altura de todos
	 */
	/**
	 * Largura do s mbolo que ser  desenhado.
	 */
	int width;
	/**
	 * Altura do s mbolo que ser  desenhado.
	 */
	int height;
	
	/**
	 * Quando o painel deve ser somente limpo, recebe true
	 */
	private boolean clear = false;
	
	/**
	 * Indica se o desenho pode ser movido.
	 */
	private boolean isDragging = false;
	
	/**
	 * Guarda a posi  o do n  de origem da liga  o
	 */
	private int lineOriginObject;
	
	/**
	 * Indica a posi  o onde o objeto est . Valor   0 quando ele foi solto e   incrementado
	 * quando ele est  sendo arrastado.
	 */
	private int dragObject;
	
	/**
	 * Identifica cada n  com uma chave  nica. Quando o primeiro template   desenhado ele 
	 * recebe o valor 0 e   incrementado a medida que novos templates s o desenhados.
	 */
	public int idNo = -1;
	
	/**
	 * Vari vel auxiliar utilizada em diversos m todos.
	 */
	int aux = 0;
	

	/**
	 * Armazena o usu rio dono do modelo de simula  o
	 */
	private UsuarioCadastro user;
	
	public Desenho()
	{
		graph.setNomeModelo("ASDA_NAO_SALVO");
	}

	
	/**
	 * M todo que salva o modelo especificado.
	 * @param filename Nome do modelo
	 * @param nomeArquivo Nomde do modelo
	 */
	public void save(String filename, String nomeArquivo, UsuarioCadastro userInfo) {
		//graph.save(filename,nomeArquivo);
		
		try{
			
			user = userInfo;
			if (!filename.endsWith(".mod")) filename = filename + ".mod";
			FileOutputStream fos = new FileOutputStream(filename);
			ObjectOutputStream out = new ObjectOutputStream(fos);
			
			graph.setNomeModelo(nomeArquivo);

			out.writeObject(graph);
			
		/*	if (userInfo.getTipoModelo().equals("R"))
			{
				out.writeObject(userInfo);
			}
			*/
			out.close();

		} catch (IOException ex){
			ex.printStackTrace();
		}
		
		
	}
	
	/**
	 * M todo que abre o modelo.
	 * @param filename Nome do modelo.
	 */
	public void open(String filename, UsuarioCadastro userInfo) throws Exception{
		//this.graph = graph.open(filename);
		
		try{		
			/*FileInputStream fos = new FileInputStream(filename);
			ObjectInputStream in = new ObjectInputStream(fos);

			graph = (Graph)in.readObject();*/

			//pular a primeira linha
			//ler a linha comment
			//ler nós até que a próxima linha contenha ->
			//ler arestas até encontrar }

        String path = "graph.gv";

        // Armazenamento
        int tExec = -1, seed = -1;
        Map<Integer, String> nos = new HashMap<>();
        List<int[]> arestas = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                linha = linha.trim();

                // 1. Extrair os valores 34 e 35 do comment do grafo
                if (linha.startsWith("comment=")) {
                    Matcher matcher = Pattern.compile("comment=\"([^\"]+)\"").matcher(linha);
                    if (matcher.find()) {
                        String[] partes = matcher.group(1).trim().split(" ");
                        if (partes.length >= 8) {
                            tExec = Integer.parseInt(partes[0]);
                            seed = Integer.parseInt(partes[7]);
                        }
                    }
					this.graph.setTempoExecucao(String.valueOf(tExec));
					//set seed???
                }
				
                // 2. Ler nós com colchetes: 0 [label=... comment=" ... "]
                else if (linha.matches("\\d+\\s*\\[.*comment=.*\\]")) {
					int indexEspaco = linha.indexOf(" ");
					String nodeIdStr = linha.substring(0, indexEspaco).trim();
					int nodeId = Integer.parseInt(nodeIdStr);

					String comment = null;

					// Expressão para capturar comment com ou sem aspas
					Pattern pattern = Pattern.compile("comment=\\s*(\"[^\"]*\"|[^\\s\\]]+)");
					Matcher matcher = pattern.matcher(linha);

					if (matcher.find()) {
						comment = matcher.group(1);
						if (comment.startsWith("\"") && comment.endsWith("\"")) {
							comment = comment.substring(1, comment.length() - 1); // remove aspas
						}
					}
					//tem que testar e arrumar um monte de coisa
					//tem que mexer no código da nathalia e da sarita para que ele funcione sem GUI
					//ou vai testando pela GUI mesmo, enfim
					String[] partes = comment.trim().split("\\s+"); // divide por espaços múltiplos
					int tipo = -1;
					if (partes.length==1) {tipo = Integer.parseInt(partes[0]);}
					String distChegada = "";
					String distServico = "";
					String mediaChegada = "";
					String mediaServico = "";
					// Se você souber quantos valores esperar, pode armazenar em variáveis:
					if (partes.length >= 5) {
						tipo = Integer.parseInt(partes[0]);
						distChegada = partes[1];
						distServico = partes[2];
						mediaChegada = partes[3];
						mediaServico = partes[4];
					}
					if(tipo==1||tipo==3){this.graph.addNode(new Node(0,0,null,tipo,nodeId,""));}
					else 
					{
						Node node = new Node(0,0,null,tipo,nodeId,"");
						switch(distServico)
						{	case "0":
								node.setDistribuicaoServico("normal");
							case "1":
								node.setDistribuicaoServico("expntl");
							case "2":
								node.setDistribuicaoServico("uniform");
							default:
								node.setDistribuicaoServico("expntl");}
						switch(distChegada)
						{	case "0":
								node.setDistribuicaoChegada("normal");
							case "1":
								node.setDistribuicaoChegada("expntl");
							case "2":
								node.setDistribuicaoChegada("uniform");
							default:
								node.setDistribuicaoChegada("expntl");}
						node.setMediaFonte(mediaChegada);
						node.setMedia(mediaServico);
						this.graph.addNode(node);//o que é int chega em Node? numero de dos que saem desse no, isso sera descoberto a seguir
					}

					//nodes.put(nodeId, comment);
					this.graph.addNode(new Node(0,0,null,2,nodeId,0,""));
				}


                // 3. Ler arestas: 0 -> 2
                else if (linha.contains("->")) {
                    Matcher matcher = Pattern.compile("(\\d+)\\s*->\\s*(\\d+)").matcher(linha);
                    if (matcher.find()) {
                        int origem = Integer.parseInt(matcher.group(1));
                        int destino = Integer.parseInt(matcher.group(2));
                        //arestas.add(new int[]{origem, destino});
						this.graph.getNode(origem).setChega(this.graph.getNode(origem).getChega()+1);
						this.graph.getNode(origem).getArcs().addElement(new Arc(this.graph.getNode(origem), 
						this.graph.getNode(destino),destino,this.graph.getNode(destino).getTipoNo(),""));
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        // Exibir resultado
        System.out.println("Valor 34: " + tExec);
        System.out.println("Valor 35: " + seed);
        System.out.println("\nNós:");
        for (Map.Entry<Integer, String> entrada : nos.entrySet()) {
            System.out.println("ID: " + entrada.getKey() + ", Comentário: " + entrada.getValue());
        }

        System.out.println("\nArestas:");
        for (int[] par : arestas) {
            System.out.println(par[0] + " -> " + par[1]);
        }
    }
	catch (Exception e){	
			e.printStackTrace();
			JOptionPane.showMessageDialog(
					null,
					"Arquivo inv lido ou incompat vel!",
					"ASDA - Erro na abertura do arquivo",
					JOptionPane.ERROR_MESSAGE);
			throw e;
		}
}


			/*List<String> linhas = Files.readAllLines(Paths.get(filename));
			graph = new Graph();

			Pattern padraoAresta = Pattern.compile("\\s*(\\w+)\\s*->\\s*(\\w+)\\s*;");
			Vector pLogicos = new Vector(0);
			for (String linha : linhas) {
				Matcher matcher = padraoAresta.matcher(linha);
				if (matcher.matches()) {
					String origem = matcher.group(1);
					String destino = matcher.group(2);
					graph.adicionarAresta(origem, destino);

				}
			}
			graph.setPLogicos(pLogicos);*/
			
		/*	if (userInfo.getTipoModelo().equals("R"))
			{	user = (UsuarioCadastro)in.readObject();
				if (user==null)
					JOptionPane.showMessageDialog(
							null,
							"Usuarios de modelos redes de filas s  abrem modelos redes de filas");
			}*/
			
			//in.close();

		/*} catch (Exception e){	
			e.printStackTrace();
			JOptionPane.showMessageDialog(
					null,
					"Arquivo inv lido ou incompat vel!",
					"ASDA - Erro na abertura do arquivo",
					JOptionPane.ERROR_MESSAGE);
			throw e;
		}

		 
		
		if (graph.getSize()>0){
			this.width = graph.getNode(0).getImage().getIconWidth();
			this.height = graph.getNode(0).getImage().getIconHeight();
		}
		this.repaint();
	}*/
	
	 /**
	  * Guarda a posi  o do n  de origem da liga  o.
	  * @param x Coordenada x.
	  * @param y Coordenada y.
	  */
	 public void setLineOrigin(float x, float y){
	 	this.lineOriginObject = graph.getNodeIndex((int)x, (int)y);
	 }
	 
	 /**
	  * passa as coordenadas x e y onde a linha vai ser desenhada
	  * @param x Coordenada x.
	  * @param y Coordenada y.
	  */
	 public void drawLine(float x, float y){
	 	this.isDrawingMouseLine = true;
	 	this.mouseX = (int)x;
	 	this.mouseY = (int)y;
	 	this.repaint();
	 }
	 
	 /**
	  * Desenha o arco do n  de origem at  o n  de destino
	  * @param g O objeto que est  sendo desenhado.
	  */
	 public void drawLine(Graphics g){
	 	g.setColor(Color.black);
	 	g.drawLine(graph.getNode(this.lineOriginObject).getX(),graph.getNode(this.lineOriginObject).getY(),
	 	mouseX,mouseY);	 	
	 	
	 }
	 
	 /**
	  * Limpa o componente (desenho). Pinta tudo de branco e limpa o grafo
	  *
	  */
	 public void limpa(){
	 	this.clear = true;	 	
	 	graph.removeAllElements();
	 	graph.setNomeModelo("ASDA_NAO_SALVO");
	 	idNo = -1;					// volta o id do n  para o in cio da contagem
	 	this.repaint(); 	
	 		 	
	 }
	 
	/**
	 * Move o n  quando ele for arrastado pelo mouse (drag and drop) e os arcos.
	 * @param x Coordenada x que o n  est  sendo arrastado.
	 * @param y Coordenada y que o n  est  sendo arrastado.
	 */
	public void mover(float x, float y){

		int i = this.dragObject;

		if(!isDragging){
			isDragging = true;
			for(i=i;i<graph.getSize();i++){
				Node tempNode = graph.getNode(i);
				if ((x>tempNode.getX()-width/2)&&(x<tempNode.getX()+width/2)&&(y>tempNode.getY()-height/2)&&(y<tempNode.getY()+height/2)) 
					break;
			}
		}

		this.dragObject = i;
		Node movingNode = graph.getNode(i);

		float deltaX = movingNode.getX() - x;
		float deltaY = movingNode.getY() - y;

		movingNode.setPosition(new Point(movingNode.getX()-(int)deltaX,movingNode.getY()-(int)deltaY));

		this.repaint();

	}
	
	/**
	 * M todo que determina que o n  n o est  sendo arrastado.
	 */
	public void setDraggingFalse(){
		this.isDragging = false;
		this.dragObject = 0;
	}
	
	/**
	 * M todo que determina que a posi  o onde est  sendo desenhada n o   permitido o 
	 * desenho.
	 */
	public void setDrawingFalse(){
		this.isDrawingMouseLine = false;
	}
	
	/**
	 * Avisa quando existe um n  debaixo do cursor do mouse.
	 * @param x Coordenada x onde o n  est  sendo arrastado.
	 * @param y Coordenada y onde o n  est  sendo arrastado.
	 * @return Um valor <code>boolean</code>
	 */
	public boolean isDragabble (float x, float y){

		for(int i=0;i<graph.getSize();i++){
			Node node = graph.getNode(i);
			if ((x>node.getX()-width/2)&&(x<node.getX()+width/2)&&(y>node.getY()-height/2)&&(y<node.getY()+height/2)) // fronteiras do desenho do n 
				return true;
		}
		return false;
	}
	
	/**
	 * Desenha as arestas do grafo.
	 * @param g O objeto que est  sendo desenhado.
	 */
	public void desenhaAresta(Graphics g){

		g.setColor(Color.blue);
		
		
		for(int j=0;j<graph.getSize();j++){

			Node node = graph.getNode(j);
			
			for(int i=0;i<node.getSize();i++){
	
				final boolean ESQUERDA = false, DIREITA = true, BAIXO = false, CIMA = true;
				boolean sentidoX = false, sentidoY = false;
	
				int width = 0, height = 0;
	
				Arc arc = node.getArc(i);
	
				int x0 = arc.getX0();
				int x1 = arc.getX1();
				int y0 = arc.getY0();
				int y1 = arc.getY1();

	
				//Comprimento do arco
				int deltaX = x1 - x0;
				//Diferen a de altura
				int deltaY = y1 - y0;
	
				// Verifica o sentido que a aresta deve seguir ao ser desenhada
				if(deltaX>0) sentidoX = DIREITA; //N  origem est  a esquerda do n  destino
				else sentidoX = ESQUERDA; //N  origem est  a direita do n  de destino*/
				
				sentidoX = DIREITA;
				
				if(deltaY<0) sentidoY = CIMA; //N  de origem   mais baixo que o n  de destino
				else sentidoY = BAIXO; //N  de origem   mais alto que o n  de destino
	
				if (sentidoX==DIREITA) width = this.width;
				else width = - this.width;
	
				if (sentidoY==CIMA) height = this.height;
				else height = - this.height;
				
	
				// Se o simbolo nao estah verticalmente em cima do outro, desenha a aresta saindo da lateral
				if (deltaX>=103){
					g.drawLine(x0+width/2,y0,x0+deltaX/2,y0);
					g.drawLine(x0+deltaX/2,y0,x0+deltaX/2,y1);					
					lig.desenhaSeta(g,x0+deltaX/2,y1,x1-width/2,y1);
					
				}
				else
				{
					g.drawLine(x0+width,y0,x0+width/2,y0);					
					g.drawLine(x0+width,y0,x0+width,y1+height/2-10);
					g.drawLine(x0+width,y1+height/2-10,x1-width/2-20,y1+height/2-10);
					g.drawLine(x1-width/2-20,y1+height/2-10,x1-width/2-20,y1);					
					lig.desenhaSeta(g,x1-width/2-20,y1,x1-width/2,y1);
									

				}
				
			}
			
		}
		
	}
	
	/**
	 * Remove o arco.
	 * @param begin N  de origem do arco.
	 */
	public void removeArc(Node begin){
		int arc = begin.getX();	
	}
	
	
	/**
	 * Fixa a linha no n  de origem e no n  de destino.
	 */	
	public void fixLine(float x, float y){
		Node nodeA = graph.getNode(this.lineOriginObject);
		Node nodeB = graph.getNode(graph.getNodeIndex((int)x, (int)y));
		int idNo = graph.getIdNo(graph.getNodeIndex((int)x, (int)y));
		int tipoNo = graph.getTipoNo(graph.getNodeIndex((int)x, (int)y));
		String probabilidade = "";
		
		nodeA.addArc(nodeB,idNo,tipoNo,probabilidade);
		isSave = false;		
		this.isDrawingMouseLine = false;
		this.repaint();		
		
	}
	
	
	/**
	 * Pinta todo o painel de branco.
	 * @param g O objeto que est  sendo desenhado. 
	 */
	private void setBackgroundWhite(Graphics g){
		g.setColor(Color.white);
		g.fillRect(1,1,this.getWidth()-2, this.getHeight()-2);		
	}
	
	
	/**
	 * Desenha o grafo na tela.
	 * @param g O objeto que est  sendo desenhado.
	 */
	public void paint(Graphics g){
		// Pinta todo o painel de branco
		this.setBackgroundWhite(g);
		int nArestas = 0;
		// Caso n o seja chamada somente para limpar o fundo, desenha o grafo
		if (!clear){
			// Desenha todos os Nos jah inseridos
			for(int i=0;i<graph.getSize();i++){
				
				g.setColor(Color.black);
				
				Node node = graph.getNode(i);				
				g.drawImage(node.getImage().getImage(), node.getX()-width/2,node.getY()-height/2, this);
				
				if (node.getTipoNo() == 2){
					g.drawString(node.getNomeCentroServico(),node.getX()-width/2+5,node.getY()-height/2-5);				
				}
				else{
					if (node.getTipoNo() == 1){
						node.setNomeCentroServico("source");
						g.drawString(node.getNomeCentroServico(),node.getX()-width/2+5,node.getY()-height/2-5);
					}
					else{
						if (node.getTipoNo() == 3){
							node.setNomeCentroServico("destination");
							g.drawString(node.getNomeCentroServico(),node.getX()-width/2+5,node.getY()-height/2-5);
						}
						
					}
				}				
				if (node.getSize()>0){
				   nArestas++;
				}
			}
			if (nArestas>0){
				desenhaAresta(g); 
			}
		}
		else clear = false;
		if (isDrawingMouseLine) this.drawLine(g);			
	}

	/**
	 * Fun  o que procura pelo grafo um id que ainda n o foi utilizado
	 * @author Andr 
	 * @return um ID v lido para um novo n  do grafo (Inteiro)
	 */
	private int findValidID()
	{
		int ret = 0;
		int totElem = graph.getSize();
		if (totElem > 0) // tem algum n  no grafo
		{
			int cont = totElem;
			int cont2 = cont;
			boolean flag = true, flag2 = true;
			int ct = 0;
			while ((flag) && (cont > 0))
			{		
				ct = 0;
				cont2 = totElem;
				flag2 = true;
				while ((flag2) && (cont2 > 0))
				{
					if (graph.getNode(ct).getIdNo() == ret)
						flag2 = false;
					ct++;
					cont2--;
				}
				if (flag2) // n o achou coincidencia
					flag = false;
				else
				{
					cont--;
					ret++;
				}
			}
		}
		return ret;
	}
 
	/**
	 * Adiciona a imagem selecionada no modelo.
	 */
	public void add(ImageIcon img, float x, float y, int tipoNo){
	
		idNo = findValidID(); // coloca um id que ainda n o existe
		String nomeCentroServico = "CS_" + idNo;
		graph.addNode(new Node((int)x, (int)y, img, (int)tipoNo, (int)idNo, nomeCentroServico));
		isSave = false;
		this.width = img.getIconWidth();
		this.height = img.getIconHeight();		
		this.repaint();				
	}
}
