package frames;

import java.awt.BorderLayout;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JScrollPane;
import javax.swing.JToggleButton;

import asda.UsuarioCadastro;

/**
 * extensão da Classe janela para modelar modelos baseados em Queuing State Charts
 * @author Thais Souza Aiza
 *
 */
public class JanelaQueuingStateCharts extends Janela {
	
	public JanelaQueuingStateCharts() {
		this(null);
	}
	
	public JanelaQueuingStateCharts(UsuarioCadastro userInfo)
	{
		super(userInfo);
		
		ImageIcon[] imagem = new ImageIcon[5];		/* essa parte para as filhas */
		button = new JToggleButton[5];
		
		for(int i=0;i<button.length;i++){
			imagem[i] = new ImageIcon("IMG/t"+(i+1)+".gif");
		}
		
		
		button[0] = new JToggleButton(imagem[0]);
		button[0].setPreferredSize(new Dimension(40,button[0].getHeight()));
		button[0].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bPerformed(e);
			}
		});
		
		button[1] = new JToggleButton(imagem[1]);
		button[1].setPreferredSize(new Dimension(40,button[1].getHeight()));
		button[1].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bPerformed(e);
			}
		});
		
		button[2] = new JToggleButton(imagem[2]);
		button[2].setPreferredSize(new Dimension(40,button[2].getHeight()));
		button[2].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bPerformed(e);
			}
		});
		
		button[3] = new JToggleButton(imagem[3]);
		button[3].setPreferredSize(new Dimension(40,button[3].getHeight()));
		button[3].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				arcoPerformed(e);
			}
		});
		
		button[4] = new JToggleButton(imagem[4]);
		button[4].setPreferredSize(new Dimension(40,button[4].getHeight()));
		button[4].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				limpaPerformed(e);				
			}
		});
		
		for(int i=0;i<button.length;i++){
			tools.add(button[i]);
		}
		
		this.getContentPane().add(tools,BorderLayout.WEST);
		
	/*	JScrollPane scrollPane =
			new JScrollPane(d);
		scrollPane.setBounds(2,1,500,200);		*/
		
		
		
		
		//this.getContentPane().add(scrollPane);
		
		this.pack();
		
		this.setSize(650,550);
		
		this.setTitle("ASDA - Ambiente de Simulação Distribuída Automático");
		JFrameUtil.centraliza(this);
		this.setVisible(true);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		

	}
	
	void bPerformed(ActionEvent e){
		
		//Variáveis auxiliares
		ImageIcon img1 = new ImageIcon("img/T1.gif");
		ImageIcon img2 = new ImageIcon("img/T2.gif");
		ImageIcon img3 = new ImageIcon("img/T3.gif");
		
		
		
		ImageIcon imagem1 = new ImageIcon("imgIcones/T1.gif");	//Fonte
		ImageIcon imagem2 = new ImageIcon("imgIcones/T2.gif");  //Centro de Servico
		ImageIcon imagem3 = new ImageIcon("imgIcones/T3.gif");  //Sorvedouro
		
		
		if (selecionado == null){
			selecionado = (ImageIcon)((JToggleButton)e.getSource()).getIcon();
			
			Image img = selecionado.getImage();
			
			String aux = selecionado.toString();
			
			String aux1 = img1.toString();
			String aux2 = img2.toString();
			String aux3 = img3.toString();
			
			
			if (aux.equals(aux1)){
				selecionado = imagem1;
				tipoNo = 1; //Fonte
				
			}
			else if (aux.equals(aux2)){
				selecionado = imagem2;
				tipoNo = 2; //Centro de Servico
				
			}
			else if (aux.equals(aux3)){
				selecionado = imagem3;
				tipoNo = 3; //Sorvedouro
				
			}
			
			Dimension d = 
				Toolkit.getDefaultToolkit().getBestCursorSize(selecionado.getIconWidth(),
						selecionado.getIconHeight());
			Cursor c = Toolkit.getDefaultToolkit().createCustomCursor(img, new Point(d.width/2, d.height/2),
			"Símbolo");
			this.setCursor(c);
		}
		else this.release();
	}
	
	void limpaPerformed(ActionEvent e){
		limpaSelecionado = true;
		
	}
	
	
	
	/**
	 * Método para fácil inicialização do ambiente - para funcionar corretamente, precisa que
	 * os ajustes já tenham sido feitos (como criar um usuário em tempo de código para determinar a
	 * linguagem de simulação utilizada
	 * @param args
	 */
	public static void main(String[] args) {

		JanelaQueuingStateCharts j = new JanelaQueuingStateCharts();
	}
	
}
