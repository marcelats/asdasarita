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
 * @author Thaiz Souza Aiza
 * @author André Felipe Rodrigues - diversas modificações - reformulação
 * @version 1.0
 */
public class Servico extends JFrame {

    private JPanel       jPanel1 = new JPanel();
    private JPanel       jPanel2 = new JPanel();
    private Border       border1;
    private TitledBorder titledBorder1;
    private JRadioButton jRadioButtonExp = new JRadioButton();
    private JRadioButton jRadioButtonHiper = new JRadioButton();
    private JRadioButton jRadioButtonErl = new JRadioButton();
    private JPanel       jPanel3       = new JPanel();
    private Border       border2;
    private JRadioButton jRadioButtonTrian = new JRadioButton();
    private JRadioButton jRadioButtonUniforme = new JRadioButton();
    private JRadioButton jRadioButtonUser = new JRadioButton();
    private ButtonGroup  buttonGroup1  = new ButtonGroup();
    private JLabel       jLabel1       = new JLabel();
    private JButton      jButton1      = new JButton();
    private JButton      jButton2      = new JButton();
    private JLabel       jLabel2       = new JLabel();
    private JTextField   jTextFieldMedia   = new JTextField();
    private JLabel       jLabel3       = new JLabel();
    private JTextField   jTextFieldDesvio   = new JTextField();
    private JLabel       jLabel4       = new JLabel();
    private JTextField   jTextFieldSeq   = new JTextField();
    private JLabel       jLabel5       = new JLabel();
    private JTextField   jTextFieldPMaisP   = new JTextField();
    private JLabel       jLabel6       = new JLabel();
    private JLabel       jLabel7       = new JLabel();
    private Border       border3;
    private JPanel       jPanel4 = new JPanel();
    private Border       border4;
    private JButton      jButton3 = new JButton();
    private JButton      jButton4 = new JButton();
    
	private Node no;
	
	private String distribuicao;

    public Servico(Graph graph, Node no, int indice, int tipoNo) {
    	
		this.no = no;
		try {
            jbInit();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    private void jbInit() throws Exception {
    	
        border1 = BorderFactory.createEtchedBorder(Color.white,
                                                   new Color(165, 163, 151));
        titledBorder1 = new TitledBorder(border1, "Distribuicao");
        border2 = BorderFactory.createEtchedBorder(Color.white,
                                                   new Color(165, 163, 151));
        border3 = BorderFactory.createEtchedBorder(Color.white,
                                                   new Color(165, 163, 151));
        border4 = BorderFactory.createEtchedBorder(Color.white,
                                                   new Color(165, 163, 151));

        jPanel1.setLayout(null);
        jPanel2.setBorder(titledBorder1);
        jPanel2.setBounds(new Rectangle(9, 9, 311, 141));
        jPanel2.setLayout(null);
        this.setTitle("Servico");
        jRadioButtonExp.setSelected(true);
        distribuicao = "expntl";
        jRadioButtonExp.setText("Exponencial");
        jRadioButtonExp.setBounds(new Rectangle(18, 26, 105, 23));
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
        
        
        jTextFieldMedia.setText(no.getMedia());
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
        jTextFieldDesvio.setText(no.getDesvioPadrao());
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
        
        jTextFieldSeq.setText(no.getSequencia());              
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
        jTextFieldPMaisP.setText(no.getPontoMaisProvavel());
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
        jLabel6.setText("Provavel");
        jLabel6.setBounds(new Rectangle(187, 245, 62, 15));
        jLabel7.setText("(Distribuicao Triangular)");
        jLabel7.setBounds(new Rectangle(187, 258, 150, 15));
        jPanel1.setBorder(border3);
        jPanel4.setBorder(border4);
        jPanel4.setBounds(new Rectangle(9, 293, 311, 10));
        jButton3.setBounds(new Rectangle(68, 320, 73, 25));
        jButton3.setText("Ok");
        
        jButton3.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){				
				okPerformed(e);
				
			}
		});
		
