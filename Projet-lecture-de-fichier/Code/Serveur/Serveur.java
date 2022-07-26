/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Serveur;

import ClassesUtiles.Partie;
import ClassesUtiles.Joueur;
import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * 
 */
class Serveur {
  //attributs
  static int port = 8080;
  static final int maxClients = 50; //nombre de client max pouvant se connectant en même tps sur le serveur
  static int numClient = 0;// nb de client de départ
  //attribut stockant le chemin du fichier à analyser (il le distribut à tt les instances qui en on besoin)
  public static String fichier = "/Users/strainchampsclothilde/Desktop/UB/Semestre_4/Info4B/BelasselStrainchamps/Code/Donnees/fichierLiChess.pgn";
  static Traitement tables = new Traitement();//chargement des tables de données
  

  // Pour utiliser un autre port pour le serveur, l'exécuter avec la commande :
  // java Serveur 8081
  public static void main(String[] args) throws Exception {
    if (args.length != 0) {
      port = Integer.parseInt(args[0]);
    }
    try (// 1 - Ouverture du ServerSocket par le serveur
    ServerSocket s = new ServerSocket(port)) {
      System.out.println("SOCKET ECOUTE CREE => " + s);
      System.out.println("Tables chargées");// signal côté serveur pour nous indiqué que le serveur est prêt à être
                                            // utilisé et peut acceuillir un client 
      while (numClient < maxClients) {//tant que le serveur n'est pas "plein"n 50 connexion
        /*
         * 2 - Attente d'une connexion client (la méthode s.accept() est bloquante
         * tant qu'un client ne se connecte pas)
         */
        Socket soc = s.accept();
        /*
         * 3 - Pour gérer plusieurs clients simultanément, le serveur attend que les
         * clients se connectent,
         * et dédie un thread à chacun d'entre eux afin de le gérer indépendamment des
         * autres clients
         */
        ConnexionClient cc = new ConnexionClient(soc);
        System.out.println("NOUVELLE CONNEXION - SOCKET => " + soc);
        numClient++;
        cc.start();
      }
    }
  }
}

//Thread gérant les demandes du client
class ConnexionClient extends Thread {
  //attributs
  private boolean arret = false; // boolean servant à la déconnexion
  private Socket s; // connexion socket complet
  public Partie partieCourante; // sert à stocker la partie demandé par le client
  public Joueur joueurCourant; // sert à stocker le joueur demandé par le client
  private BufferedReader sisr;//BufferReader: object servant à lire les lignes du terminal côté serveur
  private PrintWriter sisw;//PrintWriter: object servant à envoyer une ligne de caractères

