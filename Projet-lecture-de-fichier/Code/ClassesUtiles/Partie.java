/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ClassesUtiles;
import java.io.*;
/**
 *
 * @author strainchampsclothilde
 */
public class Partie{
    //attributs de la classe
    private final String site;
    private final String jBlanc;
    private final String jNoir;
    private final String resultat;
    private final String date;
    private final String heure;
    private final String duree;
    private final String ouverture;
    private final String fin;
    
    //constructeur standard
    public Partie(String site, String jBlanc, String jNoir, String resultat, String date, 
                    String heure, String duree, String ouverture, String fin){  
        this.site = site;
        this.jBlanc = jBlanc;
        this.jNoir = jNoir;
        this.resultat = resultat;
        this.date = date;
        this.heure = heure;
        this.duree = duree;
        this.ouverture = ouverture;
        this.fin = fin;   
    }

    //méthode d'affichage de la classe
    public String toString(){
        return "\nLa Partie n°: "+site
                + "\nà commencé le "+date+" à "+heure+" et à duree "+duree+"."
                + "\nLe joueur "+jBlanc+" pour les Blancs et le joueur "+jNoir+" pour les Noirs se sont affrontés."
                + "\nLe joueur Blancs à ouvert la partie avec "+ouverture+"."
                + "\nLa partie c'est terminé par "+fin+" et le résultat est "+resultat;
    }
    
}
