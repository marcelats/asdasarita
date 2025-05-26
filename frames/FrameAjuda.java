package frames;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollBar;
import javax.swing.JScrollPane;
import javax.swing.event.HyperlinkEvent;

/**
 * 
 * @author André Felipe Rodrigues
 * Janela que mostra um texto de ajuda
 * @version 1.0
 */
public class FrameAjuda extends JFrame {

	private JPanel jContentPane = null;
	private JPanel jPanel = null;
	private JButton jButton = null;
	private JScrollPane jScrollPane = null;
	private JEditorPane jEditorPane = null;
	/**
	 * This is the default constructor
	 */
	public FrameAjuda() {
		super();
		initialize();
	}

	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initialize() {
		this.setSize(500, 600);
		this.setResizable(true);
		this.setDefaultCloseOperation(javax.swing.JFrame.DISPOSE_ON_CLOSE);
		this.setContentPane(getJContentPane());
		this.setTitle("Ajuda");
		
		JFrameUtil.centraliza(this);
		this.setVisible(true);
	}

	/**
	 * This method initializes jContentPane
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {
			jContentPane = new JPanel();
			jContentPane.setLayout(new BorderLayout());
			jContentPane.add(getJPanel(), java.awt.BorderLayout.SOUTH);
			jContentPane.add(getJScrollPane(), java.awt.BorderLayout.CENTER);
		}
		return jContentPane;
	}

	/**
	 * This method initializes jPanel	
	 * 	
	 * @return javax.swing.JPanel	
	 */
	private JPanel getJPanel() {
		if (jPanel == null) {
			jPanel = new JPanel();
			jPanel.add(getJButton(), null);
		}
		return jPanel;
	}

	/**
	 * This method initializes jButton	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButton() {
		if (jButton == null) {
			jButton = new JButton();
			jButton.setText("Sair");
			jButton.addActionListener( new ActionListener() {
				public void actionPerformed(ActionEvent e)
				{
					setVisible(false);
					dispose();
				}
			});
		}
		return jButton;
	}

	/**
	 * This method initializes jScrollPane	
	 * 	
	 * @return javax.swing.JScrollPane	
	 */
	private JScrollPane getJScrollPane() {
		if (jScrollPane == null) {
			jScrollPane = new JScrollPane();
			jScrollPane.setViewportView(getJEditorPane());
		}
		return jScrollPane;
	}

