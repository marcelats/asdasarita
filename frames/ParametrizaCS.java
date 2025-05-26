package frames;
import graph.Arc;
import graph.Graph;
import graph.Node;
import graph.ProcessoLogicoParSMPL;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import java.awt.event.ItemEvent;
import javax.swing.border.*;
import javax.swing.JLabel;
import java.awt.Rectangle;
import javax.swing.JTextField;
import javax.swing.JComboBox;

import asda.UsuarioCadastro;


/**
 * Classe que exibe o Frame para a parametrização do centro de serviço.
 * @author Thais Souza Aiza
 * @author André Felipe Rodrigues (algumas modificações)
 * @version 1.0
 */

public class ParametrizaCS extends JFrame implements ItemListener {
	
	JPanel contentPane;
	BorderLayout borderLayout1 = new BorderLayout();
	JPanel jPanel1 = new JPanel(); //Borda do Parametro Analisado.
	JLabel jLabel1 = new JLabel();
	JTextField nomeCentroServico = new JTextField();
	JTextField numServidores = new JTextField();
	JTextField numFilas = new JTextField();
	JLabel jLabel2 = new JLabel();
	JLabel jLabel3 = new JLabel();
	Border borderParam;
	Border borderDist;
	JPanel jPanel2 = new JPanel();
	Border border1;
	TitledBorder titledBorder1;
	JCheckBox tempoResposta = new JCheckBox();
	JCheckBox throughput = new JCheckBox();
	JCheckBox tamanhoFila = new JCheckBox();
	Border border2;
	TitledBorder titledBorder2;
	ButtonGroup buttonGroup1 = new ButtonGroup();
	Border border3;
	//	JButton jButtonEdit = new JButton();
	JButton jButton1 = new JButton();
	JButton jButton2 = new JButton();
	
	boolean varTempoResposta = false;
	boolean varThroughput = false;
	boolean varTamanhoFila = false;
	
	char c = '-';
	
	StringBuffer choices;
	
	StringBuffer parametroAnalisado;
	
	int param;
	
	Probabilidades frame;
	
	Servico frame2;
	
	/**
	 * Nó que está sendo parametrizado.
	 */
	public Node no;
	
	
	/**
	 * Modelo que contém o recurso que está sendo parametrizado.
	 */
	public Graph graph;
	
	/**
	 * Indica quais as ligações que o nó possui.
	 */
	public Arc arc;
	
	/**
	 * Indica qual é o indíce do nó no vetor de nós.
	 */
	public int indice;
	
	/**
	 * Indica qual é o tipo de nó.
	 */
	public int tipoNo;
	
	ParametrizaFonte frame3;
	
	
	JLabel labelNome = new JLabel();
	
	Border border4;
	JPanel jPanel4 = new JPanel();
	Border border5;
	JCheckBox jCheckBox1 = new JCheckBox();
	JCheckBox jCheckBox2 = new JCheckBox();
	JButton jButton3 = new JButton();
	JButton jButton4 = new JButton();
	Border border6;
	TitledBorder titledBorder3;
	JPanel jPanel5 = new JPanel();
	Border border7;
	JRadioButton jRadioButton4 = new JRadioButton();
	JRadioButton jRadioButton5 = new JRadioButton();
	ButtonGroup buttonGroup2 = new ButtonGroup();
	JButton jButton5 = new JButton();
	JButton jButton6 = new JButton();
	Border border8;
	JPanel jPanel6 = new JPanel();
	Border border9;
	JPanel jPanel3 = new JPanel();
	Border border10;
	private JLabel jLabelTid = null;
	private JComboBox jComboBox = null;
	
