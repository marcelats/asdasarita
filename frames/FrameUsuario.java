package frames;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.sql.*;
import java.util.*;
import javax.swing.JButton;

import asda.UsuarioCadastro;

/**
 * Classe que permite que o superUsuário insira, edite e exclua os usuários do 
 * ASDA.
 * @author Thais Souza Aiza
 * @author André Felipe Rodrigues - responsável pela total reformulação 
 * 			desse Frame, visto que funcionava muito mal	na primeira versão)
 * @version 1.0
 */

public class FrameUsuario extends JFrame {
	private JPanel contentPane;

	private JLabel statusBar = new JLabel();

	private BorderLayout borderLayout1 = new BorderLayout();

	private TitledBorder titledBorder1;

	private JPanel jPanel1 = new JPanel();

	private Icon proximo = new ImageIcon("imagens/Forward24.gif");

	private JButton jButtonProx = new JButton(proximo);

	private Icon inserir = new ImageIcon("imagens/Add24.gif");

	private JButton jButtonIns = new JButton(inserir);

	private Icon editar = new ImageIcon("imagens/Edit24.gif");

	private JButton jButtonEdit = new JButton(editar);

	private Icon apagar = new ImageIcon("imagens/Delete24.gif");

	private JButton jButtonApagar = new JButton(apagar);

	private Icon salvar = new ImageIcon("imagens/Save24.gif");

	private JButton jButtonSalvar = new JButton(salvar);

	private Icon ajuda = new ImageIcon("imagens/Help24.gif");

	private JButton jButtonHelp = new JButton(ajuda);

	private Icon cancelar = new ImageIcon("imagens/cancel.gif");

	private JButton jButtonCancelar = new JButton(cancelar);

	private Icon anterior = new ImageIcon("imagens/Back24.gif");

	private JButton jButtonAnt = new JButton(anterior);

	private JButton jButton8 = new JButton();

	private JLabel jLabel1 = new JLabel();

	private JLabel jLabel2 = new JLabel();

	private JLabel jLabel3 = new JLabel();

	private JLabel jLabel4 = new JLabel();

	private JLabel jLabel5 = new JLabel();

	private JLabel jLabel6 = new JLabel();

	private JLabel jLabel7 = new JLabel();

	private JLabel jLabel8 = new JLabel();

	private JLabel jLabel9 = new JLabel();

	private JTextField jTextFieldID = new JTextField();

	private JTextField jTextFieldNome = new JTextField();

	private JPasswordField jPasswordField1 = new JPasswordField();

	private String[] usuariosStrings = { "SuperUsuário", "Usuário de Simulaçao" }; // não precisa de String de controle - só S ou U

	private JComboBox jComboBoxTipoUsuario = new JComboBox(usuariosStrings);

	private String[] modelosStrings = { "Queuing Statecharts", "Redes de Filas" }; // por enquanto também não, só Q ou R

	private JComboBox jComboBoxTipoModelo = new JComboBox(modelosStrings);

	private String[] abordagensStrings = { "Seqüencial", "MRIP", "SRIP - CMB",
			"SRIP - TimeWarp", "SRIP - CMB/TW" };

	private String[] abordagensCodes = { "S", "M", "C", "T", "B" }; // código para abordagens
	private String[] tipoCodes = { "S" , "U" };
	private String[] tipoModeloCodes = { "Q" , "R" };

	private JComboBox jComboBoxAbordagem = new JComboBox(abordagensStrings);

	private String[] linguagensStrings = { "SMPL", "SMPLX", "ParSMPL", "SIMPACK", "SIMPACK2" };
	

	private JComboBox jComboBoxLinguagem = new JComboBox(linguagensStrings);

	private JTextField jTextFieldWarmUp = new JTextField();

	private JTextField jTextFieldLote = new JTextField();

	private JLabel jLabel10 = new JLabel();

	private JTextField jTextFieldPlataforma = new JTextField();

	private FrameAjuda fAjuda;

	private UsuarioCadastro userInfo;

	/**
	 * Usado como um auxiliar para a exibição apropriada dos dados
	 */
	private int idAnterior;

	/**
	 * Estabelece a conexão com o banco de dados.
	 */
	private Connection con;

	/**
	 * Usado para indicar se está ocorrendo uma edição ou inserção no banco de dados.
	 */
	private boolean isEdit = false;

	private JButton jButtonIniciar = null;
	
	private Janela j;
	
