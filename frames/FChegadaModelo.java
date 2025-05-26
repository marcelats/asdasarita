package frames;
import graph.Chegada;
import graph.Graph;
import graph.Node;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.Border;


/**
 * Frame que configura <code>Chegada</code>.
 * @author Thais Souza Aiza
 * @author André Felipe Rodrigues - 
 * 			adição do combo box centro de serviço e alterações necessárias
 * @version 1.0
 */

public class FChegadaModelo extends JFrame implements ActionListener{
	
  JPanel jPanel1 = new JPanel();
  JLabel jLabel1 = new JLabel();
  JTextField jTextField1 = new JTextField();
  JLabel jLabel2 = new JLabel();
  JTextField jTextField2 = new JTextField();
  JButton jButton3 = new JButton();
  JButton jButton4 = new JButton();
  JButton jButton6 = new JButton();
  JTextArea saida = new JTextArea();
  Border border1;
  JLabel jLabel3 = new JLabel();
  JLabel jLabel4 = new JLabel();
  Icon add24 = new ImageIcon("imagens/Add24.gif");
  Icon back24 = new ImageIcon("imagens/Back24.gif");
  Icon forward24 = new ImageIcon("imagens/Forward24.gif");
  Icon save24 = new ImageIcon("imagens/Save24.gif");
  Icon delete24 = new ImageIcon("imagens/Delete24.gif");
  JButton anterior = new JButton(back24);
  JButton posterior = new JButton(forward24);
  JButton inserir = new JButton(add24);
  JButton salvar = new JButton(save24);
  JButton apagar = new JButton(delete24);
  
  /**
   * Variável auxiliar utilizada para indicar se a operação corrente já ocorreu.
   * Operações: inserir e editar chegadas.
   */
  private boolean ok = true;

  /**
   * Modelo que está sendo parametrizado.
   */
  public Graph graph;
  
  /**
   * Variável que indica a posição corrente do vetor de chegadas.
   */
  private int posicao;
  
  /**
   * Variável que indica a primeira posição do vetor de chegadas.
   */
  private int minPosicao;
  
  /**
   * Variável que indica a última posição do vetor de chegadas.
   */
  private int maxPosicao;
  
  private int conversor[];
  
private JLabel jLabelNode = null;
private JComboBox jComboBoxNode = null;

