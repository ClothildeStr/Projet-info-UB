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
public class Joueur {//classe représentant un joueur
    
    private String pseudo;// atttribut pour le pseudo du joueur
    private int score;// atttribut pour le score du joueur
    
    public Joueur(){// constructeur par défaut
        this.pseudo = "";// on initialise le pseudo vide
        this.score = 0;// et le score à 0
    }
    public Joueur(String ps){// constructeur standard
        this.pseudo = ps;// le pseudo est initialisé par la valeur passé en paramètre
        this.score = 0;// et le score à 0
    }
    
    public String getPseudo(){// accesseur en lecture du pseudo
        return this.pseudo;
    }
    public int getScore(){// accesseur en lecture du score
        return this.score;
    }
    public void setPseudo(String ps){// accesseur en 2criture du pseudo
        this.pseudo = ps;
    }
    public void setScore(int s){// accesseur en écriture du score
        this.score += s;
    }
    
    public void tourDeJeuJoueur(Case c1, Case c2){//méthode représentant le tour d'un joueur qui fait des hypothèses sur les cases choisies
        System.out.print("\nVeux-tu faire des hypothèses sur les valeurs des cases choisies (oui/non) :");//on lui demande sil veut faire des hypothèses
        String choix = Lire.S();// entre son choix
        if(choix.equals("oui")){// si il marque "oui" 
            System.out.print("Valeur de la première case : ");// on lui demande la valeur de la première case
            int reponse1 = Lire.i();
            System.out.print("Valeur de la seconde case : ");// on lui demande la valeur de la deuxième case
            int reponse2 = Lire.i();
            if(reponse1 == c1.getValeur() && reponse2 == c2.getValeur()){// si la réponse 1 est la même que la valeur de la case 1 à deviner et de même pour la case 2
                System.out.println("Bien jouer ! Tu as touver les bonnes valeurs !"// alors le joueur à gagné
                        + "\nPassons au prochain joueur !\n");
                this.score = this.score + c1.getValeur() + c2.getValeur();// à son score on ajoute la valeur de la case1 et de la case 2
                c1.setDecouverte(true);// on découvre la case 1
                c2.setDecouverte(true);// on découvre la case 2
            }
            else
                System.out.println("Dommage mais c'est perdu !"// si il a faux on passe au prochain joueur
                        + "\nPassons au prochain joueur !\n");
        }
        else
            System.out.println("Ok, passons au prochain joueur !\n");// si il ne voulais pas faire d'hypothèses on passe au joueur suivant
    }
    
    public String toString() {// méthode pour afficher un objet joueur
        String res= "\nJoueur " + this.pseudo + ". ";
        res+= "Score: " + this.score + ".";
        return res;
    }  
}
