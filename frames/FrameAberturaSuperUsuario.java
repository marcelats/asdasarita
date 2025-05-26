package frames;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import asda.UsuarioCadastro;

import java.sql.*;


/**
 * Classe que exibe uma mensagem de saudação ao superusuário dizendo as permissões que ele 
 * tem no ambiente. 
 * @author Thais Souza Aiza
 * @author André Felipe Rodrigues (adição da passagem das informações de CadastroUsuario)
 * @version 1.0
 */
public class FrameAberturaSuperUsuario extends JFrame {

    private JPanel               contentPane;
    private JPanel               jPanel1       = new JPanel();
    private JLabel               jLabel1       = new JLabel();
    private JLabel               jLabel2       = new JLabel();
    private JLabel               jLabel3       = new JLabel();
    private JTextPane            jTextPane1    = new JTextPane();
    private JTextPane            jTextPane2    = new JTextPane();
    private JLabel               jLabel4       = new JLabel();
    private JLabel               jLabel5       = new JLabel();
    private JLabel               jLabel6       = new JLabel();
    private Icon                 logo = new ImageIcon("imagens/logo_lasdpc.jpg");
    private BorderLayout         borderLayout1 = new BorderLayout();
    private JButton              jButton1      = new JButton();
    
    private Connection connection;
    private String nome;
    private UsuarioCadastro user;
    
    /**
     * Frame que permite ao superusuário adicionar novos usuários e alterar as 
     * informaçoes de usuários já cadastrados. 
     */
    private FrameUsuario frameUsuario;
    
    // public FrameEscolhaSuperUsuario frameEscolhaSuperUsuario;

    /**
     * Construtor da classe.
     */
    public FrameAberturaSuperUsuario() {}

    /**
     * Construtor da classe.
     * @param con Conexão com o banco de dados asda - MySQL.
     * @param nome Nome do usuário que está conectado com o banco de dados.
     */
    public FrameAberturaSuperUsuario(Connection con, String nome, UsuarioCadastro user) {

        enableEvents(AWTEvent.WINDOW_EVENT_MASK);
        this.user = user;

        try {
			//frameEscolhaSuperUsuario = new FrameEscolhaSuperUsuario();
            
        	connection = con;
        	this.nome = nome;

            jbInit();
            jLabel3.setText("Seja bem-vindo ao ASDA, " + nome + "!");
            jButton1.grabFocus();
           
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Inicializa os componentes do Frame.     
     */
    private void jbInit() throws Exception {

        contentPane = (JPanel) this.getContentPane();

        jPanel1.setBackground(
            UIManager.getColor("InternalFrame.activeTitleGradient"));
        contentPane.setLayout(borderLayout1);
        this.getContentPane().setBackground(
            UIManager.getColor("InternalFrame.activeTitleGradient"));
        this.setDefaultCloseOperation(HIDE_ON_CLOSE);
        this.setContentPane(contentPane);
        this.setForeground(Color.black);
        this.setResizable(false);
        this.setSize(new Dimension(415, 340));
        this.setTitle("Bem-vindo SuperUsuário");
        jPanel1.setLayout(null);
        jPanel1.setBackground(
            UIManager.getColor("InternalFrame.activeTitleGradient"));
        jPanel1.setBorder(BorderFactory.createLoweredBevelBorder());
        jLabel1.setFont(new java.awt.Font("Dialog", 1, 12));
        jLabel1.setText(
            "ASDA - Ambiente de Simulaçao Distribuída Automático");
        jLabel1.setBounds(new Rectangle(11, 10, 312, 20));
        jLabel2.setText("");
        jLabel2.setIcon(logo);
        jLabel2.setBounds(new Rectangle(10, 42, 110, 105));
        jLabel3.setFont(new java.awt.Font("Dialog", 1, 12));
        jLabel3.setBounds(new Rectangle(136, 62, 252, 25));
        jTextPane1.setBackground(
            UIManager.getColor("InternalFrame.activeTitleGradient"));
        jTextPane1.setToolTipText("");
        jTextPane1.setEditable(false);
        jTextPane1.setText(
            "Voce tem permissao para alterar as variáveis do ASDA, bem como as "
            + "variáveis dos módulos avaliador, escalonamento e replicador.");
        jTextPane1.setBounds(new Rectangle(136, 90, 259, 71));
        jTextPane2.setBounds(new Rectangle(136, 162, 258, 71));
        jTextPane2.setText(
            "Tem permissão tambem para adicionar novos usuários e alterar as informaçoes "
            + "de usuários já cadastrados.");
        jTextPane2.setToolTipText("");
        jTextPane2.setEditable(false);
        jTextPane2.setBackground(
            UIManager.getColor("InternalFrame.activeTitleGradient"));
        jLabel4.setEnabled(true);
        jLabel4.setFont(new java.awt.Font("Dialog", 1, 12));
        jLabel4.setText("LASDPC");
        jLabel4.setBounds(new Rectangle(10, 215, 87, 24));
        jLabel5.setBounds(new Rectangle(10, 233, 374, 24));
        jLabel5.setText(
            "Laboratório de Sistemas Distribuídos e Programação Concorrente");
        jLabel5.setFont(new java.awt.Font("Dialog", 1, 11));
        jLabel5.setEnabled(true);
        jLabel6.setFont(new java.awt.Font("Dialog", 2, 11));
        jLabel6.setText("Versao 1.0");
        jLabel6.setBounds(new Rectangle(261, 30, 62, 19));
        contentPane.setBorder(BorderFactory.createEtchedBorder());
        jButton1.setBounds(new Rectangle(155, 264, 95, 29));
        jButton1.setText("Entrar");
        jButton1.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){				
			button1Performed(e);
				
			}
		});
		
        contentPane.add(jPanel1, BorderLayout.CENTER);
        jPanel1.add(jLabel1, null);
        jPanel1.add(jLabel6, null);
        jPanel1.add(jTextPane1, null);
        jPanel1.add(jTextPane2, null);
        jPanel1.add(jLabel3, null);
        jPanel1.add(jLabel2, null);
        jPanel1.add(jLabel5, null);
        jPanel1.add(jLabel4, null);
        jPanel1.add(jButton1, null);
    }

    /**
     * Fecha o Frame e sai do ambiente. 
     */
    protected void processWindowEvent(WindowEvent e) {

        super.processWindowEvent(e);

        if(e.getID() == WindowEvent.WINDOW_CLOSING) {
            System.exit(0);
        }
    }

    /**
     * Fecha o Frame de Abertura Superusuário e exibe o frame que permite ao superusuário 
     * adicionar novos usuários e alterar as informaçoes de usuários já cadastrados.
     * @param e Indica em qual componente ocorreu o ato de teclar.
     */
    public void button1Performed(ActionEvent e) {
		setVisible(false);
		dispose();
		
		frameUsuario = new FrameUsuario(connection, nome, user);
		
		JFrame.setDefaultLookAndFeelDecorated( false );
		JFrameUtil.centraliza(frameUsuario);
		frameUsuario.setVisible( true );
		
		
        
        
    }
}

