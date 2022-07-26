
import java.awt.Graphics;
import java.awt.Image;
import javax.swing.JPanel;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author strainchampsclothilde
 */
public class PanneauImage extends JPanel{
    private Image img; // de type Image – c’est l’image à afficher sur le panneau
    
    public PanneauImage() // constructeur par défaut
    { super();  // appel du constructeur par défaut de la classe ancêtre ici JPanel
        this.img=null; // on initialise la valeur à null
    }
    
    public PanneauImage(Image im) // constructeur avec en paramètre l’image
    {   super(); // appel du constructeur par défaut de la classe ancêtre ici JPanel
        this.img=im; // on initialise la valeur de l’attribut img au paramètre im
    }
    
    public Image getImage () { return this.img;}
    public void setImage (Image im){ this.img=im;this.repaint();
    }  //on affecta la valeur de l’attribut au paramètre 
// appel de la repaint() qui appelle paint(g) -> redessine le panneau et son image

    @Override
    public void paint(Graphics g) // surcharge de la méthode paint (méthode présente dans la classe ancêtre dont on hérite)
{
        super.paint(g); // appel de la méthode paint de la classe JPanel
        if (img != null)
        { g.drawImage(img,0,0, this.getWidth(), this.getHeight(),this);  }       // on dessine l’image dans la totalité du panneau    
    }
}

