package asda;

import java.awt.*;
import javax.swing.*;

import frames.FrameAsda;
import frames.JFrameUtil;

import java.awt.event.*;

/**
 * Classe principal que inicializa o ASDA.
 * @author Thais Souza Aiza
 * @version 1.0
 */
public class Asda {

    boolean packFrame = false;

    /**
     * Construtor da aplicação.
     */
    public Asda() {

        FrameAsda frame = new FrameAsda();

        //Validate frames that have preset sizes
        //Pack frames that have useful preferred size info, e.g. from their layout
        if(packFrame) {
            frame.pack();
        } else {
            frame.validate();
        }

        //Center the window
        JFrameUtil.centraliza(frame);
                        
        frame.setVisible(true);
    }

    /**
     * Método principal
     * @param args
     */
    public static void main(String[] args) {

        JFrame.setDefaultLookAndFeelDecorated(false);

        FrameAsda app = new FrameAsda();

        new Asda();
        app.addWindowListener(new WindowAdapter() {

            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
    }
}