	private int conversor[];
	/**
	 * Construtor do frame.
	 */
	public ParametrizaCS(Graph graph, Node no, int indice, int tipoNo, UsuarioCadastro user) {
		
		this.no = no;
		this.graph = graph;
		this.indice = indice;
		this.tipoNo = tipoNo;	
		

		
		enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		try {
			
			
			jbInit();
			
			tempoResposta.setEnabled(false);
			throughput.setEnabled(false);
			tamanhoFila.setEnabled(false);
			
			if (user.getLinguagem().equals("ParSMPL")) // ser for ParSMPL - checa o comboBox
			{
				
				jCheckBox1.setEnabled(false);
				jCheckBox2.setEnabled(false);
				
				conversor = new int[graph.getPLogicos().size()];
				
				if (graph.getPLogicos().size() == 0)
				{
					jComboBox.setVisible(false);
					jLabelTid.setVisible(false);
				}
				else
				{
					for (int i = 0; i < graph.getPLogicos().size(); i++)
					{
						jComboBox.addItem(String.valueOf(((ProcessoLogicoParSMPL)graph.getPLogicos().get(i)).getTid()));
						conversor[i] = ((ProcessoLogicoParSMPL)graph.getPLogicos().get(i)).getTid();
					}
				}
				
				try
				{
					jComboBox.setSelectedIndex(indexOfTid());
				}
				catch(Exception e)
				{
					e.printStackTrace();
					jComboBox.setSelectedIndex(-1);
					JOptionPane.showMessageDialog(
							null,
							"Defina os processos lógicos da simulação primeiro!",
							"Processos lógicos não definidos",
							JOptionPane.WARNING_MESSAGE);
					setVisible(false);
					dispose();					
				}
			}
			else // senão não tem TID
			{
				jComboBox.setVisible(false);
				jLabelTid.setVisible(false);
			}
			
			if (user.getLinguagem().equals("SMPLX"))
			{
				jCheckBox1.setEnabled(false);
				jCheckBox2.setEnabled(false);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
		//int s = no.tipoNo;
		
	}
	
	private int indexOfTid()
	{
		for (int i = 0; i < conversor.length; i++)
		{
			if (conversor[i] == no.getTid())
				return i;
		}

		
			return 0;
	}
	
	private void jbInit() throws Exception {
		
		jLabelTid = new JLabel();
		jLabelTid.setBounds(new Rectangle(286, 16, 17, 16));
		jLabelTid.setText("PL");
		contentPane = (JPanel) this.getContentPane();
		border1 =
			BorderFactory.createEtchedBorder(
					Color.white,
					new Color(151, 145, 140));
		titledBorder1 =
			new TitledBorder(
					BorderFactory.createEmptyBorder(),
			"Parametro Analisado");
		
		border2 =
			BorderFactory.createEtchedBorder(
					Color.white,
					new Color(151, 145, 140));
		titledBorder2 = new TitledBorder(border2, "Distribuição");
		border3 =
			BorderFactory.createEtchedBorder(
					Color.white,
					new Color(151, 145, 140));
		border4 =
			BorderFactory.createEtchedBorder(
					Color.white,
					new Color(148, 145, 140));
		border5 =
			new TitledBorder(
					BorderFactory.createEmptyBorder(),
			"Estatísticas das filas");
		border6 =
			BorderFactory.createEtchedBorder(
					Color.white,
					new Color(148, 145, 140));
		titledBorder3 = new TitledBorder(border6, "Escolha do Próximo Recurso");
		border7 =
			new TitledBorder(
					BorderFactory.createEmptyBorder(),
			"Choice Next Resource");
		border8 =
			BorderFactory.createEtchedBorder(
					Color.white,
					new Color(165, 163, 151));
		border9 =
			BorderFactory.createEtchedBorder(
					Color.white,
					new Color(165, 163, 151));
		border10 =
			BorderFactory.createEtchedBorder(
					Color.white,
					new Color(165, 163, 151));
		contentPane.setLayout(borderLayout1);
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		this.setContentPane(contentPane);
		this.setResizable(false);
		this.setSize(new Dimension(451, 383));
		this.setState(Frame.NORMAL);
		this.setTitle("Parametrizar Centro de Serviço");
		jPanel1.setLayout(null);
		jLabel1.setText("Nome");
		jLabel1.setBounds(new Rectangle(11, 19, 39, 16));
		nomeCentroServico.setText(no.getNomeCentroServico());
		nomeCentroServico.setBounds(new Rectangle(51, 16, 218, 23));
		nomeCentroServico.addKeyListener(
				new ParametrizaCS_nomeCentroServico_keyAdapter(this));
		numServidores.setBounds(new Rectangle(146, 46, 36, 23));
		if ( (no.getNumServidores() != null) )
			numServidores.setText(no.getNumServidores());
		else
			numServidores.setText("1");
		
	
		
		if (tipoNo == 2) {
			numServidores.setEditable(false);
			numFilas.setEditable(false);
		}
		
		numFilas.setText("1");
		numFilas.setBounds(new Rectangle(329, 46, 36, 23));
		jLabel2.setText("Número de Servidores");
		jLabel2.setBounds(new Rectangle(11, 49, 132, 16));
		jLabel3.setBounds(new Rectangle(204, 49, 113, 16));
		jLabel3.setText("Número de Filas");
		jPanel2.setFont(new java.awt.Font("Dialog", 1, 12));
		jPanel2.setBorder(titledBorder1);
		jPanel2.setBounds(new Rectangle(3, 177, 177, 111));
		jPanel2.setLayout(null);
		
		

		
		tempoResposta.setText("Tempo de Resposta");
		tempoResposta.setBounds(new Rectangle(7, 18, 138, 25));
		
		if (no.getTempoResposta() == true) {
			tempoResposta.setSelected(true);
		} else
			tempoResposta.setSelected(false);
		
		throughput.setText("Throughput");
		throughput.setBounds(new Rectangle(7, 48, 91, 25));
		
		if (no.getThroughput() == true) {
			throughput.setSelected(true);
		} else
			throughput.setSelected(false);
		
		tamanhoFila.setText("Tamanho da Fila");
		tamanhoFila.setBounds(new Rectangle(7, 78, 126, 25));
		
		if (no.getTamanhoFila() == true) {
			tamanhoFila.setSelected(true);
		} else
			tamanhoFila.setSelected(false);
		
		
		jButton1.setBounds(new Rectangle(119, 316, 79, 25));
		jButton1.setText("Ok");
		
		jButton1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				okPerformed(e);
			}
		});
		
