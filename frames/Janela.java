
package frames;
import java.awt.BorderLayout;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRootPane;
import javax.swing.JScrollPane;
import javax.swing.JToggleButton;
import javax.swing.JToolBar;
import javax.swing.KeyStroke;
import javax.swing.WindowConstants;

import asda.BrowseFileFilter;
import asda.UsuarioCadastro;
import avaliador.AvaliadorNivelUmB;
import gerador.Gerador;
import gerador.GeradorParSMPL;
import gerador.GeradorSIMPACK;
import gerador.GeradorSIMPACK2;
import gerador.GeradorSMPL;
import gerador.GeradorSMPLX;
import graph.Graph;
import graph.Node;
import graph.ProcessoLogicoParSMPL;


/**
 * 
 * @author André Felipe Rodrigues - correção de diversos erros
 * 						e adição de diversas funcionalidades
 * @author Thais Souza Aiza (concepção inicial)
 */

public class Janela extends JFrame implements ActionListener{
	
	Desenho d = null;
	
	String filename = null;
	
	private String currentDir; // diretório corrente da aplicação
	

	
	JFileChooser chooser;
	JToggleButton[] b;
	JToggleButton[] button;
	ImageIcon selecionado = null;
	int tipoNo = 0;
	
	FramePLogico fpLogico;
	/*
	 * 
	 */
	
	private JButton buttonNovo;
	private JButton buttonAbrir;
	private JButton buttonSalvar;
	private JButton buttonSalvarComo;
	private JMenuItem menuItemSalvar;
	private JMenuItem menuParametrizar;
	private JMenuItem menuParametrizarModelo;
	
	
	ParametrizaCS frame2;
	ParametrizaFonte frame3;
	FrameVisualizaCodigo frame4;
		
	private boolean cursorIsHand = false;
	private boolean lockPositions = false;
	private boolean isDrawing = false;
	public boolean limpaSelecionado = false;
	
	public int indice;
	
	private AvaliadorNivelUmB avalia = new AvaliadorNivelUmB();	
	
	private JToolBar toolBar;	// barra de ferramente que tem botões novo, salvar, etc
	protected JPanel tools;		// painél que têm os botões para adicionar componentes do modelo de simulação
	
	private UsuarioCadastro userInfo;
	
	private String absPath;

	Janela() {
		this(null);
	}