  public ConnexionClient(Socket s) {//constructeur standard
    this.s = s;

    /*
     * 5a - A partir du Socket connectant le serveur à un client, le serveur ouvre 2
     * flux :
     * 1) un flux entrant (InputStream) afin de recevoir ce que le client
     * envoie
     * 2) un flux sortant (PrintWriter) afin d'envoyer des messages au client
     */
    // BufferedReader permet de lire par ligne
    try {
      sisr = new BufferedReader(new InputStreamReader(s.getInputStream()));
      sisw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(s.getOutputStream())), true);
    } catch (IOException e) {
      e.printStackTrace();
    }

  }
  public String donneLigne(int numero) throws IOException{//méthode qui retourne la ligne à analyser
    BufferedReader reader = new BufferedReader(new FileReader(Serveur.fichier));
    for(int i = 0; i < numero; i++){
       reader.readLine();
      }
      
    String ligneVoulue = reader.readLine();
    return ligneVoulue;
}


  public void creerPartie(int debut) throws IOException {// méthode qui initialise l'attribut partieCourante
    String ligne;
    String site = "";
    String jBlanc = "";
    String jNoir = "";
    String resultat = "";
    String date = "";
    String heure = "";
    String ouverture = "";
    String duree = "";
    String fin = "";

    for (int i = debut-1; i <= debut + 16; ++i) {
      ligne = donneLigne(i);

      // pour récuperer le numéro de la partie
      Pattern pSite = Pattern.compile("Site " + "\\\"" + "https://lichess.org/" + "[a-zA-Z_0-9]*" + "\\\"");
      Matcher mSite = pSite.matcher(ligne);

      // pour prendre les joueurs
      Pattern pJoueurBlanc = Pattern.compile("White " + "\\\"" + ".*" + "\\\"");
      Matcher mJoueurBlanc = pJoueurBlanc.matcher(ligne);

      Pattern pJoueurNoir = Pattern.compile("Black " + "\\\"" + ".*" + "\\\"");
      Matcher mJoueurNoir = pJoueurNoir.matcher(ligne);

      // pour le résultat
      Pattern pResultat = Pattern.compile("Result " + "\\\"" + "[_0-9]*" + "-" + "[_0-9]*" + "\\\"");
      Matcher mResultat = pResultat.matcher(ligne);

      // Pour le jour de la partie
      Pattern pDate = Pattern.compile("UTCDate " + "\\\"" + "[_0-9]*" + "." + "[_0-9]*" + "." + "[_0-9]*" + "\\\"");
      Matcher mDate = pDate.matcher(ligne);

      // pour l'heure de la parite
      Pattern pHeure = Pattern.compile("UTCTime " + "\\\"" + "[_0-9]*" + ":" + "[_0-9]*" + ":" + "[_0-9]*" + "\\\"");
      Matcher mHeure = pHeure.matcher(ligne);

      // pour l'ouverture
      Pattern pOuverture = Pattern.compile("Opening " + "\\\"" + ".*" + "\\\"");
      Matcher mOuverture = pOuverture.matcher(ligne);

      // pour la durée de la partie
      Pattern pDuree = Pattern.compile("TimeControl " + "\\\"" + "[_0-9]*" + "[^\s]" + "[_0-9]*" + "\\\"");
      Matcher mDuree = pDuree.matcher(ligne);

      // pour la fin
      Pattern pFin = Pattern.compile("Termination " + "\\\"" + ".*" + "\\\"");
      Matcher mFin = pFin.matcher(ligne);

      if (mSite.find()) {
        site = mSite.group().substring(26, mSite.group().length() - 1);
      }
      if (mJoueurBlanc.find()) {
        jBlanc = mJoueurBlanc.group().substring(7, mJoueurBlanc.group().length() - 1);
      }
      if (mJoueurNoir.find()) {
        jNoir = mJoueurNoir.group().substring(7, mJoueurNoir.group().length() - 1);
      }
      if (mResultat.find()) {
        resultat = mResultat.group().substring(8, mResultat.group().length() - 1);
      }
      if (mDate.find()) {
        date = mDate.group().substring(9, mDate.group().length() - 1);
      }
      if (mHeure.find()) {
        heure = mHeure.group().substring(9, mHeure.group().length() - 1);
      }

      if (mOuverture.find()) {
        ouverture = mOuverture.group().substring(9, mOuverture.group().length() - 1);
      }
      if (mDuree.find()) {

        duree = mDuree.group().substring(13, mDuree.group().length() - 1);
      }
      if (mFin.find()) {
        fin = mFin.group().substring(13, mFin.group().length() - 1);
      }
    }
    partieCourante = new Partie(site, jBlanc, jNoir, resultat, date, heure, duree, ouverture, fin);
  }

  public void creerJoueur(String joueur) throws IOException{//méthode qui permet d'initialiser l'attribut joueurCourant
    String ligne;
    String site = "";
    ArrayList<String> listeParties = new ArrayList<String>();

    for (int i = 0; i < Serveur.tables.joueurs.get(joueur).size() ; ++i) {
      ligne = donneLigne(Serveur.tables.joueurs.get(joueur).get(i));

      // pour récuperer le numéro de la partie
      Pattern pSite = Pattern.compile("Site " + "\\\"" + "https://lichess.org/" + "[a-zA-Z_0-9]*" + "\\\"");
      Matcher mSite = pSite.matcher(ligne);

      if (mSite.find()) {
        site = mSite.group().substring(26, mSite.group().length() - 1);
        listeParties.add(site);
      }  
    }
    System.out.println("fin");
    joueurCourant = new Joueur(joueur,listeParties);
  }

  

  public void run() {
    try {
      sisw.println("\nCommande de Recherche: "
                    +"\nsotie: pour ce déconnecter du serveur."
                    +"\npartie: pour visuliser une partie précise."
                    +"\njoueur: pour visualiser les parties auxquelles le joueur à participé."
                    +"\nouverture: pour visualiser le nombre de fois qu'une ouverture à été jouée."
                    +"\nouverture la plus jouée: pour visualiser l'ouverture la plus jouée."
                    +"\njoueur le plus actif: pour visualiser le joueur qui à jouer le plus de partie"+"\n");
      while (!arret) {
        /*
         * 6 - Le serveur attend que le client envoie des messages avec le PrintWriter
         * côté client
         * que le serveur recevra grâce à son BufferedReader (la méthode
         * sisr.readObject() est bloquante)
         */

        String message = sisr.readLine();
        switch (message) {
          case "sortie" :{
            arret = true;
            break;
          }
          case "partie": {
              sisw.println("entrer un numéro de partie:");
              String numPartie = sisr.readLine();
              if (Serveur.tables.parties.containsKey(numPartie)) {
                creerPartie(Serveur.tables.parties.get(numPartie));//rempli l'attribut partieCourante de mon thread
                sisw.println(partieCourante.toString());
              } else {
                sisw.println("Cette partie n'est pas dans le fichier."+"\n");
              }
            break;
          }
          case "joueur":{
            sisw.println("entrer le nom d'un joueur:");
            String nomJoueur = sisr.readLine();
            if (Serveur.tables.joueurs.containsKey(nomJoueur)) {
              creerJoueur(nomJoueur);
              sisw.println(joueurCourant.toString());
              //sisw.println(joueurCourant.toString());

            }else {
              sisw.println("Ce joueur n'est pas dans le fichier."+"\n");
            }
            break;
          }
          case "ouverture":{
            sisw.println("entrez une ouverture:");
            String nomOuverture = sisr.readLine();
            if (Serveur.tables.ouvertures.containsKey(nomOuverture)){
              sisw.println("Ouverture jouée "+Serveur.tables.ouvertures.get(nomOuverture)+ " fois.");
            }
            else{
              sisw.println("Cette ouverture n'est pas dans le fichier."+"\n");
            }
            break;
          }
          case "ouverture la plus jouée":{
            sisw.println(Serveur.tables.plusOuvertures.toString()+" est l'ouverture la plus jouée."+"\n");
            break;
          }
          case "joueur le plus actif":{
            sisw.println(Serveur.tables.plusJoueurs.toString()+" est le joueur le plus actif."+"\n");
            break;
          }
        }
      }

      // 10a - Le serveur ferme ses flux

      sisw.close();
      sisr.close();
      s.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
