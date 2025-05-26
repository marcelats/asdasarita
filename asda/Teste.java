package asda;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Teste extends JFrame{
	
	private JPanel panel;
	
	
	public Teste() { this("Sem nome"); }
	
	public Teste(String title)
	{
		super (title);
		initComponents();
	}
	
	private void initComponents()
	{
		Container c = getContentPane();
		c.setLayout(new BorderLayout());
				
		panel = new JPanel();
		
		
		
		c.add(panel, BorderLayout.CENTER);

		
		
		
		
		
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		
	}
	

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