	private UsuarioCadastro user;

	//	private String stateForm[];

	/**
	 * Construtor do Frame.
	 *
	 */
	public FrameUsuario() {
		this(null,null,null);
	}

	public FrameUsuario(Connection connect, String nomeUS, UsuarioCadastro user) {
		enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		con = connect;
		this.user = user;
		try {
			jbInit();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void exibir(ResultSet rs, boolean senha) {
		try {
			jTextFieldID.setText(rs.getString(1));
			jTextFieldNome.setText(rs.getString(2));
			if (senha)
				jPasswordField1.setText(rs.getString(3));
			else
				jPasswordField1.setText("");

			if (rs.getString(4).equals("S"))
				jComboBoxTipoUsuario.setSelectedIndex(0);
			else
				jComboBoxTipoUsuario.setSelectedIndex(1);

			if (rs.getString(5).equals("Q"))
				jComboBoxTipoModelo.setSelectedIndex(0);
			else
				jComboBoxTipoModelo.setSelectedIndex(1);

			if (rs.getString(6).equals("S"))
				jComboBoxAbordagem.setSelectedIndex(0);
			else if (rs.getString(6).equals("M"))
				jComboBoxAbordagem.setSelectedIndex(1);
			else if (rs.getString(6).equals("C"))
				jComboBoxAbordagem.setSelectedIndex(2);
			else if (rs.getString(6).equals("T"))
				jComboBoxAbordagem.setSelectedIndex(3);
			else if (rs.getString(6).equals("B"))
				jComboBoxAbordagem.setSelectedIndex(4);

			jComboBoxLinguagem.setSelectedItem(rs.getString(7));
			jTextFieldLote.setText(rs.getString(8));
			jTextFieldWarmUp.setText(rs.getString(9));
			jTextFieldPlataforma.setText(rs.getString(10));
		} catch (SQLException sqlex) {
			JOptionPane.showMessageDialog(null,
					"Não foi possível obter as informações do banco de dados",
					"Erro", JOptionPane.ERROR_MESSAGE);
			sqlex.printStackTrace();
		}

	}

	/**
	 * Inicialização dos Componentes. 
	 */
	private void jbInit() throws Exception {
		contentPane = (JPanel) this.getContentPane();
		titledBorder1 = new TitledBorder("");
		contentPane.setLayout(borderLayout1);
		this.setSize(new Dimension(527, 339));
		this.setTitle("ASDA - SuperUsuário");
		this.setResizable(false);
		statusBar.setFont(new java.awt.Font("Dialog", 1, 12));
		statusBar.setBorder(BorderFactory.createEtchedBorder());
		statusBar
				.setText(" ASDA - Ambiente de Simulação Distribuída Automático");
		jPanel1.setLayout(null);
		jPanel1.setBorder(BorderFactory.createLoweredBevelBorder());
		jButtonProx.setToolTipText("Próximo usuário");
		jButtonProx.setBounds(new Rectangle(87, 5, 54, 34));

		jButtonAnt.setToolTipText("Usuário anterior");

		jButtonIns.setToolTipText("Inserir");
		jButtonIns.setBounds(new Rectangle(147, 5, 54, 34));
		jButtonEdit.setBounds(new Rectangle(206, 5, 54, 34));
		jButtonIns.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				inserePerformed(e);
			}
		});

