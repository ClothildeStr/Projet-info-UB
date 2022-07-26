/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ClassesUtiles;
import java.io.*;
import java.util.*;
/**
 *
 * @author strainchampsclothilde
 */

 // classe définissant un joueur d'échec
public class Joueur{
    //attributs
    private final String ID;//nom du joueur
    private final ArrayList<String> partiesJouees;//liste des numéros de parties que le joueur à joué
    
    //constructeur standard
    public Joueur(String ID, ArrayList<String> partiesJouees){
        this.ID = ID;
        this.partiesJouees = partiesJouees;
    }
    
    //méthode d'affichage de la classe   
    public String toString(){
        return "\nLe joueur: "+ID+" à joué dans les parties suivantes:"
                +"\n"+partiesJouees.toString();
    }
   
}
