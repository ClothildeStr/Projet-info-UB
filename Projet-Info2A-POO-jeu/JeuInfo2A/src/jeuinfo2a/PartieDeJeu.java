/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jeuinfo2a;

import java.util.ArrayList;

/**
 *
 * @author strainchampsclothilde
 */
public class PartieDeJeu {
    
    private ArrayList<Joueur> lstJ;// attribut lstJ de type arrayList, pour la liste de joueurs
    private Plateau plateau;// attribut pour le plateau de jeu
    
    public PartieDeJeu(){
        lstJ = new ArrayList<Joueur>();
        initJoueur(); 
        initPlateau();
        jouer();
    }
    
    public void initJoueur(){
        System.out.println("**************** Règle du jeu ! ****************"
                + "\n--> Le but est de deviner les valeurs des deux cases choisies par le joueur, grâce à deux indices."
                + "\n--> Ces indices peuvent être une somme ou le produit de ces deux cases."
                + "\n--> Une case découverte ne peut pas être sélectionée.");
        boolean c = false;// déclartion d'un boolean, on l'initialise à false
        String choix;// déclaration de la variable choix de type string
        System.out.println("**************** Qui sont les Joueurs ? ****************");// on affiche...
        do{// tant que choix c == false
            System.out.print("Voulez-vous ajouter un joueur: oui/non => ");// on affiche...
            choix = Lire.S();// l'utilisateur entre oui ou non
            switch(choix){// en fonction de son choix
                case "oui" :{// si choix == "oui"
                    System.out.print("Entrez le pseudo du joueur: ");// on affiche...
                    String ps = Lire.S();// il entre le pseudo
                    Joueur j = new Joueur(ps);// on créer un objet j de type joueur
                    lstJ.add(j);// on l'ajoute à notre liste de joueur
                    break;// on s'arrête pour ne pas éxécuter le cas suivant
                }
                case "non":{// si choix == "non"
                    if(lstJ.size() == 0){// si la liste est vide, donc aucun joueur ajouter
                        System.out.println("Pour commencer une partie il faut ajouter un joueur.");// on affiche...
                    }
                    else{
                        c = true;// on assigne true à c
                        System.out.println("\nLes joueurs sont: ");// on affiche...
                        for(int i=0; i<lstJ.size();i++){// on fait une boucle sur les joueurs
                            Joueur j = this.lstJ.get(i);// pour chaque joueur
                            System.out.println("\nJoueur n°"+(i+1)+j.toString()+"\n");// on affiche... nos joueurs
                        }
                    }
                }
            }
        }while(c == false);// si c==true on passe aux lignes suivantes
    }
    
    public void initPlateau(){
        System.out.print("**************** Niveau de jeu ! ****************"
                + "\nAvec quel niveau de jeu voulez-vous jouer ?: "
                + "\nFACILE : les valeurs des cases à devinées sont entre 0 et 9;"
                + "\nMOYEN : les valeurs des cases à devinées sont entre 0 et 19;"
                + "\nDIFFICILE : les valeurs des cases à devinées sont entre 0 et 29.");// on affiche...
        System.out.print("\nNiveau choisi: ");// on affiche...
        int c = 0;// on initialise c à 0
        String choix1 = Lire.S();// on assigne à choix1 la valeur entré
        switch(choix1){
            case "FACILE":{// si "FACILE"
                c = 9;// on assigne à c la valeur 9
                break;// on s'arrête pour ne pas éxécuter le cas suivant
            }
            case "MOYEN":{
                c = 19;// on assigne à c la valeur 19
                break;// on s'arrête pour ne pas éxécuter le cas suivant
            }
            case "DIFFICILE":{
                c = 29;// on assigne à c la valeur 29
            }
        }
        
        int nbColonne, nbLigne;// on déclare deux int 
        System.out.print("\n**************** Configuration du plateau ! ****************"
                + "\nVoulez-vous jouer avec les paramètres prédéfinie => oui/non: ");// on affiche...
        String choix2 = Lire.S();// on assigne à choix ce que l'utilsateur à entré
        if(choix2.equals("oui")){// si oui
            this.plateau = new Plateau(c);// on créer un plateau par défaut
            System.out.println("Voici votre plateau de jeu:");// on affiche...
            plateau.afficherPlateau();// on affiche le plateau avec le méthode affichePlateau()
        }
        else{// sinon
            do{// pour vérifier que le plateau à bien un nombre de case paire
                System.out.print("Combien de lignes voulez-vous: ");// on affiche...
                nbLigne = Lire.i();// on assigne à nbLigne ce que l'utilsateur à entré
                System.out.print("Combien de colonnes voulez-vous: ");
                nbColonne = Lire.i();// on assigne à nbColonne ce que l'utilsateur à entré
                this.plateau = new Plateau(nbLigne, nbColonne,c);// on créer un plateau avec les nb entrés
                if(plateau.plateauJouer() == false)
                    System.out.println("Votre plateau doit avoir un nombre de cases pairs!");
            }while(plateau.plateauJouer() == false);
            System.out.println("Voici votre plateau de jeu:");// on affiche
            plateau.afficherPlateau();// on affiche le plateau avec le méthode affichePlateau()
        }
    }

