package frames;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.sql.*;
import javax.swing.JLabel;
import javax.swing.JPasswordField;
import javax.swing.JButton;

import asda.UsuarioCadastro;

/**
 * Classe que conecta o ASDA ao banco de dados asda (MySQL) e verifica se 
 * o usu   rio     um usu   rio com permiss   es para usar a aplica      o. Se o usu   rio 
 * possui est    cadastrado o uso do ambiente     liberado conforme o tipo do usu   rio.
 * @author Thais Souza Aiza
 * @author Andr    Felipe Rodrigues
 * 			(diversas modifica      es, entre elas
 * 				cria      o do bot   o ajuda, do textfield para a senha do root MySQL,
 * 				abertura da janela de simula      o de acordo com o tipo de usu   rio,
 * 				entre outros)
 * @version 1.0
 */

public class FrameAsda extends JFrame {
  private JPanel contentPane;
  private BorderLayout borderLayout1 = new BorderLayout();
  private JPanel jPanel1 = new JPanel();
  private JLabel jLabel1 = new JLabel();
  private JLabel jLabel2 = new JLabel();
  private JLabel jLabel3 = new JLabel();
  private JTextField jTextField1 = new JTextField();
  private JPasswordField jPasswordField1 = new JPasswordField();
  private JButton jButton1 = new JButton();
  private JButton jButton2 = new JButton();
  private String url = "jdbc:mysql://localhost/asda";
  private Connection con;
  private FrameAberturaSuperUsuario fAberturaSuperUsuario;
  private FrameAberturaUsuarioSimulacao fAberturaUsuarioSimulacao;
  private FrameUsuario fCadastroSuperUsuario;
  //private FrameUsuario frameUsuario;
  private JLabel jLabel = null;
  private JPasswordField jPasswordField = null;
  private JButton jButtonAjuda = null;
  
  
/**
   *  Construtor do Frame
   */
  public FrameAsda() {
	enableEvents(AWTEvent.WINDOW_EVENT_MASK);
	
	try {
		Class.forName("org.gjt.mm.mysql.Driver");
	}
	catch(java.lang.ClassNotFoundException ex) {
		JOptionPane.showMessageDialog(null,"ClassNotFoundException:" + ex.getMessage() + 
				"\n\nProblemas ao tentar abir org.qjt.mm.mysql.Driver\n" +
				"Provavelmente deve ser algum problema com o MySQL Connector/J\n" +
				"Tente Reinstal   -lo","ClassNotFoundException",JOptionPane.ERROR_MESSAGE);
		System.err.print("ClassNotFoundException: ");
		System.err.println(ex.getMessage());
	}
	
	try {
		
	  jbInit();	  
	}
	catch(Exception e) {
	  e.printStackTrace();	  
	}
  }
  /**
   *  Inicializa      o dos componentes do frame
   */
  private void jbInit() throws Exception  {
	jLabel = new JLabel();
	jLabel.setBounds(new java.awt.Rectangle(33,122,111,24));
	jLabel.setToolTipText("Senha root do MySQL instalado em sua m   quina");
	jLabel.setText("Senha root MySQL");
	contentPane = (JPanel) this.getContentPane();
	contentPane.setLayout(borderLayout1);
	this.setLocale(java.util.Locale.getDefault());
	this.setContentPane(contentPane);
	this.setSize(new java.awt.Dimension(296,224));
	this.setResizable(false);
	this.setTitle("ASDA - Login");
	jPanel1.setLayout(null);
	jLabel1.setFont(new java.awt.Font("Dialog", 1, 12));
	jLabel1.setText("Entrada no Sistema");
	jLabel1.setBounds(new Rectangle(88, 19, 111, 16));
	jLabel2.setFont(new java.awt.Font("Dialog", 1, 12));
	jLabel2.setToolTipText("Usu   rio da Simula      o");
	jLabel2.setText("Usu   rio");
	jLabel2.setBounds(new Rectangle(33, 53, 47, 24));
	jLabel3.setBounds(new Rectangle(34, 87, 47, 24));
	jLabel3.setToolTipText("Senha do usu   rio da simula      o");
	jLabel3.setText("Senha");
	jLabel3.setFont(new java.awt.Font("Dialog", 1, 12));
	jTextField1.setText("");
	jTextField1.setBounds(new Rectangle(101, 53, 152, 22));
	jTextField1.addActionListener(new java.awt.event.ActionListener() {   
		public void actionPerformed(java.awt.event.ActionEvent e) {    
			jPasswordField1.grabFocus();
		}
	
	});
	jPasswordField1.setMaximumSize(new Dimension(8, 8));
	jPasswordField1.setMinimumSize(new Dimension(4, 8));
	jPasswordField1.setPreferredSize(new Dimension(8, 21));
	jPasswordField1.setText("");
	jPasswordField1.setBounds(new Rectangle(101, 85, 92, 22));
	jPasswordField1.addActionListener(new java.awt.event.ActionListener() {
		public void actionPerformed(java.awt.event.ActionEvent e) {
			jPasswordField.grabFocus();
		}
	});
	jButton1.setBounds(new java.awt.Rectangle(17,162,69,26));
	jButton1.setText("Entrar");
	jButton1.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
				okPerformed(e);
		}
	});
	
	
	
	jButton2.setText("Cancelar");
	jButton2.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
				cancelaPerformed(e);
		}
	});
	jButton2.setBounds(new java.awt.Rectangle(103,162,85,26));
	contentPane.add(jPanel1, BorderLayout.CENTER);
	jPanel1.add(jTextField1, null);
	jPanel1.add(jLabel1, null);
	jPanel1.add(jLabel2, null);
	jPanel1.add(jLabel3, null);
	jPanel1.add(jPasswordField1, null);
	jPanel1.add(jButton1, null);
	jPanel1.add(jButton2, null);

	jPanel1.add(jLabel, null);
	jPanel1.add(getJPasswordField(), null);
	jPanel1.add(getJButtonAjuda(), null);
  }

  /**
   * Fecha o Frame e sai do ambiente.
   */
  protected void processWindowEvent(WindowEvent e) {
	super.processWindowEvent(e);
	if (e.getID() == WindowEvent.WINDOW_CLOSING) {
	  System.exit(0);
	}
  }

  /**
   * Fecha o Frame e sai do ambiente.
   */
  public void cancelaPerformed(ActionEvent e) {
	   System.exit(0);
  }
 
  

  /**
   * Verifica se o usu   rio     um usu   rio cadastrado no ambiente e qual o tipo
   * do usu   rio.
   * @param e Indica em qual componente ocorreu o ato de teclar.
   */
  public void okPerformed(ActionEvent e) {
	  
	  /* Para obter a senha do root do MySQL */
	  char[] tempSenhaMySQL = jPasswordField.getPassword();
	  String senhaMySQL = new String(tempSenhaMySQL);
	  	 
	  /* obtendo conex   o com o banco de dados */
	  try {
		  		  
		  con = DriverManager.getConnection(url,"root", senhaMySQL);	
		  
		  System.out.println("Conex   o com o banco foi estabelecida!");
		  //con.close();
	  }	  
	  catch(SQLException exc) {
		  JOptionPane.showMessageDialog(null,
				"Problemas durante a conex   o com o banco de dados MySQL\n" +
		  		"Tente inicializar novamente o servidor de banco de dados\n" +
		  		"e verifique se a senha esta correta, ou ent   o, clique em ajuda\n" +
		  		"e tente resolver o problema","Falha na conex   o com o MySQL",JOptionPane.ERROR_MESSAGE);
		  
		  System.err.println("SQLException:  "  + exc.getMessage());
	  }
	  	  
	  String nome;
	  String tipoUsuario = "";
	  String senha;
	  
	  nome = jTextField1.getText();
	  char[] tempSenha = jPasswordField1.getPassword();
	  senha = new String(tempSenha);
	  
	  try 
	  {
	  
		  
		  Statement statement = con.createStatement();		  
		  String checkQuery = "SELECT * FROM usuario WHERE tipo='S'"; // checagem da exist   ncia de super usu   rios
		  ResultSet rs = statement.executeQuery(checkQuery);	
		  
		  if (rs.next())
		  {			  
			  String query = "SELECT * FROM usuario " +
			  					"WHERE nomeUsuario = '" +
			  					nome + "'";	// procura do usu   rio digitado
			  
			  rs = statement.executeQuery(query);		  
			  String senhaBanco="";			  
			  
			  int count = 0;
			  while (rs.next()) 
			  {
				  count++;
				  senhaBanco = rs.getString("senha");
				  System.out.println("senha do banco " + senhaBanco);			  
			  }
		  
		  
		  
			  if (count > 0 && senha.equals(senhaBanco)) 
			  {				  
				  rs.beforeFirst();
				  rs.next();
				  nome = rs.getString("nomeUsuario");		
				  tipoUsuario = rs.getString("tipo");
				  UsuarioCadastro user = new UsuarioCadastro(rs);
				  
				  //tipoUsuario = "1";		
				  if ( tipoUsuario.equals("S") )
				  {
				  
					  setVisible(false);
					  dispose();
					  
					  JFrame.setDefaultLookAndFeelDecorated(false);	
					  
					  fAberturaSuperUsuario = new FrameAberturaSuperUsuario(con, nome, user);
					  JFrameUtil.centraliza(fAberturaSuperUsuario);
					  //frameUsuario = new FrameUsuario(con,nome);
					  //Center the window			
					  fAberturaSuperUsuario.setVisible(true);
					  
					  
				  }
				  else 
				  {
					  if (tipoUsuario.equals("U"))
					  {
						  UsuarioCadastro userInfo = new UsuarioCadastro(rs);
						  setVisible(false);
						  dispose();
						  JFrame.setDefaultLookAndFeelDecorated(false);
						  fAberturaUsuarioSimulacao = new FrameAberturaUsuarioSimulacao(userInfo);
						  //Center the window			
						  JFrameUtil.centraliza(fAberturaUsuarioSimulacao);
						  fAberturaUsuarioSimulacao.setVisible(true);
						  
					  }
				  }
				  
			  }
			  else
			  {
				  Toolkit.getDefaultToolkit().beep();
				  JOptionPane.showMessageDialog(null,"Usu   rio e/ou senha inv   lida!","Erro",JOptionPane.ERROR_MESSAGE);
				  jTextField1.setText("");
				  jPasswordField1.setText("");
				  jTextField1.grabFocus();
			  }
		  }
		  else
		  {			  
			  setVisible(false);
			  dispose();
			  JFrame.setDefaultLookAndFeelDecorated(false);
			  fCadastroSuperUsuario = new FrameUsuario(con, nome, null);
			  //Center the window
			  JFrameUtil.centraliza(fCadastroSuperUsuario);
			  fCadastroSuperUsuario.setVisible(true);
		  }
	  }
	  catch (SQLException e1) {
			 
		  e1.printStackTrace();
	  }
		  
		  
  }
