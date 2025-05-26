package frames;
import graph.Graph;
import graph.ProcessoLogicoParSMPL;

import java.awt.BorderLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;


import java.awt.Dimension;


/**
 * TODO - COMENTAR
 * @author andrefr
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class FramePLogico extends JFrame {

	private static final long serialVersionUID = 1L;

	private JPanel jContentPane = null;

	private JPanel jPanel1 = null;

	private JButton jButtonNext = null;

	private JButton jButtonAnt = null;

	private JButton jButtonNovo = null;

	private JButton jButtonSalvar = null;

	private JButton jButtonApagar = null;

	private JButton jButtonSair = null;

	private JCheckBox jCheckBox = null;

	private JLabel jLabel = null;

	private JTextField jTextFieldTid = null;

	private JLabel jLabel1 = null;

	private JTextField jTextFieldSlaveName = null;

	private JButton jButtonEditar = null;

	private JLabel jLabelValorSemente = null;

	private JTextField jTextFieldValorSemente = null;
	
	
	// para ver visual - comentar essas variáveis
	private Graph graph;	
	private int cp;	
	private boolean editar, naveg, novo, paiSelected;

	/**
	 * This is the default constructor
	 */
	public FramePLogico(Graph graph) {
		super();
		initialize();
		this.graph = graph;
		
		jTextFieldTid.setEditable(false);
		
		editar = false;
		novo = false;
		naveg = true;
		paiSelected = false;
		
		
		camposBotoesEnabled();
		
		if (graph.getPLogicos().size() == 0)
		{
			cp = -1;
			JOptionPane.showMessageDialog(
					null
					,"Defina os processos lógicos - ainda não existe nenhum processo lógico definido"
					,"Defina Processos Lógicos",
					JOptionPane.INFORMATION_MESSAGE
					);
		}
		else
		{
			loadInfo(0);
			cp = 0;
		}
			
	}
	
	
	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initialize() {
		this.setSize(437, 237);
		this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		this.setContentPane(getJContentPane());
		this.setTitle("Definição de Processos Lógicos");
		this.setVisible(true);
	}

	/**
	 * This method initializes jContentPane
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {
			BorderLayout borderLayout = new BorderLayout();
			borderLayout.setHgap(1);
			borderLayout.setVgap(1);
			jContentPane = new JPanel();
			jContentPane.setLayout(borderLayout);
			jContentPane.add(getJPanel1(), BorderLayout.CENTER);
		}
		return jContentPane;
	}

	/**
	 * This method initializes jPanel1	
	 * 	
	 * @return javax.swing.JPanel	
	 */
	private JPanel getJPanel1() {
		if (jPanel1 == null) {
			jLabelValorSemente = new JLabel();
			jLabelValorSemente.setBounds(new Rectangle(24, 95, 113, 21));
			jLabelValorSemente.setText("Valor da semente");
			jLabel1 = new JLabel();
			jLabel1.setText("SLAVENAME");
			jLabel1.setBounds(new Rectangle(26, 69, 81, 16));
			jLabel = new JLabel();
			jLabel.setText("Número do Processo Lógico:");
			jLabel.setBounds(new Rectangle(26, 43, 172, 16));
			jPanel1 = new JPanel();
			jPanel1.setLayout(null);
			jPanel1.add(getJCheckBox(), null);
			jPanel1.add(jLabel, null);
			jPanel1.add(getJTextFieldTid(), null);
			jPanel1.add(jLabel1, null);
			jPanel1.add(getJTextFieldSlaveName(), null);
			jPanel1.add(getJButtonNext(), null);
			jPanel1.add(getJButtonAnt(), null);
			jPanel1.add(getJButtonNovo(), null);
			jPanel1.add(getJButtonSalvar(), null);
			jPanel1.add(getJButtonApagar(), null);
			jPanel1.add(getJButtonSair(), null);
			jPanel1.add(getJButtonEditar(), null);
			jPanel1.add(jLabelValorSemente, null);
			jPanel1.add(getJTextFieldValorSemente(), null);
		}
		return jPanel1;
	}

	/**
	 * This method initializes jButtonNext	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButtonNext() {
		if (jButtonNext == null) {
			jButtonNext = new JButton();
			jButtonNext.setToolTipText("");
			jButtonNext.setName("jButtonNext");
			jButtonNext.setBounds(new Rectangle(114, 129, 82, 26));
			jButtonNext.setText("Próximo");
			jButtonNext.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					nextPerformed(e);
				}
			});
		}
		return jButtonNext;
	}
	
	private void nextPerformed(ActionEvent e)
	{
		if (cp < graph.getPLogicos().size()-1)
		{
			cp++;
			loadInfo(cp);
			jButtonAnt.setEnabled(true);
			if (cp == graph.getPLogicos().size()-1)
				jButtonNext.setEnabled(false);
		}
	}

	/**
	 * This method initializes jButtonAnt	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButtonAnt() {
		if (jButtonAnt == null) {
			jButtonAnt = new JButton();
			jButtonAnt.setText("Anterior");
			jButtonAnt.setBounds(new Rectangle(22, 129, 80, 26));
			jButtonAnt.setName("jButtonAnt");
			jButtonAnt.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					anteriorPerformed(e);
				}
			});
		}
		return jButtonAnt;
	}
	
	private void anteriorPerformed(ActionEvent e)
	{
		if (cp > 0)
		{
			cp--;
			loadInfo(cp);
			jButtonNext.setEnabled(true);
			if (cp==0)
				jButtonAnt.setEnabled(false);
		}

	}

	/**
	 * This method initializes jButtonNovo	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButtonNovo() {
		if (jButtonNovo == null) {
			jButtonNovo = new JButton();
			jButtonNovo.setText("Novo");
			jButtonNovo.setBounds(new Rectangle(25, 167, 62, 26));
			jButtonNovo.setName("jButtonNovo");
			jButtonNovo.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					novoPerformed(e);
				}
			});
		}
		return jButtonNovo;
	}
	
	private void novoPerformed(ActionEvent e)
	{
		int nTid;
		if (graph.getPLogicos().size() > 0)
		    nTid = ((ProcessoLogicoParSMPL)graph.getPLogicos().get(graph.getPLogicos().size()-1)).getTid() + 1;
		else
			nTid = 0;

	//	jTextFieldLookAhead.setText("");
		jTextFieldSlaveName.setText("");
		jCheckBox.setSelected(false);
	//	jTextFieldNomeMaquina.setText("");
		jTextFieldValorSemente.setText("");
		
		jTextFieldTid.setText(String.valueOf(nTid));
		
		editar = false;
		novo = true;
		naveg = false;
		
	/*	jButtonAnt.setEnabled(true);
		jButtonNext.setEnabled(false);*/
		
		camposBotoesEnabled();
		
	}

	/**
	 * This method initializes jButtonSalvar	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButtonSalvar() {
		if (jButtonSalvar == null) {
			jButtonSalvar = new JButton();
			jButtonSalvar.setText("Salvar");
			jButtonSalvar.setBounds(new Rectangle(274, 167, 70, 26));
			jButtonSalvar.setName("jButtonSalvar");
			jButtonSalvar.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					salvarPerformed(e);
				}
			});
		}
		return jButtonSalvar;
	}

	private void salvarPerformed(ActionEvent e)
	{

		int nTid = graph.getPLogicos().size();
		int tidPai = -1;
		boolean jaTemPai = false;
		ProcessoLogicoParSMPL p = new ProcessoLogicoParSMPL();
		for (int i=0; (i < nTid) && (!jaTemPai); i++)
		{
			if (((ProcessoLogicoParSMPL)graph.getPLogicos().get(i)).isProcessoPai())
			{
				tidPai = ((ProcessoLogicoParSMPL)graph.getPLogicos().get(i)).getTid();
				jaTemPai = true;	
			}

		}
		
		if (!editar)
		{			
			if (!jaTemPai)
			{
				p.setProcessoPai(jCheckBox.isSelected());
				if (jCheckBox.isSelected())
				{
	//				p.setNomeMaquina(jTextFieldNomeMaquina.getText());
					p.setValorSemente(Integer.parseInt(jTextFieldValorSemente.getText()));
				}
			}
			else
			{
				if ((jCheckBox.isSelected() && (tidPai != Integer.parseInt(jTextFieldTid.getText()))))
				
					JOptionPane.showMessageDialog(
							null,
							"Já existe um processo pai registrado.\n" +
							"Só é permitido um processo pai por simulação",
							"ASDA - Processo pai já existente",
							JOptionPane.WARNING_MESSAGE
							);
					p.setProcessoPai(false);
					jCheckBox.setSelected(false);				
			}
			
			int nextTid;
			
			if (graph.getPLogicos().size()!=0)
			   nextTid = ((ProcessoLogicoParSMPL)graph.getPLogicos().get(graph.getPLogicos().size() -1)).getTid() + 1;
			else
				nextTid = 0;
			
			p.setTid(nextTid);
	//		if ((jTextFieldLookAhead.getText()==null) || jTextFieldLookAhead.getText().equals(""))
	//			jTextFieldLookAhead.setText("0.0");
	//		p.setLookAhead(Double.parseDouble(jTextFieldLookAhead.getText()));
			p.setSlaveName(jTextFieldSlaveName.getText());
			
//			if ((jTextFieldNomeMaquina.getText()!=null) && (!jTextFieldNomeMaquina.getText().equals("")))
	//			p.setNomeMaquina(jTextFieldNomeMaquina.getText());
			
			if ((jTextFieldValorSemente.getText()!=null) && (!jTextFieldValorSemente.getText().equals("")))
				p.setValorSemente(Integer.parseInt(jTextFieldValorSemente.getText()));
			
			graph.getPLogicos().add(p);
			cp = nextTid;
			loadInfo(cp);
		}
		else
		{
			if (cp!=-1)
			{
				if (!jaTemPai)
				{
					((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setProcessoPai(jCheckBox.isSelected());
					if (jCheckBox.isSelected())
					{
	//					((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setNomeMaquina(jTextFieldNomeMaquina.getText());
						((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setValorSemente(Integer.parseInt(jTextFieldValorSemente.getText()));
					}
				}
				else
				{
					if ((jCheckBox.isSelected() && (tidPai != Integer.parseInt(jTextFieldTid.getText()))))
						JOptionPane.showMessageDialog(
								null,
								"Já existe um processo pai registrado.\n" +
								"Só é permitido um processo pai por simulação",
								"ASDA - Processo pai já existente",
								JOptionPane.WARNING_MESSAGE
								);
					
					((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setProcessoPai(false);
					jCheckBox.setSelected(false);					
				}
				
			//	((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setTid();
		//		((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setLookAhead(Double.parseDouble(jTextFieldLookAhead.getText()));
				((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setSlaveName(jTextFieldSlaveName.getText());
		//		if ((jTextFieldNomeMaquina.getText()!=null) && (!jTextFieldNomeMaquina.getText().equals("")))
		//			((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setNomeMaquina(jTextFieldNomeMaquina.getText());
				
				if ((jTextFieldValorSemente.getText()!=null) && (!jTextFieldValorSemente.getText().equals("")))
					((ProcessoLogicoParSMPL)graph.getPLogicos().get(cp)).setValorSemente(Integer.parseInt(jTextFieldValorSemente.getText()));
			}
		}
		
		naveg = true;
		novo = false;
		editar = false;
		camposBotoesEnabled();
	}
	/**
	 * This method initializes jButtonApagar	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButtonApagar() {
		if (jButtonApagar == null) {
			jButtonApagar = new JButton();
			jButtonApagar.setText("Apagar");
			jButtonApagar.setBounds(new Rectangle(184, 167, 75, 26));
			jButtonApagar.setName("jButtonApagar");
			jButtonApagar.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					apagarPerformed(e);
				}
			});
		}
		return jButtonApagar;
	}
	
	private void apagarPerformed(ActionEvent e)
	{
		if (cp!=-1)
		{
			graph.getPLogicos().remove(cp);
			if (cp > 0)
				anteriorPerformed(e);
			else
				if (cp < graph.getPLogicos().size()-1)
					nextPerformed(e);			
		}
		
		if (graph.getPLogicos().size()==0)
		{
			cp = -1;
		//	jTextFieldLookAhead.setText("");
			jTextFieldSlaveName.setText("");
			jTextFieldTid.setText("");
			//jTextFieldNomeMaquina.setText("");
			jTextFieldValorSemente.setText("");
		}
		naveg = true;
		novo = false;
		editar = false;
		camposBotoesEnabled();
	}

	/**
	 * This method initializes jButtonSair	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButtonSair() {
		if (jButtonSair == null) {
			jButtonSair = new JButton();
			jButtonSair.setText("Sair");
			jButtonSair.setBounds(new Rectangle(359, 167, 57, 26));
			jButtonSair.setName("jButtonSair");
			jButtonSair.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					sairPerformed(e);
				}
			});
		}
		return jButtonSair;
	}
	
	private void sairPerformed(ActionEvent e)
	{
		dispose();
		setVisible(false);
	}

	/**
	 * This method initializes jCheckBox	
	 * 	
	 * @return javax.swing.JCheckBox	
	 */
	private JCheckBox getJCheckBox() {
		if (jCheckBox == null) {
			jCheckBox = new JCheckBox();
			jCheckBox.setText("Processo Pai");
			jCheckBox.setBounds(new Rectangle(26, 17, 101, 16));
			jCheckBox.addItemListener(new java.awt.event.ItemListener() {
				public void itemStateChanged(java.awt.event.ItemEvent e) {
					if (jCheckBox.isSelected())
						paiSelected = true;
					else
						paiSelected = false;
					
					camposBotoesEnabled();
							
				}
			});
		}
		return jCheckBox;
	}

	/**
	 * This method initializes jTextFieldTid	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextFieldTid() {
		if (jTextFieldTid == null) {
			jTextFieldTid = new JTextField();
			jTextFieldTid.setColumns(4);
			jTextFieldTid.setBounds(new Rectangle(205, 40, 45, 23));
		}
		return jTextFieldTid;
	}

	/**
	 * This method initializes jTextFieldNMaquina	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextFieldSlaveName() {
		if (jTextFieldSlaveName == null) {
			jTextFieldSlaveName = new JTextField();
			jTextFieldSlaveName.setColumns(50);
			jTextFieldSlaveName.setBounds(new Rectangle(113, 67, 299, 20));
		}
		return jTextFieldSlaveName;
	}

	/**
	 * This method initializes jButtonEditar	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButtonEditar() {
		if (jButtonEditar == null) {
			jButtonEditar = new JButton();
			jButtonEditar.setText("Editar");
			jButtonEditar.setBounds(new Rectangle(102, 167, 67, 26));
			jButtonEditar.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					editarPerformed(e);
				}
			});
		}
		return jButtonEditar;
	}
	
	private void editarPerformed(ActionEvent e)
	{
		editar = true;
		novo = false;
		naveg = false;
		camposBotoesEnabled();

	}



	private void camposBotoesEnabled()
		{
			if ((graph.getPLogicos().size() == 0) && (!novo))
			{
				jButtonAnt.setEnabled(false);
				jButtonNext.setEnabled(false);
				jButtonNovo.setEnabled(true);
				jButtonApagar.setEnabled(false);
				jButtonEditar.setEnabled(false);
				jButtonSalvar.setEnabled(false);
				
				jTextFieldSlaveName.setEditable(false);
				//jTextFieldLookAhead.setEditable(false);
				jCheckBox.setEnabled(false);
				//jTextFieldNomeMaquina.setEditable(false);
				jTextFieldValorSemente.setEditable(false);
				
				jButtonNovo.grabFocus();
				
				naveg = false;
				novo = false;
				editar = false;
				return;
			}
			else if ((graph.getPLogicos().size()==1) && (!novo) && (!editar))
			{
				jButtonAnt.setEnabled(false);
				jButtonNext.setEnabled(false);
				jButtonNovo.setEnabled(true);
				jButtonApagar.setEnabled(true);
				jButtonEditar.setEnabled(true);
				jButtonSalvar.setEnabled(false);
				
				jTextFieldSlaveName.setEditable(false);
				//jTextFieldLookAhead.setEditable(false);
				jCheckBox.setEnabled(false);
				//jTextFieldNomeMaquina.setEditable(false);
				jTextFieldValorSemente.setEditable(false);
				
				
				jButtonNovo.grabFocus();
				
				naveg = false;
				novo = false;
				editar = false;
				return;
			}
			
			if (paiSelected)
			{
				//jLabelNomeMaquina.setVisible(true);
				//jTextFieldNomeMaquina.setVisible(true);
				jLabelValorSemente.setVisible(true);
				jTextFieldValorSemente.setVisible(true);
				//jTextFieldNomeMaquina.setEditable(true);
				jTextFieldValorSemente.setEditable(true);
				
			}
			else
			{
				//jLabelNomeMaquina.setVisible(false);
				//jTextFieldNomeMaquina.setVisible(false);
				jLabelValorSemente.setVisible(false);
				jTextFieldValorSemente.setVisible(false);
				//jTextFieldNomeMaquina.setEditable(false);
				jTextFieldValorSemente.setEditable(false);
				
			}
			
			if (naveg)
			{
				
				jButtonAnt.setEnabled(true);
				jButtonNext.setEnabled(true);
				jButtonNovo.setEnabled(true);
				jButtonApagar.setEnabled(true);
				jButtonEditar.setEnabled(true);
				jButtonSalvar.setEnabled(false);
				
				jCheckBox.setEnabled(false);
				jTextFieldSlaveName.setEditable(false);
				//jTextFieldLookAhead.setEditable(false);
				//jTextFieldNomeMaquina.setEditable(false);
				jTextFieldValorSemente.setEditable(false);
				
				
				jButtonNext.grabFocus();
				return;
			}
			
			if (editar)
			{
				jButtonAnt.setEnabled(false);
				jButtonNext.setEnabled(false);
				jButtonNovo.setEnabled(false);
				jButtonApagar.setEnabled(true);
				jButtonEditar.setEnabled(false);
				jButtonSalvar.setEnabled(true);
				
				jCheckBox.setEnabled(true);
				jTextFieldSlaveName.setEditable(true);
				//jTextFieldLookAhead.setEditable(true);
				//jTextFieldNomeMaquina.setEditable(true);
				jTextFieldValorSemente.setEditable(true);
				
				
				jTextFieldSlaveName.grabFocus();
				
				return;
			}
			
			if (novo)
			{
				
				jButtonAnt.setEnabled(false);
				jButtonNext.setEnabled(false);
				jButtonNovo.setEnabled(false);
				jButtonApagar.setEnabled(false);
				jButtonEditar.setEnabled(false);
				jButtonSalvar.setEnabled(true);
				
				jCheckBox.setEnabled(true);
				jTextFieldSlaveName.setEditable(true);
				//jTextFieldLookAhead.setEditable(true);
				//jTextFieldNomeMaquina.setEditable(true);
				jTextFieldValorSemente.setEditable(true);
				
				
				jTextFieldSlaveName.grabFocus();
				
				return;
			}
		}
		
		private void loadInfo(int i)
		{
			ProcessoLogicoParSMPL p = (ProcessoLogicoParSMPL)graph.getPLogicos().get(i);
			jTextFieldTid.setText(String.valueOf(p.getTid()));
			jTextFieldSlaveName.setText(p.getSlaveName());
			//jTextFieldLookAhead.setText(String.valueOf(p.getLookAhead()));
		    jCheckBox.setSelected(p.isProcessoPai());   
		    
		   // jTextFieldNomeMaquina.setText(p.getNomeMaquina());
		    
		    jTextFieldValorSemente.setText(String.valueOf(p.getValorSemente()));
		    	
		    //  cp = i;
			
		}


		/**
		 * This method initializes jTextFieldValorSemente	
		 * 	
		 * @return javax.swing.JTextField	
		 */
		private JTextField getJTextFieldValorSemente() {
			if (jTextFieldValorSemente == null) {
				jTextFieldValorSemente = new JTextField();
				jTextFieldValorSemente.setBounds(new Rectangle(149, 96, 56, 21));
			}
			return jTextFieldValorSemente;
		}

	


	

/*	public static void main (String args[])
	{
		FramePLogico app= new FramePLogico();
	}*/

}  //  @jve:decl-index=0:visual-constraint="10,10"
