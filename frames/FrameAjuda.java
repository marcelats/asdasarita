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
 * @author Andr    Felipe Rodrigues
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
			jEditorPane.setText("<html><title>Ajuda para cadastros de usu   rios</title></head><body><p align=\"center\"><b><font size=\"5\">Ajuda para cadastros de usu   rios</font></b></p><ul>  <li><i name=\"adicionando\"><a href=\"#Adicionando um novo usu   rio\">Adicionando   um novo usu   rio</a></i></li>  <li><i name=\"removendo\"><a href=\"#Removendo um usu   rio\">Removendo um usu   rio</a></i></li>  <li><i name=\"editando\">  <a href=\"#Editando as informa      es de um usu   rio j    existente\">Editando as informa      es de um usu   rio j    existente</a></i></li>  <li><i><a href=\"#Procurando por um usu   rio existente\">Procurando por um usu   rio existente</a></i></li>  <li><i><a href=\"#Primeiro acesso ao sistema\">Primeiro acesso ao sistema</a></i></li>  <li><i><a href=\"#O que significa cada campo\">O que significa cada campo?</a></i></li>  <li><i><a href=\"#Problemas\">Problemas</a></i></li></ul><hr><p><b><font size=\"4\"><a name=\"Adicionando um novousu   rio\">Adicionando um novo usu   rio</a></font></b></p><p>Para adicionar um novo usu   rio ao sistema clique no bot   o de inserir um novo usu   rio (Figura), em seguida, preencha as informa      es do cadastro. O nome     de preenchimento obrigat   rio e o ID do usu   rio     de preenchimento autom   tico. As outras informa      es se n   o forem preenchidas, ser   o preenchidas automaticamente pelo sistema. Os valores padr   o s   o: senha vazia, tipo de usu   rio super-usu   rio, tipo de modelo queueing state charts, abordagem sequencial, linguagem SMPL, tamanho de warm-up 0, tamanho do lote 0 plataforma vazia. Depois de tudo feito, basta clicar no bot   o salvar (Figura) e as informa      es ser   o adicionadas ao banco de dados do sistema. Caso n   o queira mais adicionar um novo usu   rio, basta clicar em Cancelar (Figura)</p><p><b><font size=\"4\"><a name=\"Removendo um usu   rio\">Removendo um usu   rio</a></font></b></p><p>Clique no bot   o de remover um usu   rio (Figura). Ser    mostrado uma caixa de di   logo para confirmar a opera      o. Se a escolha for &quot;sim&quot;, ent   o o usu   rio ser    apagado do sistema, caso contr   rio, nenhuma opera      o ser    realizada.</p><p><b><font size=\"4\"><a name=\"Editando as informa      es de um usu   rio j    existente\">Editando as informa      es de um usu   rio j    existente</a></font></b></p><p>Clique no bot   o editar (Figura). Desse modo, todas as informa      es estar   o dispon   veis para a edi      o. Depois de realizada a altera      o, basta clicar em &quot;Salvar&quot; (Figura). Caso n   o queira mais alterar as informa      es desse usu   rio, clique em Cancelar (Figura).</p><p><b><font size=\"4\"><a name=\"Procurando por um usu   rio existente\">Procurando por um usu   rio existente</a></font></b></p><p>Clique nas setas esquerda (Figura) ou direita (Figura) para percorrer os usu   rio existentes na ordem em que eles foram cadastrados no sistema (pelo ID do usu   rio).</p><p><b><font size=\"4\"><a name=\"Primeiro acesso ao sistema\">Primeiro acesso ao sistema</a></font></b></p><p>No primeiro acesso, como n   o existem usu   rios cadastradas ainda no sistema, a    nica op      o de cadastros do sistema ser    a de adicionar um novo usu   rio.</p><p><b><font size=\"4\"><a name=\"O que significa cada campo\">O que significa cada campo?</a></font></b></p><p align=\"left\"><b><i>ID do usu   rio</i>:</b>     um c   digo que identifica unicamente cada usu   rio do sistema.<br><b><i>Nome do usu   rio</i></b>:     esse o nome que identifica o usu   rio no sistema. <br><b><i>Senha</i></b>: Senha de acesso ao sistema.     necess   rio o nome do usu   rio, a senha e a senha do banco de dados MySQL<b><i> </i></b>para ter acesso ao sistema.<br><b><i>Tipo usu   rio</i></b>: Super-usu   rio     aquele que tem acesso ao cadastro de usu   rios no sistema, e usu   rio de simula      o     aquele que tem acesso ao editor gr   fico do ASDA para gerar programas de simula      o.<br><i><b>Tipo Modelo</b></i>: Queuing state charts     o tipo de modelo desenvolvido no LASDPC na Universidade de S   o Paulo em S   o Carlos. Redes de filas     um dos tipos de modelo mais conhecidos e usados na realiza      o de simula      es.<br><b><i>Abordagem</i></b>: ...<br><b><i>Linguagem:</i></b> SMPL ara desenvolvimento de simula      es criado por MacDougall e implementado na linguagem C. ParSMPL ... e Simpack ...<br><b><i>Tamanho Warm-up</i></b>: Estabele a partir de que quantidade de tempo os dados estat   sticos come   ar   o a ser coletados.     o tempo necess   rio para as vari   veis do sistema estabilizarem, pois no in   cio todos os servidores est   o desocupados, entre outros.<br><b><i>Tamanho Lote:</i></b> ,,,<br><b><i>Plataforma:</i></b> Plataforma em que o usu   rio utiliza o ASDA.<br>&nbsp;</p><p align=\"left\"><b><font size=\"4\"><a name=\"Problemas\">Problemas</a></font></b></p><p align=\"left\">Sendo encontrado algum problema, contate:<a href=\"mailto:andre.fe.ro@gmail.com\">andre.fe.ro@gmail.com</a><br>ou ent   o: <a href=\"mailto:sarita@icmc.usp.br\">sarita@icmc.usp.br</a><br>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p></body></html>");
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
