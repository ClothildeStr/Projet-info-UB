/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;
import java.io.*;
import java.net.*;


/**
 *
 * @author strainchampsclothilde
 */
class Client {
   static boolean arreter=false;//boolean servant à la déconnexion du client
   static int port = 8080;

   // Le client attend comme argument l'adresse du serveur (ex. : java Client 127.0.0.1 ou localhost pour l'exécuter)
   public static void main(String[] args) throws Exception {
      Socket socket = new Socket(args[0], port);
      System.out.println("SOCKET = " + socket);
      // illustration des capacites bidirectionnelles du flux:
      //BufferReader: object servant à lire les lignes du terminal côté client
      BufferedReader sisr = new BufferedReader(
                              new InputStreamReader(socket.getInputStream()));
      //PrintWriter: object servant à envoyer une ligne de caractères
      PrintWriter sisw = new PrintWriter(new BufferedWriter(
                              new OutputStreamWriter(socket.getOutputStream())),true);
        
      GererSaisie saisie=new GererSaisie(sisw);  // création d'un thread GererSaisie, avec pour paramètre notre PrintWriter 
                                                // déclaré au dessus
      saisie.start();// départ du thread                        
      String str;

      while(arreter!=true){ // tant que le client ne veut pas ce déconnecter en tapant "END"
         str = sisr.readLine(); // notre BufferReader lit ce qui nous est envoyé de la part du serveur  
         System.out.println(str); // et nous l'affiche dans le terminal côté client
      }
                           
      System.out.println("Déconnexion réussite!");   
      //sisw.println("END") ;

      // le client ferme les flux
      sisr.close();
      sisw.close();
      socket.close();
   }
}
// classe gérant la saisie dans le terminal côté client                           
class GererSaisie extends Thread{
   // attributs
   private BufferedReader entreeClavier;
   private PrintWriter pw;
   
   //constructeur standard
   public GererSaisie(PrintWriter pw){
      entreeClavier = new BufferedReader(new InputStreamReader(System.in));
      this.pw=pw;
   }
   
   //méthode run() définissant les "actions" du thread
   public void run(){
      String str;
      try{
         do {
            str = entreeClavier.readLine();
            pw.println(str);
        } while (!str.equals("sortie"));
      }catch(IOException e){e.printStackTrace();}   
      Client.arreter=true;      
   }
}