		jButtonEdit.setToolTipText("Editar");
		jButtonEdit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				editaPerformed(e);
			}
		});

		jButtonApagar.setToolTipText("Apagar");
		jButtonApagar.setBounds(new Rectangle(266, 5, 54, 34));
		jButtonApagar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				deletePerformed(e);
			}
		});

		//Botão que salva o novo registro/alterações na tabela "usuario"
		jButtonSalvar.setBounds(new Rectangle(325, 5, 54, 34));
		jButtonSalvar.setToolTipText("Salvar");
		jButtonSalvar.setEnabled(false);
		jButtonSalvar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				salvaPerformed(e);
			}
		});

		jButtonHelp.setToolTipText("Ajuda");
		jButtonHelp.setBounds(new Rectangle(444, 5, 54, 34));
		jLabel1.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel1.setText("Id Usuário");
		jLabel1.setBounds(new java.awt.Rectangle(13, 60, 65, 21));
		jLabel2.setBounds(new java.awt.Rectangle(167, 60, 84, 21));
		jLabel2.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel2.setToolTipText("");
		jLabel2.setText("Nome Usuário");
		jLabel3.setBounds(new Rectangle(13, 99, 43, 21));
		jLabel3.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel3.setText("Senha");
		jLabel4.setBounds(new Rectangle(167, 99, 76, 21));
		jLabel4.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel4.setText("Tipo Usuário");
		jLabel5.setBounds(new Rectangle(13, 138, 76, 21));
		jLabel5.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel5.setText("Tipo Modelo");
		jLabel6.setBounds(new Rectangle(258, 138, 76, 21));
		jLabel6.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel6.setText("Abordagem");
		jLabel7.setBounds(new Rectangle(13, 178, 76, 21));
		jLabel7.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel7.setText("Linguagem");
		jLabel8.setBounds(new Rectangle(258, 178, 118, 21));
		jLabel8.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel8.setText("Tamanho Warm-Up");
		jLabel9.setBounds(new java.awt.Rectangle(13, 218, 86, 21));
		jLabel9.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel9.setText("Tamanho Lote");

		Statement statement = con.createStatement();
		String query = "SELECT * FROM usuario ";
		ResultSet rs = statement.executeQuery(query);
		//statement.close();
		if (rs.next()) {
			exibir(rs, false);
		} else {
			JOptionPane.showMessageDialog(null,
					"Não existem usuários cadastrados - é necessário \n"
							+ "cadastrar o primeiro super usuário! ",
					"Atenção", JOptionPane.INFORMATION_MESSAGE);
			jButtonAnt.setEnabled(false);
			jButtonProx.setEnabled(false);
			jButtonEdit.setEnabled(false);
			jButtonCancelar.setEnabled(false);
			jButtonApagar.setEnabled(false);

		}

		jTextFieldID.setBounds(new Rectangle(81, 59, 74, 23));
		jTextFieldID.setEditable(false);
		jTextFieldNome.setBounds(new Rectangle(259, 59, 244, 23));

		jTextFieldNome.setEditable(false);

		jPasswordField1.setText("");
		jPasswordField1.setBounds(new Rectangle(59, 98, 96, 23));
		jPasswordField1.setEditable(false);
		jComboBoxTipoUsuario.setBounds(new Rectangle(260, 99, 153, 24));
		jComboBoxTipoUsuario.setEditable(false);

		jComboBoxTipoModelo.setBounds(new Rectangle(91, 136, 153, 24));
		jComboBoxTipoModelo.setEditable(false);

		jComboBoxAbordagem.setBounds(new Rectangle(334, 136, 153, 24));
		jComboBoxAbordagem.setEditable(false);

		jComboBoxLinguagem.setBounds(new Rectangle(91, 176, 153, 24));
		jComboBoxLinguagem.setEditable(false);

		jTextFieldWarmUp.setBounds(new Rectangle(378, 177, 74, 23));

		jTextFieldWarmUp.setEditable(false);

		jTextFieldLote.setBounds(new Rectangle(103, 217, 74, 23));
		jTextFieldLote.setEditable(false);
		jButtonCancelar.setBounds(new Rectangle(384, 5, 54, 34));
		jButtonCancelar.setToolTipText("Cancelar");
		jButtonCancelar.setEnabled(false);
		jButtonCancelar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cancelarPerformed(e);
			}
		});
		jButton8.setBounds(new java.awt.Rectangle(414, 250, 89, 28));
		jButton8.setFont(new java.awt.Font("Dialog", 1, 12));
		jButton8.setToolTipText("Sair do sistema de cadastro de usuários");
		jButton8.setText("Sair");
		jButton8.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				sairPerformed(e);

			}
		});
		jLabel10.setText("Plataforma");
		jLabel10.setFont(new java.awt.Font("Dialog", 1, 12));
		jLabel10.setBounds(new java.awt.Rectangle(215, 218, 69, 21));
		jTextFieldPlataforma.setBounds(new Rectangle(291, 217, 110, 23));
		jTextFieldPlataforma.setEditable(false);

		jButtonAnt.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				anteriorPerformed(e);
			}
		});

		jButtonProx.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				proximoPerformed(e);
			}
		});

		jButtonAnt.setBounds(new Rectangle(27, 5, 54, 34));

		jButtonHelp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ajudaPerformed(e);
			}
		});
		contentPane.add(jPanel1, BorderLayout.CENTER);
		jPanel1.add(jLabel1, null);
		jPanel1.add(jTextFieldID, null);
		jPanel1.add(jLabel2, null);
		jPanel1.add(jTextFieldNome, null);

		jPanel1.add(jLabel3, null);
		jPanel1.add(jPasswordField1, null);
		jPanel1.add(jLabel4, null);
		jPanel1.add(jComboBoxTipoUsuario, null);
		jPanel1.add(jComboBoxTipoModelo, null);
		jPanel1.add(jLabel6, null);
		jPanel1.add(jComboBoxAbordagem, null);
		jPanel1.add(jLabel5, null);
		jPanel1.add(jLabel7, null);
		jPanel1.add(jLabel8, null);
		jPanel1.add(jTextFieldWarmUp, null);
		jPanel1.add(jComboBoxLinguagem, null);
		jPanel1.add(jLabel9, null);
		jPanel1.add(jLabel10, null);
		jPanel1.add(jTextFieldPlataforma, null);
		jPanel1.add(jTextFieldLote, null);
		jPanel1.add(jButton8, null);
		jPanel1.add(jButtonEdit, null);
		jPanel1.add(jButtonApagar, null);
		jPanel1.add(jButtonSalvar, null);
		jPanel1.add(jButtonCancelar, null);
		jPanel1.add(jButtonHelp, null);
		jPanel1.add(jButtonProx, null);
		jPanel1.add(jButtonIns, null);
		jPanel1.add(jButtonAnt, null);
		jPanel1.add(getJButtonIniciar(), null);
		contentPane.add(statusBar, BorderLayout.SOUTH);

		this.setContentPane(contentPane);

		statement.close();
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

	private UsuarioCadastro saveStateForm() {
		UsuarioCadastro user = new UsuarioCadastro();

		try
		{
			user.setId(Integer.parseInt(jTextFieldID.getText()));
			user.setNome(jTextFieldNome.getText());
			user.setPassword(new String((jPasswordField1.getPassword())));
			user.setTipoUsuario((String) jComboBoxTipoUsuario.getSelectedItem());
			user.setTipoModelo((String) (jComboBoxTipoModelo.getSelectedItem()));
			user.setAbordagem((String) (jComboBoxAbordagem.getSelectedItem()));
			user.setLinguagem((String) (jComboBoxLinguagem.getSelectedItem()));
			user.setLote(Integer.parseInt(jTextFieldLote.getText()));
			user.setWarmup(Integer.parseInt(jTextFieldWarmUp.getText()));
			user.setPlataforma(jTextFieldPlataforma.getText());
			return user;
		}
		catch (Exception e)
		{
			e.printStackTrace();
			return null;
		}
			
		/*stateForm = new String[10];
		 stateForm[0] = (jTextFieldID.getText());
		 stateForm[1] = (jTextFieldNome.getText());
		 stateForm[2] = new String((jPasswordField1.getPassword()));
		 stateForm[3] = (String)(jComboBoxTipoUsuario.getSelectedItem());
		 stateForm[4] = (String)(jComboBoxTipoModelo.getSelectedItem());
		 stateForm[5] = (String)(jComboBoxAbordagem.getSelectedItem());
		 stateForm[6] = (String)(jComboBoxLinguagem.getSelectedItem());
		 stateForm[7] = (jTextFieldLote.getText());
		 stateForm[8] = (jTextFieldWarmUp.getText());
		 stateForm[9] = (jTextFieldPlataforma.getText()); */

	}

	private void loadStateForm() {

		if (userInfo != null) {
			jTextFieldID.setText(String.valueOf(userInfo.getId()));
			jTextFieldNome.setText(userInfo.getNome());
			// jPasswordField1.setText(userInfo.getPassword());
			jComboBoxTipoUsuario.setSelectedItem(userInfo.getTipoUsuario());
			jComboBoxTipoModelo.setSelectedItem(userInfo.getTipoModelo());
			jComboBoxAbordagem.setSelectedItem(userInfo.getAbordagem());
			jComboBoxLinguagem.setSelectedItem(userInfo.getLinguagem());
			jTextFieldLote.setText(String.valueOf(userInfo.getLote()));
			jTextFieldWarmUp.setText(String.valueOf(userInfo.getWarmup()));
			jTextFieldPlataforma.setText(userInfo.getPlataforma());
		}
		/*  jTextFieldID.setText((String)stateForm[0]);
		 jTextFieldNome.setText((String)stateForm[1]);
		 //jPasswordField1.setText((String)stateForm[2]);
		 jComboBoxTipoUsuario.setSelectedItem(stateForm[3]);
		 jComboBoxTipoModelo.setSelectedItem(stateForm[4]);
		 jComboBoxAbordagem.setSelectedItem(stateForm[5]);
		 jComboBoxLinguagem.setSelectedItem(stateForm[6]);
		 jTextFieldLote.setText(stateForm[7]);
		 jTextFieldWarmUp.setText(stateForm[8]);
		 jTextFieldPlataforma.setText(stateForm[9]);*/

		arrumarBotoes();
		camposSetEditable(false);
		jPasswordField1.setText("");
	}

	private void arrumarBotoes() {
		jButtonAnt.setEnabled(true);
		jButtonProx.setEnabled(true);
		jButtonIns.setEnabled(true);
		jButtonEdit.setEnabled(true);
		jButtonApagar.setEnabled(true);
		jButtonSalvar.setEnabled(false);
		jButtonCancelar.setEnabled(false);
	}

	private void camposSetEditable(boolean valor) {

		jTextFieldNome.setEditable(valor);
		jTextFieldWarmUp.setEditable(valor);
		jTextFieldLote.setEditable(valor);
		jTextFieldPlataforma.setEditable(valor);
		jPasswordField1.setEditable(valor);
		jComboBoxTipoUsuario.setEditable(valor);
		jComboBoxTipoModelo.setEditable(valor);
		jComboBoxAbordagem.setEditable(valor);
		jComboBoxLinguagem.setEditable(valor);

	}

	private void ajudaPerformed(ActionEvent e) {
		fAjuda = new FrameAjuda();
		fAjuda.setVisible(true);
	}

	/**
	 * Fecha o Frame e sai do ambiente. 
	 */
	private void sairPerformed(ActionEvent e) {
		System.exit(0);
	}

	/**
	 * Método que edita as informações dos usuários na tabela <code>usuario</code>.
	 * @param e Indica em qual componente ocorreu o ato de teclar.
	 */
	private void editaPerformed(ActionEvent e) {

		userInfo = saveStateForm();
		isEdit = true;
		statusBar
				.setText(" ASDA - Ambiente de Simulação Distribuída Automático                        Editando Usuário");
		jTextFieldNome.grabFocus();
		jTextFieldID.setEditable(false); // como é edição - o id não muda
		jTextFieldNome.setEditable(true);
		jTextFieldWarmUp.setEditable(true);
		jTextFieldLote.setEditable(true);
		jTextFieldPlataforma.setEditable(true);
		jPasswordField1.setEditable(true);
		jComboBoxTipoUsuario.setEditable(true);
		jComboBoxTipoModelo.setEditable(true);
		jComboBoxAbordagem.setEditable(true);
		jComboBoxLinguagem.setEditable(true);

		try {
			Statement st = con.createStatement();
			String query = "SELECT * FROM usuario " + "WHERE idUsuario = '"
					+ jTextFieldID.getText() + "'";
			ResultSet rs = st.executeQuery(query);
			rs.next();
			exibir(rs, true);
		} catch (SQLException sqlex) {
			JOptionPane.showMessageDialog(null,
					"Problema na obtenção de senha do banco da dados\n"
							+ "Por favor, digite uma nova senha",
					"Erro na obtenção da senha", JOptionPane.ERROR_MESSAGE);
			jPasswordField1.setText("");
			sqlex.printStackTrace();
		}

		jButtonAnt.setEnabled(false);
		jButtonProx.setEnabled(false);
		jButtonIns.setEnabled(false);
		jButtonEdit.setEnabled(false);
		jButtonApagar.setEnabled(false);
		jButtonSalvar.setEnabled(true);
		jButtonCancelar.setEnabled(true);

	}

	/**
	 * Método que move uma posição a frente na tabela <code>usuario</code>.
	 * @param e Indica em qual componente ocorreu o ato de teclar.
	 */
	private void proximoPerformed(ActionEvent e) {

		try {

			Statement statement = con.createStatement();
			String query = "SELECT * FROM usuario " + "WHERE idUsuario > "
					+ jTextFieldID.getText() + " ORDER BY idUsuario LIMIT 1;";
			ResultSet rs = statement.executeQuery(query);

			if (rs.next()) {
				exibir(rs, false);
			}

			statement.close();
		} catch (SQLException sqlex) {
			System.out.println(sqlex);
		}
	}

	/**
	 * Método que recua uma posição na tabela <code>usuario</code>.
	 * @param e Indica em qual componente ocorreu o ato de teclar.
	 * 
	 * :-( mas não está recuando apenas uma, está recuando para o inicio da tabela ARRUMAR
	 * 
	 */
	private void anteriorPerformed(ActionEvent e) {

		try {
			Statement statement = con.createStatement();
			String query = "SELECT * FROM usuario " + "WHERE idUsuario < "
					+ jTextFieldID.getText()
					+ " ORDER BY idUsuario DESC LIMIT 1";
			ResultSet rs = statement.executeQuery(query);

			if (rs.next()) {
				exibir(rs, false);
			}
			statement.close();
		} catch (SQLException sqlex) {
			System.out.println(sqlex);
		}

	}

	/**
	 * Método que insere um novo usuário na tabela <code>usuario</code>.
	 * @param e Indica em qual componente ocorreu o ato de teclar. 
	 */
	private void inserePerformed(ActionEvent e) {
		isEdit = false;

		userInfo = saveStateForm();

		statusBar
				.setText(" ASDA - Ambiente de Simulação Distribuída Automático                        Inserindo Usuário");
		jTextFieldNome.grabFocus();
		jTextFieldID.setEditable(false);
		try {
			idAnterior = Integer.parseInt(jTextFieldID.getText());
		} catch (NumberFormatException ne) {
			idAnterior = 1; // ou zero?
		}

		jTextFieldID.setText("");
		jTextFieldNome.setEditable(true);
		jTextFieldNome.setText("");
		jTextFieldWarmUp.setEditable(true);
		jTextFieldWarmUp.setText("");
		jTextFieldLote.setEditable(true);
		jTextFieldLote.setText("");
		jTextFieldPlataforma.setEditable(true);
		jTextFieldPlataforma.setText("");
		jPasswordField1.setEditable(true);
		jComboBoxTipoUsuario.setEditable(true);
		jComboBoxTipoModelo.setEditable(true);
		jComboBoxAbordagem.setEditable(true);
		jComboBoxLinguagem.setEditable(true);

		jButtonAnt.setEnabled(false);
		jButtonProx.setEnabled(false);
		jButtonIns.setEnabled(false);
		jButtonEdit.setEnabled(false);
		jButtonApagar.setEnabled(false);
		jButtonSalvar.setEnabled(true);
		jButtonCancelar.setEnabled(true);
	}

	/**
	 * Método que remove um usuário da tabela <code>usuario</code>.
	 * @param e Indica em qual componente ocorreu o ato de teclar.
	 */
	private void deletePerformed(ActionEvent e) {

		try {

			Statement statement = con.createStatement();

			if (!jTextFieldID.getText().equals("")
					&& !jTextFieldNome.getText().equals("")
					&& !jPasswordField1.getPassword().equals("")) {

				int n = JOptionPane.showConfirmDialog(null,
						"Deseja excluir o usuário?", "ASDA",
						JOptionPane.YES_NO_OPTION);

				if (n == JOptionPane.YES_OPTION) {
					String query = "DELETE FROM usuario WHERE idUsuario = "
							+ jTextFieldID.getText();

					statement.executeUpdate(query);

					anteriorPerformed(e);
					proximoPerformed(e);
					anteriorPerformed(e);

				}
			}

		} catch (SQLException sqlex) {
			System.out.println(sqlex);
		}

	}

	/**
	 * Método que cancela a inserção de um novo usuário ou a edição de um já existente
	 * @param e Indica em qual componente ocorreu o ato de teclar.
	 * 
	 */
	private void cancelarPerformed(ActionEvent e) {
		loadStateForm();

	}

	/**
	 * Método que salva as alterações na tabela <code>usuario</code>.
	 * @param e Indica em qual componente ocorreu o ato de teclar.
	 */
	private void salvaPerformed(ActionEvent e) {
		
		jButtonProx.grabFocus();
		
		statusBar
		.setText(" ASDA - Ambiente de Simulação Distribuída Automático");
		
		try {
			Statement statement = con.createStatement();
			
			if (!jTextFieldNome.getText().equals("")) // pode cadastrar usuários com senhas vazias
			{
				char[] tempSenha = jPasswordField1.getPassword();
				
				String senha = new String(tempSenha);
				
				String query = "SELECT * FROM usuario WHERE nomeUsuario = '"
					+ jTextFieldNome.getText() + "'";
				ResultSet rs = statement.executeQuery(query);
				if (!rs.next()) // não tem usuário com o nome cadastrado
				{
					if (!isEdit) 
					{
						query = "INSERT INTO usuario ("
							+ "nomeUsuario, senha, tipo, tipoModelo, "
							+ "abordagem, linguagem, tamanhoLote, tamWarmUp, plataformaUsuario"
							+ ") VALUES ('"
							+ jTextFieldNome.getText()
							+ "', '"
							+ senha
							+ "', '"
							+ tipoCodes[jComboBoxTipoUsuario.getSelectedIndex()]
							            + "', '"
							            + tipoModeloCodes[jComboBoxTipoModelo.getSelectedIndex()]
							                              + "', '"
							                              + abordagensCodes[jComboBoxAbordagem.getSelectedIndex()] 
							                                                + "', '"
							                                                + jComboBoxLinguagem.getSelectedItem() + "', '"
							                                                + jTextFieldLote.getText() + "', '"
							                                                + jTextFieldWarmUp.getText() + "', '"
							                                                + jTextFieldPlataforma.getText() + "')";
						int result = statement.executeUpdate(query);
						
						if (result == 1) {
							camposSetEditable(false);
							arrumarBotoes();
							jPasswordField1.setText("");
							
							query = "SELECT * FROM usuario WHERE nomeUsuario = '"
								+ jTextFieldNome.getText() + "'";
							rs = statement.executeQuery(query);
							rs.next();
							exibir(rs, false);
							
							jButtonProx.grabFocus();
							statusBar
							.setText(" ASDA - Ambiente de Simulação Distribuída Automático");
							JOptionPane.showMessageDialog(null,
									"Usuário inserido com sucesso!",
									"Inserção de usuário",
									JOptionPane.INFORMATION_MESSAGE);
						} else {
							JOptionPane.showMessageDialog(null,
									"Inserção Fracassou! Tente novamente",
									"ASDA - Erro", JOptionPane.ERROR_MESSAGE);
							jButtonIns.grabFocus();
							
							camposSetEditable(true);
						}
						
					}
					else
					{
						if (isEdit)
						{
							char[] aux = jPasswordField1.getPassword();
							String senhaAux = new String(aux);
							query = "UPDATE IGNORE usuario SET "
								+ "nomeUsuario = '" + jTextFieldNome.getText()
								+ "', "
								+ "senha = '" + senhaAux
								+ "', "
								+ "tipo = '" + tipoCodes[jComboBoxTipoUsuario.getSelectedIndex()]
								+ "', "
								+ "tipoModelo = '" + tipoModeloCodes[jComboBoxTipoModelo.getSelectedIndex()]
								+ "', "
								+ "abordagem = '" + abordagensCodes[jComboBoxAbordagem.getSelectedIndex()] 
								+ "', "
								+ "linguagem = '" + jComboBoxLinguagem.getSelectedItem()
							    + "', "
								+ "tamanhoLote = '" + jTextFieldLote.getText()
								+ "', " 
								+ "tamWarmUp = '" + jTextFieldWarmUp.getText() 
								+ "', "
								+ "plataformaUsuario = '" + jTextFieldPlataforma.getText()
								+ "' " 
								+ "WHERE idUsuario = " + jTextFieldID.getText();
							
							int result = statement.executeUpdate(query);
							
							if (result == 1) {
								jButtonProx.grabFocus();
								camposSetEditable(false);
								arrumarBotoes();
								
								query = "SELECT * FROM usuario WHERE nomeUsuario = '"
									+ jTextFieldNome.getText() + "'";
								rs = statement.executeQuery(query);
								rs.next();
								exibir(rs, false);
								
								statusBar
								.setText(" ASDA - Ambiente de Simulação Distribuída Automático");
							} else {
								JOptionPane.showMessageDialog(null,
										"Edição Fracassou! Tente novamente",
										"ASDA - Erro", JOptionPane.ERROR_MESSAGE);
								jButtonIns.grabFocus();
								camposSetEditable(true);
							}
						}
						else
							JOptionPane
							.showMessageDialog(
									null,
									"Usuário já existente - Inserção não permitida!",
									"Usuário Duplicado",
									JOptionPane.INFORMATION_MESSAGE);
					}
				}
				else 
				{	if (isEdit)
					{
						char[] aux = jPasswordField1.getPassword();
						String senhaAux = new String(aux);
						query = "UPDATE IGNORE usuario SET "
							+ "nomeUsuario = '" + jTextFieldNome.getText()
							+ "', "
							+ "senha = '" + senhaAux
							+ "', "
							+ "tipo = '" + tipoCodes[jComboBoxTipoUsuario.getSelectedIndex()]
							+ "', "
							+ "tipoModelo = '" + tipoModeloCodes[jComboBoxTipoModelo.getSelectedIndex()]
							+ "', "
							+ "abordagem = '" + abordagensCodes[jComboBoxAbordagem.getSelectedIndex()] 
							+ "', "
							+ "linguagem = '" + jComboBoxLinguagem.getSelectedItem()
						    + "', "
							+ "tamanhoLote = '" + jTextFieldLote.getText()
							+ "', " 
							+ "tamWarmUp = '" + jTextFieldWarmUp.getText() 
							+ "', "
							+ "plataformaUsuario = '" + jTextFieldPlataforma.getText()
							+ "' " 
							+ "WHERE idUsuario = " + jTextFieldID.getText();
						
						int result = statement.executeUpdate(query);
						
						if (result == 1) {
							jButtonProx.grabFocus();
							camposSetEditable(false);
							arrumarBotoes();
							
							query = "SELECT * FROM usuario WHERE nomeUsuario = '"
								+ jTextFieldNome.getText() + "'";
							rs = statement.executeQuery(query);
							rs.next();
							exibir(rs, false);
							
							statusBar
							.setText(" ASDA - Ambiente de Simulação Distribuída Automático");
						} else {
							JOptionPane.showMessageDialog(null,
									"Edição Fracassou! Tente novamente",
									"ASDA - Erro", JOptionPane.ERROR_MESSAGE);
							jButtonIns.grabFocus();
							camposSetEditable(true);
						}
					}
					else
						JOptionPane
						.showMessageDialog(
								null,
								"Usuário já existente - Inserção não permitida!",
								"Usuário Duplicado",
								JOptionPane.INFORMATION_MESSAGE);
					
				}
			}
			else {
				JOptionPane.showConfirmDialog(null,
						"Campo Nome do Usuário não pode ser vazio!",
						"Nome não digitado", JOptionPane.INFORMATION_MESSAGE);
			}
			
			statement.close();
		} catch (SQLException sqlex) {
			sqlex.printStackTrace();
			if (!isEdit) {
				JOptionPane.showMessageDialog(null,
						"Problemas na inserção - Tente novamente",
						"ASDA - Erro", JOptionPane.ERROR_MESSAGE);
				statusBar.setText(" ASDA - Ambiente de Simulação Distribuída Automático"
						+ "                       Inserção Fracassou!!!");
				camposSetEditable(true);
			}
			JOptionPane.showMessageDialog(null,
					"IdUsuário Duplicado ou campos inválidos!\n"
					+ "Tente Novamente", "ASDA - Erro",
					JOptionPane.ERROR_MESSAGE);
			jButtonIns.grabFocus();
		}
	}

	/**
	 * This method initializes jButtonIniciar	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButtonIniciar() {
		if (jButtonIniciar == null) {
			jButtonIniciar = new JButton();
			jButtonIniciar.setBounds(new java.awt.Rectangle(316, 250, 85, 28));
			jButtonIniciar.setToolTipText("Iniciar Ambiente de Simulação");
			jButtonIniciar.setText("Iniciar");
			jButtonIniciar.addActionListener(new java.awt.event.ActionListener() {
						public void actionPerformed(java.awt.event.ActionEvent e) {
							//userInfo = saveStateForm();
							if (user==null)
							{
								JOptionPane.showMessageDialog(null,
										"Problema com a primeira entrada",
										"Reentre no ASDA e tente esse botão novamente",
										JOptionPane.ERROR_MESSAGE);
								jButtonIniciar.setEnabled(false);
							}
							else if (user.getTipoModelo().equals("R"))
								j = new JanelaRedes(user);
							else if (user.getTipoModelo().equals("Q"))
								j = new JanelaQueuingStateCharts(user);
							else
								JOptionPane.showMessageDialog(
										null,
										"Não foi possível iniciar a janela de modelagem!",
										"ASDA - Erro",
										JOptionPane.ERROR_MESSAGE);
							
							setVisible(false);
							dispose();
						}
					});
		}
		return jButtonIniciar;
	}

}