	/**
	 * This method initializes jEditorPane	
	 * 	
	 * @return javax.swing.JEditorPane	
	 */
	private JEditorPane getJEditorPane() {
		if (jEditorPane == null) {
			jEditorPane = new JEditorPane();
			jEditorPane.setContentType("text/html");
			jEditorPane.setEditable(false);
			jEditorPane.setText("<html><title>Ajuda para cadastros de usuários</title></head><body><p align=\"center\"><b><font size=\"5\">Ajuda para cadastros de usuários</font></b></p><ul>  <li><i name=\"adicionando\"><a href=\"#Adicionando um novo usuário\">Adicionando   um novo usuário</a></i></li>  <li><i name=\"removendo\"><a href=\"#Removendo um usuário\">Removendo um usuário</a></i></li>  <li><i name=\"editando\">  <a href=\"#Editando as informações de um usuário já existente\">Editando as informações de um usuário já existente</a></i></li>  <li><i><a href=\"#Procurando por um usuário existente\">Procurando por um usuário existente</a></i></li>  <li><i><a href=\"#Primeiro acesso ao sistema\">Primeiro acesso ao sistema</a></i></li>  <li><i><a href=\"#O que significa cada campo\">O que significa cada campo?</a></i></li>  <li><i><a href=\"#Problemas\">Problemas</a></i></li></ul><hr><p><b><font size=\"4\"><a name=\"Adicionando um novousuário\">Adicionando um novo usuário</a></font></b></p><p>Para adicionar um novo usuário ao sistema clique no botão de inserir um novo usuário (Figura), em seguida, preencha as informações do cadastro. O nome é de preenchimento obrigatório e o ID do usuário é de preenchimento automático. As outras informações se não forem preenchidas, serão preenchidas automaticamente pelo sistema. Os valores padrão são: senha vazia, tipo de usuário super-usuário, tipo de modelo queueing state charts, abordagem sequencial, linguagem SMPL, tamanho de warm-up 0, tamanho do lote 0 plataforma vazia. Depois de tudo feito, basta clicar no botão salvar (Figura) e as informações serão adicionadas ao banco de dados do sistema. Caso não queira mais adicionar um novo usuário, basta clicar em Cancelar (Figura)</p><p><b><font size=\"4\"><a name=\"Removendo um usuário\">Removendo um usuário</a></font></b></p><p>Clique no botão de remover um usuário (Figura). Será mostrado uma caixa de diálogo para confirmar a operação. Se a escolha for &quot;sim&quot;, então o usuário será apagado do sistema, caso contrário, nenhuma operação será realizada.</p><p><b><font size=\"4\"><a name=\"Editando as informações de um usuário já existente\">Editando as informações de um usuário já existente</a></font></b></p><p>Clique no botão editar (Figura). Desse modo, todas as informações estarão disponíveis para a edição. Depois de realizada a alteração, basta clicar em &quot;Salvar&quot; (Figura). Caso não queira mais alterar as informações desse usuário, clique em Cancelar (Figura).</p><p><b><font size=\"4\"><a name=\"Procurando por um usuário existente\">Procurando por um usuário existente</a></font></b></p><p>Clique nas setas esquerda (Figura) ou direita (Figura) para percorrer os usuário existentes na ordem em que eles foram cadastrados no sistema (pelo ID do usuário).</p><p><b><font size=\"4\"><a name=\"Primeiro acesso ao sistema\">Primeiro acesso ao sistema</a></font></b></p><p>No primeiro acesso, como não existem usuários cadastradas ainda no sistema, a única opção de cadastros do sistema será a de adicionar um novo usuário.</p><p><b><font size=\"4\"><a name=\"O que significa cada campo\">O que significa cada campo?</a></font></b></p><p align=\"left\"><b><i>ID do usuário</i>:</b> É um código que identifica unicamente cada usuário do sistema.<br><b><i>Nome do usuário</i></b>: É esse o nome que identifica o usuário no sistema. <br><b><i>Senha</i></b>: Senha de acesso ao sistema. É necessário o nome do usuário, a senha e a senha do banco de dados MySQL<b><i> </i></b>para ter acesso ao sistema.<br><b><i>Tipo usuário</i></b>: Super-usuário é aquele que tem acesso ao cadastro de usuários no sistema, e usuário de simulação é aquele que tem acesso ao editor gráfico do ASDA para gerar programas de simulação.<br><i><b>Tipo Modelo</b></i>: Queuing state charts é o tipo de modelo desenvolvido no LASDPC na Universidade de São Paulo em São Carlos. Redes de filas é um dos tipos de modelo mais conhecidos e usados na realização de simulações.<br><b><i>Abordagem</i></b>: ...<br><b><i>Linguagem:</i></b> SMPL ara desenvolvimento de simulações criado por MacDougall e implementado na linguagem C. ParSMPL ... e Simpack ...<br><b><i>Tamanho Warm-up</i></b>: Estabele a partir de que quantidade de tempo os dados estatísticos começarão a ser coletados. É o tempo necessário para as variáveis do sistema estabilizarem, pois no início todos os servidores estão desocupados, entre outros.<br><b><i>Tamanho Lote:</i></b> ,,,<br><b><i>Plataforma:</i></b> Plataforma em que o usuário utiliza o ASDA.<br>&nbsp;</p><p align=\"left\"><b><font size=\"4\"><a name=\"Problemas\">Problemas</a></font></b></p><p align=\"left\">Sendo encontrado algum problema, contate:<a href=\"mailto:andre.fe.ro@gmail.com\">andre.fe.ro@gmail.com</a><br>ou então: <a href=\"mailto:sarita@icmc.usp.br\">sarita@icmc.usp.br</a><br>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p></body></html>");
			jEditorPane.addHyperlinkListener(new javax.swing.event.HyperlinkListener() {
				public void hyperlinkUpdate(javax.swing.event.HyperlinkEvent e) {
					if (e.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
					      try {
					        jEditorPane.setPage(e.getURL());
					      } catch(IOException ioe) {
					    	  ioe.printStackTrace();
					      }
				}
			}
			});
		}
		return jEditorPane;
	}

}  //  @jve:decl-index=0:visual-constraint="10,10"
