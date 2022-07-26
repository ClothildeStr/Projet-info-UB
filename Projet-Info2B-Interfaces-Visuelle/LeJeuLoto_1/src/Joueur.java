
import java.awt.*;
import javax.swing.*;

/**
 *
 * @author strainchampsclothilde
 */
public class Joueur {
    private String pseudo;
    private Color couleur;
    private double solde;
    private ImageIcon photo;
    private LesCartes mesC;
    private boolean achatCarte;

    public Joueur() {
        this.pseudo = "";
        this.couleur=Color.gray;
        this.solde = 20;
        this.photo = new ImageIcon(getClass().getResource("/joueurDefaut.png"));
        this.mesC = new LesCartes();
        achatCarte = false;
    }
   
   public Joueur(String p) {
        this.pseudo = p;
        this.couleur=Color.gray;
        this.solde = 20;
        this.photo = new ImageIcon();
        this.mesC = new LesCartes();
        achatCarte = false;
    }
   
    public String getPseudo(){ 
        return this.pseudo;  
    }
    public Color getCouleur(){ 
        return this.couleur; 
    }
    public double getSolde(){ 
        return this.solde; 
    }
    public ImageIcon getPhoto(){ 
        return this.photo;
    }
    public LesCartes getMesCartes(){
        return this.mesC;
    }
    public boolean getAchatCarte(){
        return this.achatCarte;
    }
    public void setPseudo(String p){ 
        this.pseudo=p; 
    }
    public void setCouleur(Color c){ 
        this.couleur = c; 
    }
    public void setPhoto(ImageIcon p){ 
        this.photo = p; 
    }
    public void setSolde(double s){ 
        this.solde = s; 
    }
    
    public boolean acheter(CarteLoto c){
        if(this.solde >= c.getPrix() && mesC.getTaille() < 2){
            mesC.ajouteCarte(c);
            this.solde = this.solde - c.getPrix();
            achatCarte = true;
            return true;
        }
        else
            return false;
    }
    
    public void effaceCartes(){
        mesC = new LesCartes();
    }
    
    public String toString() {
        String res= "\nJoueur " + this.pseudo;
        res+= "\nCouleur " + this.couleur;
        res+= "\nSolde " + this.solde;
        res += "\nNb de cartes pocédé: " + this.mesC.getTaille();
        return res;
    }  
}
