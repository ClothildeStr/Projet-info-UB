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
public abstract class Indice {// déclaration de la classe abstraite Indice
    
    private int ind;// atttribut de type int pour la valeur de l'indice
    
    public Indice(){// constructeur par défaut
        this.ind = 0;// initialisation de ind à 0

    }
    public int getInd(){// accesseur en lecture pour notre attribut ind
        return this.ind;
    }
    public void setInd(int n){// accesseur en écriture pour notre attribut ind
        this.ind = n;
    }
    public abstract int donneIndice(Case c1, Case c2);// méthode abstraite permettant de donner un indice pour les cases c1 et c2
}
