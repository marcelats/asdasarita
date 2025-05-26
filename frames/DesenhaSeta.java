package frames;
import java.awt.*;

/**
 * Classe que desenha a seta que indica o sentido das liga    es (arcos).
 * @author Thais Souza Aiza
 * @version 1.0
 */
public class DesenhaSeta {
    
    /**
     * Altura da cabe  a da seta.
     */
    int al = 12;
    
    /**
     * Largura da cabe  a da seta.
     */
    int aw = 10;
    
    
    /**
     * Ponto onde a seta deve se encontrar com a cabe  a da seta.
     */
    int haw       = aw / 2;
    
    /**
     * Array de coordenadas x.
     */
    int xValues[] = new int[3];
    
    /**
     * Array de coordenadas y.
     */
    int yValues[] = new int[3];
    

    /**
     * Construtor da classe.
     */
    public void desenhaSeta(Graphics g, int x1, int y1, int x2, int y2) {


        g.drawLine(x1, y1, x2, y2);
        calcValues(x1, y1, x2, y2);

        g.fillPolygon(xValues, yValues, 3);
    }

    /**
     * Calcula os valores de x-y para a cabe  a da seta.
     */
    public void calcValues(int x1, int y1, int x2, int y2) {

        //Norte ou sul
        if(x1 == x2) {

            //Norte
            if(y2 < y1) {
                arrowCoords(x2, y2, x2 - haw, y2 + al, x2 + haw, y2 + al);

                //Sul
            } else {
                arrowCoords(x2, y2, x2 - haw, y2 - al, x2 + haw, y2 - al);
            }

            return;
        }

        //Leste ou Oeste
        if(y1 == y2) {

            //Leste
            if(x2 > x1) {
                arrowCoords(x2, y2, x2 - al, y2 - haw, x2 - al, y2 + haw);

                //Oeste
            } else {
                arrowCoords(x2, y2, x2 + al, y2 - haw, x2 + al, y2 + haw);
            }

            return;
        }

        //Calcula o quadrante
        calcValuesQuad(x1, y1, x2, y2);
    }

    /**
     * Calcula os valores x-y onde a dire    o n  o    paralela aos
     * eixos x ou y.
     */
    public void calcValuesQuad(int x1, int y1, int x2, int y2) {

        double arrowAng = Math.toDegrees(Math.atan((double) haw
                                                   / (double) al));
        double dist = Math.sqrt(al * al + aw);
        double lineAng = Math.toDegrees(Math.atan(((double) Math.abs(x1 - x2))
                                                  / ((double) Math.abs(y1
                                                      - y2))));

        // Adjust line angle for quadrant
        if(x1 > x2) {

            // South East
            if(y1 > y2) {
                lineAng = 180.0 - lineAng;
            }
        } else {

            // South West
            if(y1 > y2) {
                lineAng = 180.0 + lineAng;

                // North West
            } else {
                lineAng = 360.0 - lineAng;
            }
        }

        // Calculate coords
        xValues[0] = x2;
        yValues[0] = y2;

        calcCoords(1, x2, y2, dist, lineAng - arrowAng);
        calcCoords(2, x2, y2, dist, lineAng + arrowAng);
    }

    /**
     * Calcula as coordenatas: determina novas coordendas x-y dado uma coordenada x-y 
     * inicial, a dist  ncia e a dire    o.
     */
    public void calcCoords(int index, int x, int y, double dist,
                           double dirn) {

       while(dirn < 0.0) {
            dirn = 360.0 + dirn;
        }

        while(dirn > 360.0) {
            dirn = dirn - 360.0;
        }

        // Norte-Leste
        if(dirn <= 90.0) {
            xValues[index] = x + (int) (Math.sin(Math.toRadians(dirn))
                                        * dist);
            yValues[index] = y - (int) (Math.cos(Math.toRadians(dirn))
                                        * dist);

            return;
        }

        // Sul-Leste
        if(dirn <= 180.0) {
            xValues[index] = x + (int) (Math.cos(Math.toRadians(dirn - 90))
                                        * dist);
            yValues[index] = y + (int) (Math.sin(Math.toRadians(dirn - 90))
                                        * dist);

            return;
        }

        // Sul-Oeste
        if(dirn <= 90.0) {
            xValues[index] = x - (int) (Math.sin(Math.toRadians(dirn - 180))
                                        * dist);
            yValues[index] = y + (int) (Math.cos(Math.toRadians(dirn - 180))
                                        * dist);
        }

        // Norte-Oeste    
        else {
            xValues[index] = x - (int) (Math.cos(Math.toRadians(dirn - 270))
                                        * dist);
            yValues[index] = y - (int) (Math.sin(Math.toRadians(dirn - 270))
                                        * dist);
        }
    }

    /**
     * Carrega os valores x-y nos arrays.
     */ 
    public void arrowCoords(int x1, int y1, int x2, int y2, int x3, int y3) {

        xValues[0] = x1;
        yValues[0] = y1;
        xValues[1] = x2;
        yValues[1] = y2;
        xValues[2] = x3;
        yValues[2] = y3;
    }
}


