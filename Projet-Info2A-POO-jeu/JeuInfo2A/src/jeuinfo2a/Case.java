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
public class Case {
    
    private int valeur;// atttribut pour la valeur de la case
    private boolean decouverte;// atttribut pour savoir si la case est découverte
    
    public Case(){// constructeur par défaut
        this.valeur = (int)(0 + 9 * Math.random());// on fixe par défaut aléatoirement la valeur de la case entre 0 et 9
        this.decouverte = false;// on fixe que par défaut la case n'est pas découverte
    }
    
    public Case(int valmax){// constructeur standard
        this.valeur = (int)(0 + valmax * Math.random());// on fixe par défaut aléatoirement la valeur de la case entre 0 et et la valeur max choisie par l'utilisateur
        this.decouverte = false;// on fixe que par défaut la case n'est pas découverte
    }
    public int getValeur(){// accesseur en lecture de la valeur de la case
        return this.valeur;
    }
    public boolean getDecouverte(){// accesseur en lecture pour le boolean de si elle est découverte
        return this.decouverte;
    }
    public void setValeur(int n){// accesseur en écriture de la valeur de la case
        this.valeur = n;
    }
    public void setDecouverte(boolean n){// accesseur en écriture pour le boolean de si elle est découverte
        this.decouverte = n;
    }
    
    
    public String toString(){// méthode d'affichage de la classe case
        String s = "";// on initialise une chaine de caractère vide
        if(decouverte == false)// si la case n'est pas découverte 
            s += "#";// on ajoute à notre chaîne de caractère 
        else// sinon si la case est découverte
            s += this.valeur;// on retoune sa valeur 
        return s;// on retourne notre chaîne de carctère
    }
}