	Janela(UsuarioCadastro user){
		
	    
		userInfo = user;
		
		setCurrentDir(System.getProperty("user.dir"));
		
	//	ajustaMakeFile();
		
		d = new Desenho();
		
		// para testes TODO (APAGAR)
		if (userInfo == null)
		{
			String val = JOptionPane.showInputDialog(
					this,
					"Digite o tipo de linguagem - POSSÍVEIS:\n" +
					"SMPL SMPLX ParSMPL SIMPACK SIMPACK2",
					"Escolha de Linguagem",
					JOptionPane.INFORMATION_MESSAGE);
			/*int val = JOptionPane.showConfirmDialog(
				null,
				"Para testes ::: " +
				"YES = ParSMPL || NO = SMPL",
				"ParSMPL ou SMPL?",
				JOptionPane.YES_NO_CANCEL_OPTION);
				*/

			if (val!=null)
			{
				userInfo = new UsuarioCadastro();
				userInfo.setId(1);	
				userInfo.setLinguagem(val);
			/*
			if (val == JOptionPane.YES_OPTION)
			{
				userInfo.setLinguagem("ParSMPL");
			}
			else if (val == JOptionPane.NO_OPTION)
			{
				userInfo.setLinguagem("SMPL");
			}
			else if (val == JOptionPane.CANCEL_OPTION)
			{
				userInfo.setLinguagem("SMPLX");
			}
			*/
			}
			else
				System.exit(0);
			
		}
		/*****/
		

		
		absPath = null;
		
		
		
		JMenuBar menuBar;
		JMenu menu;
		JMenuItem menuItem;
		
		
		//Cria a barra de menu.
		menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		//Constroi o primeiro menu.
		menu = new JMenu("Arquivo");
		menu.setMnemonic(KeyEvent.VK_F);
		menuBar.add(menu);
		
		//Adiciona os items do Menu Arquivo
		
		menuItem = new JMenuItem("Novo", KeyEvent.VK_N);		
		menu.add(menuItem);
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				novoModelo(e);
			}
		});
		
		
		
		menuItem = new JMenuItem("Abrir", KeyEvent.VK_O);
		menuItem.setAccelerator(KeyStroke.getKeyStroke( KeyEvent.VK_O, ActionEvent.CTRL_MASK));
		menu.add(menuItem);
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				abrirGrafo(e);
			}
		});
		
		menuItemSalvar = new JMenuItem("Salvar", KeyEvent.VK_S);
		menuItemSalvar.setAccelerator(KeyStroke.getKeyStroke( KeyEvent.VK_S, ActionEvent.CTRL_MASK));
		menu.add(menuItemSalvar);
		menuItemSalvar.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				salvarGrafo(e);
			}
		});
		
		menuItem = new JMenuItem("Salvar Como");
		menu.add(menuItem);
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				salvarComo(e);
			}
		});
		
		menuItem = new JMenuItem("Sair", KeyEvent.VK_X);
		menuItem.setAccelerator(KeyStroke.getKeyStroke( KeyEvent.VK_X, ActionEvent.CTRL_MASK));
		menu.add(menuItem);
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
					if (d.graph.getSize() > 0)
					{
						int n = JOptionPane.showConfirmDialog(
								null,
								"Deseja salvar o modelo?",
								"ASDA",
								JOptionPane.YES_NO_CANCEL_OPTION);
						if (n == JOptionPane.YES_OPTION)
						{
							salvarGrafo(null);
							System.exit(0);
						}
						else if (n == JOptionPane.NO_OPTION)
							System.exit(0);

					}
					else
						System.exit(0);
					// YES - salva e sai do programa
					// NO - Apenas sai do programa
					// CANCEL - não faz nada		
				}
			});
			
		
		
		
		
		//Cria o menu Parametrizar
		menu = new JMenu("Parametrizar");
		
		menuParametrizarModelo = new JMenuItem("Modelo");
		menuParametrizarModelo.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				parametrizaModelo(e);
			}
		});
		
		
		menu.add(menuParametrizarModelo);

		menuParametrizar = new JMenuItem("Processos Lógicos");
	
		if ( (userInfo!=null) && (userInfo.getLinguagem().equals("ParSMPL")))
		{
			menuParametrizar.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent e){
					fpLogico = new FramePLogico(d.graph);
					JFrameUtil.centraliza(fpLogico);
					
				}
			});
			menu.add(menuParametrizar);
		}
		menuBar.add(menu);
		
		menu = new JMenu("Gerador");
		menuBar.add(menu);
		
		
		
		menuItem = new JMenuItem("Gerar", KeyEvent.VK_X);
		menu.add(menuItem);
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
		//		imprimirGraph(d.graph);
				if (avalia.verificaValoresMinimos(d.graph)) // verifica os valores mínimos para gerar um programa de simulação
				{
					Gerador gerador;
					
					if ( (userInfo != null) && (userInfo.getLinguagem().equals("SMPL")))
					{
						gerador = new GeradorSMPL(d.graph);
						gerador.criaArquivo();
						gerador.leGabarito("gabaritos/GABARITO.DAT");
						
						filename = gerador.getFilename();
																		
						JOptionPane.showMessageDialog(
								null,
								"Código gerado com sucesso!!!",
								"ASDA",
								JOptionPane.INFORMATION_MESSAGE);
					}
					else if ( (userInfo != null) && (userInfo.getLinguagem().equals("ParSMPL")))
					{
						gerador = new GeradorParSMPL(d.graph);
						gerador.leGabarito(null); // não precisa passar gabarito, o gerador é quem controla
						
						filename = gerador.getFilename();
						JOptionPane.showMessageDialog(
									null,
									"Código gerado com sucesso!!!",
									"ASDA",
									JOptionPane.INFORMATION_MESSAGE
									);
						
					}
					else if ( (userInfo != null) && (userInfo.getLinguagem().equals("SMPLX")))
					{
						gerador = new GeradorSMPLX(d.graph);
						gerador.criaArquivo();
						gerador.leGabarito("gabaritos/GABARITO_SMPLX.DAT");
						
						filename = gerador.getFilename();
												
						JOptionPane.showMessageDialog(
								null,
								"Código gerado com sucesso!!!",
								"ASDA",
								JOptionPane.INFORMATION_MESSAGE);
					}
					else if ( (userInfo != null) && (userInfo.getLinguagem().equals("SIMPACK")))
					{
						gerador = new GeradorSIMPACK(d.graph);
						gerador.criaArquivo();
						gerador.leGabarito("gabaritos/GABARITO_SIMPACK.DAT");
						
						filename = gerador.getFilename();
												
						JOptionPane.showMessageDialog(
								null,
								"Código gerado com sucesso!!!",
								"ASDA",
								JOptionPane.INFORMATION_MESSAGE);
					}
					else if ( (userInfo != null) && (userInfo.getLinguagem().equals("SIMPACK2")))
					{
						gerador = new GeradorSIMPACK2(d.graph);
						gerador.criaArquivo();
						gerador.leGabarito("gabaritos/GABARITO_SIMPACK2.DAT");
						
						filename = gerador.getFilename();
												
						JOptionPane.showMessageDialog(
								null,
								"Código gerado com sucesso!!!",
								"ASDA",
								JOptionPane.INFORMATION_MESSAGE);
					}
					
				}
			}
		});
		
		menuItem = new JMenuItem("Gerar Executável", KeyEvent.VK_X);
		menu.add(menuItem);
		menuItem.addActionListener(new ActionListener(){	
			public void actionPerformed(ActionEvent e){
				// TODO tentar implementar gerador
				/* pode consistir de simplesmente rodar
				 * um comando no console nas pastas corretas
				 */
				
				if (d.graph == null)
					JOptionPane.showMessageDialog(
							null,
							"Modele algo e gere o código antes de executar!",
							"ASDA - erro",
							JOptionPane.ERROR_MESSAGE );
				else
				{
					
					if ( (userInfo != null) && (userInfo.getLinguagem().equals("SMPL")))
					{
						File fsrc = new File("src/" + d.graph.getNomeModelo() + ".c");
						if (!fsrc.exists())
							JOptionPane.showMessageDialog(
									null,
									"Gere o código fonte primeiro",
									"ASDA - ERRO",
									JOptionPane.ERROR_MESSAGE );
						else
						{
						    File fDest = new File("exec/smpl/modelo.c");
						    if (fDest.exists())
						    	fDest.delete();
						    copiarArquivos(fsrc,fDest);
						    
							
							String cmd = "cc -o exec/tmp/" + d.graph.getNomeModelo() + 
								" exec/smpl/modelo.c " +
								" exec/smpl/smpl.c exec/smpl/rand.c exec/smpl/bmeans.c -lm";
							try
							{
								// Aqui é executada a compilação
								// Observação: sempre compila-se também os fontes do SMPL
								// isso é bom para não dar conflitos entre códigos objetos de compiladores diferentes
							    Process p = Runtime.getRuntime().exec(cmd);			    
								p.waitFor();
						    	//  terminada a compilação
								// manda executar o programa
						    	Process p2 = Runtime.getRuntime().exec(
						    			"./exec/tmp/" + d.graph.getNomeModelo() );
						    	p2.waitFor();
						    	// mover o relatorio para a pasta de relatorios
						    	File f = new File(d.graph.getNomeModelo() + ".out");
						    	File f2 = new File("relatorio/" + d.graph.getNomeModelo() + ".out");
						    	if (f2.exists())
						    		f2.delete();
						    	
						    	if (f.exists())
						    		f.renameTo(f2 );	
						    	
						    	// agora é só visualizar o relatório
						    	JOptionPane.showMessageDialog(
						    			null,
						    			"Compilação e execução do programa com sucesso",
						    			"ASDA - Módulo Executor",
						    			JOptionPane.INFORMATION_MESSAGE
						    			);
							    
							}
							catch (IOException eio)
							{
								eio.printStackTrace();	
								JOptionPane.showMessageDialog(
										null,
										"Problemas ao gerar executável\n" +
										"certifique-se de estar no Linux e de ter um compilador C (cc)",
										"ASDA - ERRO",
										JOptionPane.ERROR_MESSAGE );
							}
							catch (InterruptedException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
						}
					}
					else if ( (userInfo != null) && (userInfo.getLinguagem().equals("SIMPACK2")))
					{
						File fsrc = new File("src/" + d.graph.getNomeModelo() + ".cpp");
						if (!fsrc.exists())
							JOptionPane.showMessageDialog(
									null,
									"Gere o código fonte primeiro",
									"ASDA - ERRO",
									JOptionPane.ERROR_MESSAGE );
						else
						{
							try
							{
								File fInclude = new File("/usr/include/strstream.h");
								if (fInclude.exists())
								{
									Process pCopy = Runtime.getRuntime().exec(
									"cp exec/simpack/strstream.h /usr/include/");
									pCopy.waitFor();
									// copia arquivo necessário para compilação
								}
							
								
								
							    File fDest = new File("exec/tmp/modelo.cpp");
							    if (fDest.exists())
							    	fDest.delete();
							    copiarArquivos(fsrc,fDest);
							    
								System.getProperty("user.dir");
								String cmd = "make -C exec/tmp/";
							
								// Aqui é executada a compilação
								// Observação: sempre compila-se também os fontes do SMPL
								// isso é bom para não dar conflitos entre códigos objetos de compiladores diferentes
							    Process p = Runtime.getRuntime().exec(cmd);			    
								p.waitFor();
						    	//  terminada a compilação
								// manda executar o programa
						/*  TODO  	Process p2 = Runtime.getRuntime().exec(
						    			"./exec/tmp/" + d.graph.getNomeModelo() );
						    	p2.waitFor();
						    	// mover o relatorio para a pasta de relatorios
						    	File f = new File(d.graph.getNomeModelo() + ".out");
						    	File f2 = new File("relatorio/" + d.graph.getNomeModelo() + ".out");
						    	if (f2.exists())
						    		f2.delete();
						    	
						    	if (f.exists())
						    		f.renameTo(f2 );	
						    	*/
						    	// agora é só visualizar o relatório
						    	JOptionPane.showMessageDialog(
						    			null,
						    			"Compilação e execução do programa com sucesso",
						    			"ASDA - Módulo Executor",
						    			JOptionPane.INFORMATION_MESSAGE
						    			);
							    
							}
							catch (IOException eio)
							{
								eio.printStackTrace();	
								JOptionPane.showMessageDialog(
										null,
										"Problemas ao gerar executável\n" +
										"certifique-se de estar no Linux e de ter um compilador C (cc)",
										"ASDA - ERRO",
										JOptionPane.ERROR_MESSAGE );
							}
							catch (InterruptedException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
						}
					}
					else if ( (userInfo != null) && (userInfo.getLinguagem().equals("ParSMPL")))
					{
							// TODO nada por enquanto						
						
					}
					else if ( (userInfo != null) && (userInfo.getLinguagem().equals("SMPLX")))
					{
						File fsrc = new File("src/" + d.graph.getNomeModelo() + ".c");
						if (!fsrc.exists())
							JOptionPane.showMessageDialog(
									null,
									"Gere o código fonte primeiro",
									"ASDA - ERRO",
									JOptionPane.ERROR_MESSAGE );
						else
						{
						    File fDest = new File("exec/smplx/modelo.c");
						    if (fDest.exists())
						    	fDest.delete();
						    copiarArquivos(fsrc,fDest);
						    
							
							String cmd = "cc -o exec/tmp/" + d.graph.getNomeModelo() + 
								" exec/smplx/modelo.c " +
								" exec/smplx/smplx.c exec/smplx/randpar.c -lm";
							try
							{
								//TODO
							    Process p = Runtime.getRuntime().exec(cmd);  
							  /*  if (p.exitValue()!=0)
							     {
									JOptionPane.showMessageDialog(
											null,
											"Problemas ao gerar executável\n" +
											"certifique-se de estar no Linux e de ter um compilador C (cc)",
											"ASDA - ERRO",
											JOptionPane.ERROR_MESSAGE );
							    } 
							    else
							    */
							    
									p.waitFor();
							    	//    	 rodar o programa
									Process p2 = Runtime.getRuntime().exec(
							    			"./exec/tmp/" + d.graph.getNomeModelo() );
									p2.waitFor();
							    	// mover o relatorio para a pasta de relatorios
							    	File f = new File(d.graph.getNomeModelo() + ".out");
							    	File f2 = new File("relatorio/" + d.graph.getNomeModelo() + ".out");
							    	if (f2.exists())
							    		f2.delete();
							    	
							    	if (f.exists())
							    		f.renameTo(f2 );
							    	JOptionPane.showMessageDialog(
							    			null,
							    			"Compilação e execução do programa com sucesso",
							    			"ASDA - Módulo Executor",
							    			JOptionPane.INFORMATION_MESSAGE
							    			);
							}
							catch (IOException eio)
							{
								eio.printStackTrace();	
								JOptionPane.showMessageDialog(
										null,
										"Problemas ao gerar executável\n" +
										"certifique-se de estar no Linux e de ter um compilador C (cc)",
										"ASDA - ERRO",
										JOptionPane.ERROR_MESSAGE );
							}
							catch (InterruptedException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
						}
					}
				}
			
							
			}
		});
		
		
		
		menuItem.setEnabled(true);
			
		
		
		menu = new JMenu("Visualizar");
		menu.setMnemonic(KeyEvent.VK_P);		
		menuBar.add(menu);
		
		menuItem = new JMenuItem("Código");	
		menu.add(menuItem);
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				
				if ((userInfo!=null) && (userInfo.getLinguagem().equals("ParSMPL")))
				{
					int incx=0,incy=0;
					for (int i=0; i < d.graph.getPLogicos().size(); i++)
					{
						filename = d.graph.getNomeModelo();
						ProcessoLogicoParSMPL temp = (ProcessoLogicoParSMPL)d.graph.getPLogicos().get(i);
						if (temp.isProcessoPai())
							filename = "src/" + filename + "_PAI_" + temp.getTid() + ".c";
						else
							filename = "src/" + filename + "_" + temp.getTid() + ".c";
						File f = new File(filename);
						if (f.exists()){
							FrameVisualizaCodigo frame4 = new FrameVisualizaCodigo(filename);
							JFrameUtil.centraliza(frame4);
							
							int posx = frame4.getX();
							int posy = frame4.getY();
							frame4.setLocation(posx + incx, posy + incy);
							frame4.setVisible(true);
							
							incx += 20;
							incy += 20;
						}
						else
						{
							JOptionPane.showMessageDialog(
									null,
									"O código ainda não foi gerado ou o código gerado não existe mais!!!\n" + 
									"Arquivo = " + filename,
									"ASDA - Erro",
									JOptionPane.ERROR_MESSAGE);	
						}
					}
				}
				else if ((userInfo!=null) && (
						(userInfo.getLinguagem().equals("SMPL")) 
						|| ( (userInfo.getLinguagem().equals("SMPLX"))) 
						|| (userInfo.getLinguagem().equals("SIMPACK")) 
						|| (userInfo.getLinguagem().equals("SIMPACK2"))
						) )
				{
					
					filename = d.graph.getNomeModelo();
					
					filename = "src/" + filename + ".c";
					File f = new File(filename);
					if (f.exists()){	
						
						
						FrameVisualizaCodigo frame4 = new FrameVisualizaCodigo(filename);
						JFrameUtil.centraliza(frame4);
						frame4.setVisible(true);
						
					}
					else{
						JOptionPane.showMessageDialog(
								null,
								"O código ainda não foi gerado ou o código gerado não existe mais!!!\n" + 
								"Arquivo = " + filename,
								"ASDA - Erro",
								JOptionPane.ERROR_MESSAGE);					
					}
				}
			}
		});
		
		menuItem = new JMenuItem("Relatório");	
		menu.add(menuItem);
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				String filename = "relatorio/" + d.graph.getNomeModelo() + ".out";
				File f = new File(filename);
				if (f.exists())
				{
					FrameVisualizaCodigo frame4 = new FrameVisualizaCodigo(filename);
					JFrameUtil.centraliza(frame4);
					frame4.setVisible(true);
				}
			}
		});
			
		
		menu = new JMenu("Ajuda");

		menuBar.add(menu);
		
		
		menuItem = new JMenuItem("Ajuda");	
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				JOptionPane.showMessageDialog(
						null,
						"Ajuda ainda não disponível",
						"Ajuda ASDA",
						JOptionPane.INFORMATION_MESSAGE
						);
			}
		});
		menu.add(menuItem);
		
		menuItem = new JMenuItem("Sobre");
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				JOptionPane.showMessageDialog(
						null,
						"ASDA - Ambiente de Simulação Distribuída Automático\n" +
						"\nConcepção do ASDA: Sarita Mazzini Bruschi" +
						"\nImplementação inicial do ambiente + Queueing Statecharts = Thais S. A." +
						"\nDiversas melhorias no ambiente + Redes de Filas + \"Distruída Automático\" do ambiente: André Felipe Rodrigues",
						"Sobre ASDA",
						JOptionPane.PLAIN_MESSAGE
						);
			}
		});
		menu.add(menuItem);
		
		//Create the toolbar.
		toolBar = new JToolBar();
		toolBar.setBorderPainted(true);
		toolBar.setAutoscrolls(true);
		addButtons(toolBar);		// chama método de adicionar botões do tipo novo, salvar, etc
		
		this.getContentPane().setLayout(new BorderLayout());
		
		tools = new JPanel();
		tools.setLayout(new BoxLayout(tools, BoxLayout.Y_AXIS));		
		
		
		
		
		
		
		
		d.addMouseListener(new MouseAdapter(){
			public void mousePressed(MouseEvent e) {
				drawMousePressed(e);
			}
			public void mouseReleased(MouseEvent e) {
				drawMouseReleased(e);
			}
			public void mouseClicked(MouseEvent e){
				drawMouseClicked(e);
			}
		});
		
		d.addMouseMotionListener(new MouseMotionListener(){
			public void mouseDragged(MouseEvent e) {
				drawMouseDragged(e);
			}
			
			public void mouseMoved(MouseEvent e) {
				drawMouseMoved(e);
			}
		});
		
		
		chooser = new JFileChooser("./models");
		// Classe que filtra os arquivos vistos por extensao
		// Nota: exemplo da classe ExampleFileFilter pode ser visto em FileChooserDemo,
		// no diretorio demo/jfc directory no Java 2 SDK, Standard Edition.
		BrowseFileFilter filter = new BrowseFileFilter();
		filter.addExtension("mod");
		filter.setDescription("Modelo");
		chooser.setFileFilter(filter);
		
		JScrollPane scrollPane =
			new JScrollPane();
		scrollPane.getViewport().add(d);
		
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		this.addWindowListener(
				new WindowAdapter()
				{
					public void windowClosing(WindowEvent e)
					{
						if (d.graph.getSize() > 0)
						{
//							 YES - salva e sai do programa
							// NO - Apenas sai do programa
							// CANCEL - não faz nada
							int n = JOptionPane.showConfirmDialog(
									null,
									"Deseja salvar o modelo?",
									"ASDA",
									JOptionPane.YES_NO_CANCEL_OPTION);
							if (n == JOptionPane.YES_OPTION)
							{
								salvarGrafo(null);
								System.exit(0);
							}
							else if (n == JOptionPane.NO_OPTION)
								System.exit(0);

						}
						else
							System.exit(0);
								
					}
				});
		

		
		buttonSalvar.setEnabled(false);
		menuItemSalvar.setEnabled(false);
		
		menuParametrizar.setEnabled(false);
		
		if (userInfo.getLinguagem().equals("ParSMPL"))
		{
			menuParametrizar.setEnabled(true);
		}
		
		
		//	scrollPane.setBounds(2,1,500,200);	
		
		this.getContentPane().add(scrollPane,BorderLayout.CENTER);		
		this.getContentPane().add(toolBar, BorderLayout.NORTH);
		
		
		
		/* quem herda precisa setar as configurações comentadas a seguir no construtor */
		
