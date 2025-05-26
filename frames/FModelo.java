package frames;
import gerador.Gerador;
import graph.Graph;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.*;


import java.awt.Color;


/**
 * Classe que parametriza as informa      es do modelo.
 * @author Thais Souza Aiza
 * @version 1.0
 */

public class FModelo extends JFrame implements ActionListener, ItemListener{



  JPanel contentPane;
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel jPanel1 = new JPanel();
  JLabel jLabel1 = new JLabel();
  JTextField jTextField1 = new JTextField();
  Border border1;
  TitledBorder titledBorder1;

  JLabel jLabel2 = new JLabel();
  JTextField jTextField2 = new JTextField();
  JPanel jPanel2 = new JPanel();
  Border border2;
  TitledBorder titledBorder2;
  JRadioButton jRadioButton1 = new JRadioButton();
  JRadioButton jRadioButton2 = new JRadioButton();
  ButtonGroup buttonGroup1 = new ButtonGroup();
  JTextField jTextField3 = new JTextField();
  JLabel jLabel4 = new JLabel();
  JTextField jTextField5 = new JTextField();
  JLabel jLabel5 = new JLabel();
  JTextField jTextField6 = new JTextField();
  JButton jButton1 = new JButton();
  JButton jButton2 = new JButton();
  JButton jButton3 = new JButton();
  JButton jButton4 = new JButton();
  Border border3;
  
  /**
   * Modelo que est    sendo parametrizado.
   */
  public Graph graph;
  
  public Gerador gerador;

  /**
   * Construtor do Frame.
   * @param graph Modelo que est    sendo parametrizado.
   */
  public FModelo(Graph graph) {
  	
  	this.graph = graph;  	
  	
	enableEvents(AWTEvent.WINDOW_EVENT_MASK);
	try {
	  jbInit();
	  jTextField2.grabFocus();
	  
	}
	catch(Exception e) {
	  e.printStackTrace();
	}
  }
  
