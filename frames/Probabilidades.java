package frames;
import graph.Arc;
import graph.Graph;
import graph.Node;

import javax.swing.*;
import java.awt.*;
import javax.swing.border.*;


import java.awt.event.*;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2003</p>
 * <p>Company: </p>
 * @author Andr    Felipe Rodrigues - corre      es e implementa      o de m   todos para robustez
 * @author Thaiz Souza Aiza
 * @version 1.0
 */

public class Probabilidades extends JFrame {
  JPanel jPanel1 = new JPanel();
  Border border1;
  JLabel jLabel2 = new JLabel();
  JLabel labelOrigem = new JLabel();
  JTextField jTextField1 = new JTextField();
  Border border2;
  JButton jButton1 = new JButton();
  JLabel destino = new JLabel();
  JLabel labelDestino = new JLabel();
  Icon back24 = new ImageIcon("imagens/Back24.gif");
  Icon forward24 = new ImageIcon("imagens/Forward24.gif");


  public Node no;

  public Graph graph;

  public Arc arc;

  public int indice;

  public int tipoNo;

  public double prob = 100;

  public int ind = 0;
  
  private int posicao;
  private int minPosicao;
  
  public Probabilidades(Graph graph, Node no, int indice, int tipoNo) {

		this.no = no;
		this.graph = graph;
		this.indice = indice;
		this.tipoNo = tipoNo;


				try {
				  jbInit();
				}
				catch(Exception e) {
				  e.printStackTrace();
				}
  }
  private void jbInit() throws Exception {
  	
  	posicao = 0;
  	minPosicao = 0;

				border1 = BorderFactory.createEtchedBorder(Color.white,new Color(178, 178, 178));
				border2 = BorderFactory.createEtchedBorder(Color.white,new Color(151, 145, 140));
				jPanel1.setLayout(null);
				this.setResizable(false);
				this.setTitle("Probabilidades");
				jLabel2.setText("Probabilidade");
				jLabel2.setBounds(new Rectangle(19, 68, 88, 16));

				jTextField1.setBounds(new Rectangle(107, 65, 47, 22));

	jTextField1.addKeyListener(new KeyAdapter()  {
		public void keyTyped(KeyEvent e) {
			JFrameUtil.verificaDigito(e);
		}
	});
		
	jTextField1.addFocusListener(new FocusAdapter() {
		public void focusLost(FocusEvent e) {
			JFrameUtil.verificaNumeroReal(e);
		}
	});
				

				if (no.getSize() == 1){

						no.getArc(posicao).setProbabilidade("100");
						jTextField1.setText("100");
						jTextField1.setEditable(false);
				}
				else{
					if ((no.getArc(posicao).getProbabilidade().equals("100")) || (no.getArc(posicao).getProbabilidade().equals(""))){
							jTextField1.setText("");
							jTextField1.setEditable(true);
					}
					else
					{
						jTextField1.setText(no.getArc(posicao).getProbabilidade());
						jTextField1.setEditable(true);
					}
				}




				jPanel1.setBorder(border2);
				jButton1.setBounds(new Rectangle(51, 96, 79, 25));
				jButton1.setText("Ok");
				jButton1.addActionListener(new Probabilidades_jButton1_actionAdapter(this));
				destino.setText("Destino");
				destino.setBounds(new Rectangle(20, 39, 48, 15));


				labelDestino.setText(no.getArc(posicao).getNodeB().getNomeCentroServico());
				labelDestino.setBounds(new Rectangle(86, 39, 65, 15));

				jPanel1.add(labelOrigem, null);
				this.getContentPane().add(jPanel1, BorderLayout.CENTER);
				jPanel1.add(destino, null);
				jPanel1.add(labelDestino, null);
				jPanel1.add(jLabel2, null);
				jPanel1.add(jTextField1, null);
				jPanel1.add(jButton1, null);
				this.setResizable(false);
				this.setSize(new Dimension(220, 180));
	
	
  }
  

  
  public void posteriorPerformed(ActionEvent e){
  	
  		posicao = posicao + 1;
		labelDestino.setText(no.getArc(posicao).getNodeB().getNomeCentroServico());
		jTextField1.grabFocus();
	  	jTextField1.setText(no.getArc(posicao).getProbabilidade());
		if (posicao == no.getSize()-1) // colocando automaticamente a porcentagem para ultima porcentagem a colocar
		{	double somatemp = 0;
			double probtemp;
			for (int i=0; i < posicao; i++)
				somatemp += Double.parseDouble(no.getArc(i).getProbabilidade());
			probtemp = 100 - somatemp;
			jTextField1.setText(String.valueOf(probtemp));
			jTextField1.setEditable(false);
		}

  		
  }

  

  void jButton1_actionPerformed(ActionEvent e) {

		
		if (jTextField1.getText().equals("")){
			JOptionPane.showMessageDialog(null,"Campo n   o pode ser nulo!!!",
			"ASDA - Erro",
			JOptionPane.ERROR_MESSAGE);	
			jTextField1.grabFocus();			
		}
		else
		{
			
			if (posicao < no.getSize()-1) // se ainda n   o     a    ltima posi      o de probabilidade
			{
				double somatemp = 0;
				double probtemp;
				for (int i=0; i < posicao; i++)
					somatemp += Double.parseDouble(no.getArc(i).getProbabilidade());
				probtemp = Double.parseDouble(jTextField1.getText());
				if (somatemp + probtemp > 100.5)
					JOptionPane.showMessageDialog(
							null,
							"Ultrapassou 100% - Redigite a porcentagem\n" +
							"Restaram " + (100 - somatemp) + "%",
							"ASDA - Limite ultrapassado",
							JOptionPane.ERROR_MESSAGE);
				else
				{
					no.getArc(posicao).setProbabilidade(jTextField1.getText());
					posteriorPerformed(e);
				}				
				jTextField1.grabFocus();
			}
			else // est    na ultima posi      o - preencher automaticamente
			{
			/*	if (no.getSize() > 1) // se tem mais que um n    (se tiver um n    s   , j    est    como 100% preenchidos ao iniciar
				{
					double somatemp = 0;
					double probtemp;
					for (int i=0; i < posicao; i++)
						somatemp += Double.parseDouble(no.getArc(i).getProbabilidade());
					probtemp = 100 - somatemp;
					jTextField1.setText(String.valueOf(probtemp));
					jTextField1.setEditable(false);		
				}*/
				no.getArc(posicao).setProbabilidade(jTextField1.getText());		
				setVisible(false);
				dispose();
			}
			
		}
  }
  
  public static double somaLig(Node no)
  {
	  double num = 0;
	  for (int i = 0; i < no.getSize(); i++)
		  if ( (no.getArc(i).getProbabilidade()!=null) && (!no.getArc(i).getProbabilidade().equals("")) )
			  num += Double.parseDouble(no.getArc(i).getProbabilidade());
	  
	  return num;
  }
  
}


class Probabilidades_jButton1_actionAdapter implements java.awt.event.ActionListener {
  Probabilidades adaptee;

  Probabilidades_jButton1_actionAdapter(Probabilidades adaptee) {
				this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
				adaptee.jButton1_actionPerformed(e);
  }
}