    public void jouer(){
        System.out.print("\n**************** Commençons à jouer ! ****************");
        plateau.afficherPlateau();
        Case cc1, cc2;// on déclare deux cases courantes
        Indice ind1, ind2;// on déclare deux indices courants
        
        do{// tant que les toutes les cases du plateau ne son pas découvertes, on fait:
            for(int i=0; i<lstJ.size(); i++){// pour chaque joueur i
                do{// tant que c1 est découverte
                    System.out.print("\nJoueur n°" + (i+1) + " choisissez votre première case sur le plateau: "// on affiche...
                            + "\nNuméro de ligne entre 1 et " + plateau.getNbLigne() +" : ");
                    int lig1 = Lire.i();// on assigne à Lig1 ce que l'utilsateur à entré (de type int)
                    System.out.print("Numéro de colonne entre 1 et " + plateau.getNbColonne() +" : ");// on affiche..
                    int col1 = Lire.i();;// on assigne à Col1 ce que l'utilsateur à entré (de type int)
                    cc1 = plateau.getCasePlateau(lig1, col1);// on attribut la case choisie dans le plateau à cc1  
                    if(cc1.getDecouverte() == true)// si cc1 est découverte on affiche...
                        System.out.println("Cette case est déjà découverte, veuillez en choisir une autre!");
                }while(cc1.getDecouverte() == true);// si elle n'est pas découverte on passe à la suite du prgm
                do{
                    System.out.print("\nJoueur n°" + (i+1) + " choisissez votre deuxième case sur le plateau: "
                            + "\nNuméro de ligne entre 1 et " + plateau.getNbLigne() +" : ");// on affiche.. 
                    int lig2 = Lire.i();// on assigne à Lig2 ce que l'utilsateur à entré (de type int)
                    System.out.print("Numéro de colonne entre 1 et " + plateau.getNbColonne() +" : ");// on affiche..
                    int col2 = Lire.i();;// on assigne à Col2 ce que l'utilsateur à entré (de type int)
                    cc2 = plateau.getCasePlateau(lig2, col2);// on attribut la case choisie dans le plateau à cc2  
                    if(cc2.getDecouverte() == true)// si cc2 est découverte on affiche...
                        System.out.println("Cette case est déjà découverte, veuillez en choisir une autre!");
                }while(cc2.getDecouverte() == true);// si elle n'est pas découverte on passe à la suite du prgm 
                int choix = (int)(1 + 2 * Math.random()); // on génère un nombre aléatoire entre 1 et 2
                switch(choix){// enfonction de la valeur de choix
                    case 1:{// si 1
                        ind1 = new IndiceSomme();// on créer un objet ind1 de type IndiceSomme
                        System.out.println("\nIndice première case: " + ind1.donneIndice(cc1, cc2));// on applique la méthode donneIndice à ind1, et on affiche...
                        ind2 = new IndiceMult();// on créer un objet ind2 de type IndiceMult
                        System.out.println("Indice deuxième case: " + ind2.donneIndice(cc1, cc2));// on applique la méthode donneIndice à ind2, et on affiche...
                        break;// on s'arrête pour ne pas éxécuter le cas suivant
                }
                    case 2:{// si 2
                        ind1 = new IndiceMult();// on créer un objet ind1 de type IndiceMult
                        System.out.println("\nIndice première case: " + ind1.donneIndice(cc1, cc2));// on applique la méthode donneIndice à ind1, et on affiche...
                        ind2 = new IndiceSomme();// on créer un objet ind2 de type IndiceSomme
                        System.out.println("Indice deuxième case: " + ind2.donneIndice(cc1, cc2));// on applique la méthode donneIndice à ind2, et on affiche...
                    }
                }
                lstJ.get(i).tourDeJeuJoueur(cc1, cc2);// on applique la méthode tourDeJeuJoueur au joueur i
                for(int k=0; k<lstJ.size();k++){// on fait une boucle sur les joueurs
                            Joueur j = this.lstJ.get(k);// pour un joueur k
                            System.out.println("\nJoueur n°"+(k+1)+j.toString()+"\n");// on affiche... nos joueurs
                        }
                plateau.afficherPlateau();// on affiche le plateau avec le méthode affichePlateau()
            }
        }while(plateau.getCaseDecouv() == false);
        if(lstJ.size() == 1){
            System.out.println("**************** Fin de partie ! ****************"
                                    +"\nBravo, vous avez gagné" + lstJ.toString());// on affiche...
        }
        else{
            if(lstJ.size()>1){
                int max_score = lstJ.get(0).getScore();
                for(int g=1; g<lstJ.size(); g++){
                    if(lstJ.get(g).getScore() > max_score);
                        max_score = lstJ.get(g).getScore();
                System.out.println("**************** Fin de partie ! ****************"
                                    +"\nLe gagnant est: "+lstJ.get(g).toString());// on affiche...
                }
            }
        }
    }
}
