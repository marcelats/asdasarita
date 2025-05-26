package frames;
import graph.Graph;
import graph.Node;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.border.*;


/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: </p>
 * @author Andr    Felipe Rodrigues (diversas modifica      es)
 * @author Thais Souza Aiza
 * @version 1.0
 */

public class ParametrizaFonte extends JFrame {

  JPanel jPanel1 = new JPanel();
  JPanel jPanel2 = new JPanel();
  Border border1;
  TitledBorder titledBorder1;
  JRadioButton jRadioButtonExp = new JRadioButton();
  JRadioButton jRadioButtonHiper = new JRadioButton();
  JRadioButton jRadioButtonErl = new JRadioButton();
  JPanel jPanel3 = new JPanel();
  Border border2;
  JRadioButton jRadioButtonTrian = new JRadioButton();
  JRadioButton jRadioButtonUniforme = new JRadioButton();
  JRadioButton jRadioButtonUser = new JRadioButton();
  ButtonGroup buttonGroup1 = new ButtonGroup();
  JLabel jLabel1 = new JLabel();
  JButton jButton1 = new JButton();
  JButton jButton2 = new JButton();
  JLabel jLabel2 = new JLabel();
  JTextField jTextFieldMedia = new JTextField();
  JLabel jLabel3 = new JLabel();
  JTextField jTextFieldDesvio = new JTextField();
  JLabel jLabel4 = new JLabel();
  JTextField jTextFieldSeq = new JTextField();
  JLabel jLabel5 = new JLabel();
  JTextField jTextFieldPMaisP = new JTextField();
  JLabel jLabel6 = new JLabel();
  JLabel jLabel7 = new JLabel();
  Border border3;
  JPanel jPanel4 = new JPanel();
  Border border4;
  JButton jButton3 = new JButton();
  JButton jButton4 = new JButton();
  JPanel jPanel5 = new JPanel();
  Border border5;

  ButtonGroup buttonGroup2 = new ButtonGroup();
    
  public Node no;
  
  
  private String distribuicao;
  