//		Adiciona barras de rolagem
		
		
		
		/*	
		 
		 this.getContentPane().add(scrollPane);
		 
		 this.pack();
		 
		 this.setSize(650,550);
		 
		 this.setTitle("ASDA - Ambiente de Simulação Distribuída Automático");
		 JFrameUtil.centraliza(this);
		 this.setVisible(true);
		 this.setDefaultCloseOperation(EXIT_ON_CLOSE);*/
		
	}
	/********************************** - FIM DO CONSTRUTOR PRINCIPAL ***********************/
	
	private void copiarArquivos(File f1, File f2)
	{

		try {
			String temp;
				BufferedReader ori = new BufferedReader(new FileReader(f1));
				FileWriter dest = new FileWriter(f2,true);
				while ((temp = ori.readLine()) != null)
				{
					temp = temp + "\n";
					dest.write(temp);
				}
				ori.close();
				dest.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		

		
	}

	
/*	private void ajustaMakeFile()
	{


			try {
				RandomAccessFile file = new RandomAccessFile(new File(getCurrentDir()+"/TMP/ASIA1.MAK"),"rw");
				file.seek(257);
				file.writeUTF("INCLUDE = " + getCurrentDir()+"\\TMP\n" );
				file.writeUTF("LIB = " + getCurrentDir() + "\\TMP");
				file.close();
			} catch (FileNotFoundException e) {
				
				e.printStackTrace();
			} catch (IOException e) {
				
				e.printStackTrace();
			}
			
			

	}
	*/
	

	/* PASSAR ESSE MÉTODO PARA O TOSTRING DA CLASSE GRAPH :-( */
	public void imprimirGraph(Graph graph)
	{
		for (int i = 0 ; i < graph.getSize() ; i++)
		{
			System.out.println("Nó = " + graph.getNode(i).getNomeCentroServico() + " ID do nó = " + graph.getNode(i).getIdNo());
			for (int j = 0; j < graph.getNode(i).getSize(); j++)
			{
				System.out.println("   Ligações = " + graph.getNode(i).getArc(j).getNodeB().getNomeCentroServico());
				
			}
		}
	}
	
	protected JRootPane createRootPane() {
		
		KeyStroke stroke = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0);
		JRootPane rootPane = new JRootPane();
		rootPane.registerKeyboardAction(this, stroke, JComponent.WHEN_IN_FOCUSED_WINDOW);
		return rootPane;
		
	}
	
	/**
	 * Método que limpa a janela para a criação de um novo modelo.
	 * @param e
	 */
	public void novoModelo(ActionEvent e){
		
		if (d.graph.getSize() > 0){
			int n = JOptionPane.showConfirmDialog(
					null,
					"Deseja salvar o modelo?",
					"ASDA",
					JOptionPane.YES_NO_OPTION);
			if (n == JOptionPane.YES_OPTION) {
				salvarGrafo(e);
				if (d.isSave){
					absPath = null;
					filename = null;
					d.limpa();	
					this.setTitle("ASDA - Ambiente de Simulação Distribuída Automático");			
				}
			} else if (n == JOptionPane.NO_OPTION) {
				d.limpa();
				absPath = null;
				filename = null;
				buttonSalvar.setEnabled(false);
				menuItemSalvar.setEnabled(false);
				this.setTitle("ASDA - Ambiente de Simulação Distribuída Automático");
			}
		}
	}
	
	public void abrirGrafo(ActionEvent e){
		chooser.setApproveButtonText("Abrir");
		chooser.setDialogTitle("Abrir");
		String oldPath;
		int returnVal = chooser.showOpenDialog(this);
		
		// Apos o usuario escolher o arquivo
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			if (absPath != null)
				oldPath = new String(absPath);
			else
				oldPath = null;
			absPath = chooser.getSelectedFile().getAbsolutePath();
			try
			{
				d.open(absPath,userInfo);
				this.setTitle("ASDA - "+ d.graph.getNomeModelo().toUpperCase());
				buttonSalvar.setEnabled(false);
				menuItemSalvar.setEnabled(false);
			}
			catch (Exception ex){
				absPath = oldPath;				
			}
		}
	}
	
	public void salvarGrafo(ActionEvent e){
		if (absPath == null){
			salvarComo(e);
		}
		else  // o arquivo já foi salvo
		{
			d.save(absPath ,d.graph.getNomeModelo(), userInfo);
			d.isSave = true;
			buttonSalvar.setEnabled(false);
			menuItemSalvar.setEnabled(false);
			this.setTitle("ASDA - "+ d.graph.getNomeModelo());
		}		
		
	}
	
	
	public void salvarComo(ActionEvent e){
		
		if (d.graph.getSize() != 0){			
			chooser.setApproveButtonText("Salvar");
			chooser.setDialogTitle("Salvar");
			int returnVal = chooser.showSaveDialog(this);
		
			// Apos o usuario escolher o arquivo
			if(returnVal == JFileChooser.APPROVE_OPTION) {					
				String nomeArquivo = chooser.getSelectedFile().getName();					
				nomeArquivo = nomeArquivo.replaceAll(".mod","").toUpperCase();
				absPath = chooser.getSelectedFile().getAbsolutePath();
				d.save(absPath ,nomeArquivo, userInfo);	
				d.isSave = true;
				buttonSalvar.setEnabled(false);
				menuItemSalvar.setEnabled(false);
				this.setTitle("ASDA - "+nomeArquivo);
			
			}
		}
		else{	
			JOptionPane.showMessageDialog(
					null,
					"Não é possível salvar o modelo!!!",
					"ASDA - Erro",
					JOptionPane.ERROR_MESSAGE);			
		}
	}
	
	public void parametrizaModelo(ActionEvent e){
		/*
		 * Verificar a validade do modelo
		 */
		if (avalia.verificaValidadeDoModelo(d.graph)){
			
			avalia.verificaTipoModelo(d.graph); // adiciona em graph o tipo do modelo nessa chamada (bad :-( )
			
			FModelo fModelo = new FModelo(d.graph);
			
			JFrame.setDefaultLookAndFeelDecorated(false);			
			JFrameUtil.centraliza(fModelo);			
			fModelo.setVisible(true);
			buttonSalvar.setEnabled(true);
			menuItemSalvar.setEnabled(true);
		}
	}
	
	
	public void actionPerformed(ActionEvent actionEvent) {
		this.release();
	}
	
	public void arcoPerformed(ActionEvent e){
		this.lockPositions = true;
		Cursor c = new Cursor(Cursor.CROSSHAIR_CURSOR);
		this.setCursor(c);
	}
	
	public void drawMouseDragged(MouseEvent e){
		if ((selecionado==null)&&(d.isDragabble(e.getX(),e.getY()))&&(!lockPositions)){
			Cursor c = new Cursor(Cursor.MOVE_CURSOR);
			this.setCursor(c);
			d.mover(e.getX(),e.getY());
			buttonSalvar.setEnabled(true);
			menuItemSalvar.setEnabled(true);
		}
	}
	
	public void drawMouseClicked(MouseEvent e){
		int aux;
		
		if ((selecionado==null)&&(d.isDragabble(e.getX(),e.getY()))&&(!lockPositions)){			
			aux = e.getClickCount();
			buttonSalvar.setEnabled(true);
			menuItemSalvar.setEnabled(true);
			
			if ((aux==1)&&(limpaSelecionado)){
				indice = d.graph.getNodeIndex(e.getX(),e.getY());
				d.graph.remove(indice);			
				this.release();
				limpaSelecionado = false;				
			}
			if (aux==2){						// Tratamento do clique duplo
				
				indice = d.graph.getNodeIndex(e.getX(),e.getY());
				Node node = d.graph.getNode(indice);
			
				if (node.getTipoNo()==2) {
					
					ParametrizaCS frame2 = new ParametrizaCS(d.graph,node,indice,node.getTipoNo(), userInfo);
					
					ImageIcon imagem = new ImageIcon("imgIcones/R1xi.gif"); // meio PIG-CODE - única maneira que encontrei
					String aux2 = imagem.toString();
					if (node.getImage().toString().equals(aux2))
						frame2.numServidores.setEditable(true);
					
					
					JFrameUtil.centraliza(frame2);
				
					frame2.setVisible(true);
				}
			
			}	
		}		
	}
	
	public void drawMouseReleased(MouseEvent e){
		
		this.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
		d.setDraggingFalse();
	}
	
	public void drawMouseMoved(MouseEvent e){
		if ((selecionado==null)&&(!lockPositions)){
			if(d.isDragabble(e.getX(),e.getY())){
				this.cursorIsHand = true;
				Cursor c = new Cursor(Cursor.HAND_CURSOR);
				int indice = d.graph.getNodeIndex(e.getX(),e.getY()); // obtendo nó para tooltiptext
				Node temp = d.graph.getNode(indice);
				d.setToolTipText("<html><p><b>Nome do nó:</b> " + temp.getNomeCentroServico() + "</p>"
						+ "<p><b>Média de serviço:</b> " + temp.getMedia() + "</p>"
						+ "<p><b>Estatísticas: </b>" + "</p>"
						+ "<p>  Fila vazia =" + temp.getEstatisticaFilaVazia() + "</p>"
						+ "<p>  Comprimento Máx/Min: " + temp.getComprimentoMaxMin() + "</p></html>"						
						);
				
						
					
				
				this.setCursor(c);
			}
			else if (this.cursorIsHand) 
			{
				this.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
				d.setToolTipText(null);
			}
		}
		if(isDrawing){
			d.drawLine(e.getX(),e.getY());
		}
	}
	
	void drawMousePressed(MouseEvent e) {
		if(selecionado!=null){
			d.add(selecionado,e.getX(), e.getY(), tipoNo);
			buttonSalvar.setEnabled(true);
			menuItemSalvar.setEnabled(true);
			this.release();
		}
		else if(lockPositions&&!isDrawing){
			if (d.isDragabble(e.getX(),e.getY())){
				this.isDrawing = true;
				d.setLineOrigin(e.getX(), e.getY());
				buttonSalvar.setEnabled(true);
				menuItemSalvar.setEnabled(true);
				return;
			}
			else release();
		}
		if(isDrawing){
			if (d.isDragabble(e.getX(),e.getY())){
				d.fixLine(e.getX(),e.getY());
				this.isDrawing = false;
				this.lockPositions = false;
				this.release();
				buttonSalvar.setEnabled(true);
				menuItemSalvar.setEnabled(true);
			}
		}
	}
	
	void release(){
		
		this.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
		for(int i=0;i<button.length;i++) button[i].setSelected(false);
		
		this.selecionado = null;
		this.lockPositions = false;
		this.isDrawing = false;
		this.tipoNo = 0;
		d.setDrawingFalse();
		d.repaint();
		
	}
	
	
	
	protected void addButtons(JToolBar toolBar) {
		
				
		Icon novo = new ImageIcon("imagens/New24.gif");
		buttonNovo = new JButton(novo);
		buttonNovo.setToolTipText("Novo");
		buttonNovo.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				novoModelo(e);
			}
		});
		
		toolBar.add(Box.createRigidArea(new Dimension(2,2)));
		toolBar.add(buttonNovo);
		
		Icon abrir = new ImageIcon("imagens/Open24.gif");
		buttonAbrir = new JButton(abrir);
		buttonAbrir.setToolTipText("Abrir");
		buttonAbrir.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				abrirGrafo(e);
			}
		});
		
		toolBar.add(Box.createRigidArea(new Dimension(2,2)));
		toolBar.add(buttonAbrir);
		
		Icon salvar = new ImageIcon("imagens/Save24.gif");
		buttonSalvar = new JButton(salvar);
		buttonSalvar.setToolTipText("Salvar");
		buttonSalvar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				salvarGrafo(e);
			}
		});
		
		toolBar.add(Box.createRigidArea(new Dimension(2,2)));
		toolBar.add(buttonSalvar);
		
		Icon salvarComo = new ImageIcon("imagens/SaveAs24.gif");
		buttonSalvarComo = new JButton(salvarComo);
		buttonSalvarComo.setToolTipText("Salvar como...");
		buttonSalvarComo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				salvarComo(e);
			}
		});
		
		toolBar.add(Box.createRigidArea(new Dimension(2,2)));
		toolBar.add(buttonSalvarComo);
		
		
		Icon modelo = new ImageIcon("imagens/Down24.gif");
		JButton buttonModelo = new JButton(modelo);
		buttonModelo.setToolTipText("Parametrizar o Modelo");
		buttonModelo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				parametrizaModelo(e);
			}
		});
		
		
		toolBar.add(Box.createRigidArea(new Dimension(20,20)));
		toolBar.add(buttonModelo);
	}
	

	
	public UsuarioCadastro getUserInfo() {
		return userInfo;
	}

	public void setUserInfo(UsuarioCadastro userInfo) {
		this.userInfo = userInfo;
	}
	


	public static void main(String args[]){ // para testes
		Janela j = new Janela();
	}

	public void setCurrentDir(String currentDir) {
		this.currentDir = currentDir;
	}

	public String getCurrentDir() {
		return currentDir;
	}
	
}
