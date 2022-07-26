/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jeuinfo2a;

/**
 *
 * @author strainchampsclothilde
 */
public class IndiceMult extends Indice {
    
    
    public IndiceMult(){// constructeur par défaut 
        super();// on appelle le constructeur par défaut de la super classe Indice

    }

    public int donneIndice(Case c1, Case c2){// méthode pour donner l'indice rendu obligatoire par la classe abstraite Indice
        int i = c1.getValeur() * c2.getValeur();// on affecte à i la valeur de l'indice donner en fonction de c1 et c2 (produit)
        setInd(i);// on modifie la valeur de notre attribut ind
        return getInd();// on affiche la valeur de notre attribut ind
    }
    
}