  /**
   * Contrutor da classe.
   * @param graph Modelo que está sendo parametrizado.
   */
  public FChegadaModelo(Graph graph) {
  	
		this.graph = graph; 

		try {

		  jbInit();		  
		  exibirChegadas();
	  
	  
		}
		catch(Exception e) {
		  e.printStackTrace();
		}
  }
  
			
  private void jbInit() throws Exception {
  	
		border1 = BorderFactory.createEtchedBorder(Color.white,new Color(178, 178, 178));
		jLabelNode = new JLabel();
		
		jLabelNode.setText("JLabel");

		jLabelNode.setBounds(new java.awt.Rectangle(16,114,116,17));
		jLabelNode.setText("Centro de serviço");
		conversor = new int[graph.getSize()];
		
			
		jPanel1.add(getJComboBoxNode(), null);
		
		
		

		this.setTitle("Chegada");
		jPanel1.setLayout(null);
		jLabel1.setText("Número de Clientes");
		jLabel1.setBounds(new Rectangle(14, 50, 121, 16));
		jTextField1.setText("");
		jTextField1.setBounds(new Rectangle(142, 47, 125, 22));
		jTextField1.addKeyListener(new KeyAdapter()  {
			public void keyTyped(KeyEvent e) {
				verificaDigito(e);
			}
		});
		
		jTextField1.addFocusListener(new FocusAdapter() {
			public void focusLost(FocusEvent e) {
				verificaNumeroReal(e);
			}
		});

		jLabel2.setBounds(new Rectangle(14, 83, 121, 16));
		jLabel2.setText("Tempo de Chegada");
		jTextField2.setBounds(new Rectangle(142, 80, 125, 22));
		jTextField2.addKeyListener(new KeyAdapter()  {
			public void keyTyped(KeyEvent e) {
				verificaDigito(e);
			}
		});
		
		jTextField2.addFocusListener(new FocusAdapter() {
			public void focusLost(FocusEvent e) {
				verificaNumeroReal(e);
			}
		});
		
		jTextField2.setText("");
		
		jTextField1.setEditable(false);
		jTextField2.setEditable(false);
		
		jButton3.setBounds(new java.awt.Rectangle(13,252,79,25));
		jButton3.setText("Ok");
		jButton3.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){				
				okPerformed(e);
				
			}
		});
		
		
		jButton4.setBounds(new java.awt.Rectangle(100,252,79,25));
		jButton4.setText("Cancel");
		jButton4.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){				
			cancelPerformed(e);
				
			}
		});
		
		jButton6.setBounds(new java.awt.Rectangle(187,252,79,25));
		jButton6.setText("Ajuda");
		
		//saida.setBorder(border1);
		saida.setText("");
		saida.setEditable(false);
		JScrollPane scrollPane =
		new JScrollPane(saida);
		scrollPane.setBounds(new java.awt.Rectangle(13,162,254,82));

		jLabel3.setText("Clientes");
		jLabel3.setBounds(new java.awt.Rectangle(14,145,52,16));
		jLabel4.setText("Tempo");
		jLabel4.setBounds(new java.awt.Rectangle(144,145,41,16));
		
	    anterior.setBounds(new Rectangle(37, 9, 35, 31));
		anterior.setText("");
		posterior.setText("");
		posterior.setBounds(new Rectangle(78, 9, 35, 31));
		inserir.setText("");
		inserir.setBounds(new Rectangle(119, 9, 35, 31));
		salvar.setText("");
		salvar.setBounds(new Rectangle(160, 9, 35, 31));
		apagar.setText("");
		apagar.setBounds(new Rectangle(201, 9, 35, 31));
		
		this.getContentPane().add(jPanel1, BorderLayout.CENTER);
		jPanel1.add(jTextField1, null);
		jPanel1.add(jLabel1, null);
		jPanel1.add(jLabel2, null);
		jPanel1.add(jTextField2, null);
		jPanel1.add(scrollPane, null);


		jPanel1.add(jButton4, null);
		jPanel1.add(jButton6, null);
		jPanel1.add(jButton3, null);
		jPanel1.add(jLabel3, null);
		jPanel1.add(jLabel4, null);
		jPanel1.add(anterior, null);
		jPanel1.add(posterior, null);
		jPanel1.add(inserir, null);
		jPanel1.add(salvar, null);
		jPanel1.add(apagar, null);
		jPanel1.add(jLabelNode, null);
		
		this.setResizable(false);
		this.setSize(new java.awt.Dimension(290,322));
			this.setContentPane(jPanel1);
		
		//Registro de Listener para os Buttons
		anterior.addActionListener(new ActionListener(){			

			public void actionPerformed(ActionEvent e){
				anteriorPerformed(e);
			}
		});
		
		posterior.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				posteriorPerformed(e);
			}
		});
		
		inserir.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				inserirPerformed(e);
			}
		});
		
		salvar.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				salvarPerformed(e);
			}
		});
		
		apagar.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				apagarPerformed(e);
			}
		});
		


  }
  
  /**
   * Método que exibe todas as chegadas em um componente jTextArea.   
   */  
  public void exibirChegadas(){

	String novaLinha = "\n";
	
	if (graph.getChegadaSize() > 0){	
		jTextField1.setText(Float.toString(graph.getChegada(0).getNumeroClientes()));
		jTextField2.setText(Float.toString(graph.getChegada(0).getTempoChegada()));
		
		jComboBoxNode.setSelectedItem(graph.getNode(conversor[0]));
		for (int i = 0; i < graph.getChegadaSize(); i++){	
			saida.append(Float.toString(graph.getChegada(i).getNumeroClientes()) + "                                         " + Float.toString(graph.getChegada(i).getTempoChegada()) + novaLinha);
		}
	}
	
	posicao = 0;
	maxPosicao = graph.getChegadaSize();
	minPosicao = 0;
	
  }
    
  /**
   * Método que retorna e exibe uma posição no vetor de chegadas.
   * @param e Indica em qual componente ocorreu uma ação.
   */
  public void anteriorPerformed(ActionEvent e){
  	
	JFrame frame = null;
	
  	if (posicao == minPosicao){
		JOptionPane.showMessageDialog(frame,"!!!",
			  "ASDA - Erro",
			  JOptionPane.ERROR_MESSAGE);
			  jTextField1.grabFocus();
  	} 
  	else{
		posicao = posicao -1;
  		jTextField1.setText(Float.toString(graph.getChegada(posicao).getNumeroClientes()));
  		jTextField2.setText(Float.toString(graph.getChegada(posicao).getTempoChegada()));
  		jComboBoxNode.setSelectedItem(graph.getNode(graph.getChegada(posicao).getNodeIndex()));
  	}
  	
  }
  /**
   * Método que avança e exibe uma posição no vetor de chegadas. 
   * @param e Indica em qual componente ocorreu uma ação.
   */
  public void posteriorPerformed(ActionEvent e){
  	
	JFrame frame = null;
  	
	if (posicao == graph.getChegadaSize()){
		JOptionPane.showMessageDialog(frame,"!!!",
			  "ASDA - Erro",
			  JOptionPane.ERROR_MESSAGE);
			  jTextField1.grabFocus();
	}
	else{		
		posicao = posicao+1;	
		jTextField1.setText(Float.toString(graph.getChegada(posicao).getNumeroClientes()));
		jTextField2.setText(Float.toString(graph.getChegada(posicao).getTempoChegada()));
		jComboBoxNode.setSelectedItem(graph.getNode(graph.getChegada(posicao).getNodeIndex()));
				
	}
  }
  
  /**
   * Insere um objeto <code>Chegada<> na última posição do vetor de chegadas.
   * @param e Indica em qual componente ocorreu uma ação.
   */
  public void inserirPerformed(ActionEvent e){
  	
  	ok = false;
  	
  	jTextField1.setEditable(true);
	jTextField1.setText("");
  	jTextField2.setEditable(true);
	jTextField2.setText("");
	
  	jTextField1.grabFocus();
  }
  
  /**
   * Método que salva um objeto <code>Chegada</code> no vetor de chegadas.
   * @param e Indica em qual componente ocorreu uma ação.
   */
  public void salvarPerformed(ActionEvent e){
	
	JFrame frame = null;
	
	String novaLinha = "\n";
		
  	if ((jTextField1.getText().equals("")) || (jTextField2.getText().equals(""))){
		JOptionPane.showMessageDialog(frame,"Campo não pode ser nulo!!!",
			  "ASDA - Erro",
			  JOptionPane.ERROR_MESSAGE);

				
				if (jTextField1.getText().equals("")){
					jTextField1.grabFocus();
							  	
				}
				else{
					jTextField2.grabFocus();
				}
  	}
  	else{
  		
  		if (graph.chegadas.size() == 0){
  			Node temp = (Node)jComboBoxNode.getSelectedItem();
			graph.addChegada(new Chegada((int)Float.valueOf(jTextField1.getText()).floatValue(),Float.valueOf(jTextField2.getText()).floatValue(), conversor[jComboBoxNode.getSelectedIndex()]));
			saida.append( Float.toString(graph.getChegada(graph.getChegadaSize()-1).getNumeroClientes()) + "                                         " + Float.toString(graph.getChegada(graph.getChegadaSize()-1).getTempoChegada()) + novaLinha);
			jTextField1.setEditable(false);
			jTextField2.setEditable(false);
			maxPosicao = graph.getChegadaSize();
			posicao = graph.getChegadaSize()-1;
			ok = true;
  			
  		}
  		else{
			int ind = graph.chegadas.size()-1;
			Chegada aux1;
			aux1 = (Chegada) graph.getChegada(ind);
			if (Float.valueOf(jTextField2.getText()).floatValue() < aux1.getTempoChegada()){
				JOptionPane.showMessageDialog(frame,"Tempo da Próxima Chegada Menor que o Valor Anterior!!!",
					  "ASDA - Erro",
					  JOptionPane.ERROR_MESSAGE);
					  jTextField2.setText("");
					  jTextField2.grabFocus();

			}
			else{
				graph.addChegada(new Chegada((int)Float.valueOf(jTextField1.getText()).floatValue(),Float.valueOf(jTextField2.getText()).floatValue(), conversor[jComboBoxNode.getSelectedIndex()]));
				saida.append( Float.toString(graph.getChegada(graph.getChegadaSize()-1).getNumeroClientes()) + "                                         " + Float.toString(graph.getChegada(graph.getChegadaSize()-1).getTempoChegada()) + novaLinha);
				jTextField1.setEditable(false);
				jTextField2.setEditable(false);
				maxPosicao = graph.getChegadaSize();
				posicao = graph.getChegadaSize()-1;
				ok = true;

			}
			
  		}
  	}
  }
  
  /**
   * Método que apaga um objeto <code>Chegada</code> na posição selecionada.
   * @param e Indica em qual componente ocorreu uma ação.
   */
  public void apagarPerformed(ActionEvent e){
  	graph.removeChegada(posicao);
  	jTextField1.setText(Float.toString(graph.getChegada(posicao).getNumeroClientes()));
	jTextField2.setText(Float.toString(graph.getChegada(posicao).getTempoChegada()));
	jComboBoxNode.setSelectedItem(graph.getNode(graph.getChegada(posicao).getNodeIndex()));
	saida.setText("");
	exibirChegadas();	
  }
	
  

  /**
   * Método emite um aviso sonoro se o caracter digitado é diferente de um número, a tecla
   * de back space, delete ou ponto. Remove o caracter digitado se ele não é o permitido. 
   * @param e Indica em qual componente ocorreu o ato de teclar.
   */ 
  void verificaDigito(KeyEvent e) {
	  char c = e.getKeyChar();
	  int p = 0;		
	  if (!((Character.isDigit(c))
		  || (c == KeyEvent.VK_BACK_SPACE)
		  || (c == KeyEvent.VK_DELETE)
		  || (c == KeyEvent.VK_PERIOD))) {
		  getToolkit().beep();			
		  e.consume();
	  }
  }
  
  /**
   * Método que verifica se o número digitado é <code>float</code>.
   * @param e Indica qual componente perdeu o foco. 
   */
  public void verificaNumeroReal(FocusEvent e){
		
	  JTextField textField = (JTextField)e.getSource();
	  JFrame frame = null;		
	  String content = textField.getText();
		
	  if (content.length() != 0) {
		  try {
			  Double.parseDouble(content);			   
		  } catch (NumberFormatException nfe) {
			  getToolkit().beep();
			  JOptionPane.showMessageDialog(frame,"Número Inválido!!!",
			  "ASDA - Erro",
			  JOptionPane.ERROR_MESSAGE);
			  textField.requestFocus();				
			  textField.setText("");								
		  }
	  }
  }
  
  /**
   * Método que fecha o Frame se todas as operações foram encerradas.
   * @param e Indica em qual componente ocorreu uma ação.
   */
  public void okPerformed(ActionEvent e){
  	
	JFrame frame = null;  	

	if (ok){
		setVisible(false);
		dispose();		
	}
	else{
		JOptionPane.showMessageDialog(frame,"Finalizar a inclusão!!!",
		"ASDA - Erro",
		JOptionPane.ERROR_MESSAGE);
		salvar.grabFocus();
				
	}
  	
  }  
  
  /**
   * Método que fecha o Frame e cancela a operação que está acontecendo.
   * @param e
   */
  public void cancelPerformed(ActionEvent e){

	  setVisible(false);
	  dispose();
  }

/* (non-Javadoc)
 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
 */
public void actionPerformed(ActionEvent arg0) {
	// TODO Auto-generated method stub
	
}


/**
 * This method initializes jComboBoxNode	
 * 	
 * @return javax.swing.JComboBox	
 */
private JComboBox getJComboBoxNode() {
	if (jComboBoxNode == null) {
		jComboBoxNode = new JComboBox();
		jComboBoxNode.setBounds(new java.awt.Rectangle(140,111,127,20));
		jComboBoxNode.setMaximumRowCount(5);
		
		int cont = 0;
		
		for (int i = 0; i < graph.getSize(); i++) // adiciona os primeiros recursos pro combo
		{
			Node temp = graph.getNode(i);
			if (temp.isPrimRec())
			{
				jComboBoxNode.addItem(temp);
				conversor[cont] = i;
				cont++;
			}
		}
		
	}
	return jComboBoxNode;
}
  
}  //  @jve:decl-index=0:visual-constraint="10,10"