/**
 * This method initializes jPasswordField	
 * 	
 * @return javax.swing.JPasswordField	
 */
private JPasswordField getJPasswordField() {
	if (jPasswordField == null) {
		jPasswordField = new JPasswordField();
		jPasswordField.setLocation(new java.awt.Point(155,122));
		jPasswordField.setSize(new java.awt.Dimension(118,22));
		jPasswordField.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent e) {
				jButton1.grabFocus();
			}
		});
	}
	return jPasswordField;
}
/**
 * This method initializes jButtonAjuda	
 * 	
 * @return javax.swing.JButton	
 */
private JButton getJButtonAjuda() {
	if (jButtonAjuda == null) {
		jButtonAjuda = new JButton();
		jButtonAjuda.setBounds(new java.awt.Rectangle(205,161,66,26));
		jButtonAjuda.setText("Ajuda");
		jButtonAjuda.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent e) {
				
				String output = "Para entrar como super-usu   rio, apenas digite\n" +
						"o nome do usu   rio e a senha.\n" +
						"Para entrar como usu   rio de simula      o, digite o nome\n" +
						"do usu   rio e a senha cadastrada.\n" +
						"\nPara ambos os casos ser    necess   rio a senha root do MySQL\n" +
						"se n   o a tiver, obtenha com o admistrador do sistema.\n" +
						"\nPrimeiro acesso? Ent   o n   o h    necessidade de usu   rio e senha,\n" +
						"apenas digite a senha root do MySQL e a janela de cadastro de novos\n" +
						"usu   rios ser    aberta.";
				JOptionPane.showMessageDialog(null,output,"Ajuda",JOptionPane.INFORMATION_MESSAGE);
				
			/*	int opc = JOptionPane.showConfirmDialog(null,"Deseja recriar tentar criar o banco de dados" +
						" automaticamente?","Ajuda do ASDA",JOptionPane.YES_NO_CANCEL_OPTION);
				
				if (opc == JOptionPane.YES_OPTION)
				{
					try
					{
						String nurl = "jdbc:mysql://localhost/";
						String senha = JOptionPane.showInputDialog(null,"Digite a senha root MySQL");
						con = DriverManager.getConnection(nurl,"root",senha);
						Statement st = con.createStatement();
						String query = "CREATE DATABASE asda";
						con.close();
						st.close();
						con = DriverManager.getConnection(url,"root",senha);
						st = con.createStatement();
						query = "CREATE TABLE usuario " +
								"idUsuario int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT," +
								"nomeUsuario varchar(60) )";
						st.execute(query);
						
					}
					catch (SQLException sqlex)
					{
						sqlex.printStackTrace();
					}
				}
				*/
			}
		});
	}
	return jButtonAjuda;
}
	

}  //  @jve:decl-index=0:visual-constraint="10,10"



