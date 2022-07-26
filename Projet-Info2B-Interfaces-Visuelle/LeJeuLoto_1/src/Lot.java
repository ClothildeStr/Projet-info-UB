
import javax.swing.ImageIcon;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author strainchampsclothilde
 */
public abstract class Lot {
    private String description;
    private int niveau;
    private ImageIcon photo;
    
    public Lot(){
        description = "";
        niveau = 0;
        this.photo = new ImageIcon(getClass().getResource("/cadeau.jpg"));
    }
    public Lot(String s, int i){
        description = s;
        niveau = i;
        this.photo = new ImageIcon(getClass().getResource("/cadeau.jpg"));
    }
    // accesseurs en lecture
    public String getDescription(){
        return description;
    }
    public int getNiveau(){
        return niveau;
    }
    public ImageIcon getPhoto(){
        return photo;
    }
    // accesseurs en écriture
    public void setDescription(String s){
        description = s;
    }
    public void setNiveau(int n){
        niveau = n;
    }
    public void setPhoto(ImageIcon p){
         this.photo=p;
    }
    
    public abstract String toString(); //une méthode abstraite qu'on va remplir par la suite dans les sous-classes
}