        jButton4.setBounds(new Rectangle(184, 320, 85, 25));
        jButton4.setText("Cancelar");
        jButton4.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){				
				cancelPerformed(e);
				
			}
		});
        
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
        
		this.setTitle("Serviço");
		this.setSize(new Dimension(338, 400));
		this.setState(Frame.NORMAL); 
        
    	if (no.getDistribuicaoServico().equals("expntl"))
    		jRadioButtonExp.setSelected(true);
    	else if (no.getDistribuicaoServico().equals("hyperx"))
    		jRadioButtonHiper.setSelected(true);
    	else if (no.getDistribuicaoServico().equals("erlang"))
    		jRadioButtonErl.setSelected(true);
    	else if (no.getDistribuicaoServico().equals("normal"))
    		jRadioButtonTrian.setSelected(true);
    	else if (no.getDistribuicaoServico().equals("uniform"))
    		jRadioButtonUniforme.setSelected(true);
        
       
    }
    
    private boolean checkProbs()
    {  
  	  if (jTextFieldMedia.getText().equals("")) {
  		  JOptionPane.showMessageDialog(
  				  null,
  				  "Digite a média para a distribuição",
  				  "ASDA - Formulário Incompleto",
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
  					  "Digite o desvio padrão para a distribuição",
  					  "ASDA - Formulário Incompleto",
  					  JOptionPane.ERROR_MESSAGE);
  			  return false;			  
  		  }	
		  else if (jRadioButtonHiper.isSelected())
		  {
			  if ((jTextFieldDesvio.getText() != null) && (jTextFieldMedia.getText()!=null))
				  // checa se desvio maior que media (tem que ser)
				  if ((Double.parseDouble(jTextFieldDesvio.getText())) <= Double.parseDouble(jTextFieldMedia.getText()))
				  {
					  JOptionPane.showMessageDialog(
							  this,
							  "Desvio deve ser maior que média para hiperexponencial",
							  "Valores inválidos",							  
							  JOptionPane.INFORMATION_MESSAGE);
					  return false;
				  }
		  }
		  else if (jRadioButtonErl.isSelected())
		  {
			  if ((jTextFieldDesvio.getText() != null) && (jTextFieldMedia.getText()!=null))
				  // checa se desvio maior que media (tem que ser)
				  if ((Double.parseDouble(jTextFieldDesvio.getText())) >= Double.parseDouble(jTextFieldMedia.getText()))
				  {
					  JOptionPane.showMessageDialog(
							  this,
							  "Desvio deve ser menor que média para earlang",
							  "Valores inválidos",							  
							  JOptionPane.INFORMATION_MESSAGE);
					  return false;
				  }
		  }
		  else if (jRadioButtonUniforme.isSelected())
		  {
			  if ((jTextFieldDesvio.getText() != null) && (jTextFieldMedia.getText()!=null))
				  // checa se desvio maior que media (tem que ser)
				  if ((Double.parseDouble(jTextFieldDesvio.getText())) <= Double.parseDouble(jTextFieldMedia.getText()))
				  {
					  JOptionPane.showMessageDialog(
							  this,
							  "Desvio deve ser maior que a média para uniforme (média=limite inferior, desvio_padrão=limite_superior",
							  "Valores inválidos",							  
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
  					  "Digite o desvio padrão",
  					  "ASDA - Formulário Incompleto",
  					  JOptionPane.ERROR_MESSAGE);
  			  return false;			  
  		  }				  
  	  }
  	  
  	  return true;
    }
    
    public void okPerformed(ActionEvent e){

    	JFrame frame = null;
        	
    	if (jTextFieldMedia.getText().equals("")){
    		JOptionPane.showMessageDialog(frame,"Digite a média de chegada na fonte!!!",
    		"ASDA - Erro",
    		JOptionPane.ERROR_MESSAGE);
    		jTextFieldMedia.grabFocus();
    	}
    	else{
    		if (jTextFieldSeq.getText().equals("")){
    			JOptionPane.showMessageDialog(frame,"Digite a seqüência de distribuição - 0-15)!!!",
    			"ASDA - Erro",
    			JOptionPane.ERROR_MESSAGE);
    			jTextFieldSeq.grabFocus();    			
    		}
    		else
    			if ( (Integer.parseInt(jTextFieldSeq.getText()) < 0) || (Integer.parseInt(jTextFieldSeq.getText()) > 15) ){
    				JOptionPane.showMessageDialog(frame,"Só pode ser um valor de 0 à 15",
    						"ASDA - Erro",
    						JOptionPane.ERROR_MESSAGE);
    						jTextFieldSeq.grabFocus();
    			}
    			else{
    				if (checkProbs()){
    					no.setDistribuicaoServico(distribuicao);
    					no.setMedia(jTextFieldMedia.getText());
    					no.setSequencia(jTextFieldSeq.getText());
    					if (!jTextFieldDesvio.equals(""))
    					{
    						no.setDesvioPadrao(jTextFieldDesvio.getText());
    					}
    					
    					if (!jTextFieldPMaisP.equals(""))
    					{
    						no.setPontoMaisProvavel(jTextFieldPMaisP.getText());
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


