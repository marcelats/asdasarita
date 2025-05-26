package frames;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import asda.UsuarioCadastro;

import java.sql.*;


/**
 * Classe que exibe uma mensagem de saudação ao usuário de simulação.  
 * @author Thais Souza Aiza
 * @author André Felipe Rodrigues - passagem do Cadastro de usuário para a próxima janela
 * @version 1.0
 */
public class FrameAberturaUsuarioSimulacao extends JFrame {

    private JPanel         contentPane;
    private JPanel         jPanel1       = new JPanel();
    private JLabel         jLabel1       = new JLabel();
    private JLabel         jLabel2       = new JLabel();
    private JLabel         jLabel3       = new JLabel();
    private JTextPane      jTextPane1    = new JTextPane();
    private JLabel         jLabel4       = new JLabel();
    private JLabel         jLabel5       = new JLabel();
    private JLabel         jLabel6       = new JLabel();
    private Icon           logo          = new ImageIcon("imagens/logo_lasdpc.jpg");
    private BorderLayout   borderLayout1 = new BorderLayout();
    private JButton        jButton1      = new JButton();
    private JLabel         jLabel7       = new JLabel();
    private JLabel         jLabel8       = new JLabel();
    
    private Janela menuPrincipal;
    
    /**
     * Armazena as informações do usuário
     */
    private UsuarioCadastro userInfo;

    /**
     * Construtor do frame.
     */
    public FrameAberturaUsuarioSimulacao() {}

    /**
     * Construtor do frame.
     * @param con Conexão com o banco de dados asda - MySQL.
     * @param nome Nome do usuário do ambiente.
     */
    public FrameAberturaUsuarioSimulacao(UsuarioCadastro user) {
    	
    	userInfo = user;

        enableEvents(AWTEvent.WINDOW_EVENT_MASK);

        try {
            jbInit();
            jLabel3.setText("Seja bem-vindo ao ASDA, " + userInfo.getNome() + "!");
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Inicializa os componentes do frame.
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
        this.setTitle("Bem-vindo Usuário de Simulação");
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
            "Voce tem permissao para desenvoler novos programas de simulação, "
            + "bem como utiizar programas já desenvolvidos e replicá-los.");
        jTextPane1.setBounds(new Rectangle(136, 90, 259, 71));
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
        jButton1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
					okPerformed(e);
			}
		});
        contentPane.add(jPanel1, BorderLayout.CENTER);
        jPanel1.add(jLabel1, null);
        jPanel1.add(jLabel6, null);
        jPanel1.add(jTextPane1, null);
        jPanel1.add(jLabel3, null);
        jPanel1.add(jLabel2, null);
        jPanel1.add(jLabel5, null);
        jPanel1.add(jLabel4, null);
        jPanel1.add(jButton1, null);
        jPanel1.add(jLabel7, null);
        jPanel1.add(jLabel8, null);
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
     * Exibe o frame para a especificação do modelo.
     * @param e Indica em qual componente ocorreu o ato de teclar.
     */
    public void okPerformed(ActionEvent e) {

        JFrame.setDefaultLookAndFeelDecorated(false);

        if (userInfo.getTipoModelo().equals("Q"))
        {
        	menuPrincipal = new JanelaQueuingStateCharts(userInfo);
        }
        else if (userInfo.getTipoModelo().equals("R"))
        {
        	menuPrincipal = new JanelaRedes(userInfo);
        }
        menuPrincipal.setVisible(true);
        
        setVisible(false);
        dispose();
        
    }
}

