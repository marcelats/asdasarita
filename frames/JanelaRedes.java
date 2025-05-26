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
 * Classe que extende Janela e implementa as funcionalidades para modelagem
 * baseada na teoria de redes de filas
 * @author Andr    Felipe Rodrigues
 *
 */
public class JanelaRedes extends Janela {
	
	/* tipoNo de qualquer centro de servi   o     o mesmo valor - tipoNo serve para o modulo avaliador */
	
	public JanelaRedes()
	{
		this(null); 
	}
	
	public JanelaRedes(UsuarioCadastro user)
	{
		super(user);
		
		ImageIcon[] imagem = new ImageIcon[8];		/* essa parte para as filhas */
		button = new JToggleButton[8];
		
		for(int i=0;i<button.length;i++){
			imagem[i] = new ImageIcon("IMG/r"+(i+1)+".gif");
		}
				
		/* at    button[5] o m   todo bEntetyPerformed controla */
		button[0] = new JToggleButton(imagem[0]);
		button[0].setPreferredSize(new Dimension(40,button[0].getHeight()));
		button[0].setToolTipText("Uma fila e um servidor");
		button[0].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bEntityPerformed(e);
			}
		});
		
		button[1] = new JToggleButton(imagem[1]);
		button[1].setPreferredSize(new Dimension(40,button[1].getHeight()));
		button[1].setToolTipText("Um fila e v   rios servidores");
		button[1].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bEntityPerformed(e);
			}
		});
		
		button[2] = new JToggleButton(imagem[2]);
		button[2].setPreferredSize(new Dimension(40,button[2].getHeight()));
		button[2].setToolTipText("V   rias filas e um servidor");
		button[2].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bEntityPerformed(e);
			}
		});
		button[2].setEnabled(false);
		
		button[3] = new JToggleButton(imagem[3]);
		button[3].setPreferredSize(new Dimension(40,button[3].getHeight()));
		button[3].setToolTipText("V   rias filas e v   rios servidores");
		button[3].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bEntityPerformed(e);
			}
		});
		button[3].setEnabled(false);
		
		
		button[4] = new JToggleButton(imagem[4]);
		button[4].setPreferredSize(new Dimension(40,button[4].getHeight()));
		button[4].setToolTipText("Chegada do modelo");
		button[4].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bEntityPerformed(e);				
			}
		});
		
		button[5] = new JToggleButton(imagem[5]);
		button[5].setPreferredSize(new Dimension(40,button[5].getHeight()));
		button[5].setToolTipText("Saida do modelo");
		button[5].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				bEntityPerformed(e);			
			}
		});
				
		button[6] = new JToggleButton(imagem[6]);
		button[6].setPreferredSize(new Dimension(40,button[6].getHeight()));
		button[6].setToolTipText("criar liga      o entre centros de servi   o");
		button[6].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				arcoPerformed(e);		
			}
		});
		
		button[7] = new JToggleButton(imagem[7]);
		button[7].setPreferredSize(new Dimension(40,button[7].getHeight()));
		button[7].setToolTipText("Excluir centro de servi   o");
		button[7].addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				limpaPerformed(e);				
			}
		});
		
		
		
		for(int i=0;i<button.length;i++){
			tools.add(button[i]);
		}
		
		this.getContentPane().add(tools,BorderLayout.WEST);
		
		/*tentativa de usar scrollpane - n   o funcionando */
		JScrollPane scrollPane =
			new JScrollPane(d);
		scrollPane.setBounds(2,1,500,200);		
		
		this.getContentPane().add(scrollPane);
		
		this.pack();
		
		this.setSize(650,550);
		
		this.setTitle("ASDA - Ambiente de Simula      o Distribu   da Autom   tico - Redes de Filas");
		JFrameUtil.centraliza(this);
		this.setVisible(true);
	}
	
	void bEntityPerformed(ActionEvent e){
		
		ImageIcon imagemR1x1 = new ImageIcon("imgIcones/R1x1.gif");
		ImageIcon imagemR1xi = new ImageIcon("imgIcones/R1xi.gif");
		ImageIcon imagemRix1 = new ImageIcon("imgIcones/Rix1.gif");
		ImageIcon imagemRixi = new ImageIcon("imgIcones/Rixi.gif");
		ImageIcon imagemSource = new ImageIcon("imgIcones/Rsource.gif");
		ImageIcon imagemEnd = new ImageIcon("imgIcones/REnd.gif");
		
		
		
		if (selecionado == null){
			selecionado = (ImageIcon)((JToggleButton)e.getSource()).getIcon();
			
			Image img = selecionado.getImage();
			
			
			if (e.getSource() == button[0])  // Uma fila um servidor
			{
				selecionado = imagemR1x1;
				tipoNo = 2; // Centro de servi   o
				

			}
			else if (e.getSource() == button[1]) // uma fila e v   rios servidores
			{
				selecionado = imagemR1xi;
				tipoNo = 2;
				

			}
			else if(e.getSource() == button[2]) // v   rias filas e um servidor
			{
				selecionado = imagemRix1;
				tipoNo = 2;
				

			}
			else if(e.getSource() == button[3]) // v   rias filas e v   rios servidores
			{
				selecionado = imagemRixi;
				tipoNo = 2;
				

			}
			else if(e.getSource() == button[4])
			{			
				selecionado = imagemSource;
				tipoNo = 1;	// fonte
			}
			else if(e.getSource() == button[5])
			{
				selecionado = imagemEnd;
				tipoNo = 3; // sorvedouro
			}
			
			Dimension d = 
				Toolkit.getDefaultToolkit().getBestCursorSize(selecionado.getIconWidth(),
						selecionado.getIconHeight());
			Cursor c = Toolkit.getDefaultToolkit().createCustomCursor(img, new Point(d.width/2, d.height/2),
			"S   mbolo");
			this.setCursor(c);
		}
		else this.release();
	}
	
	void limpaPerformed(ActionEvent e){
		limpaSelecionado = true;
		
	}
	
	
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JanelaRedes j = new JanelaRedes();
	//	System.out.println(System.getProperty("os.version"));
		//System.out.println(args[0]);
	}
	
}

	