  public ParametrizaFonte(Graph graph, Node no, int indice, int tipoNo) {
  	
  	this.no = no;
  	
	try {
	  jbInit();
	}
	catch(Exception e) {
	  e.printStackTrace();
	}
  }
  private void jbInit() throws Exception {
  	
	border1 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
	titledBorder1 = new TitledBorder(border1,"Distribuicao");
	border2 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
	border3 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
	border4 = BorderFactory.createEtchedBorder(Color.white,new Color(165, 163, 151));
	border5 = BorderFactory.createEmptyBorder();
	jPanel1.setLayout(null);
	jPanel2.setBorder(titledBorder1);
	jPanel2.setBounds(new Rectangle(9, 9, 311, 141));
	jPanel2.setLayout(null);
	this.setTitle("Parametriza Fonte");
	this.setSize(new Dimension(338, 480));
	this.setState(Frame.NORMAL);
	
	
	jRadioButtonExp.setText("Exponencial");
	jRadioButtonExp.setSelected(true);
	distribuicao = "expntl";
	jRadioButtonExp.setBounds(new Rectangle(18, 26, 120, 23));
	jRadioButtonExp.addItemListener(new ItemListener(){
				public void itemStateChanged(ItemEvent e){
					jTextFieldMedia.setEnabled(true);
					jTextFieldMedia.setEditable(true);
					jTextFieldDesvio.setEnabled(false);
					jTextFieldDesvio.setEditable(false);
					jTextFieldPMaisP.setEnabled(false);
					jTextFieldPMaisP.setEditable(false);	
					distribuicao = "expntl";
				}
				
			});
	jRadioButtonHiper.setEnabled(true);
	jRadioButtonHiper.setText("Hiperexponencial");
	jRadioButtonHiper.setBounds(new Rectangle(18, 64, 130, 23));
	jRadioButtonHiper.addItemListener(new ItemListener(){
		public void itemStateChanged(ItemEvent e){
			jTextFieldMedia.setEnabled(true);
			jTextFieldMedia.setEditable(true);
			jTextFieldDesvio.setEnabled(true);
			jTextFieldDesvio.setEditable(true);
			jTextFieldPMaisP.setEnabled(false);
			jTextFieldPMaisP.setEditable(false);
			distribuicao = "hyperx";
		}
		
	});
	jRadioButtonErl.setEnabled(true);
	jRadioButtonErl.setText("Erlang");
	jRadioButtonErl.setBounds(new Rectangle(18, 101, 91, 23));
	jRadioButtonErl.addItemListener(new ItemListener(){
		public void itemStateChanged(ItemEvent e){
			jTextFieldMedia.setEnabled(true);
			jTextFieldMedia.setEditable(true);
			jTextFieldDesvio.setEnabled(true);
			jTextFieldDesvio.setEditable(true);
			jTextFieldPMaisP.setEnabled(false);
			jTextFieldPMaisP.setEditable(false);
			distribuicao = "erlang";
		}
		
	});
	jPanel3.setBorder(border2);
	jPanel3.setBounds(new Rectangle(155, 25, 10, 104));
	jRadioButtonTrian.setEnabled(true);
	jRadioButtonTrian.setText("Normal");
	jRadioButtonTrian.setBounds(new Rectangle(184, 26, 91, 23));
	jRadioButtonTrian.addItemListener(new ItemListener(){
		public void itemStateChanged(ItemEvent e){
			jTextFieldMedia.setEnabled(true);
			jTextFieldMedia.setEditable(true);
			jTextFieldDesvio.setEnabled(true);
			jTextFieldDesvio.setEditable(true);
			jTextFieldPMaisP.setEnabled(false);
			jTextFieldPMaisP.setEditable(false);	
			distribuicao = "normal";			
		}
		
	});
	jRadioButtonUniforme.setEnabled(true);
	jRadioButtonUniforme.setText("Uniforme");
	jRadioButtonUniforme.setBounds(new Rectangle(184, 64, 91, 23));
	jRadioButtonUniforme.addItemListener(new ItemListener(){
		public void itemStateChanged(ItemEvent e){
			jTextFieldMedia.setEnabled(true);
			jTextFieldMedia.setEditable(true);
			jTextFieldDesvio.setEnabled(true);
			jTextFieldDesvio.setEditable(true);
			jTextFieldPMaisP.setEnabled(false);
			jTextFieldPMaisP.setEditable(false);
			distribuicao = "uniform";
		}
		
	});
	jRadioButtonUser.setEnabled(false);
	jRadioButtonUser.setText("Do Usuario");
	jRadioButtonUser.setBounds(new Rectangle(184, 101, 91, 23));
	jLabel1.setText("Distribuicao do Usuario");
	jLabel1.setBounds(new Rectangle(16, 166, 138, 15));
	jButton1.setBounds(new Rectangle(160, 161, 73, 25));
	jButton1.setEnabled(false);
	jButton1.setText("Gerar");
	jButton2.setBounds(new Rectangle(247, 161, 73, 25));
	jButton2.setEnabled(false);
	jButton2.setText("Ler");
	jLabel2.setText("Media");
	jLabel2.setBounds(new Rectangle(16, 205, 40, 15));
	
	jTextFieldMedia.setText(no.getMediaFonte());
	jTextFieldMedia.setBounds(new Rectangle(75, 202, 57, 21));
	jTextFieldMedia.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
		
	jTextFieldMedia.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});
	
	jLabel3.setText("Desvio Padrao");
	jLabel3.setBounds(new Rectangle(162, 205, 90, 15));
	jTextFieldDesvio.setEnabled(false);
	jTextFieldDesvio.setEditable(false);
	jTextFieldDesvio.setText(no.getDesvioPadraoFonte());
	jTextFieldDesvio.setBounds(new Rectangle(263, 202, 57, 21));
	jTextFieldDesvio.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
		
	jTextFieldDesvio.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});
	jLabel4.setText("Sequencia");
	jLabel4.setBounds(new Rectangle(16, 242, 69, 15));
	jTextFieldSeq.setText(no.getSequenciaFonte());
	jTextFieldSeq.setBounds(new Rectangle(100, 239, 57, 21));
	jTextFieldSeq.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
		
	jTextFieldSeq.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});

	
	jLabel5.setText("Ponto mais");
	jLabel5.setBounds(new Rectangle(187, 232, 83, 15));
	jTextFieldPMaisP.setEnabled(false);
	jTextFieldPMaisP.setEditable(false);
	jTextFieldPMaisP.setText(no.getPontoMaisProvavelFonte());
	jTextFieldPMaisP.setBounds(new Rectangle(263, 239, 57, 21));
	jTextFieldPMaisP.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
		
	jTextFieldPMaisP.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});
	jLabel6.setText("Prov   vel");
	jLabel6.setBounds(new Rectangle(187, 245, 67, 15));
	jLabel7.setText("(Distribui      o Triangular)");
	jLabel7.setBounds(new Rectangle(187, 258, 142, 15));
	jPanel1.setBorder(border3);
	jPanel4.setBorder(border4);
	jPanel4.setBounds(new Rectangle(9, 378, 311, 10));
	jButton3.setBounds(new Rectangle(68, 405, 73, 25));
	jButton3.setText("Ok");
	jButton3.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				okPerformed(e);
			}
		});
	jButton4.setBounds(new Rectangle(184, 405, 89, 25));
	jButton4.setText("Cancelar");
	jButton4.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){				
			cancelPerformed(e);				
		}
	});
	jPanel5.setBounds(new Rectangle(8, 280, 304, 86));
	jPanel5.setLayout(null);

	this.getContentPane().add(jPanel1, BorderLayout.CENTER);
	jPanel1.add(jPanel2, null);
	jPanel2.add(jRadioButtonExp, null);
	jPanel2.add(jRadioButtonErl, null);
	jPanel2.add(jRadioButtonHiper, null);
	jPanel2.add(jPanel3, null);
	jPanel2.add(jRadioButtonTrian, null);
	jPanel2.add(jRadioButtonUniforme, null);
	jPanel2.add(jRadioButtonUser, null);
	buttonGroup1.add(jRadioButtonExp);
	buttonGroup1.add(jRadioButtonHiper);
	buttonGroup1.add(jRadioButtonErl);
	buttonGroup1.add(jRadioButtonTrian);
	buttonGroup1.add(jRadioButtonUniforme);
	buttonGroup1.add(jRadioButtonUser);
	jPanel1.add(jButton2, null);
	jPanel1.add(jLabel1, null);
	jPanel1.add(jButton1, null);
	jPanel1.add(jLabel2, null);
	jPanel1.add(jTextFieldMedia, null);
	jPanel1.add(jLabel3, null);
	jPanel1.add(jTextFieldDesvio, null);
	jPanel1.add(jLabel4, null);
	jPanel1.add(jTextFieldSeq, null);
	jPanel1.add(jTextFieldPMaisP, null);
	jPanel1.add(jLabel5, null);
	jPanel1.add(jLabel6, null);
	jPanel1.add(jLabel7, null);
	jPanel1.add(jPanel4, null);
	jPanel1.add(jButton3, null);
	jPanel1.add(jButton4, null);
	jPanel1.add(jPanel5, null);

	
	
	if (no.getDistribuicaoChegada().equals("expntl"))
		jRadioButtonExp.setSelected(true);
	else if (no.getDistribuicaoChegada().equals("hyperx"))
		jRadioButtonHiper.setSelected(true);
	else if (no.getDistribuicaoChegada().equals("erlang"))
		jRadioButtonErl.setSelected(true);
	else if (no.getDistribuicaoChegada().equals("normal"))
		jRadioButtonTrian.setSelected(true);
	else if (no.getDistribuicaoChegada().equals("uniform"))
		jRadioButtonUniforme.setSelected(true);
	
  }
  
  
  private boolean checkProbs()
  {  
	  if (jTextFieldMedia.getText().equals("")) {
		  JOptionPane.showMessageDialog(
				  null,
				  "Digite a m   dia para a distribui      o",
				  "ASDA - Formul   rio Incompleto",
				  JOptionPane.ERROR_MESSAGE);
		 return false;
	  }
	  
	  if (jRadioButtonExp.isSelected()){
		 return true;
	  }
	  
	  if ( (jRadioButtonHiper.isSelected()) 
			  || (jRadioButtonErl.isSelected()) 
			  || (jRadioButtonTrian.isSelected())
			  || (jRadioButtonUniforme.isSelected()) ) {
		  if (jTextFieldDesvio.getText().equals("")){
			  JOptionPane.showMessageDialog(
					  null,
					  "Digite o desvio padr   o para a distribui      o",
					  "ASDA - Formul   rio Incompleto",
					  JOptionPane.ERROR_MESSAGE);
			  return false;			  
		  }
		  else if (jRadioButtonHiper.isSelected())
		  {
			  if ((jTextFieldDesvio.getText() != null) && (jTextFieldMedia.getText()!=null))
				  // checa se desvio maior que media (tem que ser)
				  if ((Integer.parseInt(jTextFieldDesvio.getText())) <= Integer.parseInt(jTextFieldMedia.getText()))
				  {
					  JOptionPane.showMessageDialog(
							  this,
							  "Desvio deve ser maior que m   dia para hiperexponencial",
							  "Valores inv   lidos",							  
							  JOptionPane.INFORMATION_MESSAGE);
					  return false;
				  }
		  }
		  else if (jRadioButtonErl.isSelected())
		  {
			  if ((jTextFieldDesvio.getText() != null) && (jTextFieldMedia.getText()!=null))
				  // checa se desvio maior que media (tem que ser)
				  if ((Integer.parseInt(jTextFieldDesvio.getText())) >= Integer.parseInt(jTextFieldMedia.getText()))
				  {
					  JOptionPane.showMessageDialog(
							  this,
							  "Desvio deve ser menor que m   dia para earlang",
							  "Valores inv   lidos",							  
							  JOptionPane.INFORMATION_MESSAGE);
					  return false;
				  }
		  }
		  else if (jRadioButtonUniforme.isSelected())
		  {
			  if ((jTextFieldDesvio.getText() != null) && (jTextFieldMedia.getText()!=null))
				  // checa se desvio maior que media (tem que ser)
				  if ((Integer.parseInt(jTextFieldDesvio.getText())) <= Integer.parseInt(jTextFieldMedia.getText()))
				  {
					  JOptionPane.showMessageDialog(
							  this,
							  "Desvio deve ser maior que a m   dia para uniforme (m   dia=limite inferior, desvio_padr   o=limite_superior",
							  "Valores inv   lidos",							  
							  JOptionPane.INFORMATION_MESSAGE);
					  return false;
				  }
		  }
	  }
	  
	  if (jRadioButtonTrian.isSelected())
	  {
		  if (jTextFieldDesvio.getText().equals("")){
			  JOptionPane.showMessageDialog(
					  null,
					  "Digite o desvio padr   o para a distribui      o",
					  "ASDA - Formul   rio Incompleto",
					  JOptionPane.ERROR_MESSAGE);
			  return false;			  
		  }				  
	  }
	  
	  return true;
  }
  
  
  public void okPerformed(ActionEvent e){

	JFrame frame = null;
    	
	if (jTextFieldMedia.getText().equals("")){
		JOptionPane.showMessageDialog(frame,"Digite a m   dia de chegada na fonte!!!",
		"ASDA - Erro",
		JOptionPane.ERROR_MESSAGE);
		jTextFieldMedia.grabFocus();
	}
	else{
		if (jTextFieldSeq.getText().equals("")){
			JOptionPane.showMessageDialog(frame,"Digite a seq      ncia de distribui      o - 0-15)!!!",
			"ASDA - Erro",
			JOptionPane.ERROR_MESSAGE);
			jTextFieldSeq.grabFocus();    			
		}
		else
			if ( (Integer.parseInt(jTextFieldSeq.getText()) < 0) || (Integer.parseInt(jTextFieldSeq.getText()) > 15) ){
				JOptionPane.showMessageDialog(frame,"S    pode ser um valor de 0     15",
						"ASDA - Erro",
						JOptionPane.ERROR_MESSAGE);
						jTextFieldSeq.grabFocus();
			}
			else{
				if (checkProbs()){
					no.setDistribuicaoChegada(distribuicao);
					no.setMediaFonte(jTextFieldMedia.getText());
					no.setSequenciaFonte(jTextFieldSeq.getText());
					if (!jTextFieldDesvio.equals(""))
					{
						no.setDesvioPadraoFonte(jTextFieldDesvio.getText());
					}
					
					if (!jTextFieldPMaisP.equals(""))
					{
						no.setPontoMaisProvavelFonte(jTextFieldPMaisP.getText());
					}
					setVisible(false);
					dispose();
				}		    			
			}
	}	
  }
	
	public void cancelPerformed(ActionEvent e){
		
		setVisible(false);
		dispose();
	}
   	
 
}