  /**
   * Inicializa os componentes do Frame.
   */
  private void jbInit() throws Exception  {
	contentPane = (JPanel) this.getContentPane();
	border1 = BorderFactory.createEtchedBorder(Color.white,new Color(142, 142, 142));
	titledBorder1 = new TitledBorder(border1,"Ordem de Chegada");
	border2 = BorderFactory.createEtchedBorder(Color.white,new Color(151, 145, 140));
	titledBorder2 = new TitledBorder(border2,"Tempo de Warmup");
	border3 = BorderFactory.createEtchedBorder(Color.white,new Color(151, 145, 140));
	contentPane.setLayout(borderLayout1);
	this.setSize(new Dimension(325, 300));
	this.setTitle("Modelo");
	jPanel1.setLayout(null);
	jLabel1.setText("Nome");
	jLabel1.setBounds(new Rectangle(10, 17, 41, 16));
	
	jTextField1.setText(graph.getNomeModelo().toUpperCase());
	jTextField1.setEditable(false);
	jTextField1.setEnabled(false);
	jTextField1.setBounds(new Rectangle(58, 15, 221, 20));
	
  	jLabel2.setText("Tempo de Execu   ao");
	jLabel2.setBounds(new Rectangle(10, 50, 117, 16));
	jTextField2.setText(graph.getTempoExecucao());
	jTextField2.setBounds(new Rectangle(184, 43, 95, 22));
	jTextField2.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
	
	jTextField2.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});
	
	jPanel2.setBorder(titledBorder2);
	jPanel2.setBounds(new Rectangle(7, 111, 303, 53));
	jPanel2.setLayout(null);
	
	
	jRadioButton1.setText("Autom   tico");
	jRadioButton1.setBounds(new Rectangle(6, 20, 96, 25));
		
	jRadioButton2.setText("Definido");
	jRadioButton2.setBounds(new Rectangle(115, 20, 75, 25));

	
	//Registra Eventos
	jRadioButton1.addItemListener(this);
	jRadioButton2.addItemListener(this);	
	
		
	jTextField3.setBounds(new Rectangle(199, 21, 93, 22));
	jTextField3.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
	
	jTextField3.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});
	
	jRadioButton1.setSelected(false);
			jRadioButton2.setSelected(false);
			jTextField3.setEditable(false);
			jTextField3.setEnabled(false);
	
         
        

		if (graph.getTamWarmUp() == null){
			jRadioButton1.setSelected(true);
			jTextField3.setEditable(false);	
			jTextField3.setEnabled(false);
		}
		else{		
				jRadioButton2.setSelected(true);
				jTextField3.setEditable(true);
				jTextField3.setEnabled(true);
				jTextField3.setText(graph.getTamWarmUp());		
		}

	
	
	jLabel4.setText("N   mero M   ximo de Entidades");
	jLabel4.setBounds(new Rectangle(11, 83, 169, 16));
	jTextField5.setBounds(new Rectangle(184, 80, 95, 22));
	jTextField5.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
		
	jTextField5.setText(graph.getNumeroMaximoEntidades());
	jTextField5.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});
	
	jLabel5.setText("Tamanho Batch");
	jLabel5.setBounds(new Rectangle(11, 183, 98, 16));
	jTextField6.setText(graph.getTamanhoBatch());
	jTextField6.setBounds(new Rectangle(113, 180, 87, 22));
	jTextField6.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
	
	jTextField6.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});
	
	jButton1.setBounds(new Rectangle(214, 176, 94, 30));
	jButton1.setDebugGraphicsOptions(0);
	jButton1.setText("Chegada");
	jButton1.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
			chegadaModelo(e);
		}
	});

	jButton2.setBounds(new Rectangle(11, 227, 79, 25));
	jButton2.setText("Ok");
	jButton2.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
			okPerformed(e);
		}
	});
	
	jButton3.setBounds(new Rectangle(120, 227, 79, 25));
	jButton3.setText("Cancel");
	jButton3.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){				
			cancelPerformed(e);
				
		}
	});
	
	jButton4.setBounds(new Rectangle(229, 227, 79, 25));
	jButton4.setText("Ajuda");
	jPanel2.add(jRadioButton1, null);
	jPanel2.add(jRadioButton2, null);
	jPanel2.add(jTextField3, null);
	jPanel1.add(jLabel4, null);
	jPanel1.add(jTextField5, null);
	jPanel1.add(jTextField2, null);
	jPanel1.add(jPanel2, null);
	jPanel1.add(jLabel2, null);
	contentPane.add(jPanel1, BorderLayout.CENTER);
	jPanel1.add(jLabel1, null);
	jPanel1.add(jTextField1, null);
	jPanel1.add(jTextField6, null);
	jPanel1.add(jButton1, null);
	jPanel1.add(jLabel5, null);
	jPanel1.add(jButton3, null);
	jPanel1.add(jButton4, null);
	jPanel1.add(jButton2, null);
	buttonGroup1.add(jRadioButton1);
	buttonGroup1.add(jRadioButton2);
	
	//Listener para os Rabio Buttons
	jRadioButton1.addActionListener(this);
	jRadioButton2.addActionListener(this);
	
	//Listener para os Buttons
	jButton2.addActionListener(this);
	
	
	this.setResizable(false);
			this.setContentPane(contentPane);
	
  }
  
  /**
   * M   todo que habilita/desabilita o campo tamanho do WarmUp conforme a escolha do usu   rio.
   * @param e Indica em qual componente ocorreu uma a      o.
   */
  public void actionPerformed(ActionEvent e) {
	  if (jRadioButton2.isSelected()){	  	
		jTextField3.setEnabled(true);
		jTextField3.setEditable(true);	
		jTextField3.grabFocus();  	
	  }
	  else{ 
	  	if (jRadioButton1.isSelected()){
			jTextField3.setEnabled(true);
			jTextField3.setEditable(false);
		}		
	  }	  
  }


  /**
   * M   todo que exibe o Frame FChegadaModelo.
   * @see FChegadaModelo
   * @param e Indica em qual componente ocorreu uma a      o.
   */
  public void chegadaModelo(ActionEvent e){
  	
	FChegadaModelo chegada = new FChegadaModelo(graph);

	JFrame.setDefaultLookAndFeelDecorated(false);
	
	JFrameUtil.centraliza(chegada);

	chegada.setVisible(true);
	
  }
  
 
  

  /**
   * M   todo que verifica a consist   ncia de todos os campos parametrizados do modelo.    
   * @param e Indica em qual componente ocorreu o ato de teclar.
   */
  void okPerformed(ActionEvent e){
  	JFrame frame = null;
  	
  	if (jTextField1.getText().equals("")){
  		JOptionPane.showMessageDialog(frame,"Campo n   o pode ser nulo!!!",
  			  "ASDA - Erro",
  			  JOptionPane.ERROR_MESSAGE);
  			  jTextField1.grabFocus();
  	}
  	else{
  		if (jTextField2.getText().equals("")){
			JOptionPane.showMessageDialog(frame,"Campo n   o pode ser nulo!!!",
				  "ASDA - Erro",
				  JOptionPane.ERROR_MESSAGE);
				  jTextField2.grabFocus();  					
  		}
  		else{
			if (jTextField5.getText().equals("")){
				JOptionPane.showMessageDialog(frame,"Campo n   o pode ser nulo!!!",
					  "ASDA - Erro",
					  JOptionPane.ERROR_MESSAGE);
					  jTextField5.grabFocus();  					
			}
			else{
				if ((jRadioButton2.isSelected()) && (jTextField3.getText().equals(""))){
					JOptionPane.showMessageDialog(frame,"Campo n   o pode ser nulo!!!",
						  "ASDA - Erro",
						  JOptionPane.ERROR_MESSAGE);
						  jTextField3.grabFocus();
				}
				else{
					if (jTextField6.getText().equals("")){
						JOptionPane.showMessageDialog(frame,"Campo n   o pode ser nulo!!!",
							  "ASDA - Erro",
							  JOptionPane.ERROR_MESSAGE);
							  jTextField6.grabFocus();
					}
					else{
						graph.setNomeModelo(jTextField1.getText());
						graph.setTempoExecucao(jTextField2.getText());
						graph.setNumeroMaximoEntidades(jTextField5.getText());
						graph.setTamanhoBatch(jTextField6.getText());						
  		
						if (jRadioButton2.isSelected()){
							graph.setWarmUp("definido");
							graph.setTamWarmUp(jTextField3.getText());  			 
						}
						else{
							if (jRadioButton1.isSelected()){
								graph.setWarmUp("automatico");  		
								graph.setTamWarmUp("0");		
							}
							else{
								jRadioButton1.setSelected(false);
								jRadioButton2.setSelected(false);
							}
						}
												
						setVisible(false);
						dispose();
						
				}
			}
			}
  		}
  	}

  }


	/**
	 * M   todo que verifica se as configura      es de Warmup mudaram. 
	 * @param e Indica em qual componente ocorreu o ato de clicar.
	 */
	public void itemStateChanged(ItemEvent e) {
	
		Object source = e.getItemSelectable();
	
	if (source == jRadioButton1){
		jTextField3.setText("");
		graph.setWarmUp("automatico");
		graph.setTamWarmUp("");		
	}
	else{
		if (source == jRadioButton2){
			jTextField3.setEditable(true);			
			jTextField3.setText(graph.getTamWarmUp());
		}
	}
	

	}
	
	/**
	 * M   todo que fecha o Frame e n   o salva as altera      es no modelo.
	 * @param e Indica em qual componente ocorreu o ato de teclar.
	 */
	public void cancelPerformed(ActionEvent e){
		
		setVisible(false);
		dispose();
	}
	
	
}





