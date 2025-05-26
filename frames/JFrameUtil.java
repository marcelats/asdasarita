package frames;


import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.FocusEvent;
import java.awt.event.KeyEvent;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextField;


public class JFrameUtil {

    public static void centraliza(JFrame frame) {

        //Centraliza a janela na tela
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        Dimension frameSize  = frame.getSize();

        if(frameSize.height > screenSize.height) {
            frameSize.height = screenSize.height;
        }

        if(frameSize.width > screenSize.width) {
            frameSize.width = screenSize.width;
        }

        frame.setLocation((screenSize.width - frameSize.width) / 2,
                          (screenSize.height - frameSize.height) / 2);
    }
    
    /**
     * Método emite um aviso sonoro se o caracter digitado é diferente de um número, a tecla
     * de back space, delete ou ponto. Remove o caracter digitado se ele não é o permitido. 
     * @param e Indica em qual componente ocorreu o ato de teclar.
     */ 
    public static void verificaDigito(KeyEvent e) {
  	  char c = e.getKeyChar();
  	  int p = 0;		
  	  if (!((Character.isDigit(c))
  		  || (c == KeyEvent.VK_BACK_SPACE)
  		  || (c == KeyEvent.VK_DELETE)
  		  || (c == KeyEvent.VK_PERIOD))) {
  		  //getToolkit().beep();			
  		  e.consume();
  	  }
    }

    /**
     * Método que verifica se o número digitado é <code>float</code>.
     * @param e Indica qual componente perdeu o foco. 
     */  
    public static void verificaNumeroReal(FocusEvent e){
  		
  	  JTextField textField = (JTextField)e.getSource();
  	  JFrame frame = null;		
  	  String content = textField.getText();
  	  
  	  if (content.length() != 0) {
  		  try {
  			  Double.parseDouble(content);			   
  		  } catch (NumberFormatException nfe) {
  			  //getToolkit().beep();
  			  JOptionPane.showMessageDialog(frame,"Número Inválido!!!",
  			  "ASDA - Erro",
  			  JOptionPane.ERROR_MESSAGE);
  			  textField.requestFocus();				
  			  textField.setText("");								
  		  }
  	  }
    }
}


/*--- Formatted in Sun Java Convention Style on Qua, Abr 28, '04 ---*/


/*------ Formatted by Jindent 3.51 Gold 1.12 Trial --- http://www.jindent.com ------*/
