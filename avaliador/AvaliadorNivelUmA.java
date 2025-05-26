package avaliador;
import java.io.*;

/**
 * Classe que implementa o módulo Avaliador Nível 1A. Responsável por verificar se as 
 * ligações entre os nós do grafo estão corretas.
 * @author Thais Souza Aiza
 * @version 1.0
 */
public class AvaliadorNivelUmA implements Serializable {

    /**
     * Retorna true se a ligação está correta e false se a ligação está incorreta.
     * Ligações corretas: Fonte para Centro de Serviço, Centro de Serviço para Centro de 
     * Serviço e Centro de Serviço para Sorvedouro.
     * Todas as demais ligações estão incorretas. 
     * @param origem Nó de origem do arco
     * @param destino Nó de destino do arco
     * @return Um valor <code>boolean</code>.
     */
    public boolean verifica(int origem, int destino) {

        if(((origem == 1) && (destino == 3))
                || ((origem == 1) && (destino == 1))
                || ((origem == 3) && (destino == 3))
                || ((origem == 3) && (destino == 1))
                || ((origem == 3) && (destino == 2))
                || ((origem == 2) && (destino == 1))) {
            return false;
        } else {
            return true;
        }
    }
}


