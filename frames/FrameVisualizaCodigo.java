package frames;
import javax.swing.*;
import java.awt.*;
import java.io.*;
import javax.swing.border.*;

/**
 * 
 * @author Thais Souza Aiza
 * @author André Felipe Rodrigues (modificações simples)
 * @version 1.0
 */

public class FrameVisualizaCodigo extends JFrame {
	
	private String filename = null;
	// private JPanel jPanel1 = new JPanel();
	private JTextArea jTextArea1 = new JTextArea();
	private Border border1;
	private BorderLayout layout;
	
	public FrameVisualizaCodigo(String filename) {
		try {
			this.filename = filename;
			jbInit();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	private void jbInit() throws Exception {
		border1 = BorderFactory.createEtchedBorder(Color.white,new Color(178, 178, 178));
		layout = new BorderLayout();
		Container c = getContentPane();
		c.setLayout(layout);
		
		this.setTitle("ASDA");
		this.setSize(450,500);
		// jPanel1.setLayout(null);
		jTextArea1.setBorder(border1);
		//jTextArea1.setBounds(new Rectangle(2, 1, 440, 465));
		jTextArea1.setText("");	
		jTextArea1.setEditable(false);
	
		
		// SETAR UMA FONTE MELHOR PARA A VISUALIZAÇÃO DO TEXTO DO CÓDIGO :-(
		//	jTextArea1.setFont()
				
		JScrollPane scrollPane =
			new JScrollPane(jTextArea1);
		// scrollPane.setBounds(new Rectangle(2, 1, 440, 465));
		
		c.add(scrollPane, BorderLayout.CENTER);
		
		
		// this.getContentPane().add(jPanel1, BorderLayout.CENTER);
		// jPanel1.add(scrollPane, null);
		abreCodigo();
		this.setTitle("ASDA - "+filename);
		
		
	}
	
	void abreCodigo(){		
		FileReader arq;
		try {
			//System.out.println("filename em abreCodigo "+filename);
			arq = new FileReader(filename);
			
			BufferedReader sai = new BufferedReader(arq);
			
			String linha = new String();
			
			jTextArea1.setText("");
			
			while ((linha = sai.readLine()) != null){
			//	System.out.println("linha "+linha);
				jTextArea1.append(linha);
				jTextArea1.append("\n");
			}
			
			arq.close();
			
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
	}
	
	
}





