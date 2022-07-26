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
public class Plateau {
    
    private int nbLigne;// attribut pour le nombre de lignes du plateau
    private int nbColonne;// attribut pour le nombre de colonnes du plateau
    private Case[][] cases;// attribut pour notre tableau de case
   
    public Plateau(int c){// constructeur par défaut
        this.nbLigne = 3;// on fixe nbLigne à 3
        this.nbColonne = 4;// on fixe nbColonne à 4
        this.cases = new Case[this.nbLigne][this.nbColonne];// on créer un tableau de case en fonction de la valeurs nos attribut
        
        for(int i=0; i<this.nbLigne; i++) {// on fait une boucle sur les lignes
             for(int j=0; j<this.nbColonne; j++) {// et les colonnes du tableau
                 cases[i][j]=new Case(c);// initialise les cases, avec le paramètre c
             }
        }
    }
    public Plateau(int n, int p, int c){
        this.nbLigne = n;// on fixe nbLigne à notre paramètre n
        this.nbColonne = p;// on fixe nbColonne à notre paramètre p
        this.cases = new Case[this.nbLigne][this.nbColonne];// on créer un tableau de case en fonction de la valeurs nos attribut
        
        for(int i=0; i<this.nbLigne; i++) {// on fait une boucle sur les lignes
             for(int j=0; j<this.nbColonne; j++) {// et les colonnes du tableau
                 cases[i][j]=new Case(c);// initialise les cases, avec le paramètre c
             }
        }
    }
    // accesseurs en lecture
    public int getNbLigne(){
        return this.nbLigne;
    }
    public int getNbColonne(){
        return this.nbColonne;
    }
    // accesseurs en écriture
    public void setNbLigne(int n){
        this.nbLigne = n;
    }
    public void setNbColonne(int n){
        this.nbColonne = n;
    }
    
    public Case getCasePlateau(int l, int c){// méthode permettant de retourner une case précise
        Case cc = new Case();// on créer une case courante cc
        for(int i=0; i<l; i++) {// on boucle sur le tableau jusqu'au nombre de la ligne l en paramètre
             for(int j=0; j<c; j++) {// on boucle sur le tableau jusqu'au nombre de la colonne c en paramètre
                 cc = this.cases[i][j];// on assigne à cc la case  
             }
        }
        return cc;// on retourne cette case
    }
    
    public boolean getCaseDecouv(){// méthode permettant de savoir si toutes les cases du pllateau sont découvertes
        boolean cd = true;// on fixe cd à true
        for(int i=0; i<nbLigne; i++) {// on boucle sur notre tableau
            for(int j=0; j<nbColonne; j++) {
                cd &= cases[i][j].getDecouverte();//si cd=true et la cases i,j = true alors notre méthode renvoie true, sinon false;
            }
        }
        return cd;
    }
    public boolean plateauJouer(){// métode pour savoir si le nombre de case est pair
        boolean res = true;
        int compt = 0;
        for(int i=0; i<nbLigne; i++) {// on boucle sur notre tableau
            for(int j=0; j<nbColonne; j++) {
                compt += 1;
            }
        }
        if(compt %2!=0)
            res = false;
        else
            res = true;
        return res;
    }
    
    public void afficherPlateau(){// méthode pour afficher le plateau de jeu (celle d'un tableau 2X2)
        System.out.println();
        for(int i=0; i<this.nbLigne; i++){
            for(int j=0; j<this.nbColonne; j++){
                System.out.print(" | " + cases[i][j]);
            }
            System.out.println(" | ");
        }
        System.out.println();
    }
}