		jButton2.setBounds(new Rectangle(230, 316, 89, 25));
		jButton2.setText("Cancelar");
		
		jButton2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cancelPerformed(e);
			}
		});
		
		jPanel4.setBorder(border5);
		jPanel4.setBounds(new Rectangle(3, 84, 194, 92));
		jPanel4.setLayout(null);
		jCheckBox1.setText("Fila Vazia");
		jCheckBox1.setBounds(new Rectangle(9, 22, 125, 23));
		if (no.getEstatisticaFilaVazia() == true) {
			jCheckBox1.setSelected(true);
		} else
			jCheckBox1.setSelected(false);
		
		
		jCheckBox2.setText("Comprimento Max/Min");
		jCheckBox2.setBounds(new Rectangle(9, 55, 173, 23));
		if (no.getComprimentoMaxMin() == true) {
			jCheckBox2.setSelected(true);
		} else
			jCheckBox2.setSelected(false);		
		
		jButton3.setBounds(new Rectangle(71, 20, 91, 25));
		jButton3.setText("Chegada");
		
		if (no.isPrimRec()){
			jButton3.setEnabled(true);
			jButton3.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					fontePerformed(e);
				}
			});	
		}
		else{
			jButton3.setEnabled(false);
		}	
		
		
		jButton4.setBounds(new Rectangle(70, 62, 92, 25));
		jButton4.setText("Serviço");
		jButton4.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){				
				servicoPerformed(e);
				
			}
		});
		jPanel5.setBorder(border7);
		jPanel5.setBounds(new Rectangle(198, 84, 232, 92));
		jPanel5.setLayout(null);
		//jRadioButton4.setSelected(true);
		jRadioButton4.setText("Probabilidade");
		jRadioButton4.setBounds(new Rectangle(10, 23, 115, 23));
		jRadioButton5.setText("Ciclo");
		jRadioButton5.setBounds(new Rectangle(10, 59, 91, 23));
		jButton5.setBounds(new Rectangle(128, 22, 90, 25));
		jButton5.setText("Ligação");
		
		if (no.isProb()){
			jRadioButton4.setSelected(true);
		}
		else{
			if (no.isCiclo()){
				jRadioButton5.setSelected(true);
			}
		}
		
		
		if (no.getSize()>0){
			jRadioButton4.setEnabled(true);				
			jButton5.setEnabled(true);			
			jButton5.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent e){				
					probabilidadesPerformed(e);
				}
			});
		}
		else{
			jRadioButton4.setEnabled(false);
			jRadioButton5.setEnabled(false);			
			jButton5.setEnabled(false);
			jButton6.setEnabled(false);
		}
		
		jButton6.setBounds(new Rectangle(128, 58, 89, 25));
		jButton6.setText("Loop");
		
		//Registro de Listener para os JRadioButtons
		jRadioButton4.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){				
				configuraBotoes(e);
				
			}
		});
		
		jRadioButton5.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){				
				configuraBotoes(e);
				
			}
		});
		
		
		jPanel6.setBorder(border9);
		jPanel6.setBounds(new Rectangle(195, 182, 232, 109));
		jPanel6.setLayout(null);
		jPanel3.setBorder(border10);
		jPanel3.setBounds(new Rectangle(7, 298, 433, 10));
		jPanel3.setLayout(null);
		contentPane.add(jPanel1, BorderLayout.CENTER);
		jPanel1.add(jLabel1, null);
		jPanel1.add(nomeCentroServico, null);
		jPanel2.add(tempoResposta, null);
		jPanel2.add(throughput, null);
		jPanel2.add(tamanhoFila, null);
		jPanel1.add(jLabel2, null);
		jPanel1.add(numServidores, null);
		jPanel4.add(jCheckBox1, null);
		jPanel4.add(jCheckBox2, null);
		jPanel1.add(jPanel5, null);
		jPanel1.add(jPanel2, null);
		
		
		jPanel1.setBorder(border3);
		/*TitledBorder titled;
		titled =
			BorderFactory.createTitledBorder(
					borderParam,
			"Parametro Analisado");
		
		titled =
			BorderFactory.createTitledBorder(
					borderParam,
			"Distribuiçao de Serviço");*/
		
		//Registro de Listener para os CheckBoxs Parametro Analisado
		tempoResposta.addItemListener(this);
		throughput.addItemListener(this);
		tamanhoFila.addItemListener(this);
		buttonGroup2.add(jRadioButton4);
		buttonGroup2.add(jRadioButton5);
		
		//Registro de Listener para os CheckBoxs Estatisticas das Filas
		jCheckBox1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				filaVazia(e);
			}
		});
		
		jCheckBox2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				comprimentoMaxMin(e);
			}
		});
		
		
		jPanel5.add(jRadioButton4, null);
		jPanel5.add(jRadioButton5, null);
		jPanel5.add(jButton6, null);
		jPanel5.add(jButton5, null);
		jPanel1.add(jButton2, null);
		jPanel1.add(jButton1, null);
		jPanel1.add(jPanel4, null);
		jPanel1.add(jLabel3, null);
		jPanel1.add(numFilas, null);
		jPanel1.add(jPanel6, null);
		jPanel6.add(jButton3, null);
		jPanel6.add(jButton4, null);
		jPanel1.add(jPanel3, null);
		jPanel1.add(jLabelTid, null);
		jPanel1.add(getJComboBox(), null);
		
	}
	
	
	private void configuraBotoes(ActionEvent e){
		if (jRadioButton4.isSelected()){			
			jButton5.setEnabled(true);
			jButton6.setEnabled(false);
		}
		else{
			if (jRadioButton5.isSelected()){
				jButton6.setEnabled(true);
				jButton5.setEnabled(false);
			}
		}
	}
	
	/**
	 * Listens para os check boxes
	 * ---  : '0' nenhuma escolha
	 * r--  : '1' tempo de resposta
	 * -t-  : '2' throughput
	 * --f  : '3' tamanho da fila
	 * rt-  : '4' tempo de resposta e throughput
	 * r-f  : '5' tempo de resposta e tamanho da fila
	 * -tf  : '6' throughput e tamanho da fila
	 * rtf  : '7' tempo de resposta, throughput e tamanho da fila
	 */
	public void itemStateChanged(ItemEvent e) {
		
		int index = 0;
		char c = '-';
		
		Object source = e.getItemSelectable();
		
		if (source == tempoResposta) {
			index = 0;
			varTempoResposta = true;
			c = 'r';
		} else if (source == throughput) {
			index = 1;
			varThroughput = true;
			c = 't';
		} else if (source == tamanhoFila) {
			index = 2;
			varTamanhoFila = true;
			c = 'f';
		}
		
		if (e.getStateChange() == ItemEvent.DESELECTED) {
			
			c = '-';
			
			switch (index) {
			case 0 :
				varTempoResposta = false;
				break;
			case 1 :
				varThroughput = false;
				break;
			case 2 :
				varTamanhoFila = false;
				break;
			}
		}
		
	}
	
	void fontePerformed(ActionEvent e){
		
		ParametrizaFonte frame3 = new ParametrizaFonte(graph,no,indice,no.getTipoNo());
		
		/*	Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		 Dimension frameSize = frame3.getSize();
		 if (frameSize.height > screenSize.height) {
		 frameSize.height = screenSize.height;
		 }
		 if (frameSize.width > screenSize.width) {
		 frameSize.width = screenSize.width;
		 }
		 frame3.setLocation((screenSize.width - frameSize.width) / 2, (screenSize.height - frameSize.height) / 2);*/
		JFrameUtil.centraliza(frame3);
		frame3.setVisible(true);
		
	}
	
	void probabilidadesPerformed(ActionEvent e){
		
		Probabilidades frame = new Probabilidades(graph,no,indice,no.getTipoNo());
		
		
		JFrameUtil.centraliza(frame);
		frame.setVisible(true);
		/*}
		 else{
		 System.out.println(" Impossivel setar probabilidades");
		 }*/
		
	}
	
	void servicoPerformed(ActionEvent e){
		
		
		Servico frame2 = new Servico(graph,no,indice,no.getTipoNo());
		
	
		JFrameUtil.centraliza(frame2);
		frame2.setVisible(true);
		
	}
	
	
	void nomeCentroServico_keyTyped(KeyEvent e) {
		char c = e.getKeyChar();
		if (!((Character.isLetterOrDigit(c))
				|| (c == KeyEvent.VK_BACK_SPACE)
				|| (c == KeyEvent.VK_DELETE))) {
			getToolkit().beep();
			e.consume();
		}
	}
	
	
	
	void tempoMedioServico_keyTyped(KeyEvent e) {
		char c = e.getKeyChar();
		if (!((Character.isDigit(c))
				|| (c == KeyEvent.VK_BACK_SPACE)
				|| (c == KeyEvent.VK_PERIOD)
				|| (c == KeyEvent.VK_DELETE))) {
			getToolkit().beep();
			e.consume();
		}
		
	}
	
	/**
	 * Verifica se todos os parâmetros do recurso estão corretos.
	 * @param e
	 */
	public void okPerformed(ActionEvent e) {
		
		JFrame frame = null;
		
		if (nomeCentroServico.getText().equals("")){
			JOptionPane.showMessageDialog(
					frame,
					"Nome do Centro de Serviço é de preenchimento obrigatório!!!",
					"ASDA - Erro",
					JOptionPane.ERROR_MESSAGE);
			nomeCentroServico.grabFocus();			
		}
		else{
			/*if ((tempoResposta.isSelected() == false) 
					&& (throughput.isSelected() == false)
					&& (tamanhoFila.isSelected() == false)) {
				JOptionPane.showMessageDialog( CHECAGEM DO PARAMETRO DESATIVA - PARAMETROS ANALISADOS AINDA NÃO IMPLEMENTADOS
						frame,
						"Selecione pelo menos 1 parâmetro a ser analisado!!!",
						"ASDA - Erro",
						JOptionPane.ERROR_MESSAGE);
			}
			else{*/
				no.setNomeCentroServico(nomeCentroServico.getText());
				no.setTempoResposta(varTempoResposta);
				no.setThroughput(varThroughput);
				no.setTamanhoFila(varTamanhoFila);
				no.setNumServidores(numServidores.getText());  // sem tratamento de robustez (não pode digitar string)
				//no.setDistribuicaoServico("expntl");
				no.setNumFilas(Integer.parseInt(numFilas.getText()));
				
			
				if (jComboBox.isVisible())
					no.setTid(conversor[jComboBox.getSelectedIndex()]);
				
				if (jRadioButton4.isSelected()){
					no.setProb(true);
					no.setCiclo(false);
				}
				else{
					if (jRadioButton5.isSelected()){
						no.setProb(false);
						no.setCiclo(true);		
					}
				}
				
				if (no.isPrimRec()){
					if (graph.chegadas.size() == 0){
						JOptionPane.showMessageDialog(
								frame,
								"Não esqueça de preencher a primeira chegada\n" +
								"durante a parametrização do modelo!!!",
								"ASDA - Primeira chegada",
								JOptionPane.INFORMATION_MESSAGE);
						jButton3.grabFocus();
					}
				}
				setVisible(false);
				dispose();
				
			//}
			
		}
		
	}
	
	void cancelPerformed(ActionEvent e) {
		//JFrame frame = null;
		setVisible(false);
		dispose();
		
	}
	
	void filaVazia(ActionEvent e){
		
		if (jCheckBox1.isSelected()){
			no.setEstatisticaFilaVazia(true);
		}
		else {
			no.setEstatisticaFilaVazia(false);
		}
		
	}
	
	void comprimentoMaxMin(ActionEvent e){
		
		if (jCheckBox2.isSelected()){
			no.setComprimentoMaxMin(true);
		}
		else {
			no.setComprimentoMaxMin(false);
		}		
	}

	/**
	 * This method initializes jComboBox	
	 * 	
	 * @return javax.swing.JComboBox	
	 */
	private JComboBox getJComboBox() {
		if (jComboBox == null) {
			jComboBox = new JComboBox();
			jComboBox.setBounds(new Rectangle(322, 13, 58, 22));
		}
		return jComboBox;
	}
	
	
}

class ParametrizaCS_nomeCentroServico_keyAdapter
extends java.awt.event.KeyAdapter {
	ParametrizaCS adaptee;
	
	ParametrizaCS_nomeCentroServico_keyAdapter(ParametrizaCS adaptee) {
		this.adaptee = adaptee;
	}
	public void keyTyped(KeyEvent e) {
		adaptee.nomeCentroServico_keyTyped(e);
	}
}


