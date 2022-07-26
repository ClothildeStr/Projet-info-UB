/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author strainchampsclothilde
 */
public class BonAchat extends Lot{
    public BonAchat(){
        super();//appel des es méthodes de la classe parente
    }
    public BonAchat(String d,int n){
        super(d,n);//appel des es méthodes de la classe parente
    }
    // le "toString" renvoie une description de l’objet courant, sous forme d’une chaine de caractères 
     public String toString() {
        String res="";//crée une chaine de caractères 
        res+="Bon d'achat: "+this.getDescription();
        return res;//renvoie la chaine de caractères res
    }  
}
